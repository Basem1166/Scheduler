#pragma once
#include"Node.h"
#include"vector"
template<typename T>
class Queue {
private:
	Node<T>* front;
	Node<T>* rear;
public:
	Queue() {
		front = nullptr;
		rear = nullptr;
	}
	bool enQueue(T item) {
		Node<T>* temp = new Node<T>(item);

		if (isEmpty()) {
			front = temp;
			rear = temp;
		}
		else {
			rear->setNext(temp);
		}

		rear = temp;
		rear->setNext(nullptr);
		return true;
	}
	bool deQueue(T& item) {
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = front;
		item = front->getItem();
		front = front->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == rear)	 // Special case: last node in the queue
			rear = nullptr;
		delete nodeToDeletePtr;
		return true;
	}
	bool isEmpty() {
		if (!front)
			return true;
		return false;
	}
	bool peek(T& item) {
		if (front) {
			item = front->getItem();
			return true;
		}
		return false;

	}
	~Queue()
	{
		Node<T>* temp;
		T item;
		//Free (Dequeue) all nodes in the queue
		while (deQueue(item)) {
		}
	}
	Queue(const Queue<T>& LQ) //COPY CONSTRUCTOR
	{
		{
			Node<T>* NodePtr = LQ.front;
			if (!NodePtr) //LQ is empty
			{
				front = rear = nullptr;
				return;
			}

			//insert the first node
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			front = rear = ptr;
			NodePtr = NodePtr->getNext();

			//insert remaining nodes
			while (NodePtr)
			{
				Node<T>* ptr = new Node<T>(NodePtr->getItem());
				rear->setNext(ptr);
				rear = ptr;
				NodePtr = NodePtr->getNext();
			}
		}
	}
};