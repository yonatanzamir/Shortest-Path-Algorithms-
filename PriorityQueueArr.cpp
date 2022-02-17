#include "PriorityQueueArr.h"

PriorityQueueArr::PriorityQueueArr(int size) :PriorityQueue(size), MinIndex(-1)
{
	data = new PqCell[size];
	places = new int[size];
	allocated = 1;
}
PriorityQueueArr::PriorityQueueArr():PriorityQueue(), MinIndex(-1)
{

}


PriorityQueueArr::~PriorityQueueArr()
{
	if (allocated) 
	{
		delete[] data;
	}

	delete[] places;

}
void PriorityQueueArr::Build(PqCell* arr, int n) // build priority queue (we get an allocted array)
{
	data = arr;
	allocated = 0;
	LogicalSize = MaxSize = n;
	places = new int[n];
	InitPlacesArray();
	FindMin();
}


void PriorityQueueArr::Insert(PqCell item) // insert new item to the priority queue and fix it
{
	if (LogicalSize == MaxSize)
	{
		cout << "ERROR:Place is over ";
		exit(1);
	}
	data[LogicalSize].key_dist = item.key_dist;
	data[LogicalSize].data_vertex = item.data_vertex;
	places[data[LogicalSize].data_vertex-1] = LogicalSize;
	if (MinIndex == -1)
	{
		MinIndex = LogicalSize;
	}



	else if((!data[MinIndex].key_dist.infinity && !data[LogicalSize].key_dist.infinity && data[MinIndex].key_dist.key_dValue > data[LogicalSize].key_dist.key_dValue) || (data[MinIndex].key_dist.infinity && !data[LogicalSize].key_dist.infinity))
	{
		MinIndex = LogicalSize;
	}
	LogicalSize++;

}
PriorityQueue::PqCell PriorityQueueArr::DeleteMin() // delete the item with the minimum key and fix priority queue
{
	if (LogicalSize < 1)
	{
		cout << "ERROR:PriorityQueue empty" << endl;
		exit(1);
	}
	else
	{
		PqCell temp;
		temp.data_vertex = data[MinIndex].data_vertex;
		temp.key_dist = data[MinIndex].key_dist;
		swapPqCell(data[MinIndex], data[LogicalSize - 1]);
		swapInt(places[data[MinIndex].data_vertex-1], places[data[LogicalSize - 1].data_vertex-1]);
		LogicalSize--;
		FindMin();
		return temp;
	}
}
void PriorityQueueArr::FindMin() // find the index of the item with the minimum key
{

	MinIndex = FindFirstFiniteValue();
	if (MinIndex != -1)
	{
		float min = data[MinIndex].key_dist.key_dValue;

		for (int i = 0; i < LogicalSize; i++)
		{
			if (!data[i].key_dist.infinity  &&  min > data[i].key_dist.key_dValue)
			{
				min = data[i].key_dist.key_dValue;
				MinIndex = i;
			}
		}
	}

	else
	{
		MinIndex = 0;
	}
	
}


int PriorityQueueArr::FindFirstFiniteValue() 
{
	for (int i = 0; i < LogicalSize; i++)
	{
		if (data[i].key_dist.infinity == false)
			return i;
	}

	return -1; // if all dist are infinity
}

void PriorityQueueArr::DecreaseKey(float newKey, int place) // decrease key of vertex and fix priority queue
{
	int placeInArr = places[place-1];
	data[placeInArr].key_dist.key_dValue = newKey;
	data[placeInArr].key_dist.infinity = false;
	if ((data[MinIndex].key_dist.infinity) || data[placeInArr].key_dist.key_dValue < data[MinIndex].key_dist.key_dValue)
	{
		MinIndex = placeInArr;
	}
}




