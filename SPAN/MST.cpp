#include "pch.h"
#include "MST.h"

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
void MST::PopulateEdges(int vertexIndex1, int vertexIndex2, int edgeWeight)
{
	//index1 is row, index2 is column
	if (!vertexList.is_empty())
	{
		if (edgeWeight != 0)
		{
			//create new edge and add in data 
			edge *newEdge = new edge(); 
			newEdge->vertex1 = vertexList.get(vertexIndex1);
			newEdge->vertex2 = vertexList.get(vertexIndex2);
			newEdge->weight = edgeWeight;
			edgeList.Add(newEdge); 
		}
	}
}

MST::~MST()
{

}
