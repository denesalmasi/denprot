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
 * \file PropertyReactor.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * Contains declaration of the XmlParserInner class.
 */

#ifndef DPTCPP_CONFIG_XMLPARSERINNER_H
#define DPTCPP_CONFIG_XMLPARSERINNER_H

#include <glibmm.h>
#include <boost/shared_ptr.hpp>
#include <stack>
#include <libxml++/libxml++.h>
#include "ParseContext.h"
#include "Exception.h"

namespace denprot {
	namespace config {
		/**
		 * \brief Xml parser class.
		 * Uses SAX parsing method. (See: http://en.wikipedia.org/wiki/Simple_API_for_XML)
		 */
		class XmlParserInner : public xmlpp::SaxParser {
			private:
				/**
				 * \internal
				 * \brief A stack of ParseContexts. The topmost context is always the currently used one.
				 */
				std::stack<ParseContext::Dyn> stck;
		
				/**
				 * \internal
				 * \brief Shows whether any errors occured during parsing or not.
				 * If fault is truem, getThrown will return a dynamically allocated Exception describing the error.
				 */
				bool fault;
		
				/**
				 * \internal
				 * \brief May point to an Exception describing an error that happened during parsing.
				 *
				 * The dynamically allocated object is freed by the destructor of the parser so
				 * one must take a copy of it to use it outside of the scope of the parser.
				 */
				denprot::Exception* thrown;
			public:
				/**
				 * Constructs a new XmlParserInner object using a given context.
				 * \param [in] initCtx The initial context of the parser.
				 */
				XmlParserInner(ParseContext::Dyn initCtx);
		
				/**
				 * Destructs the XmlParserInner object, potentially freeing its allocated exception object.
				 */
				~XmlParserInner();
		
				/**
				 * Callback fired when touching an element opening in the xml.
				 * \param [in] name The name of the tag just passed.
				 * \param [in] attrList The attributes of the tag just passed.
				 */
				void on_start_element(const Glib::ustring& name,
									  const xmlpp::SaxParser::AttributeList& attrList);
				/**
				 * Callback fired when touching the end of an element in the xml.
				 * \param [in] name The name of the tag just passed.
				 */
				void on_end_element(const Glib::ustring& name);
		
				/**
				 * Shows whether any parsing errors occured or not.
				 * \return True if an exception occured during parsing.
				 */
				bool getFault() const;
		
				/**
				 * Getter for the internal Exception object of the parser.
				 * If fault is true, this method will return an Exception object
				 * that was thrown from inside the parser. Deallocation of this object
				 * is done by the parser so a copy should be made if the client is 
				 * willing to use it outside the scope of the parser.
				 * \return An exception object or NULL.
				 */
				denprot::Exception* getThrown() const;
		};
	}
}

#endif
