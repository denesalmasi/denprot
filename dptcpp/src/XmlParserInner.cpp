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

#include "dptcpp/XmlParserInner.h"
#include "dptcpp/Debug.h"

namespace denprot {
namespace config {

XmlParserInner::XmlParserInner(ParseContext::Dyn initCtx) : fault(false), thrown(NULL) {
	stck.push(initCtx);
}

void XmlParserInner::on_start_element(const Glib::ustring& name,
							 	    const xmlpp::SaxParser::AttributeList& attrList) {
	if(!fault) {
		try {
			ParseContext::Dyn p = stck.top()->getParser(name);
			stck.push(p);
			stck.top()->start(name, attrList);
		} catch(Exception& e) {
			fault = true;
			thrown = new Exception(e.getMsg(),e.getFile(),e.getFunc(),e.getLine());
		}
	} 
}

void XmlParserInner::on_end_element(const Glib::ustring& name) {
	if(!fault) {
		try {
			stck.top()->end(name);
			stck.pop();
		} catch(Exception& e) {
			fault = true;
			thrown = new Exception(e.getMsg(),e.getFile(),e.getFunc(),e.getLine());
		}
	}
}

XmlParserInner::~XmlParserInner() {
	delete thrown;
}

bool XmlParserInner::getFault() const {
	return fault;
}

Exception* XmlParserInner::getThrown() const {
	return thrown;
}

}
}

