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

#ifndef DPTCPP_CONFIG_VALUECONVERT_H
#define DPTCPP_CONFIG_VALUECONVERT_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <glibmm.h>
#include <stdint.h>

namespace denprot {
	namespace config {


		template<class T, class U>
		void valueConvert(const T& src, U& dest) {
			T::PleaseSpecialiseThisTemplate();
			U::PleaseSpecialiseThisTemplate();
		}

		template<>
		inline void valueConvert<Glib::ustring,Glib::ustring>(const Glib::ustring& src,
		                                               Glib::ustring& dest) {
			dest = src;
		}


		template<>
		inline void valueConvert<Glib::ustring,unsigned>
		  (const Glib::ustring& src, unsigned& dest) {
			using boost::spirit::qi::uint_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			Glib::ustring::const_iterator first = src.begin();
			Glib::ustring::const_iterator last = src.end();
			bool r = phrase_parse(first, last, (uint_[ref(dest) = _1]), space);

			if (!r || first != last) { // fail if we did not get a full match 
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as unsigned!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
		}
	
		
		template<>
		inline void valueConvert<Glib::ustring,double>
		  (const Glib::ustring& src, double& dest) {
			using boost::spirit::qi::double_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			Glib::ustring::const_iterator first = src.begin();
			Glib::ustring::const_iterator last = src.end();
			bool r = phrase_parse(first, last, (double_[ref(dest) = _1]), space);

			if (!r || first != last) { // fail if we did not get a full match 
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as double!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
		}


		template<>
		inline void valueConvert<Glib::ustring,float>
		  (const Glib::ustring& src, float& dest) {
			using boost::spirit::qi::float_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			Glib::ustring::const_iterator first = src.begin();
			Glib::ustring::const_iterator last = src.end();
			bool r = phrase_parse(first, last, (float_[ref(dest) = _1]), space);

			if (!r || first != last) { // fail if we did not get a full match 
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as float!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
		}


		template<>
		inline void valueConvert<Glib::ustring,int>(const Glib::ustring& src, int& dest) {
			using boost::spirit::qi::int_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			Glib::ustring::const_iterator first = src.begin();
			Glib::ustring::const_iterator last = src.end();
			bool r = phrase_parse(first, last, (int_[ref(dest) = _1]), space);
			if(!r || first != last) {
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as int!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
		}


		template<>
		inline void valueConvert<Glib::ustring,int16_t>(const Glib::ustring& src, int16_t& dest) {
			using boost::spirit::qi::int_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			int q;
			Glib::ustring::const_iterator first = src.begin();
			Glib::ustring::const_iterator last = src.end();
			bool r = phrase_parse(first, last, (int_[ref(q) = _1]), space);
			if(!r || first != last) {
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as int16!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
			if(q> 32767)
				q = 32767;
			else if(q<-32768)
				q = -32768;
			dest = q;
		}


		template<>
		inline void valueConvert<Glib::ustring,bool>
		  (const Glib::ustring& src, bool& dest) {
			using boost::spirit::qi::int_;
			using boost::spirit::qi::_1;
			using boost::spirit::lit;
			using boost::spirit::qi::phrase_parse;
			using boost::spirit::ascii::space;
			using boost::phoenix::ref;
	
			Glib::ustring lower = src.lowercase();
			Glib::ustring::const_iterator first = lower.begin();
			Glib::ustring::const_iterator last = lower.end();
			Glib::ustring::const_iterator f2 = first;
			Glib::ustring::const_iterator l2 = last;
			bool r = phrase_parse(first, last, (lit("1") | "true"), space);
			bool q = phrase_parse(f2, l2, (lit("0") | "false"), space);
			if(!r && !q) {
				std::stringstream strm;
				strm << "Could not parse \"" << src << "\" as bool!";
				throw denprot::Exception(strm.str().c_str(),CodePos);
			}
			if(r) dest=true;
			if(q) dest=false;
		}


		template<>
		inline void valueConvert<unsigned, Glib::ustring>
		  (const unsigned& src, Glib::ustring& dest) {
			std::stringstream strm;
			strm << src;
			dest = strm.str();
		}


		template<>
		inline void valueConvert<int,Glib::ustring>(const int& src, Glib::ustring& dest) {
			std::stringstream strm;
			strm << src;
			dest = strm.str();
		}
		
		
		template<>
		inline void valueConvert<int16_t,Glib::ustring>(const int16_t& src, Glib::ustring& dest) {
			std::stringstream strm;
			strm << src;
			dest = strm.str();
		}


		template<>
		inline void valueConvert<double,Glib::ustring>(const double& src, Glib::ustring& dest) {
			std::stringstream strm;
			strm << src;
			dest = strm.str();
		}


		template<>
		inline void valueConvert<float,Glib::ustring>(const float& src, Glib::ustring& dest) {
			std::stringstream strm;
			strm << src;
			dest = strm.str();
		}


		template<>
		inline void valueConvert<bool,Glib::ustring>(const bool& src, Glib::ustring& dest) {
			if(src)
				dest = "true";
			else
				dest = "false";
		}

	}
}
#endif
