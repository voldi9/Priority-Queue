#ifndef UI_HPP
#define UI_HPP

#include "lib/item.hpp"
#include "lib/pqueue.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

#define DEFAULT_KEYS 'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'

class UI {
	private:
		std::vector <int> mapIntToKey;
		int mapCharToInt(char c);
	public:
		UI() :
			mapIntToKey({DEFAULT_KEYS}) {}
		Item createItem(char c);
		void run();
};

#endif