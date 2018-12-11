#pragma once

template <typename item>
class List
{
public:
	//this list can be used for storing all of the nodes, or all of the edges associated with a vertex 
	struct listElement
	{
		int indexNum; 
		item *item; 
		listElement *nextElement = nullptr; 
	};

	//constructor 
	List()
	{
		isEmpty = true;
		numElements = 0;
	}

	//add an element to the list
	void Add(item *newItem)
	{
		if (firstElement == nullptr)
		{
			//create first element and add it to the list 
			firstElement = new listElement();
			//populate list information
			firstElement->item = newItem;
			firstElement->indexNum = numElements;
			lastElement = firstElement;

			numElements++; //increment number of elements 
			this->isEmpty = false; 
		}
		else
		{
			//create new element and add it to last element in the list 
			//listElement *newElement = new listElement();
			listElement *Element = new listElement(); 
			Element->item = newItem;
			Element->indexNum = numElements;
			lastElement->nextElement = Element; 
			lastElement = Element; //set last element in list as the new element 

			numElements++; //increment number of elements 
		}
	}

	//returns item at an index refrenced from the beginning -- 0 based
	item* get(int index)
	{
		listElement *currentElement = firstElement;
		if (firstElement != nullptr)
		{
			for (int i = 0; i <= index - 1; i++)
			{
				currentElement = currentElement->nextElement;
			}
			return currentElement->item;
		}
	}

	//return if the list is empty 
	bool is_empty()
	{
		return isEmpty; 
	}

	//return number of elements 
	int num_element()
	{
		return numElements + 1; 
	}

private: 
	bool isEmpty;
	int numElements; //will be 0 based like an array 
	listElement *firstElement = nullptr; //use this for the first element in the list
	listElement *lastElement = nullptr; //use this for quick insert, keep track of last element in list
};

