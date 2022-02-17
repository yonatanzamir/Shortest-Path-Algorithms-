#include "AdjacencyLists.h"
#include "LinkedList.h"
AdjacencyLists::AdjacencyLists(int size) :Graph(size) 
{
	MakeEmptyGraph(size);
}
AdjacencyLists::~AdjacencyLists()
{
	delete[] AdjLists;
}
void AdjacencyLists::MakeEmptyGraph(int n) // build adjcency list with n vertices and no edges
{
	AdjLists = new LinkedList[n];
	NumberOfVertices = n;
}
bool const AdjacencyLists::IsAdjacent(int u, int v) // return true if v is a neighbor of u and false if not
{
	return (AdjLists[u-1].Find(v));
}
LinkedList* AdjacencyLists::GetAdjList(int u) // return the adjcency list of vertex u
{
	return &(AdjLists[u - 1]);
}
void AdjacencyLists::AddEdge(int u, int v, float c) // add new edge to graph (u->v) with weight c
{
	AdjLists[u-1].addToHead(v, c);
}
void AdjacencyLists::RemoveEdge(int u, int v)  // remove the edge u->v 
{
	AdjLists[u - 1].deleteNode(v); 
}

void const AdjacencyLists::PrintGraph() // print the vertices and the edges of the adj list
{
	for (int i = 0; i < NumberOfVertices; i++)
	{
		cout << "The adjacency list of vertex " << i+1 << ": ";
		AdjLists[i].printList();
	}
}