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
 * \file Identifiable.h Header containing the declaration of the Identifiable class.
 * \author Dénes Almási
 */
#ifndef DPTCPP_IDENTIFIABLE_H
#define DPTCPP_IDENTIFIABLE_H

#include "IdTypes.h"

namespace denprot {
	/**
	 * A class inheriting from this class is considered identifiable:
	 * it is guaranteed that every instance has a unique id.
	 */
	class Identifiable {
		private:
			/**
			 * \internal
			 * The lastly distributed id.
			 */
			static IdRep lastId;
			
			/**
			 * \internal
			 * Returns the next id.
			 * \return The next valid id.
			 */
			static IdRep next();
			
			/**
			 * \internal
			 * The id of an actual instance.
			 */
			IdRep myId;
		public:
			/**
			 * Constructs a new identifiable object giving it a unique id.
			 */
			Identifiable();
			 
			/**
			 * Returns the unique id of the object.
			 * \return The id of the object.
			 */
			IdRep getId() const;
	};

}

#endif
