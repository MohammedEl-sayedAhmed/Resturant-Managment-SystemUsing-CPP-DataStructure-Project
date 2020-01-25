#ifndef LINKEDPQUEUEPAIR_
#define LINKEDPQUEUEPAIR_


#include "PairNode.h"
#include "PQueuePairADT.h"

template <typename T, typename N>
class LinkedPQueuePair :public PQueuePairADT<T,N>
{
private:

	PairNode<T,N>* backPtr;
	PairNode<T, N>* frontPtr;
	int count;

public:

	LinkedPQueuePair() {
		backPtr = nullptr;
		frontPtr = nullptr;
		count = 0;
	}

	LinkedPQueuePair(const LinkedPQueuePair<T,N>& obj) {

		frontPtr = nullptr;
		backPtr = nullptr;
		count = 0;
		PairNode<T,N>* p = obj.frontPtr;
		while (p) {
			enqueue(p->getCook(),p->getOrder(), p->getPri());
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

	
	bool enqueue(const T& newCook, const N& newOrder, int newPriority)
	{
		PairNode<T, N>* newNodePtr = new PairNode<T, N>(newCook, newOrder,newPriority);
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

			PairNode<T,N>* p = frontPtr->getNext();
			PairNode<T,N>* q = frontPtr;

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

	bool dequeue(T& frntCook, N& frntOrder, int& pri)
	{
		if (isEmpty())
			return false;

		PairNode<T, N>* nodeToDeletePtr = frontPtr;
		frntCook = frontPtr->getCook();
		frntOrder = frontPtr->getOrder();
		pri = frontPtr->getPri();
		frontPtr = frontPtr->getNext();
		// LinkedPqueue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the LinkedPqueue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;
	}

	/*
	Function: peek
	copies the front of this LinkedPqueue to the passed param. The operation does not modify the LinkedPqueue.

	Input: None.
	Output: The front of the LinkedPqueue.
	*/

	bool peek(T& frntCook, N&frntOrder, int& pri) const
	{
		if (isEmpty())
			return false;

		frntCook = frontPtr->getCook();
		frntOrder = frontPtr->getOrder();
		pri = frontPtr->getPri();

		return true;

	}

	T* CooktoArray(int& numElements) {
		//returns array of T (array if items) //////////////////NOT IN ADT????????????????
		{
			numElements = count;

			if (!frontPtr)
				return nullptr;
			//counting the no. of items in the pQueue
			PairNode<T,N>* p = frontPtr;
			while (p)
			{
				p = p->getNext();
			}


			T* Arr = new T[count];
			p = frontPtr;
			
			for (int i = 0; i < count; i++)
			{
				Arr[i] = p->getCook();
				p = p->getNext();
			}
			return Arr;
		}
	}
	N* OrdertoArray(int& numElements) {
		
		{
			numElements = count;

			if (!frontPtr)
				return nullptr;
			//counting the no. of items in the pQueue
			PairNode<T, N>* p = frontPtr;
			while (p)
			{
				p = p->getNext();
			}


			N* Arr = new N[count];
			p = frontPtr;

			for (int i = 0; i < count; i++)
			{
				Arr[i] = p->getOrder();
				p = p->getNext();
			}
			return Arr;
		}
	}	
	~LinkedPQueuePair()
	{
		//Free all nodes in the LinkedPqueue
		T tempC;
		N tempO;
		int tempP;
		while (dequeue(tempC, tempO, tempP));
	}
};

#endif
