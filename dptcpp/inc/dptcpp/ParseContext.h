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
 * \file ParseContext.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * Declaration of the ParseContext interface.
 */
#ifndef DPTCPP_CONFIG_PARSECONTEXT_H
#define DPTCPP_CONFIG_PARSECONTEXT_H

#include <libxml++/libxml++.h>
#include <glibmm.h>
#include <boost/shared_ptr.hpp>
#include <map>


namespace denprot {
	namespace config {
		/**
		 * \brief An interface capable of defining valid XML tags in a given context when parsing.
		 *
		 * This interface lets changing the behaviour of parsing and lets the creation of object
		 * based on decisions made by the structure of the XML document.
		 */
		class ParseContext {
			public:
				/**
				 * Helper to shorten shared pointers referencing ParseContexts.
				 */
				typedef boost::shared_ptr<ParseContext> Dyn;
		
				/**
				 * Returns the ParseContext that has to be used when reading a given tag in this context.
				 * \param [in] The tag read by the dumb SAX xml parser.
				 * \return The parser that has to be used when trying to parse the parameter tag
				 */
				virtual Dyn getParser(const Glib::ustring& name) const = 0;
		
				/**
				 * Method called when this is the active context and a new tag is encountered.
				 * \param [in] name The name of the tag that has to be handled by this ParseContext
				 * \param [in] lst The list of attributes of the tag
				 */
				virtual void start(const Glib::ustring& name,
				                    const xmlpp::SaxParser::AttributeList& lst) = 0;
		
				/**
				 * Method called when this is the active context and a tag is closed.
				 * \param [in] name The name of the tag closed
				 */
				virtual void end(const Glib::ustring& name) = 0;
		
		};

		/**
		 * A mapping between tag names and ParseContext. This helper class can be used
		 * to write dynamically extendable parsers.
		 */
		typedef std::map<Glib::ustring, ParseContext::Dyn> ParseTable;
	}
}

#endif
