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
 * \file IdentifiableClass.h Header containing the declaration of the IdentifiableClass interface.
 * \author Dénes Almási
 */
#ifndef IDENTIFIABLECLASS_H
#define IDENTIFIABLECLASS_H

#include "IdTypes.h"

namespace denprot {
	/**
	 * Every instance of an IdentifiableClass is considered to be able to
	 * return its ClassId via the getClassId() method.
	 */
	class IdentifiableClass {
		public:
			/**
			 * Returns the id of the implementing class.
			 * \return The id of the class implementing this interface.
			 */
			virtual ClassIdRep getClassId() const=0;
	};

}
#endif
