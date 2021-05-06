#ifndef PERSON_H
#define PERSON_H
#include <iostream>

using namespace std;

class person{
  public:
    friend bool operator==(person &p1, person &p2);
    friend bool operator!=(person &p1, person &p2);
    friend bool operator>(person &p1, person &p2);
    friend bool operator<(person &p1, person &p2);

    friend bool operator==(int intp1, person &p2);
    friend bool operator!=(int intp1, person &p2);
    friend bool operator>(int intp1, person &p2);
    friend bool operator<(int intp1, person &p2);

    friend bool operator==(person &p1,int intp2);
    friend bool operator!=(person &p1,int intp2);
    friend bool operator>(person &p1,int intp2);
    friend bool operator<(person &p1,int intp2);

    int IDnum; //usesd by student and Faculty
    string name; //usesd by student and Faculty
    void setID(int newID); //sets a id to given id
    int getID(); //gets id value
};

#endif
