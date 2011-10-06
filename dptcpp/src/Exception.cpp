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

#include "dptcpp/Exception.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace denprot {

const unsigned Exception::BufSize = 256;

bool Exception::copyMessage(const char* src) {
	msg = new (nothrow) char[BufSize];
	if(!msg) {
		return false;
	} else {
		unsigned len = strlen(src);
		unsigned limit = (BufSize-1<=len)?BufSize-1:len;
		int i=0;
		for(; i<limit; ++i)
			msg[i]=src[i];
		msg[i]=0;
		return true;
	}
}

Exception::Exception(const char* nMsg, const char* nFile, const char* nFunc, unsigned nLine) : 
	file(nFile),
	func(nFunc),
	line(nLine)
{
	copyMessage(nMsg);
}

Exception::Exception(const Exception& ex) :
	file(ex.getFile()),
	func(ex.getFunc()),
	line(ex.getLine())
{
	copyMessage(ex.getMsg());
}

Exception::~Exception() {
	delete[] msg;
}

const char* Exception::getFile() const {
	return file;
}

const char* Exception::getFunc() const {
	return func;
}

const char* Exception::getMsg() const {
	return safeMsg();
}

const char* Exception::safeMsg() const {
	return msg?msg:"[exception message allocation fail]";
}

unsigned Exception::getLine() const {
	return line;
}

void Exception::print() const {
	cerr << "Exception at " << file << ":" << line << ":" << func << " :: " << safeMsg() << endl;
}

}
