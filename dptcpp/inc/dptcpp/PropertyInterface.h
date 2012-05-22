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
 
#ifndef PROPERTYINTERFACE_H
#define PROPERTYINTERFACE_H

#include "IdentifiableClass.h"
#include <boost/signals2.hpp>
#include <boost/function.hpp>
#include <glibmm.h>

namespace denprot {
	namespace config {
		class PropertyInterface : public denprot::IdentifiableClass {
			public:
				/**
				 * A shorthand for making shared pointers referencing to this class.
				 */
				typedef boost::shared_ptr<PropertyInterface> Dyn;
		
				/**
				 * ClassId of the value type of this Property.
				 * \return The ClassId of the Class this Property is instantiated with.
				 */
				virtual denprot::ClassIdRep getClassId() const = 0;

				/**
				 * Getter for the name of this Property.
				 * \return The name of the Property.
				 */
				virtual const Glib::ustring& getName() const = 0;

				/**
				 * Connects a new subscriber to this Property. 
				 * \param [in] f The subscriber method to connect.
				 * \param [in] pos The connection position. (See boost::signals2::connect_position)
				 * \return A connection object to make possible disconnection and status checking.
				 */
				virtual boost::signals2::connection connect(boost::function<void()> f,
				  boost::signals2::connect_position pos = boost::signals2::at_back) = 0;
				  
				/**
				 * Connects a new subscriber to this Property. 
				 * \param [in] f The subscriber method to connect.
				 * \param [in] grp The connection group of the connection. (See boost::signals2 reference)
				 * \return A connection object to make possible disconnection and status checking.
				 */
				virtual boost::signals2::connection connect(boost::function<void()> f, int grp) = 0;

				/**
				 * Connects a new subscriber to this Property. 
		 		 * The connected function will run on the thread changing the property's value.	
				 * \param [in] f The subscriber method to connect.
				 * \return A connection object to make possible disconnection and status checking.
				 */
				virtual boost::signals2::connection connectLocal(boost::function<void()> f) = 0;
		};
	}
}

#endif
