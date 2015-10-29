#include "wrapper.hpp"

//repeats execute endlessly (or until something that changes the value of exitFlag occurs)
void Wrapper::runCleaner() {
	while(!timedCleanerExitFlag) {
		std::cout.flush();
		mutex.lock();
		try {
			tc->execute();
		}
		catch(std::exception &e) { //if exception was thrown, we need to remember to unlock the mutex
			std::cerr << e.what();
		}
		mutex.unlock();
		tc->sleep(); //everything as planned, Cleaner can go to sleep for a while
	}
}

//calls UI.execute() after each input
void Wrapper::runUI() {
	std::string s;	
	while(!UIExitFlag && std::cin >> s) {
		std::lock_guard <std::mutex> lock(mutex);
		ui->execute(s);
	}
}

//creates two threads and runs UI and TimedCleaner with them
void Wrapper::run() {
	std::thread interface(&Wrapper::runUI, this);
	std::thread cleaner(&Wrapper::runCleaner, this);
	cleaner.join();
	interface.join();
}

//need to free the memory we have allocated by calling new on UI and TimedCleaner
Wrapper::~Wrapper() {
	delete ui;
	delete tc;
}