#ifndef LINKEDPQUEUE_
#define LINKEDPQUEUE_


#include "PQNode.h"
#include "PairNode.h"
#include "PQueueADT.h"

template <typename T>
class LinkedPQueue :public PQueueADT<T>
{
private:

	PQNode<T>* backPtr;
	PQNode<T>* frontPtr;
	int count;

public:

	LinkedPQueue() {
		backPtr = nullptr;
		frontPtr = nullptr;
		count = 0;
	}

	LinkedPQueue(const LinkedPQueue<T>& obj) {

		frontPtr = nullptr;
		backPtr = nullptr;
		count = 0;
		PQNode<T>* p = obj.frontPtr;
		while (p) {
			enqueue(p->getItem());
			p = p->getNext();
		}
		return;
	}

	/*
	Function: isEmpty
	Sees whether this LinkedPqueue is empty.

	Input: None.
	Output: True if the LinkedPqueue is empty; otherwise false.
	*/
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	/*Function:enqueue
	Adds newEntry at the back of this LinkedPqueue.

	Input: newEntry .
	Output: True if the operation is successful; otherwise false.
	*/

	bool enqueue(const T& newEntry, const double& newPriority)
	{
		PQNode<T>* newNodePtr = new PQNode<T>(newEntry, newPriority);
		// Insert the new node
		if (isEmpty()) {	//special case if this is the first node to insert
			frontPtr = newNodePtr; // The LinkedPqueue is empty
			backPtr = newNodePtr; // new node inserted
			count++;
			return true;
		}
		else {
			if (frontPtr->getPri() > newPriority)
			{
				newNodePtr->setNext(frontPtr);
				frontPtr = newNodePtr;
				count++;
				return true;
			}

			PQNode<T>* p = frontPtr->getNext();
			PQNode<T>* q = frontPtr;

			while (p) {
				if (p->getPri() <= newPriority) {
					q = p;
					p = p->getNext();
				}
				else if (p->getPri() > newPriority) {
					newNodePtr->setNext(p);
					q->setNext(newNodePtr);
					count++;
					return true;
				}
			}

			q->setNext(newNodePtr);
			backPtr = newNodePtr;
			count++;
			return true;
		}
	} // end enqueue

	/*Function: dequeue
	Removes the front of this LinkedPqueue. That is, removes the item that was added
	earliest.

	Input: None.
	Output: True if the operation is successful; otherwise false.
	*/

	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		PQNode<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// LinkedPqueue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the LinkedPqueue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;
	}
	T* toArray(int& numElements) {
		//returns array of T (array if items) //////////////////NOT IN ADT????????????????
		{
			numElements = count;

			if (!frontPtr)
				return nullptr;
			//counting the no. of items in the pQueue
			PQNode<T>* p = frontPtr;
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

	/*
	Function: peek
	copies the front of this LinkedPqueue to the passed param. The operation does not modify the LinkedPqueue.

	Input: None.
	Output: The front of the LinkedPqueue.
	*/

	bool peek(T& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		
		return true;

	}
	bool peek(T& frntEntry, int& pri) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		pri = frontPtr->getPri();
		return true;

	}
	~LinkedPQueue()
	{
		//Free all nodes in the LinkedPqueue
		T temp;
		while (dequeue(temp));
	}
};

#endif