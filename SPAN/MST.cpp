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
void MST::PopulateEdges(int vertexIndex1, int vertexIndex2, double edgeWeight)
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
	//save edge list for prim 
	PrimSetup(); 
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
		//check if the verticies are contained in the same set
		if (find_set(returnedEdge->vertex1, returnedEdge->vertex2) == false)
		{
			//UNION the sets, since they are not in the same set 
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

void MST::Prim()
{
	//reset edge list after kruskal 
	edgeList = primEdgeList; 

	//need to get the root vertex where we will start from 
	//maybe just grab the first vertex in the list and use that as the root 
	vertex *rootVert = vertexList.get(0); //get the first vertex in the list 
	vertex *lastAdded = nullptr; //keep track of last vert added to tree
	//populate que with all of the verticies 
	for (int i = 0; i < vertexList.num_element() - 1; i++)
	{
		vertex *returnedVertex = vertexList.get(i); 
		if (i != 0) returnedVertex->path_length = 11111; //set every vertex to INFINTY length other than the root
		priorityHeap.Insert(returnedVertex); 
	}

	//since we start from the root, its pathLength has to be 0
	rootVert->path_length = 0; 

	//prim's algorithm runs until the que is empty 
	while (priorityHeap.size() > 0)
	{
		//get minimum from heap 
		vertex *currentVert = priorityHeap.get_min(true); //might need to remove this element from the list

		for (int j = 0; j < edgeList.num_element() - 1; j++)
		{
			edge *certifiedEdge = nullptr;
			List<vertex> adjacentVerts; //get all the adjacent verticies
			//edge *retEdge = edgeList.get(j); 

			getAdjacentVerts(&adjacentVerts, currentVert); //this will populate the adjacentVerts list with proper verticies

			for (int k = 0; k < adjacentVerts.num_element() - 1; k++)
			{
				vertex *currentAdjVert = adjacentVerts.get(k); 

				//get edge connecting current edge and the adjacent vertex -- is set to nullptr if there isn't one 
				edge *connectingEdge = getConnectingEdge(currentVert, currentAdjVert); 
				if (connectingEdge != nullptr)
				{
					//edge with smaller weight has been found -- REFRESH and set parent pointer so that path can be followed back to start later
					if ((priorityHeap.contains(currentAdjVert)) && (connectingEdge->weight < currentAdjVert->path_length))
					{
						currentAdjVert->parent = currentVert;
						currentAdjVert->path_length = connectingEdge->weight;
						lastAdded = currentAdjVert;
						certifiedEdge = connectingEdge; 
					}
				}
			}
			if (certifiedEdge != nullptr) primEdgeList.Add(certifiedEdge);
		}
	}
	calculateWeight(); 
	getPathBack(lastAdded);
}

void MST::PrimSetup()
{
	primEdgeList = edgeList;

}

//create the set (list of list)
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
		
		//grab the list of verticies 
		List<vertex> *returnedListVertex = setList.get(i); 

		//go through each of the elements contained within each list in the setList
		for (int j = 0; j < returnedListVertex->num_element() - 1; j++)
		{
			//grab the vertex in the list, and check it's key with the keys of the two verticies passed into this method, and see if they are the same
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

//combine two sets of verticies together into one 
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
}

void MST::_totalWeight()
{
	List<edge> *sortedEdgeList = new List<edge>(); 

	int weight = 0;

	sortList(&edgeList); 
	//edges that were chosen by kruskal will be set to true -- so check those elements 
	for (int i = 0; i < edgeList.num_element() - 1; i++)
	{
		if (edgeList.get(i)->chosen == true)
		{
			sortedEdgeList->Add(edgeList.get(i)); 
			weight = weight + edgeList.get(i)->weight;
		}
	}
	sortList(sortedEdgeList); 
	std::cout << weight << "\n"; 
	for (int j = 0; j < sortedEdgeList->num_element() - 1; j++)
	{
		edge *tempEdge = sortedEdgeList->get(j); 
		std::cout << tempEdge->vertex1->key << "-" << tempEdge->vertex2->key << ": " << tempEdge->weight << "\n"; 
	}

	std::cout << "---------------------------------------------\n";
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

#pragma region PrimSupport
void MST::getAdjacentVerts(List<vertex> *adjList, vertex *targetVertex)
{
	for (int i = 0; i < edgeList.num_element() - 1; i++)
	{
		//if an edge contains the target vertex, add other vertex to list of adjacent verts
		edge *returnedEdge = edgeList.get(i); 
		if (returnedEdge->vertex1 == targetVertex)adjList->Add(returnedEdge->vertex2); 
		else if (returnedEdge->vertex2 == targetVertex) adjList->Add(returnedEdge->vertex1); 
	}
}

edge* MST::getConnectingEdge(vertex *vert1, vertex *vert2)
{
	edge *connectingEdge = nullptr; 
	for (int i = 0; i < edgeList.num_element() - 1; i++)
	{
		edge *returnedEdge = edgeList.get(i); 
		if (((returnedEdge->vertex1 == vert1) && (returnedEdge->vertex2 == vert2)) || ((returnedEdge->vertex2 == vert1) && (returnedEdge->vertex1 == vert2)))
		{
			//this edge contains both vert1 and vert2 
			connectingEdge = returnedEdge; 
			return connectingEdge; 
		}
	}
	return connectingEdge; 
}

//used for prim -- calculate weight of tree
void MST::calculateWeight()
{
	int weight = 0; 
	vertex *lastVert = nullptr; 
	edge *chosenEdge = nullptr; 

	for (int i = 0; i < vertexList.num_element() - 1; i++)
	{
		vertex *returnedVertex = vertexList.get(i); 
		if (returnedVertex->path_length != 11111)
		{
			weight = weight + returnedVertex->path_length; 
			//use total weight and the path_length of next vertex to get path chosen and use parent pointer 
		}
	}
	std::cout << "Prim - \n" <<  weight << "\n";
}

//find edges used back to root
void MST::getPathBack(vertex *lastVertAdded)
{
	List<edge> edgesChosen; 

	if (lastVertAdded == nullptr)
	{
		std::cout << "Empty \n"; 
		return; 
	}
	vertex *currentFocus = lastVertAdded; 

	while (currentFocus->parent != nullptr)
	{
		//get adj vertex 
		List<vertex> *adjVerts = new List<vertex>(); 
		List<edge> *childrenEdge = new List<edge>(); 

		getAdjacentVerts(adjVerts, currentFocus); 

		//check adjacent verts to see if their parents are this vertex 
		for (int i = 0; i < adjVerts->num_element() - 1; i++)
		{
			vertex *tempVert = adjVerts->get(i);

			//call the traverse method on each child to see if they are connected 
			if (tempVert->parent == currentFocus)
			{
				edge *doubleCheck = getConnectingEdge(currentFocus, tempVert);
				if (edgesChosen.contains(doubleCheck) == false)
				{
					edgesChosen.Add(doubleCheck);
					childrenEdge = traverseChildren(tempVert); 
				}

				//check if the returned edge list is empty
				if (childrenEdge->is_empty() == false)
				{
					//combine these lists
					for (int j = 0; j < childrenEdge->num_element() - 1; j++)
					{
						edge *tempEdge = childrenEdge->get(j);
						if (edgesChosen.contains(tempEdge) == false)
						{
							edgesChosen.Add(tempEdge);
						}
					}
				}
			}
		}
		//iterative method will sometimes add the parent path, so check if it is already in list before adding to prevent duplicates
		edge *parentPath = getConnectingEdge(currentFocus, currentFocus->parent); 
		if (!edgesChosen.contains(parentPath)) edgesChosen.Add(parentPath); 
 
		currentFocus = currentFocus->parent; //move onto parent
	}

	//sort the list FIRST 
	sortList(&edgesChosen); 

	for (int j = 0; j < edgesChosen.num_element() - 1; j++)
	{
		//will need to sort these 
		edge *edge = edgesChosen.get(j);
		std::cout << edge->vertex1->key << "-" << edge->vertex2->key << ": " << edge->weight << "\n";
	} 
}

List<edge>* MST::traverseChildren(vertex *target)
{
	List<vertex> *adjVerts = new List<vertex>(); 
	List<edge> *chosenEdge = new List<edge>(); 

	getAdjacentVerts(adjVerts, target); 
	//while (target->parent != nullptr)
		for (int i = 0; i < adjVerts->num_element() - 1; i++)
		{
			vertex *tempAdjVert = adjVerts->get(i);
			if (tempAdjVert->parent == target)
			{
				chosenEdge->Add(getConnectingEdge(target, tempAdjVert)); //add edge between parent and child

				List<edge> *returnedListEdge = new List<edge>(); 
				returnedListEdge = traverseChildren(tempAdjVert); //traverse child looking for more edges 

				if (returnedListEdge->is_empty() == false)
				{
					//combine the two lists together into one 
					for (int j = 0; j < returnedListEdge->num_element() - 1; j++)
					{
						edge *newEdge = nullptr; 
						if (j == 0) newEdge = returnedListEdge->getFirst(); 
						else newEdge = returnedListEdge->get(i); 
						chosenEdge->Add(newEdge); 
					}
				}
			}
		}
		return chosenEdge; 
}

void MST::sortList(List<edge> *targetList)
{
	//go through each edge and ensure that the alphabetically lower edge is listed as vertex1 (BUBBLE SORT)
	for (int m = 0 ; m < targetList->num_element() - 1; m++)
	{
		edge *tempEdge = targetList->get(m); 
		if (strcmp(tempEdge->vertex1->key, tempEdge->vertex2->key) > 0)
		{
			//swap vertex1 with vertex2
			vertex *tempVertexStorage = tempEdge->vertex1; 
			tempEdge->vertex1 = tempEdge->vertex2; 
			tempEdge->vertex2 = tempVertexStorage; 
		}
	}

	for (int i = 0; i < targetList->num_element() - 1; i++)
	{
		for (int j = 0; j < targetList->num_element() - 2 - i; j++)
		{
			edge *comp1 = targetList->get(j); 
			edge *comp2 = targetList->get(j + 1); 

			vertex *Vcomp1 = comp1->vertex1; 
			vertex *Vcomp2 = comp2->vertex1; 
			if (strcmp(Vcomp1->key, Vcomp2->key) > 0)
			{
				//swap
				targetList->replaceElementItem(j, comp2); 
				targetList->replaceElementItem(j + 1, comp1); 
			}
		}
	}
}
#pragma endregion