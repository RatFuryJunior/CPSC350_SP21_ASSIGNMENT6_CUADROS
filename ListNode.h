#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>

//ListNode.h
using namespace std;

template <typename T>
class ListNode{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();
    ListNode<T> *next;
    ListNode<T> *prev;
    T data;
};


//implementation .cpp unless we are working with template classes
template <typename T>
ListNode<T>::ListNode(){}

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;//NULL or 0 or nullptr
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  next = NULL;//NULL or 0 or nullptr
  prev = NULL;
}


template <typename D>
class DoublyLinkedList{

  public:
    ListNode<D> *front;
    ListNode<D> *back;
    ListNode<D> *temp;
    size_t listsize;
    DoublyLinkedList();
    ~DoublyLinkedList();

    virtual void insertFront(D data);
    virtual void insertBack(D data);
    virtual D removeFront();
    virtual D removeBack();
    virtual D remove(D key);
    virtual bool isEmpty();
    virtual size_t getSize();
    virtual D peekFront();
    virtual D peekRear();
};

//implementation .cpp unless we are working with template classes

template <typename D>
DoublyLinkedList<D>::DoublyLinkedList(){
  listsize = 0;
  front = NULL;
  back = NULL;
}

template <typename D>
DoublyLinkedList<D>::~DoublyLinkedList(){
  while(front!=nullptr){
    temp = new ListNode<D>();
    temp = front;
    front = front -> next;
    delete temp;
  }
}

template <typename D>
void DoublyLinkedList<D>::insertFront(D data){
  ListNode<D> *node = new ListNode<D>(data);
  if(listsize == 0){
      back = node;
  }
  else{
      front->prev = node;
      node->next = front;
  }
  front = node;
  listsize++;
}

template <typename D>
void DoublyLinkedList<D>::insertBack(D data){
  ListNode<D> *node = new ListNode<D>(data);
  if(listsize == 0){
      front = node;
  }
  else{
    back->next = node;
    node->prev = front;
  }
  back = node;
  listsize++;
}

template <typename D>
D DoublyLinkedList<D>::removeFront(){
  ListNode<D> *tp = front;
  if(isEmpty()){
    cout<< "Something went wrong, Linked List isEmpty"<<endl;
    // return 0;
  }else{  //check if size == 1
    if(front->next == 0){
      back = 0;
    }else{
      //size > 1
      front -> next -> prev = NULL;
    }
    front = front->next;
    tp->next = 0;
    D temp = tp->data;
    listsize--;
    return temp;
  }

}

template <typename D>
D DoublyLinkedList<D>::removeBack(){
  ListNode<D> *tp = back;
  if(isEmpty()){
    cout<< "Something went wrong, Linked List isEmpty"<<endl;
    // return 0;
  }else{  //check if size == 1
    if(back->prev ==  0){
      front = 0;
    }else{
      //size > 1
      back -> prev -> next = NULL;
    }
    back = back -> prev;
    tp-> prev = 0;
    D temp = tp->data;
    listsize--;
    return temp;
  }
}

//deletes the list node containing a certain data and returns that data UNUSED FOR STACK APPLICATION
template <typename D>
D DoublyLinkedList<D>::remove(D key){//key is value we are looking for to remove
    //we could leverage find here but for example we aren't

    ListNode<D> *current = front;//make a pointer to the front node to start our search
    // if(getSize()<3){
    //   cout<<"TESADLKAJSD"<<endl;
    //   return removeFront();
    // }else{
    while(current->data != key){//keep going until we find the node with the right data
        current = current->next;//since we didn't find it, check the subsequent node

        if(current == NULL){//if we get to where current is null, it wasn't found so give an error since there is nothing to return
            throw runtime_error("key not found");
        }
    }

    //if we get here, we found it so now remove it
    if(current == front){//could call the remove front method
        front = current->next;//make the front point to the one after the current since it will become the front
        front->prev = NULL;//the new front has nothing before it, so null the previous pointer
    }
    else if (current == back){//if the last node
        back = current->prev;//the new back is the one before the current back
        back->next = NULL;//the new back's next is null since it is now back
    }
    else{
        //the list node to be removed is somewhere between front and back
        current->prev->next = current->next;//the node before should point to the one after the one we remove as its next
        current->next->prev = current->prev;//the node after should point to the one before the one we remove as its previous
    }
    current->next = NULL;//the current node (one with the key) should not point to anything anymore since it is being removed
    current->prev = NULL;
    D temp = current->data;//get the data
    delete current;//delete the node
    return temp;//return the data
  // }
}

template <typename D>
bool DoublyLinkedList<D>::isEmpty(){
  return listsize == 0;
}

template <typename D>
size_t DoublyLinkedList<D>::getSize(){
  return listsize;
}

template <typename D>
D DoublyLinkedList<D>::peekFront(){
  return front->data;
}

template <typename D>
D DoublyLinkedList<D>::peekRear(){
  return back->data;
}

#endif
