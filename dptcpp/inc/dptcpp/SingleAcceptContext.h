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

#ifndef DPTCPP_CONFIG_SIGNLEACCEPTCONTEXT_H
#define DPTCPP_CONFIG_SINGLEACCEPTCONTEXT_H

#include "ParseContext.h"

namespace denprot {
	namespace config {
		class SingleAcceptContext : public ParseContext {
			private:
				Glib::ustring accept;
				ParseContext::Dyn hook;
			public:
				SingleAcceptContext(const Glib::ustring& name, ParseContext::Dyn hook);
	
				ParseContext::Dyn getParser(const Glib::ustring& name) const;
		
				const Glib::ustring& getAccepts() const;
		
				ParseContext::Dyn getHook() const;

				void start(const Glib::ustring& name,
				            const xmlpp::SaxParser::AttributeList& lst);
		
				void end(const Glib::ustring& name);
		
		};
	}
}
#endif
