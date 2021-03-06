#include "item.hpp"

//returns current time since EPOCH in milliseconds
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
		default: return "unknown";
	}
}

//returns the timeout of a given item as string
std::string Item::getTimeoutString() {
	switch(timeout) {
		case 0: return "short";
		case 1: return "medium";
		case 2: return "long";
		default: return "unknown";
	}
}

//returns the time elapsed since that item has been created, in milliseconds
ull Item::timeElapsed() {
	return getCurrentTime() - timeAdded;
}

//checks if the given item is an artificial one, meaning and item that is
//supposed to make no sense
bool Item::isFaulty() {
	return (priority == -1 && timeout == -1);
}

//prints some info about the item to the standard output
void Item::printWithoutTime() {
	std::cout << "priority - " << getPriorityString() << ", timeout - " << getTimeoutString() << "\n";
}

//prints the same info as printWithoutTime() but also the time since addition
void Item::print() {
	std::cout << "priority - " << getPriorityString() << ", timeout - " << getTimeoutString() 
				<< ", added " << round((float) timeElapsed() / 100.) / 10. << " seconds ago\n";
}