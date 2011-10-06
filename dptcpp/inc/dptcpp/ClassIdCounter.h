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
 * \file ClassIdCounter.h Header containing the declaration of the ClassIdCounter class.
 * \author Dénes Almási
 */
 
#ifndef CLASSIDCOUNTER_H
#define CLASSIDCOUNTER_H

#include "IdTypes.h"

namespace denprot {

	/**
	 * A class having a counter that is incremented for any new instantiation
	 * of the ClassId generic class.
	 */
	class ClassIdCounter {
		private:
			/**
			 * The lastly distributed id
			 */
			static ClassIdRep lastId;
		public:
			/**
			 * Returns a new, yet unused class id.
			 * \return A new id
			 */
			static ClassIdRep next() {
				return ++lastId;
			}
	};

}

#endif
