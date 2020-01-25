#ifndef PQUEUEPAIR_ADT_
#define PQUEUEPAIR_ADT_

template<class T, class N>
class PQueuePairADT
{
public:
	/** Sees whether this queue is empty.
	 @return  True if the queue is empty, or false if not. */
	virtual bool isEmpty() const = 0;

	/** Adds a new entry to this queue according to priority.
	 @post  If the operation was successful, newEntry is at the
		back of the queue.
	 @param newEntry  The object to be added as a new entry.
	 @return  True if the addition is successful or false if not. */
	virtual bool enqueue(const T& newCook, const N& newOrder, int newPriorityy) = 0;

	/** Copies the front item of the queue to the passed parameter and removes it from queue
	 @post  If the operation was successful, the front of the queue
		would be copied to FrontEntry parameter and removed from the queue.
	 @return  True if the removal is successful or false if not. */
	virtual bool dequeue(T& frntCook, N& frntOrder, int& pri) = 0;

	/** Copies the front item of the queue to the passed parameter without removing it from queue
	 @pre  The queue is not empty.
	 @post  The front of the queue has been copied to FrontEntry param , and the
		queue is unchanged.
	 @return  The front of the queue. */
	virtual bool peek(T& frntCook, N& frntOrder, int& pri) const = 0;
	virtual T* CooktoArray(int& numElements)=0;
	virtual N* OrdertoArray(int& numElements) = 0;
	/** Destroys this queue and frees its memory. */
	virtual ~PQueuePairADT() { }
}; // end PQueueADT
#endif
