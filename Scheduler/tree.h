#pragma once

#include"Node.h"
#include <string>
#include <iostream>
using namespace std;
template<typename T>
class BSTree
{
private:
	Node<T>* root;

	static void rec_insertBST(Node<T>*& subRoot, int key) {
		if (subRoot == nullptr)
			subRoot = new Node(key); // this line is why we pass subRoot by reference (subRoot = something)
		else if (subRoot->getdata() < key)
		{

			//recursively call insert for the right subtree
			rec_insertBST(subRoot->getright(), key);
		}
		else
		{
			// recursive call on left
			rec_insertBST(subRoot->getleft(), key);
		}
	}
	static void rec_destroy_tree(Node<T>*& subRoot) {
		if (subRoot != nullptr)
		{
			// recursive call on left
			rec_destroy_tree(subRoot->getleft());

			// recursive call on right
			rec_destroy_tree(subRoot->getright());

			delete subRoot;
			subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
		}
	}

	void rec_printBT(const std::string& prefix, Node<T>* Node, bool isLeft) {
		if (Node != nullptr)
		{
			cout << prefix;

			cout << (isLeft ? "+-L-" : "+-R-");

			// print the value of the node
			cout << "(" << Node->getdata() << ") " << std::endl;
			//string 
			// enter the next tree level - left and right branch
			rec_printBT(prefix + (isLeft ? "|  " : "    "), node->getleft(), true);
			rec_printBT(prefix + (isLeft ? "|   " : "    "), node->getright(), false);
		}
	}

public:

	BSTree(void) {
		root = nullptr;
	}


	void printBT() {
		{
			cout << "\nPrinting BT, L means Left Child, R means Right Child(or Root)\n";
			rec_printBT("", root, false);
			cout << endl;
		}
	}

	void insertBST(int key) // not const
	{
		// not const because rec_insertBST takes the root by reference, so may change it
		rec_insertBST(root, key);
	}
	void destroy_tree() // not const
	{
		// not const because rec_destroy_tree takes the root by reference, so may change it
		rec_destroy_tree(root);
	}
	~BSTree(void) {
		destroy_tree();
	}
};

