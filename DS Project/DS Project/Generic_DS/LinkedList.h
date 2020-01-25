#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include "../Rest/Order.h"

template <typename T>
class LinkedList
{
private:

	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list

public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {

		if (Head == nullptr) {
			InsertBeg(data);
			return;
		}
		else {
			Node<T>* p = Head;
			while (p->getNext()) {
				p = p->getNext();
			}
			Node<T>* R = new Node<T>(data);
			p->setNext(R);
			count++;
			return;

		}

	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key) {
		Node<T>* p = Head;
		while (p) {
			if (p->getItem() == Key) {
				return true;
			}
			p = p->getNext();
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) {
		int occs = 0;
		Node<T>* p = Head;
		while (p) {
			if (p->getItem() == value) {
				occs++;
			}
			p = p->getNext();
		}
		return occs;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	bool DeleteFirst(T& frntEntry) {
		if (Head) {
			Node<T>* p = Head->getNext();
			//delete Head;
			frntEntry = Head->getItem();
			Head = p;
			count--;
			return true;
		}
		return false;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		if (Head == nullptr) {
			return;
		}
		else if (Head->getNext() == nullptr) {
			DeleteFirst();
			return;
		}
		else {
			Node<T>* p = Head;
			Node<T>* q = p->getNext();
			while (q->getNext()) {
				p = q;
				q = p->getNext();
			}
			delete q;
			p->setNext(nullptr);
			count--;
			return;

		}
	}

	bool DeleteNode(Order*& const value, Order*& deletedOrder) {
		if (!Head) {
			return false;
		}

		if (*value == *(Head->getItem())) {
			T deletedOrder;
			DeleteFirst(deletedOrder);
			return true;
		}
		Node<T>* p = Head;
		Node<T>* q = p->getNext();

		while (q) {
			if (*value == *(q->getItem())) {
				p->setNext(q->getNext());
				deletedOrder = q->getItem();
				count--;
				return true;
			}
			p = q;
			q = p->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value) {
		if (Head == nullptr) { return false; }
		bool flag = false;
		while (Head->getItem() == value) {
			DeleteFirst();
			flag = true;
		}
		Node<T>* p = Head;
		while (p->getNext()) {
			if ((p->getNext())->getItem() == value) {
				Node<T>* R = (p->getNext())->getNext();
				delete p->getNext();
				p->setNext(R);
				flag = true;
				count--;

			}
			else {
				p = p->getNext();
			}
		}
		return flag;
	}

	T* toArray(int& numElements) {
		//returns array of T (array if items) //////////////////NOT IN ADT????????????????
		{
			numElements = count;

			if (!Head)
				return nullptr;
			//counting the no. of items in the Queue
			Node<T>* p = Head;
			while (p)
			{
				p = p->getNext();
			}


			T* Arr = new T[count];
			p = Head;
			for (int i = 0; i < count; i++)
			{
				Arr[i] = p->getItem();
				p = p->getNext();
			}
			return Arr;
		}
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	Node<T>* getHead() const {
		return Head;
	}

	int getCount() {
		return count;
	}

	void Merge(const LinkedList& L) {
		Node<T>* p = Head;
		if (Head == nullptr) {
			Head = L->getHead();
			return;
		}
		while (p->getNext()) {
			p = p->getNext();
		}
		p->setNext(L->getHead());
		count = count + L->getCount();
		return;
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		if (Head == nullptr) { return; }
		Node<T>* p = Head;
		Node<T>* nextP = Head->getNext();
		Head->setNext(nullptr);
		while (nextP) {
			Node<T>* temp = nextP->getNext();
			nextP->setNext(p);
			p = nextP;
			nextP = temp;
		}
		Head = p;
		return;
	}
	

	bool InsertSorted(const T& value) {
		if (Head == nullptr) {
			InsertBeg(value);
			return true;
		}

		if (Head->getItem() == value) {
			return false;
		}
		else if (Head->getItem() > value)
		{
			Node<T>* b = new Node<T>(value);
			b->setNext(Head);
			Head = b;
			count++;
			return true;
		}

		Node<T>* p = Head->getNext();
		Node<T>* q = Head;

		while (p) {
			if (p->getItem() == value) {
				return false;
			}
			else if (p->getItem() < value) {
				q = p;
				p = p->getNext();
			}
			else if (p->getItem() > value) {
				Node<T>* m = new Node<T>(value);
				m->setNext(p);
				q->setNext(m);
				count++;

				return true;
			}
		}

		Node<T>* e = new Node<T>(value);
		q->setNext(e);
		count++;
		return true;
	}

	Node<T>* RemoveMin() {

		if (count == 0) {
			return nullptr;
		}

		if (count == 1)
		{
			Node<T>* p = new Node<T>(Head->getItem());
			DeleteFirst();
			return p;
		}

		Node<T>* q = Head;
		Node<T>* r = nullptr;

		Node<T>* min = q;
		Node<T>* befMin = r;

		while (q->getNext()) {
			r = q;
			q = q->getNext();
			if (q->getItem() < min->getItem()) {
				min = q;
				befMin = r;
			}
		}

		if (befMin == nullptr) {
			Node<T>* p = new Node<T>(Head->getItem());
			DeleteFirst();
			return p;
		}

		Node<T>* p = new Node<T>(min->getItem());
		befMin->setNext(min->getNext());
		delete min;
		count--;
		return p;
	}

	LinkedList<T>& CloneList() {

		LinkedList<T>* p = new LinkedList<T>();
		if (count == 0) {
			return *p;
		}

		Node<T>* q = Head;
		p->InsertBeg(q->getItem());

		while (q->getNext()) {
			q = q->getNext();
			p->InsertEnd(q->getItem());
		}

		return *p;
	}

	void SignSplit(LinkedList& Lneg, LinkedList& Lpos) {

		if (count == 0) {
			return;
		}

		Node<T>* q = nullptr;
		Node<T>* p = Head;

		do
		{
			if (p->getItem() == 0)
			{
				q = p;
				p = p->getNext();
				continue;
			}
			else if (p->getItem() > 0)
			{
				Lpos.InsertBeg(p->getItem());
				if (q == nullptr) {
					p = p->getNext();
					DeleteFirst();
				}
				else
				{
					q->setNext(p->getNext());
					delete p;
					count--;
					p = q->getNext();
				}
			}
			else if (p->getItem() < 0)
			{
				Lneg.InsertBeg(p->getItem());
				if (q == nullptr) {
					p = p->getNext();
					DeleteFirst();
				}
				else
				{
					q->setNext(p->getNext());
					delete p;
					count--;
					p = q->getNext();
				}
			}
		} while (p);

	}

	

	LinkedList<T>& MergeSorted(LinkedList& L1, LinkedList& L2) {
		LinkedList<T>* m = new LinkedList<T>();

		Node<T>* p1 = L1.Head;
		Node<T>* p2 = L2.Head;

		for (int i = 0; i < L1.getCount(); i++) {
			m->InsertSorted(p1->getItem());
			p1 = p1->getNext();
		}

		for (int i = 0; i < L2.getCount(); i++) {
			m->InsertSorted(p2->getItem());
			p2 = p2->getNext();
		}

		L1.DeleteAll();
		L2.DeleteAll();
		return *m;
	}

	LinkedList<T>& SumLists(LinkedList& L1, LinkedList& L2) {
		LinkedList<T>* l = new LinkedList<T>();

		if (L1.getCount() != L2.getCount()) {
			return *l;
		}

		if (L1.getCount() == 0)
		{
			return *l;
		}

		Node<T>* p1 = L1.Head;
		Node<T>* p2 = L2.Head;
		Node<T>* r = nullptr;

		Node<T>* q = new Node<T>(p1->getItem() + p2->getItem());
		l->Head = q;
		l->count = l->count + 1;
		r = q;

		p1 = p1->getNext();
		p2 = p2->getNext();

		while (p1) {
			q = new Node<T>(p1->getItem() + p2->getItem());
			r->setNext(q);
			r = q;

			p1 = p1->getNext();
			p2 = p2->getNext();
		}

		return *l;
	}

	void Reorder_X(T X) {
		if ((count == 0) || (count == 1)) {
			return;
		}

		Node<T>* p = Head;
		if (p->getItem() <= X) {
			InsertBeg(p->getItem());
			Head->setNext(p->getNext());
			delete p;
			count--;
		}
		p = Head->getNext();
		Node<T>* r = Head;

		while (p) {
			if (p->getItem() <= X) {
				InsertBeg(p->getItem());
				r->setNext(p->getNext());
				delete p;
				count--;
				p = r->getNext();
			}
			else
			{
				r = p;
				p = p->getNext();
			}
		}
		return;
	}

	void ShiftLargest() {
		if ((count == 0) || (count == 1)) {
			return;
		}

		Node<T>* p = Head;
		T temp;

		while (p->getNext()) {
			if (p->getItem() > p->getNext()->getItem()) {
				temp = p->getItem();
				p->setItem(p->getNext()->getItem());
				p->getNext()->setItem(temp);
			}
			p = p->getNext();
		}
		return;
	}

	void RemoveDuplicates() {

		if ((count == 0) || (count == 1)) {
			return;
		}

		while (CountOccurance(Head->getItem()) > 1) {
			DeleteFirst();
		}

		Node<T>* p = Head->getNext();
		Node<T>* r = Head;

		while (p) {
			if (CountOccurance(p->getItem()) > 1) {
				r->setNext(p->getNext());
				delete p;
				count--;
				p = r->getNext();
			}
			else
			{
				r = p;
				p = p->getNext();
			}
		}
		return;
	}
};

#endif	