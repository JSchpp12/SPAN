//Container.h
//Jacob Schaupp
//EECS 2510, Fall 2018
//Contains the edge and vertex structures

#pragma once
#include "List.h"

struct vertex;

struct edge
{
	vertex *vertex1, *vertex2;
	double weight = 0;
	bool chosen = false; 
};

struct vertex
{
	char key[1];
	double path_length = 0;
	vertex *parent; //only used for prim's algorithm
};

