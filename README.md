A Priority Queue library (libpqueue) whose items can have three possible timeout values (short, medium and long) and three priorities (high, medium, low) for the queue elements. So, 9 combinations in total. The Item class implements the items that are stored in the queue. The Pqueue implements the queue itself. It consists of 9 FIFO queues, each for one combination of item's properties. The code of Pqueue is highly flexible in case we want to change the number of priorities (not recommended for too big values though, say 1000x1000). 
As for the example application: the Wrapper class wraps together UI and TimedCleaner, runs them concurrently and keeps their work in order with a mutex since both use the same PQueue. The TimedCleaner deletes the top item and all the items that have reached their timeout. The UI class takes care of the input and adds the items the user wants it to to the standard output. In general, the complexity is (n - number of priorities, m - number of timeout values, t - number of elements that have reached their timeout):
empty(), count(), addItem(), popTop() - O(n * m)
removeAllTimedout() - O(t + n * m)

Manual:
	there is a makefile in both lib directory and main directory. The 'main' makefile triggers the lib makefile just in case.
	We launch the application by typing: ./demo x y z t, where: (x, y, z) are the three timeout values, in ascending order,
	and t is the interval value between TimedCleaner performes next removal from Pqueue. All 4 values should be put in seconds.
	If something is wrong with the arguments, then the default values are applied (5s, 10s, 15s) timeouts and TimedCleaner executes
	every 10s.
	We input items with the square matrix of keys: q,w,e (priority - high); a,s,d (priority - medium); z,x,c (priority low), in
	each row the timeout values are ascending, so q,a,z are short, w,s,x - medium and e,d,c - long timeout values. At any moment
	we can type in 'p' to print the count() and a little matrix visualizing the Pqueue.