#ifndef TIMEDCLEANER_HPP
#define TIMEDCLEANER_HPP

#include "lib/item.hpp"
#include "lib/pqueue.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

//the class is responsible for removing the top item as well as
//all timedout items from the pqueue every interval (in milliseconds
//it also prints to the standard output all those items
class TimedCleaner {
	private:
		Pqueue* pqueue;
		unsigned interval;
		int exitFlag;
	public:
		void run();
		void removeTop();
		void removeTimedout();
		TimedCleaner(Pqueue* pq, unsigned i) :
			pqueue(pq),
			interval(i),
			exitFlag(0) {}
};

#endif