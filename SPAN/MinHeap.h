#pragma once
#include "List.h"
#include  "Container.h"


class MinHeap
{
public:
	MinHeap();
	~MinHeap();

	void Insert(vertex *newElement); 
	vertex *get_min(bool deleteMinimum); 
	bool contains(vertex *targetElement); 
	int size(); 

private:
	List<vertex> vertList;
		
}; 

