#ifndef _PQNODE
#define _PQNODE

//single node declaration
template<typename T>
class PQNode
{
private:
	T item;	//data item
	PQNode<T>* next;	//pointer to next node
	double priority;

public:
	PQNode() //default constructor
	{
		next = nullptr;
		priority = 0;
	}

	PQNode(T newItem, double newPriority) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = newPriority;

	}

	void setItem(T newItem)
	{
		item = newItem;
	}

	void setNext(PQNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem() const
	{
		return item;
	}

	PQNode<T>* getNext() const
	{
		return next;
	}

	void setPri(double newPri)
	{
		priority = newPri;
	}

	double getPri() const
	{
		return priority;
	}

};

#endif	
