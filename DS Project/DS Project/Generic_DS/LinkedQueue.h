#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_


#include "Node.h"
#include "QueueADT.h"


template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;

public:

	LinkedQueue() {
		backPtr = nullptr;
		frontPtr = nullptr;
		count = 0;
	}

	LinkedQueue(const LinkedQueue<T>& obj) {

		frontPtr = nullptr;
		backPtr = nullptr;
		count = 0;
		Node<T>* p = obj.frontPtr;
		while (p) {
			enqueue(p->getItem());
			p = p->getNext();
		}
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////////

	/*
	Function: isEmpty
	Sees whether this queue is empty.

	Input: None.
	Output: True if the queue is empty; otherwise false.
	*/
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	/*Function:enqueue
	Adds newEntry at the back of this queue.

	Input: newEntry .
	Output: True if the operation is successful; otherwise false.
	*/

	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			frontPtr = newNodePtr; // The queue is empty
		else
			backPtr->setNext(newNodePtr); // The queue was not empty

		backPtr = newNodePtr; // New node is the last node now
		count++;
		return true;
	} // end enqueue

	int getCount() const {
		return count;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Function: dequeue
	Removes the front of this queue. That is, removes the item that was added
	earliest.

	Input: None.
	Output: True if the operation is successful; otherwise false.
	*/

	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;

	}




	/*
	Function: peek
	copies the front of this queue to the passed param. The operation does not modify the queue.

	Input: None.
	Output: The front of the queue.
	*/

	bool peekFront(T& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;

	}

	T* toArray(int& numElements) {
		//returns array of T (array if items) //////////////////NOT IN ADT????????????????
		{
			numElements = count;

			if (!frontPtr)
				return nullptr;
			//counting the no. of items in the Queue
			Node<T>* p = frontPtr;
			while (p)
			{
				p = p->getNext();
			}


			T* Arr = new T[count];
			p = frontPtr;
			for (int i = 0; i < count; i++)
			{
				Arr[i] = p->getItem();
				p = p->getNext();
			}
			return Arr;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////

	~LinkedQueue()
	{
		// free all nodes in the queue
		T temp;
		while (dequeue(temp));
	}
};

#endif