#pragma once
#ifndef _PAIRNODE
#define _PAIRNODE

//single node declaration
template<typename T, typename N>
class PairNode
{
private:
	T Cook;	//data item
	N Order;
	int priority;
	PairNode<T, N>* next;	//pointer to next node


public:
	PairNode() //default constructor
	{
		next = nullptr;
		priority = 0;
	}

	PairNode(T currCook, N currOrder, int newPri)
	{
		Cook = currCook;
		Order = currOrder;
		priority = newPri;
	}
	void setCook(T currCook)
	{
		Cook = currCook;
	}
	void setOrder(N currOrder)
	{
		Order = currOrder;
	}
	void setPri(int newPri)
	{
		priority = newPri;
	}

	void setNext(PairNode<T,N>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getCook() const
	{
		return Cook;
	}
	N getOrder() const
	{
		return Order;
	}

	PairNode<T, N>* getNext() const
	{
		return next;
	}

	int getPri() const
	{
		return priority;
	}
};

#endif	