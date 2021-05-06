#include "person.h"

using namespace std;

//PERSON SHOULD NEVER BE MADE, ONLY EXPANDED BY STUDENT AND FACULTY

void person::setID(int newID){
  IDnum = newID;
}

int person::getID(){
  return IDnum;
}


bool operator==(person &p1, person &p2){
  return p1.IDnum == p2.IDnum;
}
bool operator!=(person &p1, person &p2){
  return p1.IDnum != p2.IDnum;
}
bool operator < (person &p1, person &p2){
  return p1.IDnum < p2.IDnum;
}
bool operator > (person &p1, person &p2){
  return p1.IDnum > p2.IDnum;
}


bool operator==(int intp1, person &p2){
  return intp1 == p2.IDnum;
}
bool operator!=(int intp1, person &p2){
  return intp1 != p2.IDnum;
}
bool operator > (int intp1, person &p2){
  return intp1  >  p2.IDnum;
}
bool operator < (int intp1, person &p2){
  return intp1 < p2.IDnum;
}

bool operator==(person &p1,int intp2){
  return intp2 == p1.IDnum;
}
bool operator!=(person &p1,int intp2){
  return intp2 != p1.IDnum;
}
bool operator > (person &p1,int intp2){
  return intp2  >  p1.IDnum;
}
bool operator < (person &p1,int intp2){
  return intp2 < p1.IDnum;
}
