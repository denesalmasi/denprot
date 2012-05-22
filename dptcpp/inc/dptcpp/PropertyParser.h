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

#ifndef DPTCPP_CONFIG_PROPERTYPARSER_H
#define DPTCPP_CONFIG_PROPERTYPARSER_H

#include "TerminalContext.h"
#include "Property.h"
#include "PropertyCollection.h"
#include "PropertyInterface.h"
#include "PropertySerializer.h"
#include "ValueConvert.h"
#include <libxml++/libxml++.h>
#include <boost/shared_ptr.hpp>
#include <sstream>

namespace denprot {
	namespace config {
		template<class T>
		class PropertyParser : public TerminalContext, public denprot::IdentifiableClass {
			private:
				boost::shared_ptr<Property<T>> inst;
				PropertyCollection::Dyn collector;
	
				PropertyParser(PropertyCollection::Dyn collector) : collector(collector) {
				}
				
		
			public:
				typedef boost::shared_ptr<PropertyParser<T>> Dyn;
		
				static Dyn create(PropertyCollection::Dyn collector) {
					return Dyn(new PropertyParser<T>(collector));
				}
		
				~PropertyParser() {
				}
		
				denprot::ClassIdRep getClassId() const {
					return denprot::ClassId<T>::id();
				}
		
				/**
				 * Method called when this is the active context and a new tag is encountered.
				 * \param [in] name The name of the tag that has to be handled by this ParseContext
				 * \param [in] lst The list of attributes of the tag
				 */
				void start(const Glib::ustring& name, const xmlpp::SaxParser::AttributeList& lst) {
					if(validate(name, lst))
						parse(name, lst);
					else {
						std::stringstream strm;
						strm << "Invalid " << name << " tag: there must be both a name and a value attribute!";
						throw denprot::Exception(strm.str().c_str(),CodePos);
					}
				}
		
				bool validate(const Glib::ustring& name, const xmlpp::SaxParser::AttributeList& lst) {
					bool nameFound = false;
					bool valueFound = false;
					for(auto it = lst.begin(); it != lst.end(); ++it) {
						if(!nameFound && it->name.casefold() == Glib::ustring("name").casefold())
							nameFound = true;
						if(!valueFound && it->name.casefold() == Glib::ustring("value").casefold())
							valueFound = true;
					}
					return nameFound && valueFound;
				}
		
				void parse(const Glib::ustring& name, const xmlpp::SaxParser::AttributeList& lst) {
					const Glib::ustring *pName, *pValue;
					Glib::ustring nameFold = Glib::ustring("name").casefold();
					Glib::ustring valFold = Glib::ustring("value").casefold();
					for(auto it = lst.begin(); it != lst.end(); ++it) {
						if(it->name.casefold() == nameFold)
							pName = &(it->value);
						if(it->name.casefold() == valFold)
							pValue = &(it->value);
					}
					T q;
					valueConvert<Glib::ustring, T>(*pValue,q);
					inst = boost::shared_ptr<Property<T>>(new Property<T>(*pName,q));
					collector->add(*pName,boost::static_pointer_cast<PropertyInterface>(inst));
				}
		
				/**
				 * Method called when this is the active context and a tag is closed.
				 * \param [in] name The name of the tag closed
				 */
				void end(const Glib::ustring& name) {
				}
		
				Property<T> getProperty() const {
					if(!inst)
						throw denprot::Exception("PropertyParser did not parse any property yet!",CodePos);
					else
						return *inst;
				}
		};
	}
}

#endif
