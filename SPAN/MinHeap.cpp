#include "pch.h"
#include "MinHeap.h"


MinHeap::MinHeap()
{
}


MinHeap::~MinHeap()
{
}

//Insert the vertex element into the heap
void MinHeap::Insert(vertex *newElement)
{
	vertList.Add(newElement); 
}

//returns minimum value in heap
vertex* MinHeap::get_min(bool deleteMinimum)
{
	int indexMin = 0; 
	vertex *foundMinimum = nullptr; 

	for (int i = 0; i < vertList.num_element() - 1; i++)
	{
		vertex *currentReturn = vertList.get(i); 
		if (foundMinimum == nullptr) foundMinimum = currentReturn; 
		else if ((currentReturn->path_length < foundMinimum->path_length) && (currentReturn->path_length != 11111))
		{
			foundMinimum = currentReturn; 
			indexMin = i; 
		}
	}
	//pass in true in order to delte the returned value -- maybe dont do this might ruin memory
	if (deleteMinimum == true) vertList.deleteElement(indexMin); 
	return foundMinimum; 
}

bool MinHeap::contains(vertex * targetElement)
{
	for (int i = 0; i < size(); i++)
	{
		vertex *currentFocus = vertList.get(i); 
		if (currentFocus == targetElement) return true; 
	}
	return false; 
}

//returns number of elements in list, does -1 the amount
int MinHeap::size()
{
	return vertList.num_element() - 1;
}