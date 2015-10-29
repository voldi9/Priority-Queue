#ifndef PQUEUE_HPP
#define PQUEUE_HPP

#include "item.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>


#define STR_INVALID_DELETION "Error while trying to delete item - "
#define STR_INVALID_GET "Error while trying to get item - "
#define STR_INVALID_ADD "Error while trying to add an item - "
#define STR_INVALID_PRIORITY "Item's priority out of bounds\n"
#define STR_INVALID_TIMEOUT "Item's timeout out of bounds\n"
#define STR_PQUEUE_EMPTY "The priority queue is empty\n"
#define STR_PQUEUE_FULL "The priority queue is full\n"
#define MAX_ITEMS 1000000 //max number of items in the queue at a given time
#define NUM_PRIORITIES 3
#define NUM_TIMEOUTS 3
#define DEFAULT_TIMEOUTS 5000, 10000, 15000 //default timeout values in milliseconds

enum Priority { HIGH, MEDIUM, LOW };
enum Timeout { SHORT, LONG = 2 }; //medium is 1 in both of enums


//the class represents a priority queue with 3 different priorities and 3 timeouts
//it is highly flexible though, in case we needed to adjust those numbers keep in
//mind though: actions like addItem() or popTop() take O(n * m) time where n and m
//are number of timeouts and priorities, respectively, so we might want to change
//the approach to work on two sets instead of queues if those numbers grow too big
//and thus make those complexities O(log k), where k is the number of items present 
//in the pqueue 
class Pqueue {
	private:
		//each queue represents one of the priorities-timeouts combination
		std::queue <Item> itemsByProperties[NUM_PRIORITIES][NUM_TIMEOUTS]; //FIFO queues
		unsigned timeoutTimes[NUM_TIMEOUTS]; //time for each timeout in milliseconds
	public:
		const unsigned numPriorities, numTimeouts; //this is const, so can be public so we can acces it easily
		Pqueue() :
			numPriorities(NUM_PRIORITIES),
			numTimeouts(NUM_TIMEOUTS),
			timeoutTimes{DEFAULT_TIMEOUTS} {}
		Pqueue(unsigned s, unsigned m, unsigned l) : //this can of course be changed to more flexible (more than 3 timeouts)
			numPriorities(NUM_PRIORITIES),
			numTimeouts(NUM_TIMEOUTS),
			timeoutTimes{s, m, l} {}
		void addItem(Item item);
		int count();
		bool empty();
		Item popTop();
		std::vector <Item> removeAllTimedout();
		int timeTillTimeout(Item item);
		bool reachedTimeout(Item item);
		void print();
};

#endif