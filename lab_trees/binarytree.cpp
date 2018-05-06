/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <vector>
using namespace std;/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    // Base case
    if (subRoot == NULL)
        return ;

    // Recursive definition
    Node *temp = subRoot->right;
    subRoot->right = subRoot->left;
    subRoot->left = temp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here

    mirror(this->root);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order     BinaryTree<int> myTree;
traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<int> iot(this->getRoot());
    int temp = 0;
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		if(temp > (*it)->elem){
            return false;
        }
        temp = (*it)->elem;
	}
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here

    return isOrderedRecursive(this->root);
}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const
{
  if(subRoot->left == NULL && subRoot -> right == NULL){
    return true;
}else if(subRoot->left == NULL && subRoot->right != NULL){
    return (subRoot->right->elem > subRoot->elem) & isOrderedRecursive(subRoot->right) & (subRoot->elem<getRightMost(subRoot->right)) ;
}else if(subRoot->right == NULL&& subRoot->left  != NULL){
    return (subRoot->left->elem < subRoot->elem) & isOrderedRecursive(subRoot->left)& (getLeftMost(subRoot->left)<subRoot->elem) ;
  }else{
    return (subRoot->left->elem < subRoot->elem) &(subRoot->right->elem > subRoot->elem)& isOrderedRecursive(subRoot->left) &isOrderedRecursive(subRoot->right)& (getLeftMost(subRoot->left)<getRightMost(subRoot->right)) ;
  }
}
template <typename T>
T BinaryTree<T>::getLeftMost(const Node* subRoot) const
{
    if(subRoot->left == NULL && subRoot->right == NULL)
        return subRoot->elem;
    else if( subRoot->right == NULL){
        return(max(subRoot->elem, getLeftMost(subRoot->left)));
    }else if(subRoot->left == NULL){
        return(max(subRoot->elem,getLeftMost(subRoot->right)));
    }else{
        return(max(max(subRoot->elem,getLeftMost(subRoot->right)),getLeftMost(subRoot->left)));
    }

}
template <typename T>
T BinaryTree<T>::getRightMost(const Node* subRoot) const
{
    if(subRoot->left == NULL && subRoot->right == NULL)
        return subRoot->elem;
    else if( subRoot->right == NULL){
        return(max(subRoot->elem, getLeftMost(subRoot->left)));
    }else if(subRoot->left == NULL){
        return(max(subRoot->elem,getLeftMost(subRoot->right)));
    }else{
        return(max(max(subRoot->elem,getLeftMost(subRoot->right)),getLeftMost(subRoot->left)));
    }
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> temp;
    printPaths(paths,temp,root);
}
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, vector<T> &temp, const Node* subRoot) const
{
    temp.push_back(subRoot->elem);
    if(subRoot->left == NULL && subRoot->right == NULL){//leave
        paths.push_back(temp);
    }
    if(subRoot->left != NULL){
        printPaths(paths,temp,subRoot->left);
    }
    if(subRoot->right != NULL){
        printPaths(paths,temp,subRoot->right);
    }
    temp.pop_back();
}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistances(root,-1,0);
}
template <typename T>
int BinaryTree<T>::sumDistances(const Node* subRoot, int distance, int total) const
{
    distance++;
    total+=distance;
    if(subRoot->right != NULL){
        total = sumDistances(subRoot->right,distance,total);
    }
    if(subRoot->left != NULL){
        total = sumDistances(subRoot->left,distance,total);
    }
    return total;
}
