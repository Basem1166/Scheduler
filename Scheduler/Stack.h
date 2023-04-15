#pragma once
#include"Node.h"
template<typename T>

class Stack {
	Node<T>* Top;
public:
	Stack() {
		Top = nullptr;
	}
	bool isempty() {
		return top == nullptr;  // check if stack is empty
	}
	bool push(const T Item)
	{
		Node* new_node = new Node(item);
		new_node->next = top; // point to current top. Won't need to check if top is nullpointer cause it will replace it below
		top = new_node; // makes the node the new top
		return true; //item added to stack
	}
	bool pop(T& item) {
		if (isempty()) {
			return false;
		}
		item = Top->getItem();
		Top = Top->getNext();
	}
	bool peek(T& item) {
		if (isempty()) {
			return false;
		}
		item = Top->getItem();
	}
	~Stack() {
		T del; //delete variable
		while (pop(del)); // delete stack
	}
	Stack(const Stack <T>& copy) { // copy constructor
		if (copy.Top == nullptr) {
			Top = nullptr;	
			return;
		}
		Top = new Node(copy.Top->getItem()); //copy top data
		Node* temp = copy.Top->getNext; // pointer to top we're copying from
		Node* tempc = Top; //pointer to top we're pasting in
		while (temp != nullptr) {
			tempc->next = new Node(temp->data);
			tempc = tempc->next;
			temp = temp->next;
		}

	}
	void Print()
	{
		T temp;
		Stack S(*this);
		if (!S.isempty()) {
			S.pop(temp);
			cout << *temp;
		}
		while (!S.pop(temp)) {
			S.pop(temp);
			cout << ", " << *temp;
		}
	}
};