#include "pch.h"
#include "List.h"

List::List()
{
	isEmpty = true; 
	numElements = 0; 
}

//add a vertex to the list
void List::AddVertex(vertex *newVertex)
{
	if (isEmpty == true)
	{
		//create first element in list 
		firstElement = new listElement(); 
		firstElement->vertex = newVertex; 
		firstElement->indexNum = numElements; 

		lastElement = firstElement;
		//delete &newVertex; //clear passed vertex from memory -- don't need it since it was copied (might need to remove this later)
		numElements++; 
		isEmpty = false;
		return; 
	}
	else
	{
		//add the newVertex to the exsisting list, set it as next element
		listElement *newElement = new listElement(); 
		newElement->vertex = newVertex; 
		newElement->indexNum = numElements; 
		lastElement->nextElement = newElement;  
		lastElement = newElement; //set new list object as last element added to list
		//delete &newVertex; //clear passed vertex from memory -- don't need it since it was copied (might need to remove this later)
		numElements++; 
		return; 
	}
}

//adds an edge to the list -- use list for only edges or only vertexes
void List::AddEdge(edge *newEdge)
{
	if (isEmpty == true)
	{
		//create first element in list 
		firstElement = new listElement(); 
		firstElement->edge = newEdge; 
		firstElement->indexNum = numElements; 
		lastElement = firstElement; 
		//delete &newEdge; 
		isEmpty = false; 
		numElements++; 
		return; 
	}
	else
	{
		//create a new element
		listElement *newElement = new listElement();

		//add edge element to listElement 
		newElement->edge = newEdge; 
		lastElement->nextElement = newElement; 
		lastElement = newElement; 

		//delete edge element
		//delete &newEdge;  
		numElements++; 
		return; 
	}
}

//returns true is list is populated
bool List::is_empty()
{
	return isEmpty; 
}

//returns number of elements in list
int List::num_element()
{
	return numElements;
}

List::~List()
{
}
