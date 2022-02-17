#include "PriorityQueueHeap.h"

PriorityQueueHeap::PriorityQueueHeap(int max): PriorityQueue(max) // create an alloceted heap
{
	data = new PqCell[max];
	places = new int[max];
	allocated = 1;
}
PriorityQueueHeap::PriorityQueueHeap():PriorityQueue()
{
}

void PriorityQueueHeap::Build(PqCell* arr, int n) //BuildHeap with Fluid Algorithem
{
	LogicalSize = MaxSize = n;
	data = arr;
	allocated = 0;
	places = new int[n];
	InitPlacesArray();
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		FixHeap(i);
	}
}
PriorityQueueHeap::~PriorityQueueHeap() {
	MakeEmpty();
}
void PriorityQueueHeap::MakeEmpty() // delete the data only if this class allocated it  
{ 
	if (allocated)
	{
		delete[]data;
	}
	data = nullptr;
	MaxSize = LogicalSize = 0;
	delete[] places;
}
PriorityQueue::PqCell PriorityQueueHeap::Min() // return the root (item with minimum key)
{
	return data[0];
}
PriorityQueue::PqCell PriorityQueueHeap::DeleteMin() // delete the item with the minimum key and fix heap
{
	if (LogicalSize < 1)
	{
		cout << "ERROR:PriorityQueue empty" << endl;
		exit(1);
	}
	else
	{
		PqCell temp;
		temp.data_vertex = data[0].data_vertex;
		temp.key_dist = data[0].key_dist;
		LogicalSize--;
		places[data[0].data_vertex - 1] = -1;
		data[0].data_vertex = data[LogicalSize].data_vertex;
		data[0].key_dist = data[LogicalSize].key_dist;
		places[data[LogicalSize].data_vertex- 1] = 0;
		FixHeap(0);
		return temp;
	}

}
void PriorityQueueHeap::Insert(PqCell item) // insert new item to the heap and fix it
{
	if (LogicalSize == MaxSize)
	{
		cout << "ERROR:Place is over ";
		exit(1);
	}



	int i = LogicalSize;
	LogicalSize++;
	while (i > 0 && ((!data[parent(i)].key_dist.infinity && !item.key_dist.infinity && data[parent(i)].key_dist.key_dValue > item.key_dist.key_dValue) || (data[parent(i)].key_dist.infinity && !item.key_dist.infinity)))
	{
		data[i].key_dist = data[parent(i)].key_dist;
		data[i].data_vertex = data[parent(i)].data_vertex;
		places[data[parent(i)].data_vertex - 1] = i;
		i = parent(i);
	}
	data[i].key_dist = item.key_dist;
	data[i].data_vertex = item.data_vertex;
	places[data[i].data_vertex - 1] = i;
}

int PriorityQueueHeap::left(int node) // index of left son of node
{
	return(2 * node + 1);
}
int PriorityQueueHeap::right(int node) // index of right son of node
{
	return(2 * node + 2);
}
int PriorityQueueHeap::parent(int node) // index of parent of node
{
	return((node - 1) / 2);
}
void PriorityQueueHeap::FixHeap(int node)
{
	int Min;
	int Left = left(node);
	int Right = right(node);

	
	

	if (Left < LogicalSize && ((!data[node].key_dist.infinity && !data[Left].key_dist.infinity && data[node].key_dist.key_dValue > data[Left].key_dist.key_dValue) || (data[node].key_dist.infinity && !data[Left].key_dist.infinity)))
	{
		Min = Left;
	}
	else
	{
		Min = node;
	}

	if (Right < LogicalSize && ((!data[Min].key_dist.infinity && !data[Right].key_dist.infinity && data[Min].key_dist.key_dValue > data[Right].key_dist.key_dValue) || (data[Min].key_dist.infinity && !data[Right].key_dist.infinity)))
	{
		Min = Right;
	}
	if (Min != node)
	{
		swapPqCell(data[node], data[Min]);
		swapInt(places[data[node].data_vertex-1], places[data[Min].data_vertex-1]);
		FixHeap(Min);
	}
}

void PriorityQueueHeap::DecreaseKey(float newKey, int place) // decrease key of vertex and heapify up
{
	int pqPlace = places[place-1];
	data[pqPlace].key_dist.key_dValue = newKey;
	data[pqPlace].key_dist.infinity = false;
	if (pqPlace !=0 && ((!data[parent(pqPlace)].key_dist.infinity && !data[pqPlace].key_dist.infinity && data[parent(pqPlace)].key_dist.key_dValue > data[pqPlace].key_dist.key_dValue) || (data[parent(pqPlace)].key_dist.infinity && !data[pqPlace].key_dist.infinity)))
		
	{
		swapPqCell(data[parent(pqPlace)], data[pqPlace]);
		swapInt(places[data[parent(pqPlace)].data_vertex-1],places[data[pqPlace].data_vertex-1]);
		DecreaseKey(newKey, data[parent(pqPlace)].data_vertex);
	}
}
