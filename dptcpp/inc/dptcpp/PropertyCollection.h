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

#ifndef DPTCPP_CONFIG_PROPERTYCOLLECTION_H
#define DPTCPP_CONFIG_PROPERTYCOLLECTION_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <glibmm.h>
#include <sstream>
#include "Property.h"
#include "Exception.h"
#include "PropertyInterface.h"

namespace denprot {
	namespace config {

		class PropertyCollection {
			public:
				typedef boost::shared_ptr<PropertyCollection> Dyn;
				typedef std::map<Glib::ustring, boost::shared_ptr<denprot::config::PropertyInterface>> PMap;
			private:
				PMap propMap;
				PropertyCollection();
			public:
				static Dyn create();
				
				template<class T>
				Property<T> get(const Glib::ustring& name) const {
					auto it = propMap.find(name);
					if(it == propMap.end()) {
						std::stringstream strm;
						strm << "Could not find property with name: " << name;
						throw Exception(strm.str().c_str(),CodePos);
					}
					if(it->second->getClassId() != ClassId<T>::id()) {
						std::stringstream strm;
						strm << "Type mismatch for property with name: " << name;
						throw Exception(strm.str().c_str(),CodePos);
					}
					return *(boost::static_pointer_cast<Property<T>>(it->second));
				}
				
				void add(const Glib::ustring& name,
				          denprot::config::PropertyInterface::Dyn prop);
				
				bool hasProperty(const Glib::ustring& name) const;
				
				void removeProperty(const Glib::ustring& name);
				
				ClassIdRep getClassId(const Glib::ustring& name) const;
				
				void clear();
				
				PMap::const_iterator begin() const;
				PMap::const_iterator find(const Glib::ustring& name) const;
				PMap::const_iterator end() const;
		};

	}
}

#endif
