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
 * \file PropertyReadOnly.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * File declaring the Property template class.
 */
#ifndef DPTCPP_CONFIG_PROPERTYREADONLY_H
#define DPTCPP_CONFIG_PROPERTYREADONLY_H

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/function.hpp>
#include <glibmm.h>

#include "PropertyCore.h"
#include "PropertyWeak-fwd.h"
#include "PropertyInterface.h"
#include "Property.h"

namespace denprot {
	namespace config {

/**
 * \brief PropertyReadOnly template class capable of representing a read-only property of an arbitary type.
 */
template<typename T>
class PropertyReadOnly : public denprot::config::PropertyInterface {
	public:
		friend class PropertyWeak<T>;
		/**
		 * Helper to refer to a non-copyable PropertyCore object using shared pointers. This is used mainly internally.
		 */
		typedef boost::shared_ptr<PropertyCore<T>> PropertyCoreDyn;
		typedef Property<T> Property;
		friend class Property;
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
		
		PropertyReadOnly(PropertyCoreDyn prop, unsigned* refCnt, boost::mutex* mut) {
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
		PropertyReadOnly() :
			prop(new PropertyCore<T>()), refCnt(new unsigned(1)), mut(new boost::mutex()) {
		}
	
		/**
		 * \brief Copy-constructor for a property.
		 * 
		 * Copying a Property will cause the new instance to refer to the same PropertyCore, meaning that they share
		 * the property. One cannot make a real deep copy of a property because it would not make sense to copy the
		 * functions connected to the changed signal. (You write code which copies by value, of course)
		 * \param [in] p The property which should be copied
		 */
		PropertyReadOnly(const PropertyReadOnly& p) {
			p.mut->lock();
			prop = p.prop;
			mut = p.mut;
			refCnt = p.refCnt;
			++(*refCnt);
			p.mut->unlock();
		}

		PropertyReadOnly(const Property<T>& p) {
			p.mut->lock();
			prop = p.prop;
			mut = p.mut;
			refCnt = p.refCnt;
			++(*refCnt);
			p.mut->unlock();
		}
		
		~PropertyReadOnly() {
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
		 * Changes the PropertyCore to which this PropertyReadOnly refers to, meaning that the core to which this PropertyReadOnly
		 * refers to may be dropped.
		 * \param [in] The PropertyReadOnly whose core should be referenced by this PropertyReadOnly instance.
		 * \return A reference to this PropertyReadOnly.
		 */
		PropertyReadOnly<T>& operator*=(const PropertyReadOnly<T>& other) {
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
		 * Changes the PropertyCore to which this PropertyReadOnly refers to, meaning that the core to which this PropertyReadOnly
		 * refers to may be dropped.
		 * \param [in] The Property whose core should be referenced by this PropertyReadOnly instance.
		 * \return A reference to this PropertyReadOnly.
		 */
		PropertyReadOnly<T>& operator*=(const Property& other) {
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
		 * ClassId of the value type of this PropertyReadOnly.
		 * \return The ClassId of the Class this PropertyReadOnly is instantiated with.
		 */
		denprot::ClassIdRep getClassId() const {
			return prop->getClassId();
		}

		/**
		 * Getter for the name of this PropertyReadOnly.
		 * \return The name of the PropertyReadOnly.
		 */
		const Glib::ustring& getName() const { 
			return prop->getName();
		}
		
		/**
		 * Getter for the value of the PropertyReadOnly.
		 * \return The value of this PropertyReadOnly.
		 */
		const T& getValue() const {
			return prop->getValue();
		}
		
		/**
		 * Connects a new subscriber to this PropertyReadOnly. 
		 * \param [in] f The subscriber method to connect.
		 * \param [in] grp The connection group of the connection. (See boost::signals2 reference)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void()> f, int grp) {
			return prop->connect(f, grp);
		}

		/**
		 * Connects a new subscriber to this PropertyReadOnly. 
		 * \param [in] f The subscriber method to connect.
		 * \param [in] pos The connection position of the connection. (See boost::signals2::connect_position)
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void()> f,
		  boost::signals2::connect_position pos = boost::signals2::at_back) {
			return prop->connect(f,pos);
		}
		
		/**
		 * Connects a new subscriber to this PropertyReadOnly. The subscriber will always receive
		 * a valid reference to the PropertyReadOnly which just changed.
		 * \param [in] f The subscriber method to connect.
		 * \return A connection object to make possible disconnection and status checking.
		 */
		boost::signals2::connection connect(boost::function<void(PropertyReadOnly<T>&)> f) {
			return prop->connect(*this,boost::function<void(PropertyReadOnly<T>&)>(f));
		}
};

}
}

#endif
