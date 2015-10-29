#include "timedcleaner.hpp"

//removes the top item of the pqueue (if there is any) and prints it
//to the standard output
void TimedCleaner::removeTop() {
	Item top = pqueue->popTop();
	if(!top.isFaulty()) {
		std::cout << "deleted top item: ";
		top.print();
	}
}


//removes all the timedout items from the pqueue and prints them to the
//standard output
void TimedCleaner::removeTimedout() {
	std::vector <Item> deleted = pqueue->removeAllTimedout();
	if(!deleted.empty()) {
		std::cout << "removed timedout items:\n";
	}
	for(auto item : deleted) {
		item.print();
	}
}

//performs cleaning, that is removes the top item and all the obsolete
//items, prints all of them to the standard output and then sleeps
//for a time equal to interval milliseconds. It does that until the exitFlag
//is set for non-zero value or is terminated by user
void TimedCleaner::run() {
	while(!exitFlag) {
		removeTop();
		removeTimedout();
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
	}	
}
