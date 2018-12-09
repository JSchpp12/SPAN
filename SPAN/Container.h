#pragma once

struct vertex
{
	char key[1];
	int path_length = 0;
	
};

struct edge
{
	vertex *vertex1, *vertex2;
	int weight = 0;
};

