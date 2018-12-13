//MST.h
//Jacob Schaupp
//EECS 2510, Fall 2018
//Contains header definitions and variables for the minimum spanning tree algorithms 

#pragma once
#include "List.h"
#include "Container.h"
#include "MinHeap.h"
#include <string.h>

class MST
{
public:
	List<vertex> vertexList; //list that holds all of the vertexes
	List<edge> edgeList; //list that holds all of the edges

	List<edge> primEdgeList; //edge list used for prim

	List<List<vertex>> setList; //create a list of list 
	List<edge> sortedEdgeList; //used for Kruskal's, sorted edges in nondecresing order by weight

	//List<edge> primSelectedEdge; 

	MinHeap priorityHeap; //used for Prim's algorithm, basically a list 

	MST();
	void CreateVertex(char Key[1]); 
	void PopulateEdges(int vertexIndex1, int vertexIndex2, double weights); 
	void Kruskal(); 
	void Prim(); 
	void PrimSetup(); 

private: 
	//use these two to store the index of the lists that contain the respective vertexes, this will be used in the UNION method
	int index_list1 = 0; 
	int index_list2 = 0; 

	int primWeightDoubleCheck = 0; 

	void make_set(vertex *passVertex); 
	void sort_edge();
	bool find_set(vertex *targetVertex1, vertex *targetVertex2); 
	void _union(); 
	void _totalWeight();
	void printList();

	//these are supporting methods for prim's algorithm
	void getAdjacentVerts(List<vertex> *adjList, vertex* targetVertex); 
	edge* getConnectingEdge(vertex *vert1, vertex *vert2); 
	void calculateWeight(); 
	void getPathBack(vertex *lastVertAdded);
	List<edge>* traverseChildren(vertex *target); 
	void sortList(List<edge> *targetList); 
};

