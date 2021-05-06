#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include "person.h"
#include "ListNode.h"

using namespace std;

class faculty: public person{
  public:
    faculty();
    faculty(int idToSet, string nameToSet, string levelToSet, string depToSet, DoublyLinkedList<int> *listToAdd);
    ~faculty();

    string getStudentIds();

    // Faculty ID int gained from person
    // Name string gained from person
    // Level String
    string level;
    // Department String
    string department;
    //list of integers for the advisees under the faculty
    DoublyLinkedList<int> *listOfAdvisees;
    friend ostream& operator<<(ostream& os, faculty p2);
};

#endif
