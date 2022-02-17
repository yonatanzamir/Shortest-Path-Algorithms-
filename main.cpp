#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
#include "IO_Manager.h"
#include "AdjacencyLists.h"
#include "AdjacencyMatrix.h"
#include "ShortestPathAlgorithms.h"
#include "PriorityQueueHeap.h"
#include "PriorityQueueArr.h"
using namespace std;

// Instructions: before running this program, create a text file with data for building graph (number of vertices, start and end vertices, edges).
// The program will run Bellman Ford and Dijksta algorithms - with Adjacency List and Adjacency Matrix representations, and also for Dijkstra - 
// with 2 structures of priority queue. Therefore, in total there are 6 runnings.
// The running time of each algorithm and its representation will be written into text file.

void main(int argc, char* argv[])
{

	AdjacencyLists Graph_Lists;
	AdjacencyMatrix Graph_Matrix;
	PriorityQueueArr PqArr;
	PriorityQueueHeap PqHeap;
	ifstream infile(argv[1], ios::_Nocreate);
	int start_v, end_v;
	float* dist[6];
	int countEdges = 0;

	if (argc != 3)
	{
		cout << "error: incorrect number of arguments" << endl;
		exit(1);
	}

	if (!IO_Manager::IsInputValid(infile, countEdges))
	{
		exit(1);
	}

	infile.close();
	infile.open(argv[1], ios::_Nocreate);
	

	if (!IO_Manager::CheckAndBuildGraph(infile, Graph_Lists, Graph_Matrix, start_v, end_v, countEdges))
	{
		cout << "Invalid Input" << endl;
		exit(1);
	}

	ShortestPathAlgorithms::RunAlgorithmsAndMeasureTimes(dist, Graph_Lists, Graph_Matrix, PqArr, PqHeap, start_v, argv[2]);
	ShortestPathAlgorithms::ShortestPathAlgorithmsResult(dist, Graph_Matrix.getNumberOfVertices(), end_v);
	infile.close();
}





