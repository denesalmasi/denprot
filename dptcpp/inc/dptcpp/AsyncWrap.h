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
 * \file AsyncWrap.h
 * \author Denes Almasi <denes.almasi@gmail.com>
 * Declaration of the AsyncWrap helper function
 */

#ifndef DPTCPP_CONFIG_ASYNCWRAP_H
#define DPTCPP_CONFIG_ASYNCWRAP_H

#include <boost/function.hpp>

/**
 * \brief Puts an asynchronous wrapper around the function refered by the parameter.
 *
 * This means that execution of the returned function will be delegated to
 * the PropertyReactor if it is running. (If it is not running, calling the
 * wrapper will result in undefined behaviour)
 *
 * \param [in] func The function to wrap asynchronously.
 * \return The asynchronous wrapper.
 */


namespace denprot {
	namespace config {
		boost::function<void()> asyncWrap(boost::function<void()> func);
	}
}
#endif
