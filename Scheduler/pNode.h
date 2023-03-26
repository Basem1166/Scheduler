#ifndef _pNODE
#define _pNODE
#include<iostream>
using namespace std;
//First let's declare a single node in the list
template<typename T>
class pNode
{
private:
	T item;	// A data item (can be any complex sturcture)
	int priority;
	pNode<T>* next;	// Pointer to next node
public:

	pNode() //default constructor
	{
		next = nullptr;
	}

	pNode(T newItem, int prio) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = prio;

	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(pNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext
	void setPrio(int prio) {
		priority = prio;
	}

	T getItem() const
	{
		return item;
	} // end getItem

	pNode<T>* getNext() const
	{
		return next;
	}
	int getPrio()const
	{
		return priority;
	}
}; // end Node

#endif	