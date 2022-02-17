#include "IO_Manager.h"

bool IO_Manager::IsInputValid(ifstream& infile, int& countEdges) // check if the file is valid and its structure
{
	if (!infile)
	{
		cout << "ERROR: can't open the file" << endl;
		return false;
	}
	if (!(IO_Manager::ReadInput(infile, countEdges)))
	{
		cout << "Invalid Input" << endl;
		return false;
	}
	return true;
}
bool IO_Manager::ReadInput(ifstream& infile, int& countEdges) // read data from file and check if it is valid
{
	string CurrentLine;

	for (int i = 0; !infile.eof() && i < 3; i++) // read first 3 lines
	{
		getline(infile, CurrentLine, '\n');
		if (!IsLineInFileValid(CurrentLine, 1))
			return false;
	}

	if (infile.eof())
		return false;

	while (!infile.eof()) // read all E
	{
		getline(infile, CurrentLine, '\n');
		if (CurrentLine.size() != 0 && !IsLineInFileValid(CurrentLine, 3))
			return false;

		else if(CurrentLine.size() != 0)
		{
			countEdges++;
		}
	}

	return true;

}


bool IO_Manager::IsLineInFileValid(string CurrentLine, int AmountOfNumbers) // check if the current line in file is valid
{
	int i = 0;
	int counter = 0;
	bool ValidPoint = true;
	bool validSpaces = true;

	if (!isdigit(CurrentLine[i]) && CurrentLine[i]!='-')
		return false;

	while (CurrentLine[++i] != '\0')
	{
		if (CurrentLine[i] != ' ')
		{
			if (CurrentLine[i] == '-')
			{
				if (CurrentLine[i - 1] != ' ')
					return false;

				if(!isdigit(CurrentLine[i+1]))
					return false;
			}
			else if (CurrentLine[i] == '.')
			{
				if (counter != 2) 
				{
					return false;
				}
				else if(!isdigit(CurrentLine[i-1])|| !isdigit(CurrentLine[i + 1]))
				{
					return false;
				}
				else if (!ValidPoint)
				{
					return false;
				}
				ValidPoint = false;
			}
			else
			{
				validSpaces = true;
				if (!isdigit(CurrentLine[i]))
					return false;
			}
			
		}
		else // if space
		{
			if (validSpaces)
				counter++;
			validSpaces = false;
		}
	}

	if (isdigit(CurrentLine[i - 1]))
		counter++;


	if (counter != AmountOfNumbers)
		return false;

	else
		return true;
}


// read data from file, check if it represents a valid graph and build it 
bool IO_Manager::CheckAndBuildGraph(ifstream& infile, AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, int& start, int& end, int countEdges)
{
	int numberOfVertices;
	
	if (IsValidVertices(infile, numberOfVertices, start, end))
	{
		Graph_Lists.MakeEmptyGraph(numberOfVertices);
		Graph_Matrix.MakeEmptyGraph(numberOfVertices);
		if (!IsValidEdges(infile, Graph_Lists, Graph_Matrix, countEdges))
		{
			return false;
		}
	}

	else
	{
		return false;
	}
	
	return true;
	
}

void  IO_Manager::PrintResult(float* Darr, int EndIndex,string msg) // print the distance of the path to destination
{
		cout << msg <<" " <<Darr[EndIndex - 1] << endl;
}
bool IO_Manager::IsValidVertices(ifstream& infile, int& numberOfVertices, int& start, int& end) // check if number of vertices, start and end vertices are valid
{
	infile >> numberOfVertices;
	infile >> start;
	infile >> end;

	if (numberOfVertices <= 0)
	{
		cout << "invalid number of vertices" << endl;
		return false;
	}

	if (!(start >= 1 && start <= numberOfVertices))
	{
		cout << "invalid start vertex" << endl;
		return false;
	}

	if (!(end >= 1 && end <= numberOfVertices))
	{
		cout << "invalid end vertex" << endl;
		return false;
	}
	
	return true;
}

// check if the edges are according to these rules: no parallel edges, no self loops, no negative weights, valid vertices. 
// If edge is valid - add it to the graph
bool IO_Manager::IsValidEdges(ifstream& infile, AdjacencyLists& Graph_Lists, AdjacencyMatrix& Graph_Matrix, int countEdges)
{
	int v_from, v_to;
	float weight;
	int numberOfVertices = Graph_Matrix.getNumberOfVertices();

	for(int i=0; i< countEdges; i++)
	{
		infile >> v_from >> v_to >> weight;
		if (!(v_from >= 1 && v_from <= numberOfVertices) || !(v_to >= 1 && v_to <= numberOfVertices))
		{
			cout << "invalid vertex for edge" << endl;
			return false;
		}

		else if (Graph_Matrix.IsAdjacent(v_from, v_to))
		{
			cout << "invalid edge: parallel edges" << endl;
			return false;
		}

		else if (v_from == v_to)
		{
			cout << "invalid edge: self loop" << endl;
			return false;
		}

		else if (weight < 0)
		{
			cout << "invalid edge: negative weight" << endl;
			return false;
		}

		else
		{
			Graph_Lists.AddEdge(v_from, v_to, weight);
			Graph_Matrix.AddEdge(v_from, v_to, weight);
		}

	}

	return true;
}