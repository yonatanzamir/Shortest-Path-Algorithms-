#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include "AdjacencyLists.h"
#include "AdjacencyMatrix.h"
using namespace std;

class IO_Manager
{
	public:
		static bool ReadInput(ifstream& infile, int& countEdges);
		static bool IsInputValid(ifstream& infile, int& countEdges);
		static void PrintResult(float* Darr,int EndIndex, string msg);
		static bool IsLineInFileValid(string CurrentLine, int AmountOfNumbers);
		static bool CheckAndBuildGraph(ifstream& infile, AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, int& start, int& end, int countEdges);
		static bool IsValidVertices(ifstream& infile, int& numberOfVertices, int& start, int& end);
		static bool IsValidEdges(ifstream& infile, AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, int countEdges);

};

