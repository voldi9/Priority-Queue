#ifndef UI_HPP
#define UI_HPP

#include "lib/item.hpp"
#include "lib/pqueue.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>


#define STR_UNKNOWN_CHARACTER "The character '" + s + "' does not match any of the supported\n"
#define STR_INPUT_NOT_A_CHAR "The command must be a single character\n"
#define STR_ADDED_ITEM "Added item: "
#define DEFAULT_PRINT_PQUEUE_CHAR 'p'
#define DEFAULT_KEYS 'q', 'w', 'e', 'a', 's', 'd', 'z', 'x', 'c'

class UI {
	private:
		Pqueue *pqueue;
		std::vector <int> mapIntToKey;
		const char printPqueueChar;
		int mapCharToInt(char c);
		Item createItem(char c);
	public:
		UI(Pqueue *pq) :
			pqueue(pq),
			printPqueueChar(DEFAULT_PRINT_PQUEUE_CHAR),
			mapIntToKey({DEFAULT_KEYS}) {}
		void execute(std::string s);
};

#endif