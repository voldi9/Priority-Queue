#include "item.hpp"

//returns current time since EPOCH in miliseconds
ull getCurrentTime() {
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	ull currentTime = (ull) spec.tv_sec * 1000 + (spec.tv_nsec / 1e6);
	return currentTime;
}

//comparator between items
bool Item::operator<(Item other) const {
	if(priority != other.getPriority())
		return priority > other.getPriority(); //higher priority takes the precedence
	return timeAdded < other.getTimeAdded(); //FIFO
}

//returns the priority of a given item as string
std::string Item::getPriorityString() {
	switch(priority) {
		case 0: return "high";
		case 1: return "medium";
		case 2: return "low";
		default: throw std::runtime_error(STR_UNKNOWN_PRIORITY);
	}
}

//returns the timeout of a given item as string
std::string Item::getTimeoutString() {
	switch(timeout) {
		case 0: return "short";
		case 1: return "medium";
		case 2: return "long";
		default: throw std::runtime_error(STR_UNKNOWN_TIMEOUT);
	}
}

//returns the time elapsed since that item has been created, in miliseconds
ull Item::timeElapsed() {
	return getCurrentTime() - timeAdded;
}

bool Item::isFaulty() {
	return (priority == -1 && timeout == -1);
}

#include <iostream>
void Item::print() {
	std::cout << "priority: " << getPriorityString() << ", timeout: " << getTimeoutString() 
				<< ", added " << round((float) timeElapsed() / 100.) / 10. << " seconds ago\n";
}