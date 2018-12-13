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

	spanningTrees.Kruskal(); 
	spanningTrees.Prim(); 
	exit(1); 
}