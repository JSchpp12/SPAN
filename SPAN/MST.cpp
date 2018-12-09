#include "pch.h"
#include "MST.h"

MST::MST()
{
}

//create a new vertex object and add it to vertex list
void MST::CreateVertex(char key[1])
{
	vertex newVertex; 
	strcpy(newVertex.key, key); 
	vertexList.AddVertex(&newVertex); 
}

//add edges to each vertex 
void MST::PopulateEdges(int vertxIndex1, int vertexIndex2, int edgeWeight)
{

}

MST::~MST()
{

}
