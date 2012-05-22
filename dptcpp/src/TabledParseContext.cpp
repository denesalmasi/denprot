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

#include "dptcpp/TabledParseContext.h"
#include "dptcpp/Exception.h"
#include "dptcpp/Debug.h"
#include <sstream>
#include <cstdlib>

namespace denprot {
namespace config {

TabledParseContext::TabledParseContext() {
}

void TabledParseContext::start(const Glib::ustring& name, const xmlpp::SaxParser::AttributeList& lst) {
}

void TabledParseContext::end(const Glib::ustring& name) {
}

ParseContext::Dyn TabledParseContext::getParser(const Glib::ustring& name) const {
	ParseTable::const_iterator it = parseTable.find(name.casefold());
	if(it == parseTable.end()) {
		std::stringstream strm;
		strm << "Unexpected XML tag: " << name;
		throw Exception(strm.str().c_str(), CodePos);
	} else {
		return it->second;
	}
}

void TabledParseContext::registerParser(const Glib::ustring& name, ParseContext::Dyn parser) {
	Glib::ustring cfold = name.casefold();
	ParseTable::iterator it = parseTable.find(cfold);
	if(it == parseTable.end())
		parseTable[cfold] = parser;
	else {
		std::stringstream strm;
		strm << "Parser for tag " << name << " already registered in TabledParseContext.";
		throw Exception(strm.str().c_str(), CodePos);
	}
}

TabledParseContext::Dyn TabledParseContext::create() {
	return Dyn(new TabledParseContext());
}

}
}
