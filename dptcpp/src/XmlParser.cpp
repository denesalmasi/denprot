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

#include "dptcpp/XmlParser.h"

namespace denprot {
namespace config {


XmlParser::XmlParser(ParseContext::Dyn initCtx) : inner(initCtx) {
}

void XmlParser::parseFile(const Glib::ustring& file) {
	try {
		inner.parse_file(file);
		if(inner.getFault()) {
			Exception* thrown = inner.getThrown();
			Exception toThrow(*thrown);
			throw toThrow;
		}
	} catch(xmlpp::exception& e) {
		throw Exception(e.what(), CodePos);
	}
}

}
}
