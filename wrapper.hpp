#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include "lib/item.hpp"
#include "lib/pqueue.hpp"
#include "ui.hpp"
#include "timedcleaner.hpp"
#include <thread>
#include <mutex>


//A simple wrapper that binds together UI and TimedCleaner that work on the same Pqueue
//and puts their work to order (e.g. provides a mutex so there is no undefined behavior)
class Wrapper {
	private:
		UI *ui;
		TimedCleaner *tc;
		int timedCleanerExitFlag;
		int UIExitFlag;
		void runCleaner();
		void runUI();
	public:
		std::mutex mutex;
		Wrapper(Pqueue *pqueue) :
			ui(new UI(pqueue)),
			tc(new TimedCleaner(pqueue)),
			timedCleanerExitFlag(0),
			UIExitFlag(0) {}
		Wrapper(Pqueue *pqueue, int interval) : //we can pass interval for the TimedCleaner to the constructor of Wrapper
			ui(new UI(pqueue)),
			tc(new TimedCleaner(pqueue, interval)),
			timedCleanerExitFlag(0),
			UIExitFlag(0) {}
		~Wrapper();
		void run();
};

#endif