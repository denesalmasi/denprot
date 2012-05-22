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
 * \file Debug.h Header containing the declaration of various debugging macros.
 * \author Dénes Almási
 */
#ifndef DPTCPP_DEBUG_H
#define DPTCPP_DEBUG_H

#include <map>
#include <string>
#include <iostream>

namespace denprot {
	extern std::map<std::string,bool> debugDomainBoard;
}

#ifdef DEBUG



#define OnDomain(q) debugDomainBoard[(q)]=true

#define OffDomain(q) debugDomainBoard[(q)]=false

#define DomainlessDebug(x) std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << \
	" : DOMAINLESS : " << x << std::endl

#define DebugD(d,x) {\
	std::map<std::string,bool>::iterator it=debugDomainBoard.find((d));\
	if(it==debugDomainBoard.end()) {\
		std::string str="No such domain: ";\
		str+=(d);\
		DomainlessDebug(str);\
	} else { \
		if(debugDomainBoard[(d)]) {\
			std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << \
			" [" << (d) << "]" << " :: " << x << std::endl;\
		}\
	}\
}

#define Debug(x) \
	std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << \
	" :: " << x << std::endl;

#else
/**
 * \brief Sends a debug message to the standard error stream.
 * \param [in] x The message to be sent.
 */
#define Debug(x)

/**
 * \brief Sends a debug message to the standard error stream in a given domain.
 * \param [in] d The domain in which the message is sent.
 * \param [in] x The message to be sent.
 */
#define DebugD(d,x)


/**
 * \brief Turns on (and registers if needed) a debugging domain.
 * Only messages from active domains are delivered.
 * \param [in] x The domain to turn on.
 */
#define OnDomain(x)

/**
 * \brief Turns off (and registers if needed) a debugging domain.
 * Only messages from active domains are delivered.
 * \param [in] x The domain to turn off.
 */
#define OffDomain(q)


#endif

#endif
