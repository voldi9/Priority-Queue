#include "main.hpp"

//those commands untie the cin and cout from each other,
//which, since we have one thread for outputting and another
//for inputting, enables us to skip the I/O mutex
//
//IMPORTANT: after calling this, we need to remember to execute 
//cout.flush() ourselves though!
void unSyncCinCout() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cerr.tie(nullptr);
}

//called when the user has give proper arguments
void run(std::vector <int> &args) {
	Pqueue pqueue = Pqueue(args[0], args[1], args[2]);
	Wrapper wrapper(&pqueue, args[3]);
	wrapper.run();
}


//called when the given arguments were not accepted and the defaults were applied
void inproperArgs() {
	std::cout << STR_INPROPER_ARGS;
	Pqueue pqueue = Pqueue();
	Wrapper wrapper(&pqueue);
	wrapper.run();
}

int main(int argc, char* argv[]) {

	unSyncCinCout();

	if(argc != 5){
		inproperArgs();
	}
	else {
		std::vector <int> args;
		std::for_each(argv + 1, argv + argc, [&](char* arg) {
			int a;
			if(sscanf(arg, "%u", &a) == 1) {
				args.push_back(a * 1000);
			}
			else {
				inproperArgs();
				return 0;
			}
		});
		if(args[0] < args[1] && args[1] < args[2]) {
			run(args);
		}
		else {
			inproperArgs();
		}
	}
	return 0;
}