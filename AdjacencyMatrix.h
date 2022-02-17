#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Graph.h"
using namespace std;
class AdjacencyMatrix: public Graph
{
private:

	float** adjMatrix;
	bool** MarkingMatrix; // MarkingMatrix[u][v] = true only if there's an edge between u,v

public:
	AdjacencyMatrix(int size);
	AdjacencyMatrix() = default;
	~AdjacencyMatrix();
	void MakeEmptyGraph(int n) override;
	void DeleteAdjList(LinkedList* Lst) override;
	bool const IsAdjacent(int u, int v) override;
	LinkedList* GetAdjList(int u) override;
	void AddEdge(int u, int v, float c);
	void RemoveEdge(int u, int v);
	void const PrintGraph();
};

