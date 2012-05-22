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

#include <glibmm.h>
#include <sstream>
#include "dptcpp/SingleAcceptContext.h"
#include "dptcpp/Exception.h"

using std::stringstream;
using std::endl;

namespace denprot {
namespace config {


SingleAcceptContext::SingleAcceptContext(const Glib::ustring& acc, ParseContext::Dyn hook) :
  accept(acc), hook(hook) {
}

const Glib::ustring& SingleAcceptContext::getAccepts() const {
	return accept;
}

void SingleAcceptContext::start(const Glib::ustring& name, const xmlpp::SaxParser::AttributeList& lst) {
	if(name != accept) {
		stringstream strm;
		strm << "Unexpected tag: '" << name << "'";
		strm << ", expected " << accept << " instead.";
		throw Exception(strm.str().c_str(),CodePos);
	}
}

void SingleAcceptContext::end(const Glib::ustring& name) {
}

ParseContext::Dyn SingleAcceptContext::getParser(const Glib::ustring& name) const {
	if(name.casefold() != accept.casefold()) {
		stringstream strm;
		strm << "No parser registered for tag: '" << name << "' in SingleAcceptContext for '" << accept << "'";
		throw Exception(strm.str().c_str(),CodePos);
	}
	return hook;
}

ParseContext::Dyn SingleAcceptContext::getHook() const {
	return hook;
}

}
}
