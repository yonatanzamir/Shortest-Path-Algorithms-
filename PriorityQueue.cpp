#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int size) : MaxSize(size), LogicalSize(0), places(nullptr), data(nullptr), allocated(0)
{

}
PriorityQueue::PriorityQueue() : MaxSize(0), LogicalSize(0), data(nullptr),places(nullptr),allocated(0)
{

}

PriorityQueue::~PriorityQueue()
{

}

void PriorityQueue::InitPlacesArray() // initialize the array that holds places in the priority queue
{
	for (int i = 0; i < LogicalSize; i++)
	{
		places[i] = i;
	}
}

void PriorityQueue::swapInt(int& a, int& b) 
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void PriorityQueue::swapPqCell(PqCell& a, PqCell& b)
{
	PqCell temp;
	temp.key_dist = a.key_dist;
	temp.data_vertex = a.data_vertex;
	a.key_dist = b.key_dist;
	a.data_vertex = b.data_vertex;
	b.key_dist = temp.key_dist;
	b.data_vertex = temp.data_vertex;
}
