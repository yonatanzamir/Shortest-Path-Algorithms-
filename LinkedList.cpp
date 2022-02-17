#include "LinkedList.h"


LinkedList::LinkedList(): head(nullptr)
{

}
LinkedList::~LinkedList() 
{
	while (head!=nullptr)
	{
		deleteNode(head->vertex);
	}
}
const LinkedList& LinkedList::operator=(const LinkedList& ml)
{
	Node* q;
	q = ml.head;
	while (q != nullptr)
	{
		addToHead(q->vertex, q->weight);
		q = q->next;
	}
	return *this;
}
LinkedList::LinkedList(const LinkedList& ml): LinkedList() // copy consructor
{
	*this = ml;
}
void LinkedList::addToHead(int vertex, float weight) // add new node (with vertex and weight) to the head of the list
{
	Node* p = new Node;
	p->vertex = vertex;
	p->weight = weight;
	p->next = head;
	head = p;
}

void LinkedList::deleteNode(int vertex) // delete the node that contains the parameter
{
	Node* temp = head;
	if (temp->vertex == vertex)
	{
		head = head->next;
		delete temp;
	}
	else
	{
		while (temp->next->vertex != vertex)
		{
			temp = temp->next;
		}

		Node* toDelete = temp->next;
		temp->next = temp->next->next;
		delete toDelete;
	}

}
bool const LinkedList::Find(int vertex) // return true if the node is exists
{
	bool isFound = false;
	Node* temp = head;
	while (!isFound && temp != nullptr)
	{
		if (temp->vertex == vertex)
			isFound = true;
		temp = temp->next;
	}

	return isFound;
}
void const LinkedList::printList() // print the nodes - vertex and weight
{
	Node* temp = head;
	while (temp)
	{
		cout << temp->vertex << " (w:"<< temp->weight<<")    ";
		temp = temp->next;
	}
	cout << endl;
}

