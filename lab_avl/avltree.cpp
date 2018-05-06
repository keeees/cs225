/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
    cout<<"dsfsdfdsf"<<endl;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    //cout<<"rotateLeft"<<endl;

    Node *temp;

    temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    if(t->left != NULL){
      t->left->height = max(heightOrNeg1(t->left->left),heightOrNeg1(t->left->right))+1;

    }


     //cout<<"rotateLeftFinish"<<endl;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    //cout<<"rotateRight"<<endl;
    Node *temp;

    //cout<<"adfdsa"<<endl;
    temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;

    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    if(t->right != NULL){

      t->right->height = max(heightOrNeg1(t->right->left),heightOrNeg1(t->right->right))+1;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //cout<<"rebalance"<<endl;

    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balance == -2){
      int leftBalance = heightOrNeg1(subtree->left->right)- heightOrNeg1(subtree->left->left);
      if(leftBalance == -1){
        rotateRight(subtree);
      }else{
        rotateLeftRight(subtree);
      }
    }else if(balance == 2){
      int rightBalance = heightOrNeg1(subtree->right->right)- heightOrNeg1(subtree->right->left);
      if(rightBalance == 1){
        //cout<<"subtree "<<subtree->key<<endl;
        rotateLeft(subtree);
      }else{
        rotateRightLeft(subtree);
      }
    }

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    //cout<<"insert "<<key<<endl;

    if(subtree == NULL){
      subtree = new Node(key,value);
    }else if (key<subtree->key){
      insert(subtree->left,key,value);
      rebalance(subtree);
    }else if (key>subtree->key){
      insert(subtree->right,key,value);
      rebalance(subtree);
    }
    subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp;
            for(temp = subtree->left;temp->right != NULL; temp = temp->right){}
            swap(subtree,temp);
            remove(subtree->left,key);
            rebalance(subtree);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->left == NULL){
              Node* temp = subtree;
              subtree = subtree->right;
              delete temp;
              temp = NULL;

            }else if(subtree->right == NULL){
              Node* temp = subtree;
              subtree = subtree->left;
              delete temp;
              temp = NULL;
            }
            rebalance(subtree);

        }
    }
}
/*
template <class K, class V>
int AVLTree<K, V>::removeMin(Node*& subtree)
{
  int temp;
  if(subtree->left == NULL){
    Node* t = subtree;

    temp = subtree->key;
    subtree = subtree->right;
    //delete t;
    return temp;
  }else{
    temp = removeMin(subtree->left);
    return temp;
  }
}*/
