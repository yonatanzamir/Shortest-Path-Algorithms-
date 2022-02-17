#pragma once
#include "LinkedList.h"
class Graph
{
	protected:
	int NumberOfVertices;

	public:
	Graph() = default;
	Graph(int size) :NumberOfVertices(size) {};
	virtual void MakeEmptyGraph(int n)=0;
	virtual const bool IsAdjacent(int u, int v)=0;
	virtual LinkedList* GetAdjList(int u) = 0;
	virtual void DeleteAdjList(LinkedList* Lst)=0;
	virtual void AddEdge(int u, int v, float c) = 0;
	virtual void RemoveEdge(int u, int v) = 0;
	int getNumberOfVertices() { return NumberOfVertices; }
	virtual const void PrintGraph() = 0;
};

