// SPAN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "MST.h"
#include <iostream>
#include <fstream>

int main()
{
	MST spanningTrees; 

	std::fstream file; 
	int numVertex = 0; 
	int weight; 
	char name[1]; 


	file.open("Matrix.txt", std::fstream::in | std::fstream::binary);
	file >> numVertex;

	//read in the names for each vertex 
	for (int i = 0; i < numVertex; i++)
	{
		file >> name; 
		spanningTrees.CreateVertex(name); 
	}

	//read in the edge information from the matrix j - row ; k - column
	for (int j = 0; j < numVertex; j++)
	{
		for (int k = 0; k < numVertex; k++)
		{
			weight = 0; 
			file >> weight; 
			if (weight != 0) spanningTrees.PopulateEdges(j, k, weight); //if there is a weight, pass it to trees to populate
		}
	}

	std::cout << numVertex; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
