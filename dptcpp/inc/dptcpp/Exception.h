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
 * \file Exception.h Header containing the declaration of the general Exception class.
 * \author Dénes Almási
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
 * A macro that simlifies passing the code position to an exception when constructing it.
 * Usage: throw Exception("SomeMessage",CodePos);
 */
#define CodePos __FILE__,__func__,__LINE__

namespace denprot {
	/**
	 * General exception class carrying an informative message and a position in
	 * code from where the exception was thrown.
	 */
	class Exception {
		private:
			/**
			 * \internal
			 * Performs safe copying of the source string.
			 * \param [in] src The string to copy into the internal buffer of the object
			 * \return true if copying was successful, false otherwise.
			 */
			bool copyMessage(const char* src);
		public:
			/**
			 * The maximum size of the message to be carryed by the object.
			 */
			const static unsigned BufSize;
		protected:
		
			/**
			 * The message carried by the object.
			 */
			char* msg;
		
			/**
			 * The name of the function from which the exception was thrown.
			 */
			const char* func;
		
			/**
			 * The file from which the exception was thrown.
			 */
			const char* file;
		
			/**
			 * The line number in the file from where the exception was thrown.
			 */
			unsigned line;
		
			/**
			 * Returns msg or a hard-coded error message informing that memory allocation failed for msg.
			 * \return A safely readable buffer either with msg or a malloc error.
			 */
			const char* safeMsg() const;
		public:
	
			/**
			 * Constructs a new Exception object with a given message, filename,
			 * function name and line number. The passed nMsg may not be longer than BufSize-1.
			 * The message is copied.
			 * 
			 * It is convenient to use CodePos macro instead of the last three parameters:
			 * \code throw Exception("A message", CodePos); \endcode
			 *
			 * \param nMsg the message describing the exception.
			 * \param nFile the file in which the exception occured. (__FILE__)
			 * \param nFunc the function in which the exception occured. (__func__)
			 * \param nLine the line where the exception occured. (__LINE__)
			 */
			Exception(const char* nMsg, const char* nFile, const char* nFunc,
						unsigned nLine);
			
			/**
			 * Performs deep-copying of an Exception object. (A new msg buffer is allocated)
			 */
			Exception(const Exception& ex);
		
			/**
			 * Using operator= is not allowed.
			 */
			Exception& operator=(const Exception& rhs) = delete;
					
		
					
			/**
			 * Frees the message buffer when destructing the Exception object.
			 */
			virtual ~Exception();
		
			/**
			 * Returns the name of the function from where the exception was thrown.
			 * \return the name of the function from where the exception was thrown.
			 */
			const char* getFunc() const;
		
			/**
			 * Returns the name of the file from where the exception was thrown.
			 * \return the name of the file from where the exception was thrown
			 */
			const char* getFile() const;
		
			/**
			 * Returns the line number from where the exception was thrown.
			 * \return the line number from where the exception was thrown.
			 */
			unsigned getLine() const;
		
			/**
			 * Returns the message carried by this Exception object.
			 * \return the message carried by this Exception object.
			 */
			const char* getMsg() const;
		
			/**
			 * Prints information about the exception to the standard error.
			 * Usually this is overridden by the subclasses.
			 */
			virtual void print() const;
	};

}
#endif
