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
 
#include <iostream>
#include "dptcpp/Exception.h"

#include "dptcpp/InvalidPropertyException.h"

using namespace std;

namespace denprot {
namespace config {

InvalidPropertyException::InvalidPropertyException(const char* propName, 
					const char* nFile, const char* nFunc, unsigned nLine) :
	denprot::Exception("Request for an invalid property.",nFile, nFunc, nLine),
	propName(propName) {
}

const char* InvalidPropertyException::getPropName() const {
	return propName;
}

void InvalidPropertyException::print() const {
	cerr << "InvalidPropertyException at " << file << ":" << line << ":" << func << " :: " << msg <<
	" Name: " << propName << endl;
}

}
}
