#include "pch.h"
#include "List.h"

template <typename item>
List<item>::List()
{

}

template<typename item>
//returns true is list is populated
bool List<item>::is_empty()
{
	return isEmpty; 
}

template<typename item>
//returns number of elements in list
int List<item>::num_element()
{
	return numElements;
}

