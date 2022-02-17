#pragma once
#include "LinkedList.h"
#include "Graph.h"
class AdjacencyLists : public Graph
{
private:
	LinkedList* AdjLists = nullptr;

public:
	AdjacencyLists(int size);
	AdjacencyLists() = default;
	~AdjacencyLists();
	void DeleteAdjList(LinkedList* Lst) override {};
	void MakeEmptyGraph(int n) override;
	bool const IsAdjacent(int u, int v) override;
	LinkedList* GetAdjList(int u) override;
	void AddEdge(int u, int v, float c) override;
	void RemoveEdge(int u, int v) override;
	void const PrintGraph() override;
};





