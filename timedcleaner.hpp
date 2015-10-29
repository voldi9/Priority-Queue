#ifndef TIMEDCLEANER_HPP
#define TIMEDCLEANER_HPP

#include "pqueue.hpp"
#include "item.hpp"

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