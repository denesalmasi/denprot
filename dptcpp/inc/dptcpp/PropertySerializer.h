#ifndef PROPERTY_SERIALIZER_H
#define PROPERTY_SERIALIZER_H

#include "Property.h"
#include "ValueConvert.h"
#include <glibmm.h>
#include <stdint.h>

namespace denprot {
	namespace config {
		template<class T>
		Glib::ustring propertyTag() {
			T::pleaseSpecializeThisTemplate();
		}
		
		template<>
		inline Glib::ustring propertyTag<int>() {
			return "PropertyInt";
		}
		
		template<>
		inline Glib::ustring propertyTag<int16_t>() {
			return "PropertyInt16";
		}
		
		template<>
		inline Glib::ustring propertyTag<unsigned>() {
			return "PropertyUnsigned";
		}
		
		template<>
		inline Glib::ustring propertyTag<Glib::ustring>() {
			return "PropertyString";
		}
		
		template<>
		inline Glib::ustring propertyTag<bool>() {
			return "PropertyBool";
		}
		
		template<>
		inline Glib::ustring propertyTag<float>() {
			return "PropertyFloat";
		}
		
		template<>
		inline Glib::ustring propertyTag<double>() {
			return "PropertyDouble";
		}
	
		template<class T>
		Glib::ustring serializeProperty(Property<T> prop) {
			Glib::ustring val;
			valueConvert<T,Glib::ustring>(prop.getValue(),val);
			Glib::ustring rv = "<";
			rv.append(propertyTag<T>());
			rv.append(" name=\"");
			rv.append(prop.getName());
			rv.append("\" value=\"");
			rv.append(val);
			rv.append("\" />");
			return rv;
		}
		
	}
}


#endif

