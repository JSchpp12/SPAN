#pragma once
#include "List.h"
#include "Container.h"
#include <string.h>


class MST
{
public:
	List<vertex> vertexList; 


	MST();
	void CreateVertex(char Key[1]); 
	void PopulateEdges(int vertexIndex1, int vertexIndex2, int weights); 
	void Kruskal(); 
	void Prim(); 
	~MST();

private: 


};

