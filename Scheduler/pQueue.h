#pragma once
#include"pNode.h"
template<typename T>
class pQueue {
private:
	pNode<T>* front;
	pNode<T>* rear;
	int count;
public:
	pQueue() {
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	bool isEmpty() {
		return(front == nullptr);
	}
	bool enQueue(T item, int prio)
	{
		pNode<T>* temp = new pNode<T>(item, prio);
		if (isEmpty()) {
			front = temp;
			rear = temp;
			count++;
			return true;
		}
		if (front->getPrio() >= temp->getPrio()) {
			temp->setNext(front);
			front = temp;
			count++;
			return true;
		}
		pNode<T>* current = front;
		while (current->getNext()) {
			if (current->getNext()->getPrio() >= temp->getPrio()) {
				temp->setNext(current->getNext());
				current->setNext(temp);
				count++;
				return true;
			}
			current = current->getNext();
		}
		current->setNext(temp);
		rear = temp;
		rear->setNext(nullptr);
		count++;
		return true;

	}
	bool deQueue(T& item) {
		if (isEmpty())
			return false;

		pNode<T>* nodeToDeletePtr = front;
		item = front->getItem();
		front = front->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == rear)	 // Special case: last node in the queue
			rear = nullptr;
		delete nodeToDeletePtr;
		count--;
		return true;
	}
	bool peek(T& item) {
		if (front) {
			item = front->getItem();
			return true;
		}
		return false;
	}
	~pQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (deQueue(temp));
	}
	pQueue(const pQueue<T>& LQ) //COPY CONSTRUCTOR
	{
		{
			pNode<T>* NodePtr = LQ.front;
			count = LQ.count;
			if (!NodePtr) //LQ is empty
			{
				front = rear = nullptr;
				return;
			}

			//insert the first node
			pNode<T>* ptr = new pNode<T>(NodePtr->getItem(), NodePtr->getPrio());
			front = rear = ptr;
			NodePtr = NodePtr->getNext();

			//insert remaining nodes
			while (NodePtr)
			{
				pNode<T>* ptr = new pNode<T>(NodePtr->getItem(), NodePtr->getPrio());
				rear->setNext(ptr);
				rear = ptr;
				NodePtr = NodePtr->getNext();
			}
		}
	}

	void Print()
	{
		T temp;
		pQueue Q(*this);
		while (!Q.isEmpty())
		{

			if (Q.count == 1)
			{
				Q.deQueue(temp);
				cout << *temp;
			}	
			else
			{
				Q.deQueue(temp);
				cout << *temp << ", ";
			}

		}
	}

	int getCount()
	{
		return count;
	}
};
