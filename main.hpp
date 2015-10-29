#ifndef MAIN_HPP
#define MAIN_HPP

#include "lib/pqueue.hpp"
#include "lib/item.hpp"
#include "timedcleaner.hpp"
#include "ui.hpp"
#include "wrapper.hpp"
#include <vector>
#include <iostream>

#define STR_INPROPER_ARGS "usage (keep in mind that x < y < z must occur): ./demo x y z t\napplying the default values\n"

void unSyncCinCout();
void run();
void inproperArgs();
int main(int argc, char* argv[]);

#endif