#ifndef _LINKEDLIST
#endif	
#define _LINKEDLIST
#include<iostream>
#include "Node.h"
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	Node<T>* Tail;
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
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

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: Clear.
	* Deletes all nodes of the list.
	*/
	void Clear()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* E = new Node<T>(data);
		if (Head == nullptr)
			Head = E;
		Node<T>* Trvrs = Head;

		while (Trvrs->getNext()) {
			Trvrs = Trvrs->getNext();
		}
		Trvrs->setNext(E);
		E->setNext(nullptr);

	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key) {
		Node<T>* Trvrs = Head;
		while (Trvrs != nullptr) {
			if (Key == Trvrs->getItem()) {
				return true;
			}
			Trvrs = Trvrs->getNext();
		}
		return false;
	}

	bool Remove(T& item) {
		if (isEmpty())
			return false;
		Node<T>* Trvrs = Head;
		while (Trvrs->getNext()) {
			if (Trvrs->getNext()->getItem() == item) {
				Node<T>* Temp = Trvrs->getNext();
				item = Temp->getItem();
				Trvrs->setNext(Trvrs->getNext()->getNext());
				delete Temp;
				return true;
			}
			Trvrs = Trvrs->getNext();
		}
	}

		bool isEmpty() {
			if (!front)
				return true;
			return false;
		}
		int getLength() {
			Node<T>* Trvrs = Head;
			int Ln = 0;
			while (Trvrs != nullptr) {
				Ln++;
			}
			return Ln;
		}
	};