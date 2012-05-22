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
 * Contains declaration of the PropertyReactor class.
 */

#ifndef DPTCPP_CONFIG_PROPERTYREACTOR_H
#define DPTCPP_CONFIG_PROPERTYREACTOR_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/function.hpp>

namespace denprot {
	namespace config {

		/**
		 * PropertyReactor represents a separate thread of execution responsible 
		 * for running functions of property subscribers separated from the context
		 * in which the property was modified.
		 * A class encapsulating a boost proactor/reactor pattern implementation
		 */
		class PropertyReactor {
			public:
				typedef void(*ThreadStarter)(void(*handler)(void*));
				typedef void(*ThreadKiller)();
			private:
				/**
				 * \internal
				 * \brief The reactor object.
				 */
				static boost::asio::io_service reactor;
				
				/** 
				 * \internal
				 * \brief The strand used for keeping the order of handlers in the reactor
				 */
				static boost::asio::io_service::strand* strand;
		
				/**
				 * \internal
				 * \brief The thread running the reactor.
				 */
				static boost::thread* thread;
		
				/**
				 * \internal
				 * \brief A work object keeping the reactor alive until execution
				 * of the application stops.
				 */
				static boost::asio::io_service::work* keeper;
				
				/**
				 * \internal
				 * \brief Barrier helping synchronization of one other thread with the reactor.
				 */
				static boost::barrier* syncer;
				
				/**
				 * \internal
				 * \brief True when the reactor should collapse as the program finishes
				 */
				static bool quit;
				/**
				 * \internal
				 * This is the method ran by the thread, starting the reactor.
				 * The void* argument is ignored.
				 */
				static void handler(void*);
				
				/**
				 * \internal
				 * The default thread starting method using boost threads.
				 */
				static void defaultStarter(void(*handler)(void*));
				
				/**
				 * \internal
				 * The default thread joining method.
				 */
				static void defaultKiller();
			public:

				/**
				 * This method is responsible for starting the thread of the reactor.
				 * (and as a consequence, starting the reactor itself)
				 */
				static void start();
		
				/**
				 * This method is responsible for dropping the work object which keeps the
				 * reactor artificially alive and then waiting for the reactor to stop. 
				 * After the drop, the reactor will only remain active until it has any job to do,
				 * meaning that probably it will halt in the near future. Though this function
				 * may never return if for example a function got into an endless loop in the reactor.
				 */
				static void stop();
				
				/**
				 * Makes it possible for a thread to catch up with the reactor thread resulting in
				 * a state in which it is guaranteed for that thread that a reactor is in a certain
				 * state.
				 */
				static void sync();
		
				/**
				 * Dispatches a function to the reactor making it execute it on the
				 * reactor thread.
				 * \param [in] func The function to run in the reactor.
				 */
				static void post(boost::function<void()> func);
				
				/**
				 * The threadstarter algorithm used for starting the reactor thread
				 */
				static ThreadStarter starter;
				
				/**
				 * The threadkiller algorithm used for joining the reactor thread
				 */
				static ThreadKiller killer;
		};

	}
}
#endif
