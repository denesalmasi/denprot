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
 * \file ClassIdClass.h Header containing the declaration of the ClassId class.
 * \author Dénes Almási
 */

#ifndef DPTCPP_CLASSIDCLASS_H
#define DPTCPP_CLASSIDCLASS_H

#include "IdTypes.h"
#include "ClassIdCounter.h"
#include "IdentifiableClass.h"

namespace denprot {

	/**
	 * Template class capable of supporting a unique number for any type
	 * the template is instantiated with.
	 */
	template<class T>
	class ClassId : public IdentifiableClass {
		private:
			/**
			 * \internal
			 * The id of this template instance.
			 */
			static ClassIdRep clsId;
		public:
			/**
			 * Returns the id of the instantiated template class
			 */
			static ClassIdRep id() {
				if(!clsId)
					clsId = ClassIdCounter::next();
				return clsId;
			}
			
			/**
			 * Returns the id of the instantiated template class when a ClassId object is created.
			 */
			ClassIdRep getClassId() {
				return id();
			}
	};

	// The default id is 0 : no valid id can be 0, the minimum is 1 so 0 is perfect for
	// an uninitialized value.
	template <class T> ClassIdRep ClassId<T>::clsId = 0;

}
#endif
