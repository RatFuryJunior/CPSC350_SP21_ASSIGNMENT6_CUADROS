#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;
//BST class used for the storage of Faculty and Students
template<class T>
class TreeNode{
  public:
    TreeNode();
    TreeNode(T key);
    ~TreeNode();
    //TreeNode (int key, object value);
    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
template<class T>
TreeNode<T>::TreeNode(){
  left = NULL;
  right = NULL;
}
template<class T>
TreeNode<T>::TreeNode(T k){
  left = NULL;
  right = NULL;
  key = k;
}
template<class T>
TreeNode<T>::~TreeNode(){
  //put something here, reaserch
}


template<class T>
class BST{
  public:
    BST();
    ~BST();

    void deleteValue(T d);
    void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);


    void insert(T value);
    bool contains(int value);//search method
    T search(int value);

    bool deleteNode(int k);
    bool isEmpty();

    T getMin();
    T getMax();

    TreeNode<T>* getSuccessor(TreeNode<T> *d);//simplifies deleteNode a lot

    void print();//prints from root node
    void recPrint(TreeNode<T> *node);//prints from given node

    TreeNode<T>* root;
    int numOfNodes;
};

template<class T>
BST<T>::BST(){
  root = NULL;
  numOfNodes = 0;
}
template<class T>
BST<T>::~BST(){
  //build a decons
}

template<class T>
void BST<T>::recPrint(TreeNode<T> *node){
  if(node == NULL){
    return;
  }
  recPrint(node -> left);
  cout<<node -> key <<endl;
  recPrint(node -> right);

}

template<class T>
void BST<T>::print(){
  recPrint(root);
}


template<class T>
T BST<T>::getMin(){
  TreeNode<T> *current = root; //start at root;
  if(root == NULL){
  }
  while(current -> left != NULL){
    current = current -> left;
  }
  return current->key;
}

template<class T>
T BST<T>::getMax(){
  TreeNode<T> *current = root; //start at root;
  if(root == NULL){
    return NULL;
  }
  while(current -> right != NULL){
    current = current -> right;
  }
  return current->key;
}

template<class T>
void BST<T>::insert(T value){
  numOfNodes = numOfNodes + 1;
  TreeNode<T> *node = new TreeNode<T>(value);
  if(root == NULL){
    //empty tree
    root = node;
  }else{
    //not isEmpty
    TreeNode<T> *current = root;
    TreeNode<T> *parent;

    while(true){
      parent = current;
      if(value < current->key){
        current = current->left;
        if(current == NULL){
          //we found the spot
            parent->left = node;
            break;
          }
      }
      else{
        //we go right
        current = current->right;
        if(current == NULL){
          //we found insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
}

template<class T>
bool BST<T>::contains(int value){
  if(root == NULL){
    return false;
  }else{
    //not empty
    TreeNode<T> *current = root;
    while(current->key.getID() != value){
      if(value <current->key.getID()){
        current = current->left;
      }else{
        current = current-> right;
      }if(current == NULL){
        return false;
      }
    }
  }
  return true;
}
template<class T>
T BST<T>::search(int value){
  if(root == NULL){
    throw runtime_error("not found");
  }else{
    //not empty
    TreeNode<T> *current = root;
    while(current->key.getID() != value){
      if(value < current->key.getID()){
        current = current->left;
      }else{
        current = current-> right;
      }if(current == NULL){
        throw runtime_error("not found");
      }
    }
    return current->key;
  }
}

template<class T>
bool BST<T>::isEmpty(){
  if(root==NULL){
    return false;
  }
  return true;
}


template<class T>
bool BST<T>::deleteNode(int k){
  if(root==NULL){
    return false;
  }
  if(!contains(k)){
    return false;
  }
  //invoke search to see if it exists or not.
  numOfNodes = numOfNodes - 1;
  TreeNode<T>* current = root;
  TreeNode<T>* parent = root;
  bool isLeftNode = true;

  while(current->key.getID() != k){
    parent = current;
    if(k <current->key.getID()){
      isLeftNode = true;
      current = current -> left;
    }
    else{
      isLeftNode = false;
      current = current -> right;
    }
  }
  if(current == NULL){
    return false;
  }


  //we need to check three cases, no children, has two children, as one child
  //Case: Node to be delted is a leaf node
  if(current->left == NULL && current->right == NULL){
    if(current == root){
      root = NULL;
    }else if(isLeftNode){
      parent->left = NULL;
    }else{
      parent->right = NULL;
    }
  }
  //Case: Node to be delted has one child, find if dependent is left or right
  else if(current->right == NULL){
    //does not have a right child
    if(current==root){
      root = current ->left;
    }else if(isLeftNode){
      parent ->left = current ->left;
    }else{
      //is a right child
      parent ->right = current ->left;
    }
  }else if(current->left == NULL){
    //does not have a left child
    if(current==root){
      root = current ->right;
    }else if(isLeftNode){
      parent ->left = current ->right;
    }else{
      //is a left child
      parent ->right = current ->right;
    }
  }
  //Case: node to be delted has two children
  else{
    //we must find the correct Successor

    TreeNode<T> *successor = getSuccessor(current);

    if(current == root){
      root = successor;
    }else if(isLeftNode){
      parent->left = successor;
    }else{
      parent->right = successor;
    }
    successor ->left = current->left;
    current->left =NULL;
    current->right = NULL;
  }
  //do we need deletions? or do we something special in the destructor
  return true;
}

template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *current = d-> right;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }return successor;
}

#endif
