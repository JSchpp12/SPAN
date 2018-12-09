#pragma once
#include "Container.h"

class List
{
public:
	//this list can be used for storing all of the nodes, or all of the edges associated with a vertex 
	struct listElement
	{
		int indexNum; 
		edge *edge; 
		vertex *vertex; 
		listElement *nextElement; 
	};

	bool isEmpty; 
	int numElements; //will be 0 based like an array 
	listElement *firstElement = nullptr; //use this for the first element in the list
	listElement *lastElement = nullptr; //use this for quick insert, keep track of last element in list

	List();
	void AddVertex(vertex *newVertex);
	void AddEdge(edge *newEdge);
	bool is_empty();
	int num_element(); 
	~List();

private: 

};

