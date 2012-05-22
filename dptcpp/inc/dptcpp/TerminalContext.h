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

#ifndef DPTCPP_CONFIG_TERMINALCONTEXT_H
#define DPTCPP_CONFIG_TERMINALCONTEXT_H

#include "ParseContext.h"
#include <glibmm.h>

namespace denprot {
	namespace config {
		class TerminalContext : public ParseContext {
			public:
				ParseContext::Dyn getParser(const Glib::ustring& name) const;
		};
	}
}

#endif
