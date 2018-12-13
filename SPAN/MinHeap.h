//MinHeap.h
//Jacob Schaupp
//EECS 2510, Fall 2018
//12/13/2018
//Contains header definitions for the heap structure

#pragma once
#include "List.h"
#include  "Container.h"

class MinHeap
{
public:
	MinHeap(); 

	void Insert(vertex *newElement); 
	vertex *get_min(bool deleteMinimum); 
	bool contains(vertex *targetElement); 
	int size(); 

private:
	List<vertex> vertList;
		
}; 

