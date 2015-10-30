#include "test.hpp"

//performing some checks on a faulty item
int testFaultyItem() {
	Item item = Item(-1, -1);
	assert(item.isFaulty());
	assert(item.getPriorityString() == std::string("unknown"));
	assert(item.getTimeoutString() == std::string("unknown"));
	return 0;
}


//trying to pop something from empty queue
int testEmptyPqueue() {
	Pqueue pqueue = Pqueue();
	assert(pqueue.count() == 0);
	assert(pqueue.empty());
	try {
		pqueue.popTop();
	}
	catch(std::runtime_error &e) { //there SHOULD occur this exception
		assert(pqueue.count() == 0);
		assert(pqueue.empty());
		return 0;
	}
	return 1;
}

int testAddPop() {
	Pqueue pqueue = Pqueue();
	std::random_device device;
    std::mt19937 twister(device());
    std::uniform_int_distribution <int> generator(-1, 2 * std::max(NUM_PRIORITIES, NUM_TIMEOUTS)); //also checking the out-of-bounds timeout / priority values
	int numTests = 1000; //how many items we add / delete from the queue
	int numItems = 0; //how many items are currently in the queue
	for(int i = 0; i < numTests; i++) { //trying to add element to the pqueue
		numItems += pqueue.addItem(Item(generator(twister), generator(twister)));
		assert(pqueue.count() == numItems);
	}

	while(numItems--) { //deleting all the items
		pqueue.popTop();
		assert(pqueue.count() == numItems);
	}

	assert(pqueue.empty());
	return 0;
}


//TODO
int testRemovingTimedout() {
	Pqueue pqueue = Pqueue();
	std::random_device device;
    std::mt19937 twister(device());
    //in here, we will only test items with proper timeout / priority values
    std::uniform_int_distribution <int> generator(0, 2); 
	int timeouts[] = {DEFAULT_TIMEOUTS}; //we assume we have taken the default timeouts
 	int numTimeouts[sizeof(timeouts) / sizeof(int)]
 	//for(int i = 0; i<)
	return 0;
}

void printOK() {
	std::cout << "OK\n";
}

void printFailure() {
	std::cout << "FAILED\n";
}

//calling the given testing function and checking if it returns 0
//printing the output so that we know what happened
void testFunction(TestingFunction function, std::string output) {
	std::cout << output << ": ";
	if(!function()) {
		printOK();
	}
	else {
		printFailure();
	}
}


//PLEASE TEST THIS WITH THE 2> (error output) going elsewhere than the standard output
//as there will be multiple errors printed and they might greatly decrease readability
//(although the errors ARE intended to occur)
int main() {
	//functions to test (must be of type int and take 0 arguments) paired with the strings to output for each
	//also every function should return 0 if testing was succesful
	std::pair<TestingFunction, std::string> functions[] = {
		std::make_pair(testFaultyItem, std::string(STR_FAULTY_ITEM)),
		std::make_pair(testEmptyPqueue, std::string(STR_EMPTY_QUEUE_DELETION)),
		std::make_pair(testAddPop, std::string(STR_ADD_POP)),
	};

	//testing all the functions
	for(auto f : functions) {
		testFunction(f.first, f.second);
	}

	return 0;
}