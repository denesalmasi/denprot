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
 * Contains declaration of the XmlParser class.
 */
#ifndef DPTCPP_CONFIG_XMLPARSER_H
#define DPTCPP_CONFIG_XMLPARSER_H

#include <glibmm.h>
#include "XmlParserInner.h"
#include "Exception.h"

namespace denprot {
	namespace config {
		/**
		 * \brief XmlParser is (surprisingly) capable of parsing an XML document.
		 *
		 * It applies the SAX (Simple Api for XML) parsing method.
		 * When instantiating an XmlParser, a ParseContext should be given to it .
		 * The ParseContext defines the behaviour during parsing when reading specific
		 * xml tags.
		 *
		 * This class is a wrapper around XmlParserInner. The creation of this class was
		 * neccessary to make possible to throw exceptions while parsing. (This is emulated
		 * with tricks in the XmlParser. It is unknown why is it impoosible to easily 
		 * throw exceptions directly from overriden virtual methods of the xmlpp::SaxParser.
		 * It may be some asynchronous thread-related stuff...)
		 */
		class XmlParser {
			private:
				/**
				 * \internal
				 * \brief An XmlParserInner object, which derives from xmlpp::SaxParser.
				 */
				XmlParserInner inner;
		
			public:
				/**
				 * \brief Constructs a new XmlParser with a given ParseContext.
				 */
				XmlParser(ParseContext::Dyn initCtx);
		
				/**
				 * Parses an xml file.
				 * \param [in] fName The name of the xml to parse.
				 */
				void parseFile(const Glib::ustring& fName);
		};
	}
}

#endif
