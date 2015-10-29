#ifndef TIMEDCLEANER_HPP
#define TIMEDCLEANER_HPP

#include "lib/item.hpp"
#include "lib/pqueue.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#define STR_REMOVED_TOP "Removed top item: "
#define STR_REMOVED_TIMEDOUT "Removed the following timedout items:\n"
#define TAB char(9)
#define DEFAULT_INTERVAL 10000 //default interval between calling execute() functions in milliseconds


class TimedCleaner {
	private:
		Pqueue *pqueue;
		unsigned interval;
		void removeTop();
		void removeTimedout();
	public:
		TimedCleaner(Pqueue *pq) :
			pqueue(pq),
			interval(DEFAULT_INTERVAL) {}
		TimedCleaner(Pqueue *pq, unsigned i) :
			pqueue(pq),
			interval(i) {}
		void sleep();
		void execute();
};

#endif