/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator; 

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST & rhs);    
   
   ~BST();

   int  size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   //copy each node for the copy constructor
   BinaryNode <T> * copyTree (BinaryNode <T> * n);

   // determine if the tree is empty
   bool empty() const
   {
      return root == NULL;
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {    
   	deleteBinaryTree(root);
      root = NULL;
   }

   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   { 
         root = copyTree(rhs.root);
         return *this;
   }
      
   // insert an item
   void insert(const T & t) throw (const char * );

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;
};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST & rhs)
{
    root = copyTree(rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
   //deleteBinaryTree(root);
}

/*****************************************************
* Function copyTree
* Purpose: recursion for the copy constructor and 
* assignment operator
*******************************************************/
template <class T>
BinaryNode <T> * BST<T> :: copyTree (BinaryNode <T> * n)
{
   if(!n)
   {
      return NULL;
   }
   
   try
   {
      BinaryNode <T> * newNode = new BinaryNode <T>(n->data);
      newNode -> pLeft = copyTree(n -> pLeft);
      newNode -> pRight = copyTree(n -> pRight);

      return newNode;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR Cannot allocate a new BinaryNode";
   }
}

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
	if(root == NULL)
    {
       BinaryNode <T> * nbn = new BinaryNode<T>(t);
       root = nbn;
       return;
    }//close first if statement
    else
    {
   		BinaryNode <T> * n = root;
   		bool added = false;
   		while(!added)
   		{
    		if(t <= n -> data)
      		{
        		if(n -> pLeft != NULL)
         		{
            		n = n -> pLeft;
         		}
         		else//pLeft is null, insert the node here
         		{
            		try
            		{
               			BinaryNode <T> * nbn = new BinaryNode<T>(t);
               			n-> addLeft(nbn);
               			added = true;
            		}
            		catch(std::bad_alloc)
            		{
               			std::cout << "ERROR: Unable to allocate a node\n";
            		}
         		}
         	//return;
      		}//close 1st if in the while loop
     		else //this > n
      		{
        		if(n -> pRight != NULL)
         		{
            		n = n -> pRight;
         		}
         		else //pRight is NULL, insert the new node here
         		{
            		try
            		{
               			BinaryNode <T> * nbn = new BinaryNode<T>(t);
               			n -> addRight(nbn);
               			added = true;
            		}
            		catch(std::bad_alloc)
            		{
               			std::cout << "ERROR: Unable to allocate a node\n";
            		}
         		}
         		//return;
      		}//close the outer else in the while loop
   		}//close while loop
	}//close the first else statement in the function
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
	BinaryNode <T> * nodeToDelete = find(it.getNode() -> data).getNode();
	if(nodeToDelete -> pLeft == NULL &&  nodeToDelete -> pRight == NULL)
	{
		/**********************************************************************
      * This is a leaf, check to see if it's left or right of the parent and
      * set it to NULL for the parent, then delete the node
      ***********************************************************************/
		if( nodeToDelete -> pParent != NULL)
		{
			if ( nodeToDelete -> data <= nodeToDelete-> pParent -> data)
			{
				 nodeToDelete -> pParent -> pLeft = NULL;
			}
			else
			{
				 nodeToDelete -> pParent -> pRight = NULL;
			}
         delete nodeToDelete;
		}
	}//close if statement for leaf
   else if(nodeToDelete -> pLeft != NULL && nodeToDelete -> pRight == NULL)
   {
      //there is one child and it's on the right
   	  //is it to the left of the parent and is the parent !Null?
   	  if(nodeToDelete -> pParent != NULL && nodeToDelete == nodeToDelete -> pParent -> pLeft)//-> data <= nodeToDelete -> pParent -> Data)
   	  {
   	  	nodeToDelete -> pParent -> pLeft = nodeToDelete -> pLeft;
   	  	nodeToDelete -> pLeft -> pParent = nodeToDelete -> pParent;
   	  }
   	  //if the parent is not null then the node is on the right
   	  else if(nodeToDelete -> pParent != NULL && nodeToDelete == nodeToDelete -> pParent -> pRight)//nodeToDelete -> data > nodeToDelete -> pParent -> Data)
   	  {
   	  	nodeToDelete -> pParent -> pRight = nodeToDelete -> pLeft;
   	  	nodeToDelete -> pLeft -> pParent = nodeToDelete -> pParent;
   	  }
   }
   else if(nodeToDelete -> pLeft == NULL && nodeToDelete -> pRight != NULL)
   {
      //there is one child and it's on the left
   }
   else if(nodeToDelete -> pLeft != NULL && nodeToDelete -> pRight != NULL)
   {
      /**********************************************************************
      * This node has 2 children, go to the right child, 
      * then find the furthest most left child/grandchild (a)
      * if a has a right child, move the right child to this a's
      * parent's left, then delete a
      ***********************************************************************/
      //find the left most child
      BinaryNode <T> * nodeToMove = nodeToDelete;
      nodeToMove = nodeToDelete -> pRight;
      while (nodeToMove -> pLeft != NULL)
      {
         nodeToMove = nodeToMove -> pLeft;
      }

      nodeToDelete -> data = nodeToMove -> data; // copy the data for the node to be moved into the node to be deleted
      
      if(nodeToMove -> pRight != NULL)
      {
         nodeToMove -> pParent -> pLeft = nodeToMove -> pRight; //set the nodes pParent's left to the nodes pRight
         nodeToMove -> pRight -> pParent = nodeToMove -> pParent; // set hte node's pRight's parent ot the nodes parent
      }
      //delete the node to be moved
      delete nodeToMove;
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
	//BSTIterator <T> it;
	BinaryNode <T> * nodePtr = root;
	if(nodePtr -> data == t)
	{
		BSTIterator <T> it(nodePtr);
		return it;
	}
	else
	{
		bool found = false;
		while(found != true)
		{
			if(t == nodePtr -> data)
			{
				found = true;
			}
			else if(t <= nodePtr -> data && nodePtr -> pLeft != NULL)
			{
				nodePtr = nodePtr -> pLeft;
			}
			else if(t > nodePtr -> data && nodePtr -> pRight != NULL)
			{
				nodePtr = nodePtr -> pRight;
			}
			else
			{
				return NULL;
			}
		}
		BSTIterator <T> it(nodePtr);
		return it;
	}
	
}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H
