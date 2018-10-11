/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a binaryNode that has 2 parents
*    and 0+ children
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich
*    Edited by Mariah Ashley
************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   //default constructor
   BinaryNode() : data(T()), pLeft(NULL), pRight(NULL), pParent(NULL){}

   /**********************************************
   *non-Default Constructor:
   *Sets pNext
   ************************************************/
   BinaryNode(T data) : data(data), pLeft(NULL), pRight(NULL), pParent(NULL){}

   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }

   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);

   //formula to add 2 nodes together
   BinaryNode <T> & operator + (const BinaryNode <T> & rhs) const;

   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/*****************************************************
 * METHOD ADD LEFT()
 * Add smaller values to the left of the current node
 ****************************************************/
template<class T>
void BinaryNode<T> :: addLeft (BinaryNode <T> * pNode)
{
   this -> pLeft = pNode;
   if(pNode != NULL)
   {
      pNode -> pParent = this;
      pNode -> pLeft = NULL;
      pNode -> pRight = NULL;
   }
}

/*****************************************************
 * METHOD ADD Right()
 * Add larger values to the right of the current node
 ****************************************************/
template<class T>
void BinaryNode<T> :: addRight(BinaryNode <T> * pNode)
{
   this -> pRight = pNode;
   if(pNode != NULL)
   {
      pNode -> pParent = this;
      pNode -> pLeft = NULL;
      pNode -> pRight = NULL;
   }
}

/*****************************************************
 * METHOD ADD LEFT()
 * Add larger values to the right of the current node
 ****************************************************/
template<class T>
void BinaryNode<T> :: addLeft (const T & t) throw (const char *)
{
   BinaryNode<T> * newNode;
   try
   {
     newNode = new BinaryNode<T>(t);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR Cannot allocate a new node";
   }
   this -> pLeft = newNode;
   newNode -> pParent = this;
   newNode -> pLeft = NULL;
   newNode -> pRight = NULL;

}

/*****************************************************
 * METHOD ADD Right()
 * Add larger values to the right of the current node
 ****************************************************/
template<class T>
void BinaryNode<T> :: addRight(const T & t) throw (const char *)
{
   BinaryNode<T> * newNode;
   try
   {
     newNode = new BinaryNode<T>(t);
   }
   catch(std::bad_alloc)
   {
      std::cout << "ERROR Cannot allocate new node";
   }
   this -> pRight = newNode;
   newNode -> pParent = this;
   newNode -> pLeft = NULL;
   newNode -> pRight = NULL;
}


/*****************************************************
 * METHOD DELETEBINARYTREE()
 * traverse the tree to get each node and delete the
 * root
 ****************************************************/
template<class T>
void deleteBinaryTree(BinaryNode<T> *& root)
{
      if (root -> pLeft != NULL)
      {
         deleteBinaryTree(root->pLeft);
      }
      if (root -> pRight != NULL)
      {
         deleteBinaryTree(root->pRight);
      }
         delete root;
   // root -> pLeft;
   // root -> pRight;
   // delete root;
   // root = NULL;
}

/****************************************************
 * Overload ostream operator
 * Display a pair for debug purposes
 ***************************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const BinaryNode <T> * rhs)
{
   if(rhs != 0)
   {
      out << rhs -> pLeft;
      out << rhs -> data << " ";
      out << rhs -> pRight;
   }
   return out;
}


#endif // BNODE_H

