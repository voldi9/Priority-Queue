#include "timedcleaner.hpp"


void TimedCleaner::removeTop() {
	Item top = pqueue->popTop();
}

void TimedCleaner::removeTimedout() {

}

void TimedCleaner::run() {
	while(!exitFlag) {
		removeTop();
		removeTimedout();
	}	
}


