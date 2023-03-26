#pragma once
#include"pNode.h"
template<typename T>
class pQueue {
private:
	pNode<T>* front;
	pNode<T>* rear;
public:
	pQueue() {
		front = nullptr;
		rear = nullptr;
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
			return true;
		}
		if (front->getPrio() >= temp->getPrio()) {
			temp->setNext(front);
			front = temp;
			return true;
		}
		pNode<T>* current = front;
		while (current->getNext()) {
			if (current->getNext()->getPrio() >= temp->getPrio()) {
				temp->setNext(current->getNext());
				current->setNext(temp);
				return true;
			}
			current = current->getNext();
		}
		current->setNext(temp);
		rear = temp;
		rear->setNext(nullptr);
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
		while (deQueue(temp)) {

		}
	}
	pQueue(const pQueue<T>& LQ) //COPY CONSTRUCTOR
	{
		{
			pNode<T>* NodePtr = LQ.front;
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
				Node<T>* ptr = new pNode<T>(NodePtr->getItem(), NodePtr->getPrio());
				rear->setNext(ptr);
				rear = ptr;
				NodePtr = NodePtr->getNext();
			}
		}
	}
};
