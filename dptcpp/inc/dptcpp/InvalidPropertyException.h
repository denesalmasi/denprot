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
 * \file InvalidPropertyException.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * Declaration of the InvalidPropertyException class.
 */
#ifndef DPTCPP_CONFIG_INVALIDPROPERTYEXCEPTION_H
#define DPTCPP_CONFIG_INVALIDPROPERTYEXCEPTION_H

#include "Exception.h"


namespace denprot {
	namespace config {
		/**
		 * Exception thrown when a Property-related errors occur.
		 */
		class InvalidPropertyException : public denprot::Exception {
			private:
				/**
				 * The name of the invalid property.
				 */
				const char* propName;
			public:
				/** 
				 * Constructs a new InvalidPropertyException.
				 * \param [in] propName The name of the property which was invalid.
				 * \param nFile the file in which the exception occured. (__FILE__)
				 * \param nFunc the function in which the exception occured. (__func__)
				 * \param nLine the line where the exception occured. (__LINE__)
				 */
				InvalidPropertyException(const char* propName, const char* nFile,
										 const char* nFunc, unsigned nLine);
										 
				/**
				 * Getter for the name of the invalid property.
				 * \return The name of the invalid property.
				 */
				const char* getPropName() const;
				/**
				 * Prints exception information to stderr.
				 */
				virtual void print() const;
		
		};
	}
}

#endif
