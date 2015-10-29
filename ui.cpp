#include "ui.hpp"

//according to README, the {{q, w, e}, {a, s, d}, {z, x, c}} matrix
//is mapping those keys to the different <priority, timeout> values
//stored as integer: NUM_TIMEOUTS * priority + timeout
int UI::mapCharToInt(char c) {
	int x;
	auto it = std::find(mapIntToKey.begin(), mapIntToKey.end(), c);
	
	//if key not found, returning a faulty item
	if(it == mapIntToKey.end())
		return -1;
	x = it - mapIntToKey.begin();
	return x;
}


//returns an item corresponding to x = NUM_TIMEOUTS * priority + timeout
Item UI::createItem(char c) {
	int x = mapCharToInt(c);
	//something went wrong, returning a faulty item
	if(x == -1)
		return Item(-1, -1);
	return Item(x / pqueue->numTimeouts, x % pqueue->numTimeouts);
}

//takes care of the input string
void UI::execute(std::string s) {
	if(s.length() != 1){ //string is not a single-character
		std::cerr << STR_INPUT_NOT_A_CHAR;
	}
	else {
		Item item = createItem(s[0]);
		if(item.isFaulty()) {
			if(s[0] == printPqueueChar) {
				pqueue->print();
			}
			else {
				std::cerr << STR_UNKNOWN_CHARACTER;
			}
		}
		else { //input character was correct, we add the item to the Pqueue and print its info
			pqueue->addItem(item);
			std::cout << STR_ADDED_ITEM;
			item.printWithoutTime();
		}
	}
	//if anything is to be outputted, do it now
	std::cerr.flush();
	std::cout.flush();
}
