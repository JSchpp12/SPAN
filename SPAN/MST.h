#pragma once
#include "List.h"
#include "Container.h"
#include <string.h>

class MST
{
public:
	List<vertex> vertexList; //list that holds all of the vertexes
	List<edge> edgeList; //list that holds all of the edges

	List<List<vertex>> setList; //create a list of list 
	List<edge> sortedEdgeList; //used for Kruskal's, sorted edges in nondecresing order by weight

	MST();
	void CreateVertex(char Key[1]); 
	void PopulateEdges(int vertexIndex1, int vertexIndex2, int weights); 
	void Kruskal(); 
	void Prim(); 
	~MST();

private: 
	//use these two to store the index of the lists that contain the respective vertexes, this will be used in the UNION method
	int index_list1 = 0; 
	int index_list2 = 0; 

	void make_set(vertex *passVertex); 
	void sort_edge();
	bool find_set(vertex *targetVertex1, vertex *targetVertex2); 
	void _union(); 
	void _totalWeight();
	void printList(); 
};

