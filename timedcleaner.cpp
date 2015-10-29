#include "timedcleaner.hpp"

//removes the top item of the pqueue (if there is any) and prints it
//to the standard output
void TimedCleaner::removeTop() {
	if(pqueue->empty()) //we do not want to delete anything from an empty pqueue
		return;
	Item top = pqueue->popTop();
	if(!top.isFaulty()) {
		std::cout << STR_REMOVED_TOP;
		top.print();
	}
}


//removes all the timedout items from the pqueue and prints them to the
//standard output
void TimedCleaner::removeTimedout() {
	std::vector <Item> deleted = pqueue->removeAllTimedout();
	if(!deleted.empty()) {
		std::cout << STR_REMOVED_TIMEDOUT;
	}
	for(auto item : deleted) {
		std::cout << TAB; //printing horizontal tab for readability
		item.print();
	}
}

//puts the thread to sleep for an interval (thus the name: TIMED cleaner)
void TimedCleaner::sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(interval));
}

//performs cleaning, that is removes the top item and all the obsolete
//items, prints all of them to the standard output. It also makes sure that
//all the output is given at the same time by flushing cerr and cout
void TimedCleaner::execute() {
		removeTop(); //if this throws empty queue exception, we dont have to take care of it at this level, as
		removeTimedout(); //this makes no sense on an empty queue either
		std::cout.flush();
		std::cerr.flush();
}