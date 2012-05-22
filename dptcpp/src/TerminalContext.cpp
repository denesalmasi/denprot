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

#include "dptcpp/TerminalContext.h"
#include "dptcpp/Exception.h"
#include <sstream>

using namespace std;

namespace denprot {
namespace config {


ParseContext::Dyn TerminalContext::getParser(const Glib::ustring& name) const {
	stringstream strm;
	strm << "Unexpected XML tag in terminal parse context: " << name;
	throw Exception(strm.str().c_str(),CodePos);
}

}
}
