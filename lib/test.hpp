#ifndef TEST_HPP
#define TEST_HPP

#include "item.hpp"
#include "pqueue.hpp"
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <string>
#include <algorithm>
#include <random>
#define STR_FAULTY_ITEM "Faulty item test"
#define STR_EMPTY_QUEUE_DELETION "Empty queue deletion test"
#define STR_ADD_POP "Adding and then popping test"
#define STR_REMOVING_TIMEDOUT "Adding items and then removing the timedout ones test"

typedef int (*TestingFunction) (); //the testing function type

int testFaultyItem();
int testEmptyPqueue();
int testAddPop();
int testRemovingTimedout();
void printOK();
void printFailure();
void testFunction(TestingFunction function, std::string output);
int main();

#endif