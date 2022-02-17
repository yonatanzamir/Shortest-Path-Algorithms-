#pragma once
#include <iostream>
using namespace std;
class LinkedList
{
	public:
		struct Node
		{
			int	vertex;
			float weight;
			Node* next=nullptr;
		};

	private:
		Node* head=nullptr;

	public:
		LinkedList();
		~LinkedList();
		const LinkedList& operator=(const LinkedList& ml);
		LinkedList(const LinkedList&);
		void addToHead(int vertex, float weight);
		void deleteNode(int vertex);
		bool const Find(int vertex); // return true if the node is exists
		void const printList();
		Node* getHead() { return head; }
	
};

