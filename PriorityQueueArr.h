#pragma once
#include <iostream>
#include "PriorityQueue.h"
using namespace std;
class PriorityQueueArr: public PriorityQueue
{
private:
	
	int MinIndex;
public:
	PriorityQueueArr(int size);
	PriorityQueueArr();
	~PriorityQueueArr();
	void Insert(PqCell item) override;
	PqCell DeleteMin() override;
	PqCell Min() override { return data[MinIndex]; }
	void FindMin();
	void DecreaseKey(float newKey, int place) override;
	void Build(PqCell* arr, int n) override;
	int FindFirstFiniteValue();
	
};

