#pragma once
#include <iostream>
#include "PriorityQueue.h"

using namespace std;
class PriorityQueueHeap: public PriorityQueue
	{

	private:
		
		static int left(int node);
		static int right(int node);
		static int parent(int node);
		void FixHeap(int node);
	public:
		PriorityQueueHeap(int max);
		PriorityQueueHeap();
		~PriorityQueueHeap();
		void Build(PqCell* arr, int n) override;
		PqCell Min() override;
		void DecreaseKey(float newKey, int place) override;
		PqCell DeleteMin() override;
		void Insert(PqCell item) override;
		void MakeEmpty();
	};




