#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "person.h"

using namespace std;

class student:public person{
  public:
    student();
    student(int idToSet, string nameToSet, string levelToSet, string majorToSet, double gpaToSet, int facIDtoAdd);
    ~student();

    // ID int gained from person
    // Name string gained from person
    // Level strings
    string level;
    // Major Level
    string major;
    // GPA double
    double gpa;
    //fac id for advisor
    int facID;

    void setFacID(int facToSet);

    friend ostream& operator<<(ostream& os, student p2);
};

#endif
