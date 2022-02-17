#include "AdjacencyMatrix.h"
#include "LinkedList.h"

AdjacencyMatrix::AdjacencyMatrix(int size): Graph(size)
{
	MakeEmptyGraph(size);
}

AdjacencyMatrix:: ~AdjacencyMatrix()
{
	for (int i = 0; i < NumberOfVertices; i++)
	{
		delete[] adjMatrix[i];
		delete[] MarkingMatrix[i];
	}

	delete[] adjMatrix;
	delete[] MarkingMatrix;
}

void AdjacencyMatrix::MakeEmptyGraph(int n) // build adjcency matrix with n vertices and no edges
{
	adjMatrix = new float*[n];
	MarkingMatrix = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		adjMatrix[i] = new float[n];
		MarkingMatrix[i] = new bool[n];

		for (int j = 0; j < n; j++)
		{
			adjMatrix[i][j] = 0;
			MarkingMatrix[i][j] = false;
		}
	}

	NumberOfVertices = n;

}

bool const AdjacencyMatrix::IsAdjacent(int u, int v) // return true if v is a neighbor of u and false if not
{
	return MarkingMatrix[u-1][v-1];
}
void AdjacencyMatrix::DeleteAdjList(LinkedList* Lst) // delete the temporary adj list we created for a vertex
{
	delete Lst;
}
LinkedList* AdjacencyMatrix::GetAdjList(int u) // return the adjcency list of vertex u
{
	LinkedList* AdjOfU = new LinkedList;
	for (int i = 0; i < NumberOfVertices; i++)
	{
		if (MarkingMatrix[u - 1][i])
		{
			AdjOfU->addToHead(i + 1, adjMatrix[u - 1][i]);
		}
	}
	return AdjOfU; 
}

void AdjacencyMatrix::AddEdge(int u, int v, float c) // add new edge to graph (u->v) with weight c
{
	int from = u - 1;
	int to = v - 1;
	adjMatrix[from][to] = c;
	MarkingMatrix[from][to] = true;
}

void AdjacencyMatrix::RemoveEdge(int u, int v) // remove the edge u->v 
{
	int from = u - 1;
	int to = v - 1;
	adjMatrix[from][to] = 0;
	MarkingMatrix[from][to] = false;
}

void const AdjacencyMatrix::PrintGraph() // print the vertices and the edges of the adj matrix
{
	for (int i = 0; i < NumberOfVertices; i++)
	{
		cout << "The adjacency list of vertex " << i+1 << ": ";

		for (int j = 0; j < NumberOfVertices; j++)
		{
			if (MarkingMatrix[i][j])
			{
				cout <<j+1 << " (w:" << adjMatrix[i][j] << ")  ";
			}
		}

		cout << endl;
	}
}
