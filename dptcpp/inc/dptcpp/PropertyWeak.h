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

#ifndef DPTCPP_CONFIG_PROPERTYWEAK_H
#define DPTCPP_CONFIG_PROPERTYWEAK_H

#include "PropertyCore-fwd.h"
#include "Property.h"
#include <boost/weak_ptr.hpp>

namespace denprot {
	namespace config {
		template <class T>
		class PropertyWeak {
			private:
				boost::weak_ptr<PropertyCore<T>> weak;
				unsigned* refCnt;
				boost::mutex* mut;
			public:
				friend class Property<T>;
				PropertyWeak(Property<T> p) {
					p.mut->lock();
					weak = p.prop;
					refCnt = p.refCnt;
					++(*refCnt);
					mut = p.mut;
					p.mut->unlock();
				}
		
				PropertyWeak(const PropertyWeak& other) {
					other.mut->lock();
					weak = other.weak;
					refCnt = other.refCnt;
					++(*refCnt);
					mut = other.mut;
					other.mut->unlock();
				}
		
				~PropertyWeak() {
					mut->lock();
					--(*refCnt);
					if(*refCnt == 0) {
						delete refCnt;
						mut->unlock();
						delete mut;
					} else
						mut->unlock();
				}
		
				bool raise(Property<T>** p) {
					mut->lock();
					boost::shared_ptr<PropertyCore<T>> strong = weak.lock();
					mut->unlock();
					if(strong) {
						*p = new Property<T>(strong, refCnt, mut);
						return true;
					} else {
						*p = NULL;
						return false;
				
					}
				}
		};
	}
}

#endif
