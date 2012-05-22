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

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>

#include "dptcpp/PropertyReactor.h"
#include "dptcpp/Debug.h"

namespace denprot {
namespace config {

boost::asio::io_service 			PropertyReactor::reactor;
boost::asio::io_service::strand* 	PropertyReactor::strand = NULL;
boost::thread* 						PropertyReactor::thread = NULL;
boost::asio::io_service::work* 		PropertyReactor::keeper = NULL;
boost::barrier* 					PropertyReactor::syncer = NULL;
PropertyReactor::ThreadStarter 		PropertyReactor::starter = PropertyReactor::defaultStarter;
PropertyReactor::ThreadKiller		PropertyReactor::killer = PropertyReactor::defaultKiller;

bool PropertyReactor::quit = false;

void PropertyReactor::handler(void* arg) {
	while(true) {
		reactor.run();
		if(quit)
			break;
		reactor.reset();
		keeper = new boost::asio::io_service::work(reactor);
		syncer->wait();
	}
}

void PropertyReactor::start() {
	keeper = new boost::asio::io_service::work(reactor);
	syncer = new boost::barrier(2);
	strand = new boost::asio::io_service::strand(reactor);
	starter(PropertyReactor::handler);
}

void PropertyReactor::stop() {
	quit = true;
	delete keeper;
	killer();
	delete strand;
	delete syncer;
}

void PropertyReactor::post(boost::function<void()> func) {
	strand->post(func);
}

void PropertyReactor::sync() {
	delete keeper;
	syncer->wait();
}

void PropertyReactor::defaultStarter(void(*handler)(void*)) {
	void* null = NULL;
	boost::function<void()> func(boost::bind(handler,null));
	thread = new boost::thread(func);
}

void PropertyReactor::defaultKiller() {
	thread->join();
	delete thread;
}

}
}
