/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include "bnode.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	BST <T> bst; 
	int i; 

	for (i = 0; i < num; i++) 
	{
		bst.insert(array[i]); 
	} 
	i = 0;
 
	for (BSTIterator <T> it = bst.begin(); it != bst.end(); ++it, i++)
	{
		array[i] = *it;
	}
}


#endif // SORT_BINARY_H
