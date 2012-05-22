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
 * \file Property.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * File declaring the Property template class.
 */
#ifndef DPTCPP_CONFIG_PROPERTYPROXY_H
#define DPTCPP_CONFIG_PROPERTYPROXY_H

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/function.hpp>
#include <glibmm.h>

#include "PropertyCore.h"
#include "PropertyWeak-fwd.h"
#include "PropertyInterface.h"

namespace denprot {
	namespace config {

/**
 * \brief Property template class capable of representing a property of an arbitary type.
 */
template<typename T>
class Property : public denprot::config::PropertyInterface {
	public:
		friend class PropertyWeak<T>;
		/**
		 * Helper to refer to a non-copyable PropertyCore object using shared pointers. This is used mainly internally.
		 */
		typedef boost::shared_ptr<PropertyCore<T>> PropertyCoreDyn;
	private:
	
		/**
		 * \internal
		 * \brief The non-copyable core of this Property.
		 *
		 * The core is responsible for storing the value itself
		 */
		PropertyCoreDyn prop;
		
		unsigned* refCnt;
		
		boost::mutex* mut;
		
		Property(PropertyCoreDyn prop, unsigned* refCnt, boost::mutex* mut) {
			mut->lock();
			this->mut = mut;
			this->prop = prop;
			this->refCnt = refCnt;
			++(*refCnt);
			mut->unlock();
		}
	public:
		
		/**
		 * \brief Experimental empty constructor
		 */
		Property() :
			prop(new PropertyCore<T>()), refCnt(new unsigned(1)), mut(new boost::mutex()) {
		}
	
		/**
		 * \brief Constructs a new property with a given name and value.
		 * \param [in] name The name of the property
		 * \param [in] value The value of the property
		 */
		Property(const Glib::ustring& name, const T& value) :
			prop(new PropertyCore<T>(name, value)), refCnt(new unsigned(1)), mut(new boost::mutex()) {
		}
		
		/**
		 * \brief Copy-constructor for a property.
		 * 
		 * Copying a Property will cause the new instance to refer to the same PropertyCore, meaning that they share
		 * the property. One cannot make a real deep copy of a property because it would not make sense to copy the
		 * functions connected to the changed signal. (You write code which copies by value, of course)
		 * \param [in] p The property which should be copied
		 */
		Property(const Property& p) {
			p.mut->lock();
			prop = p.prop;
			mut = p.mut;
			refCnt = p.refCnt;
			++(*refCnt);
			p.mut->unlock();
		}
		
		~Property() {
			mut->lock();
			--(*refCnt);
			if(*refCnt == 0) {
				delete refCnt;
				mut->unlock();
				delete mut;
			} else
				mut->unlock();
		}
		
		/**
		 * Changes the value of this Property to the value on the right side of operator=.
		 * \param [in] val The new value of the Property.
		 * \return A reference to this Property.
		 */
		Property& operator=(const T& val) {
			*prop = val;
			return *this;
		}
		
		/**
		 * Changes the value of this Property to the value of the one on the right side of operator=.
		 * \param [in] other The Property to copy the value of.
		 * \return A reference to this Property.
		 */
		Property& operator=(const Property& other) {
			*prop = *(other.prop);
			return *this;
		}
		
		/**
		 * Changes the PropertyCore to which this Property refers to, meaning that the core to which this Property
		 * may be dropped.
		 * \param [in] The Property whose core should be referenced by this Property instance.
		 * \return A reference to this Property.
		 */
		Property<T>& operator*=(const Property<T>& other) {
			// If other refers to a different PropertyCore
			if(refCnt != other.refCnt) {
				mut->lock();
				--(*refCnt);
				if(*refCnt == 0) {
					delete refCnt;
					mut->unlock();
					delete mut;
				} else
					mut->unlock();
			
				other.mut->lock();
				mut = other.mut;
				refCnt = other.refCnt;
				++(*refCnt);
				prop = other.prop;
				other.mut->unlock();
			}
			return *this;
		}
		
		/**
		 * ClassId of the value type of this Property.
		 * \return The ClassId of the Class this Property is instantiated with.
		 */
		denprot::ClassIdRep getClassId() const {
			return prop->getClassId();
		}

		/**
		 * Getter for the name of this Property.
		 * \return The name of the Property.
		 */
		const Glib::ustring& getName() const { 
			return prop->getName();
		}
		
		/**
		 * Getter for the value of the Property.
		 * \return The value of this Property.
		 */
		const T& getValue() const {
			return prop->getValue();
		}
		
		/**
		 * Setter for the value of the Property.
		 * \param [in] The new value of the Property
		 */
		void setValue(const T& nVal)  {
			prop->setValue(nVal);
		}
		
		/**
		 * Forces this Property to notify its subscribers about the change of its value.
		 */
		void forceChange() {
			prop->forceChange();
		}

		/**
		 * Connects a new subscriber to this Property. 
		 * \param [in] f The subscriber method to connect.
		 * \param [in] pos The boost::connect_position of the connection. Default is at_back. 
		 * (See boost::signals2 reference)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void()> f,
		  boost::signals2::connect_position pos = boost::signals2::at_back) {
			return prop->connect(f,pos);
		}
		
		/**
		 * Connects a new subscriber to this Property.
		 * \param [in] f The subscriber method to connect.
		 * \param [in] grp The connection group of the connection. (See boost::signals2 reference)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void()> f, int grp) {
			return prop->connect(f,grp);
		}
		
		/**
		 * Connects a new subscriber to this Property. 
		 * \param [in] f The subscriber method to connect.
		 * The connected function will run on the thread changing the property's value.
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connectLocal(boost::function<void()> f) {
			return prop->connectLocal(f);
		}
				
		/**
		 * Connects a new subscriber to this Property. The subscriber will always receive
		 * a valid reference to the Property which just changed.
		 * \param [in] f The subscriber method to connect.
		 * \param [in] pos The boost::connect_position of the connection. Default is at_back. 
		 * (See boost::signals2 reference)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void(Property<T>&)> f,
		  boost::signals2::connect_position pos = boost::signals2::at_back) {
			return prop->connect(*this,boost::function<void(Property<T>&)>(f),pos);
		}
		
		/**
		 * Connects a new subscriber to this Property. The subscriber will always receive
		 * a valid reference to the Property which just changed.
		 * \param [in] f The subscriber method to connect.
		 * \param [in] The connection group of the connection. (See boost::signals2 reference)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void(Property<T>&)> f, int grp) {
			return prop->connect(*this,boost::function<void(Property<T>&)>(f),grp);
		}

		/**
		 * Connects a new subscriber to this Property. The subscriber will always receive
		 * a valid reference to the Property which just changed.
		 * The connected function will run on the thread changing the property's value.
		 * \param [in] f The subscriber method to connect.
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connectLocal(boost::function<void(Property<T>&)> f) {
			return prop->connectLocal(*this,boost::function<void(Property<T>&)>(f));
		}
};

}
}

#endif
