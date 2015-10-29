#include "pqueue.hpp"

#include <iostream>

//returns the number of items currently in the priority queue
int Pqueue::count() {
	int count = 0;
	for(auto queuesRow : itemsByProperties) {
		std::for_each(queuesRow, queuesRow + NUM_TIMEOUTS, [&](std::queue<Item> queue) {
			count += (int) queue.size();
		});
	}
	return count;
}

//adds item to pqueue
void Pqueue::addItem(Item item) {
	int p = item.getPriority();
	int t = item.getTimeout();
	
	if(count() >= MAX_ITEMS) {
		std::cerr << STR_INVALID_ADD << STR_PQUEUE_FULL;
	}
	//it might be, that the priority or timeout was somehow set out of bounds
	if(p < 0 || p >= NUM_PRIORITIES) {
		std::cerr << STR_INVALID_PRIORITY;
	}
	else if(t < 0 || t >= NUM_TIMEOUTS) {
		std::cerr << STR_INVALID_TIMEOUT;
	}
	else {

		//mutex!!!
		item.setTimeAdded(getCurrentTime());
		itemsByProperties[p][t].push(item);
	}
}


//determines whether the pqueue is empty
bool Pqueue::empty() {
	for(auto &queuesRow : itemsByProperties) {
		for(auto &queue : queuesRow) {
			if(!queue.empty()){
				return false;
			}
		}
	}
	return true;
}


//returns the top element of Pqueue and deletes it (many of the STL containers' deletion methods return the deleted item,
//I decided to do so as well). If pqueue is empty prints error and returns faulty Item with both priority and timeout set to -1
Item Pqueue::popTop() {
	//due to FIFO rule, the Top item might be any of the fronts of queues with the highest priority that exists
	//in the pqueue (it is in fact the one with the lowest timeAdded)
	std::queue <Item> *candidate = NULL; //points to the queue, front of which is the current candidate for top

	for(auto &queuesRow : itemsByProperties) {
		for(auto &queue : queuesRow) { //searching queues representing the same priority for lowest timeAdded items
			if(!queue.empty()) {
				if(!candidate || candidate->front().getTimeAdded() > queue.front().getTimeAdded()) {
					candidate = &queue;
				}
			}
		}
		if(candidate) { //if we found any item with this priority, we are satisfied and might end
			Item returnedItem = candidate->front();
			candidate->pop();
			return returnedItem;
		}
	}
	std::cerr << STR_INVALID_DELETION << STR_PQUEUE_EMPTY;
	return Item(-1, -1);
}

/*
//deletes item from the pqueue and returns whether it was succesful
bool Pqueue::popTop() {
	int lta;
	std::queue <Item> *candidate; //stores the list, front of which has the current candidate for top item
	for(auto &queuesRow : itemsByProperties) {
		lta = -1;
		for(auto &queue : queuesRow) {
			if(!queue.empty()) {
				if(lta == -1 || lta > queue.front().getTimeAdded()) {
					candidate = &queue;
					lta = queue.front();
				}
			}
		}
		if(lta != -1) {
			candidate->pop();
			return true;
		}
	}
	std::cerr << STR_INVALID_DELETION << STR_PQUEUE_EMPTY;
	return false;
}
*/

//deletes the items that have reached their timeout, returns a list containing them
std::vector <Item> Pqueue::deleteAllTimedout() {
	std::vector <Item> deleted;
	for(auto &queuesRow : itemsByProperties) {
		for(auto &queue : queuesRow) {
			//the decision to call getCurrentTime function for each item
			//separately is sane, as it assures as much accuracy as possible
			//and the function itself is very fast and simple
			while(!queue.empty() && reachedTimeout(queue.front())) {
				deleted.push_back(queue.front());
				queue.pop();
			}
		}
	}
	return deleted;
}



//returns how much time does the given item have until timeout
int Pqueue::timeTillTimeout(Item item) {
	return int((ull) timeoutTimes[item.getTimeout()] -  item.timeElapsed());
}

//checks whether the given item has reached its timeout
bool Pqueue::reachedTimeout(Item item) {
	return timeTillTimeout(item) <= 0;
}


//function used for debugging purposes
void Pqueue::print() {
	int i = 0;
	std::cout << "count: " << count() << "\n";
	for(auto queue : itemsByProperties) {
		std::cout << "priority " << Priority(i++) << ": " << queue[0].size() + queue[1].size() + queue[2].size() << "\n";
	}
}


int main() {
	//Item item = Item(1, 3);
	Pqueue pq = Pqueue();
	//pq.addItem(item);
	int a;
	//pq.print();
	int c = 0;
	Item popped = Item(-1, -1);
	while(std::cin >> a) {
		switch(a) {
			case 0:
				popped = pq.popTop();
				if(!popped.isFaulty()) {
					std::cout << "delete succesful: ";
					popped.print();
					//std::cout << "\n";
					pq.print();
				}
				else {
					std::cout << "mistakes were made\n";
				}
				break;
			case 1:
				pq.addItem(Item(0, 0));
				break;
			case 2:
				pq.addItem(Item(1, 2));
				break;
			case 3:
				pq.addItem(Item(2, 1));
				break;
			case 4:
				std::vector <Item> vec = pq.deleteAllTimedout();
				for(auto item : vec) {
					item.print();
				}
				break;
		}
		pq.print();
	}
	//bool b = item < Item(0, 5);
	//std::cout << item.getPriorityString() << " " << b << " " << sizeof(Item) / sizeof(int) << "\n";
}