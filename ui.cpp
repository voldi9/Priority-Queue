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
	return Item(x / NUM_TIMEOUTS, x % NUM_TIMEOUTS);
}

void UI::run() {

}