#include "ShortestPathAlgorithms.h"
#include <chrono>
#include <iomanip>


float* ShortestPathAlgorithms::Bellman_Ford(Graph& G, int start) // Bellam Ford Algorithm
{
	int numberOfVertices = G.getNumberOfVertices();
	float* d = new float[numberOfVertices];
	bool* d_IsInfinity = new bool[numberOfVertices]; 
	LinkedList* adjList;
	InitShortestPathDist(d, d_IsInfinity,start, numberOfVertices);

	for (int i = 1; i <= numberOfVertices - 1; i++)
	{
		for (int j = 1; j <= numberOfVertices; j++)
		{
			adjList = G.GetAdjList(j);
			LinkedList::Node* temp = adjList->getHead();
			while (temp != nullptr)
			{
				Relax(j, temp->vertex, d, d_IsInfinity, temp->weight);
				temp = temp->next;
			}
			G.DeleteAdjList(adjList);
		}
	}


	for (int j = 1; j <= numberOfVertices; j++)
	{
		adjList = G.GetAdjList(j);
		LinkedList::Node* temp = adjList->getHead();
		while (temp != nullptr)
		{
			if (Relax(j, temp->vertex, d,d_IsInfinity, temp->weight))
			{
				cout << "Negative cycle!" << endl;
				Delete_d(d);
				return nullptr;
			}
			temp = temp->next;
			
		}
		G.DeleteAdjList(adjList);
	}

	delete[] d_IsInfinity;
	return d;	
}

// Dijkstra Algorithm
float* ShortestPathAlgorithms::Dijkstra(Graph& G, int start, PriorityQueue& Pq)
{
	int numberOfVertices = G.getNumberOfVertices();
	float* d = new float[numberOfVertices];
	bool* d_IsInfinity = new bool[numberOfVertices]; 
	LinkedList* adjList;
	InitShortestPathDist(d, d_IsInfinity,start, numberOfVertices);
	PriorityQueue::PqCell* PqCellArr = CreateArrForPriorityQueue(d, d_IsInfinity, numberOfVertices);
	Pq.Build(PqCellArr, numberOfVertices);
	PriorityQueue::PqCell currentMin;
	while (!Pq.IsEmpty())
	{
		currentMin = Pq.DeleteMin();
		adjList = G.GetAdjList(currentMin.data_vertex);
		LinkedList::Node* temp=adjList->getHead();
		while (temp!=nullptr)
		{
			if (Relax(currentMin.data_vertex, temp->vertex, d, d_IsInfinity, temp->weight) == true)
			{
				Pq.DecreaseKey(d[temp->vertex - 1], temp->vertex);
			}
			temp = temp->next;
		}
		G.DeleteAdjList(adjList);
	}
	delete[] PqCellArr;
	delete[] d_IsInfinity;
	return d;
}

void ShortestPathAlgorithms::CheckResult(float* DList[6],int current, int EndIndex,string msg) // check if the algorithm found a path and prints its weight
{
	if (DList[current] != nullptr)
	{
		if (DList[current][EndIndex - 1] == -1)
		{
			cout << "There is no path to vertex " << EndIndex << endl;
			Delete_darr(DList);
			cout << "Invalid Input" << endl;
			exit(1);
		}
		else
		{
			IO_Manager::PrintResult(DList[current], EndIndex, msg);
		}
	}
}

 void ShortestPathAlgorithms::ShortestPathAlgorithmsResult(float* DList[6], int Size, int EndIndex) // introduce the results from each algorithm (the weight of the path)
{
	 
	 for (int i = 0; i < 6; i++)
	 {
		 switch (i)
		 {
		 case 0:
			 CheckResult(DList, i, EndIndex, "Adjacency Dijkstra heap");
			 break;
		 case 1:
			 CheckResult(DList, i, EndIndex, "Adjacency Dijkstra array");
			 break;
		 case 2:
			 CheckResult(DList, i, EndIndex, "Adjacency Bellman Ford");
			 break;
		 case 3:
			 CheckResult(DList, i, EndIndex, "Matrix Dijkstra heap");
			 break;
		 case 4:
			 CheckResult(DList, i, EndIndex, "Matrix Dijkstra array");
			 break;
		 case 5:
			 CheckResult(DList, i, EndIndex, "Matrix Bellman Ford");
			 break;
		 }
	 }
	 Delete_darr(DList);
}

void ShortestPathAlgorithms::Delete_d(float* d)
{
	delete[] d;
}


void ShortestPathAlgorithms::Delete_darr(float* DList[6]) // delete all distance arrays
{
	for (int i = 0; i < 6; i++)
	{
		delete[] DList[i];
	}
}

void ShortestPathAlgorithms::InitShortestPathDist(float* d, bool* d_IsInfinity, int start, int numberOfVertices) // initizalize distacne array for bellman ford and dijkstra
{
	d[start - 1] =0;
	d_IsInfinity[start - 1] = false;

	for (int i = 0; i < numberOfVertices; i++)
	{
		if (i != start - 1)
		{
			d[i] = -1;
			d_IsInfinity[i] = true;
		}
	}
	 
}


bool ShortestPathAlgorithms::Relax(int u, int v, float* d, bool* d_IsInfinity, float weightUV) // check if the edge improves a path
{
	if ((!d_IsInfinity[v - 1] && !d_IsInfinity[u - 1] && d[v - 1] > d[u - 1] + weightUV) || (d_IsInfinity[v - 1] && !d_IsInfinity[u - 1]))
	{
		d[v - 1] = d[u - 1] + weightUV;
		d_IsInfinity[v - 1] = false;
		return true;
	}

	return false;

}


PriorityQueue::PqCell* ShortestPathAlgorithms::CreateArrForPriorityQueue(float* d,bool *d_isInfinity, int size) // create the data that the priority queue will have
{
	PriorityQueue::PqCell* pqData = new PriorityQueue::PqCell[size];

	for (int i = 0; i < size; i++)
	{
		pqData[i].data_vertex = i + 1;
		pqData[i].key_dist.key_dValue = d[i];
		pqData[i].key_dist.infinity = d_isInfinity[i];
	}
	return pqData;
}

// this method runs all algorithms and writes to file the time that took for each one of them
void ShortestPathAlgorithms::RunAlgorithmsAndMeasureTimes(float* dist[6], AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, PriorityQueueArr& PqArr, PriorityQueueHeap& PqHeap, int start_v, string FileName)
{
	auto start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[0] = ShortestPathAlgorithms::Dijkstra(Graph_Lists, start_v, PqHeap);

	auto end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	ofstream myfile(FileName); // The name of the file which is in argv[2]

	myfile << "Adjacency Dijkstra heap : " << fixed
		<< time_taken << setprecision(9) << endl;



	//----------------------------------------------------------------------------------------

	start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[1] = ShortestPathAlgorithms::Dijkstra(Graph_Lists, start_v, PqArr);

	end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	myfile << "Adjacency Dijkstra array : " << fixed
		<< time_taken << setprecision(9) << endl;

	//----------------------------------------------------------------------------------------

	start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[2] = ShortestPathAlgorithms::Bellman_Ford(Graph_Lists, start_v);

	end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	myfile << "Adjacency Bellman Ford : " << fixed
		<< time_taken << setprecision(9) << endl;

	//----------------------------------------------------------------------------------------

	start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[3] = ShortestPathAlgorithms::Dijkstra(Graph_Matrix, start_v, PqHeap);

	end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	myfile << "Matrix Dijkstra heap : " << fixed
		<< time_taken << setprecision(9) << endl;


	//----------------------------------------------------------------------------------------

	start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[4] = ShortestPathAlgorithms::Dijkstra(Graph_Matrix, start_v, PqArr);

	end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	myfile << "Matrix Dijkstra array : " << fixed
		<< time_taken << setprecision(9) << endl;

	//----------------------------------------------------------------------------------------

	start = chrono::high_resolution_clock::now();

	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	dist[5] = ShortestPathAlgorithms::Bellman_Ford(Graph_Matrix, start_v);

	end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	myfile << "Matrix Bellman Ford : " << fixed
		<< time_taken << setprecision(9) << endl;


	myfile.close();

}
