#include "faculty.h"

using namespace std;

faculty::faculty(){
  IDnum = -1;
  name = "";
  level = "";
  department = "";
  listOfAdvisees = new DoublyLinkedList<int>();
}

//iniatializes the faculty with valeus from overload.
faculty::faculty(int idToSet, string nameToSet, string levelToSet, string depToSet,  DoublyLinkedList<int> *listToAdd){
  IDnum = idToSet;
  name = nameToSet;
  level = levelToSet;
  department = depToSet;
  listOfAdvisees = new DoublyLinkedList<int>();
  while(!listToAdd->isEmpty()){
    listOfAdvisees->insertFront(listToAdd->removeBack());
  }
}

faculty::~faculty(){
}

//returns a list of integers as such:: ,x,y,z
//Prints out the integers from the adviseeslist
string faculty::getStudentIds(){
  string toRet ="";
  if(listOfAdvisees->front != NULL){
    ListNode<int>* current = listOfAdvisees->front;
    while(current != NULL){
      toRet =toRet + "," + to_string(current->data);
      current = current->next;
    }
  }
  return toRet;
}
ostream& operator<<(ostream& os, faculty p2){
  os<<"Id: " << p2.IDnum << " Name: " << p2.name<<" Level: " << p2.level << " department: "<< p2.department;
}
//<<" student Ids "<<facultyToAdd.getStudentIds()
