#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <sys/time.h>
#include <math.h>
#include <iostream>

#define STR_UNKNOWN_PRIORITY "Unknown priority: \n"
#define STR_UNKNOWN_TIMEOUT "Unknown timeout: \n"

typedef unsigned long long ull;

ull getCurrentTime();

class Item {
	private:
		int priority;
		int timeout;
		ull timeAdded;
	public:
		Item(int p, int t) :
			priority(p),
			timeout(t) {}
		bool operator<(Item other) const;
		void setTimeAdded(ull t) { timeAdded = t; }
		int getPriority() { return priority; }
		int getTimeout() { return timeout; }
		ull getTimeAdded() { return timeAdded; } 
		ull timeElapsed();
		std::string getPriorityString();
		std::string getTimeoutString();
		bool isFaulty();
		void printWithoutTime();
		void print();
};

#endif