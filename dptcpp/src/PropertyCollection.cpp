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

#include "dptcpp/PropertyCollection.h"
#include <sstream>

using std::endl;
using std::stringstream;

namespace denprot {
namespace config {


	PropertyCollection::PropertyCollection() {}

	PropertyCollection::Dyn PropertyCollection::create() {
		return PropertyCollection::Dyn(new PropertyCollection());
	}

	void PropertyCollection::add(const Glib::ustring& name,
	                             boost::shared_ptr<PropertyInterface> prop) {
		auto it = propMap.find(name);
		if(it != propMap.end()) {
			stringstream strm;
			strm << "Property with name '" << name
				 << "' already exists in this PropertyCollection" << endl;
			throw Exception(strm.str().c_str(),CodePos);
		}
		propMap[name] = prop;
	}
	
	bool PropertyCollection::hasProperty(const Glib::ustring& name) const {
		if(propMap.find(name)==propMap.end())
			return false;
		return true;
	}
	
	ClassIdRep PropertyCollection::getClassId(const Glib::ustring& name) const {
		auto it = propMap.find(name);
		if(it == propMap.end()) {
			std::stringstream strm;
			strm << "Could not find property with name: " << name;
			throw Exception(strm.str().c_str(),CodePos);
		}
		return it->second->getClassId();
	}

	PropertyCollection::PMap::const_iterator PropertyCollection::begin() const {
		return propMap.begin();
	}
	
	PropertyCollection::PMap::const_iterator PropertyCollection::end() const {
		return propMap.end();
	}
	
	void PropertyCollection::removeProperty(const Glib::ustring& name) {
		auto it = propMap.find(name);
		if(it == propMap.end()) {
			std::stringstream strm;
			strm << "Could not find property with name for removal: " << name;
			throw Exception(strm.str().c_str(),CodePos);
		}
		propMap.erase(it);
	}
	
	PropertyCollection::PMap::const_iterator PropertyCollection::find(const Glib::ustring& name) const {
		return propMap.find(name);
	}
	
	void PropertyCollection::clear() {
		propMap.clear();
	}
}
}
