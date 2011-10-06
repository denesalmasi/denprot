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

#include "dptcpp/ClassIdCounter.h"
#include "dptcpp/Identifiable.h"

namespace denprot {

ClassIdRep ClassIdCounter::lastId = 0;
IdRep Identifiable::lastId = 0;

IdRep Identifiable::next() {
	return ++lastId;
}

Identifiable::Identifiable() {
	myId = next();
}

IdRep Identifiable::getId() const {
	return myId;
}

}
