#pragma once
#include "List.h"

struct vertex;

struct edge
{
	vertex *vertex1, *vertex2;
	int weight = 0;
};

struct vertex
{
	char key[1];
	int path_length = 0;
	List<edge> edgeList;
};

