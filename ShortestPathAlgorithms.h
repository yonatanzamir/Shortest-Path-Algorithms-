#pragma once
#include "Graph.h"
#include "IO_Manager.h"
#include "PriorityQueueHeap.h"
#include "PriorityQueueArr.h"
#include "LinkedList.h"
class ShortestPathAlgorithms
{
	public:
	static float* Bellman_Ford(Graph& G, int start);
	static float* Dijkstra(Graph& G, int start,PriorityQueue& Pq);
	static void InitShortestPathDist(float* d, bool* d_IsInfinity, int start, int numberOfVertices);
	static bool Relax(int u, int v, float* d, bool* d_IsInfinity, float weightUV);
	static void Delete_d(float* d);
	static void ShortestPathAlgorithmsResult(float* DList[6], int Size,int EndIndex);
	static void CheckResult(float* DList[6], int current, int EndIndex, string msg);
	static void Delete_darr(float* DList[6]);
	static PriorityQueue::PqCell* CreateArrForPriorityQueue(float* d, bool* d_isInfinity, int size);
	static void RunAlgorithmsAndMeasureTimes(float* dist[6], AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, PriorityQueueArr& PqArr, PriorityQueueHeap& PqHeap, int start_v, string FileName);

};

