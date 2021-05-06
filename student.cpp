#include "student.h"

using namespace std;

student::student(){
  IDnum = -1;
  name = "";
  level = "";
  major = "";
  gpa = 0;
  facID = 0;
}

//iniatializes the student with valeus from overload.
student::student(int idToSet, string nameToSet, string levelToSet, string majorToSet, double gpaToSet, int facIDtoAdd){
    IDnum = idToSet;
    name = nameToSet;
    level = levelToSet;
    major = majorToSet;
    gpa = gpaToSet;
    facID = facIDtoAdd;
}

student::~student(){
}

void student::setFacID(int facToSet){
  facID = facToSet;
}


ostream& operator<<(ostream& os, student p2){
  os<<"Id: " << p2.IDnum << " Name: " << p2.name<<" Level: " << p2.level << " Major: "<< p2.major << " GPA: " <<p2.gpa<< " Adivisor ID: " <<p2.facID;
}
