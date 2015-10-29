#include "main.hpp"

//those commands untie the cin and cout from each other,
//which, since we have one thread for outputting and another
//for inputting, enables us to skip the I/O mutex
//
//IMPORTANT: in that case, we need to remember to execute 
//cout.flush() ourselves though!
void unSyncCinCout() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cerr.tie(nullptr);
}

void runCleaner(TimedCleaner *tc) {
	tc->run();
}

int main() {
	std::cout << "OK!!\n";
	unSyncCinCout();
	Pqueue pq = Pqueue();

	TimedCleaner tc = TimedCleaner(&pq, 3000);
	std::thread cleaner(runCleaner, &tc);
	int a;
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
				std::vector <Item> vec = pq.removeAllTimedout();
				for(auto item : vec) {
					item.print();
				}
				break;
		}
		pq.print();
		std::cout.flush();
	}
	//bool b = item < Item(0, 5);
	//std::cout << item.getPriorityString() << " " << b << " " << sizeof(Item) / sizeof(int) << "\n";
	return 0;
}