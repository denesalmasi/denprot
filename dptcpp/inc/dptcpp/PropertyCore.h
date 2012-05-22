/*
 * This file is part of dptcpp.
 *
 *  dptcpp is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dptcpp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dptcpp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file PropertyCore.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * Declaration of the PropertyCore class.
 */
#ifndef DPTCPP_CONFIG_PROPERTY_H
#define DPTCPP_CONFIG_PROPERTY_H

#include <glibmm.h>
#include <boost/signals2.hpp>
#include <boost/function.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/weak_ptr.hpp>
#include <iostream>

#include "Property-fwd.h"
#include "PropertyWeak.h"
#include "AsyncWrap.h"
#include "IdentifiableClass.h"
#include "IdTypes.h"
#include "Debug.h"
#include "ClassIdClass.h"

namespace denprot {
	namespace config {
		/**
		 * \brief Represents an observable name-value pair. This class is non-copyable
		 *
		 * A pair of unicode strings, association of a name and a value.
		 * This is a simple variable concept, where other components can subscribe
		 * for changes of the value of a given property.
		 */
		template<typename T>
		class PropertyCore : denprot::IdentifiableClass {
			private:
				/**
				 * \internal
				 * The name of the PropertyCore.
				 */
				Glib::ustring name;
		
				/**
				 * \internal
				 * The value of the PropertyCore.
				 */
				T value;
		
				/**
				 * \internal
				 * The signal emitted when the property gets changed.
				 */
				boost::signals2::signal<void()> changedSignal;
		
				/**
				 * \internal
				 * The mutex protecting this property.
				 */
				mutable boost::shared_mutex mut;
			public:
				/**
				 * Copying is prohibited.
				 */
				PropertyCore(const PropertyCore<T>& p) = delete;
		
				~PropertyCore() { 
				 }
		
				/**
				 * Changes the value of this PropertyCore to the value of 
				 * the one on the right side of operator=.
				 * \param [in] other The PropertyCore to copy the value of.
				 * \return A reference to this PropertyCore.
				 */
				PropertyCore<T>& operator=(const PropertyCore<T>& other) {
					setValue(other.getValue());
					return *this;
				}
		
				/**
				 * Changes the value of this PropertyCore to the value on 
				 * the right side of operator=.
				 * \param [in] val The new value of the PropertyCore.
				 * \return A reference to this PropertyCore.
				 */
				PropertyCore<T>& operator=(const T& val) {
					setValue(val);
					return *this;
				}
		
	
				/**
				 * \brief Constructs a PropertyCore with a given name and given value.
				 * \param [in] The name of the property.
				 * \param [in] The value of the property.
				 */
				PropertyCore(const Glib::ustring& name, const T& value) :
					name(name), value(value) {
				}
				
				/**
				 * \brief Experimental empty constructor.
				 */
				PropertyCore() {
				}
		
				/**
				 * ClassId of the value type of this PropertyCore.
				 * \return The ClassId of the Class this PropertyCore is instantiated with.
				 */
				denprot::ClassIdRep getClassId() const {
					boost::shared_lock<boost::shared_mutex> lck(mut);
					return denprot::ClassId<T>::id();
				}
		
				/**
				 * Getter for the name of the property.
				 * \return The name of the property.
				 */
				const Glib::ustring& getName() const {
					return name;
				}
		
				/**
				 * Getter for the value of the property.
				 * \return The value of the property.
				 */
				const T& getValue() const {
					boost::shared_lock<boost::shared_mutex> acc(mut);
					return value;
				}
		
				/**
				 * Changes the value of the property, notifying all of its subscribers.
				 * \param [in] The new value of the PropertyCore.
				 */
				void setValue(const T& nValue) {
					{
						boost::unique_lock<boost::shared_mutex> lck(mut);
						value = nValue;
					}
					changedSignal();
				}
		
				/**
				 * Forces emission of the changed signal on the property even if
				 * the value didn't change.
				 */
				void forceChange() {
					changedSignal();
				}
		
				/**
				 * Connects a new subscriber to the changed signal of this property.
				 * The function will always receive a valid reference of the Property as a parameter.
				 * \param [in] p The Property to pass a reference of to the connected function.
				 * \param [in] func The function to connect to this PropertyCore.
				 * \param [in] pos The position of the connection. (See boost::signals2::connect_position)
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connect(Property<T>& p, boost::function<void(Property<T>&)> func,
				  boost::signals2::connect_position pos) {
					PropertyWeak<T> weak(p);
					auto wrap = [weak, func]() {
						PropertyWeak<T> w2 = weak;
						Property<T>* ptr = NULL;
						if(!w2.raise(&ptr)) {
							std::cerr << "Failed to call back changed signal event : Property does not exist anymore!" << std::endl;
						} else {
							func(*ptr);
							delete ptr;
						}
					};
					return changedSignal.connect(asyncWrap(boost::function<void()>(wrap)));
				}

				/**
				 * Connects a new subscriber to the changed signal of this property.
				 * The function will always receive a valid reference of the Property as a parameter.
				 * \param [in] p The Property to pass a reference of to the connected function.
				 * \param [in] func The function to connect to this PropertyCore.
				 * \param [in] grp The group of the connection. (See boost::signals2 reference)
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connect(Property<T>& p, boost::function<void(Property<T>&)> func, int grp) {
					PropertyWeak<T> weak(p);
					auto wrap = [weak, func]() {
						PropertyWeak<T> w2 = weak;
						Property<T>* ptr = NULL;
						if(!w2.raise(&ptr)) {
							std::cerr << "Failed to call back changed signal event : Property does not exist anymore!" << std::endl;
						} else {
							func(*ptr);
							delete ptr;
						}
					};
					return changedSignal.connect(grp,asyncWrap(boost::function<void()>(wrap)));
				}

				/**
				 * Connects a new subscriber to the changed signal of this property.
				 * The function will always receive a valid reference of the Property as a parameter.
		 		 * The connected function will run on the thread changing the property's value.	
				 * \param [in] func The function to connect to this PropertyCore.
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connectLocal(Property<T>& p, boost::function<void(Property<T>&)> func) {
					PropertyWeak<T> weak(p);
					auto wrap = [weak, func]() {
						PropertyWeak<T> w2 = weak;
						Property<T>* ptr = NULL;
						if(!w2.raise(&ptr)) {
							std::cerr << "Failed to call back changed signal event : Property does not exist anymore!" << std::endl;
						} else {
							func(*ptr);
							delete ptr;
						}
					};
					return changedSignal.connect(boost::function<void()>(wrap));
				}
				
				/**
				 * Connects a new subscriber to the changed signal of this property.
				 * \param [in] func The function to connect to this PropertyCore.
				 * \param [in] pos The position of the connection. (See boost::signals2::connect_position)
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connect(boost::function<void()> func,
				  boost::signals2::connect_position pos) {
					return changedSignal.connect(asyncWrap(func),pos);
				}

				/**
				 * Connects a new subscriber to the changed signal of this property.
				 * \param [in] func The function to connect to this PropertyCore.
				 * \param [in] grp The connection group of the connection. (See boost::signals2 reference)
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connect(boost::function<void()> func, int grp) {
					return changedSignal.connect(grp, asyncWrap(func));
				}
				
				/**
				 * Connects a new subscriber to the changed signal of this property.
		 		 * The connected function will run on the thread changing the property's value.	
				 * \param [in] func The function to connect to this PropertyCore.
				 * \return A connection that can be stored and used to check its 
				 * integrity or disconnect from the signal.
				 */
				boost::signals2::connection connectLocal(boost::function<void()> func) {
					return changedSignal.connect(func);
				}
		};
}
}

#endif
