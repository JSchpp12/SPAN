#include "pch.h"
#include "MST.h"
#include <iostream>

MST::MST()
{

}

//create a new vertex object and add it to vertex list
void MST::CreateVertex(char key[1])
{
	vertex *newVertex = new vertex(); 
	strcpy(newVertex->key, key); 
	vertexList.Add(newVertex); 
}

//add edges to each vertex 
void MST::PopulateEdges(int vertexIndex1, int vertexIndex2, int edgeWeight)
{
	//index1 is row, index2 is column
	if (!vertexList.is_empty())
	{
		if (edgeWeight != 0)
		{
			//create new edge and add in data 
			vertex *t_vert1, *t_vert2;
			edge *newEdge = new edge(); 

			t_vert1 = vertexList.get(vertexIndex1); 
			newEdge->vertex1 = t_vert1; 

			t_vert2 = vertexList.get(vertexIndex2); 
			newEdge->vertex2 = t_vert2;

			newEdge->weight = edgeWeight;

			//need to check if this edge is already in the list
			for (int i = 0; i < edgeList.num_element() - 1; i++)
			{
				edge *t_edge = edgeList.get(i); 
				if ((t_edge->vertex1 == t_vert2) && (t_edge->vertex2 == t_vert1) && (newEdge->weight == t_edge->weight))
				{
					//new edge has the opposite pointers as an edge already in the list, so they are the same 
					return; //do not insert the new edge as it already exsists
				}
			}
			edgeList.Add(newEdge); 
		}
	}
}

//find the MST using Kruskal's Algorithm 
void MST::Kruskal()
{
	//run through all of the edges in the edge list 
	for (int i = 0; i < vertexList.num_element() - 1; i++)
	{
		vertex *tempVertex = vertexList.get(i); 
		make_set(tempVertex); 
	}
	sort_edge(); //sort the edge list in nondescending order

	//go through each edge in the sorted edge list 
	for (int j = 0; j < sortedEdgeList.num_element() - 1; j++)
	{
		edge *returnedEdge = sortedEdgeList.get(j); 
		std::cout << "\n"; 
		std::cout << "Looking at this edge::: " << returnedEdge->vertex1->key << " - " << returnedEdge->vertex2->key << "\n";
		//check if the vertexes are contained in the same set
		if (find_set(returnedEdge->vertex1, returnedEdge->vertex2) == false)
		{
			//UNION the sets, since they are not in the same set 
			std::cout << "Not in the same set \n"; 
			sortedEdgeList.get(j)->chosen = true; //update edge bool value to tell program that it has chosen this edge
			_union(); 

		}
		else
		{
			sortedEdgeList.get(j)->chosen = false; //update edge bool value to tell program that it will not take this edge
		}
	}
	_totalWeight(); 
}

MST::~MST()
{

}

void MST::make_set(vertex *passVertex)
{
	List<vertex> *tempVertexList = new List<vertex>(); 
	tempVertexList->Add(passVertex); //add passed vertex to list of vertex

	setList.Add(tempVertexList); 
}

//used by kruskal's algorithm -- sort edges in list in nondescending order 
void MST::sort_edge()
{
	//make a copy of the edgeList into the new list to be sorted 
	sortedEdgeList = edgeList; 

	//use bubble sort to accomplish this sorted list
	for (int i = 0; i < sortedEdgeList.num_element() - 1; i++)
	{
		for (int j = 0; j < sortedEdgeList.num_element() - i - 2; j++)
		{
			//get 2 edges for comparison from the lsit
			edge *A, *B; 
			A = sortedEdgeList.get(j); 
			B = sortedEdgeList.get(j + 1); 

			//if one edge has a larger weight than the other one, they will be swapped in the list 
			if (A->weight > B->weight)
			{
				sortedEdgeList.replaceElementItem(j, B); 
				sortedEdgeList.replaceElementItem(j + 1, A); 
			}
		}
	}
}

//this will tell if the targetVertex is contained in the set -- used by kruskal's algorithm
bool MST::find_set(vertex *targetVertex1, vertex *targetVertex2)
{
	int returnedIndex = -1; 
	bool found1 = false; 
	bool found2 = false; 
	//need to go through the setList and get each list contained in each element in the top list --> it is a list of lists
	for (int i = 0; i < setList.num_element() - 1; i++)
	{
		found1 = found2 = false; //reset the bools for the next list element
		
		//grab the list of vertexes 
		List<vertex> *returnedListVertex = setList.get(i); 

		//go through each of the elements contained within each list in the setList
		for (int j = 0; j < returnedListVertex->num_element() - 1; j++)
		{
			//grab the vertex in the list, and check it's key with the keys of the two vertexes passed into this method, and see if they are the same
			vertex *returnedVertex = returnedListVertex->get(j);
			if (strcmp(returnedVertex->key, targetVertex1->key) == 0)
			{
				found1 = true;
				index_list1 = i; //save for later use in UNION
			}
			if (strcmp(returnedVertex->key, targetVertex2->key) == 0)
			{
				found2 = true;
				index_list2 = i; //save for later use in UNION
			}
			if (found1 && found2) return true; 
		}
	}
	return false; 
}

//combine two sets of vertexes together into one 
void MST::_union()
{
	//the two different sets are stored in the class variables index_list1 and 2
	//copy contents from list2 to list1 
	List<vertex> *list1 = setList.get(index_list1);
	List<vertex> *list2 = setList.get(index_list2);

	for (int i = 0; i < list2->num_element() - 1; i++)
	{
		list1->Add(list2->get(i));
		//list2->deleteElement(i);
	}
	setList.deleteElement(index_list2); 
	//setList.replaceElementItem(index_list1, list1); //write updated

	/*
	if (list2->num_element() - 1 == 0)
	{
		//list2 is now empty, remove it from edge list
		setList.deleteElement(index_list2);
	}
	*/ 
}

void MST::_totalWeight()
{
	int weight = 0;

	for (int i = 0; i < edgeList.num_element() - 1; i++)
	{
		if (edgeList.get(i)->chosen == true) weight = weight + edgeList.get(i)->weight; 
	}
	std::cout << "The total weight of the MST is: " << weight << "\n"; 
}

void MST::printList()
{
	std::cout << "Printing lists \n"; 
	for (int i = 0; i < setList.num_element() - 1; i++)
	{
		std::cout << "\n"; 
		std::cout << "List elements...\n";
		List<vertex> *returnedList = setList.get(i); 
		for (int j = 0; j < returnedList->num_element() - 1; j++)
		{
			std::cout << returnedList->get(j)->key << " "; 
		}
	}
}