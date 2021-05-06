#include "DBTransaction.h"

using namespace std;

//DBtransaction stores type of action and type of faculty or student aswell as the object for the given type
DBTransaction::DBTransaction(){

}
DBTransaction::DBTransaction(int transaction, bool type, student studentSubject){
  tnx_type = transaction;
  objType = type;
  studentObject = studentSubject;
}
DBTransaction::DBTransaction(int transaction, bool type, faculty facultySubject){
  tnx_type = transaction;
  objType = type;
  facultyObject = facultySubject;
}
DBTransaction::DBTransaction(int transaction, int studID, int newFacID, int oldFacID){
  tnx_type = transaction;
  newFacultyID = newFacID;
  studentID = studID;
  oldFacultyID = oldFacID;
}
DBTransaction::~DBTransaction(){

}


bool operator==(int intDB1, DBTransaction &d2){
  return intDB1 == d2.tnx_type;
}
bool operator!=(int intDB1, DBTransaction &d2){
  return intDB1 != d2.tnx_type;
}
bool operator>(int intDB1, DBTransaction &d2){
  return intDB1 < d2.tnx_type;
}
bool operator<(int intDB1, DBTransaction &d2){
  return intDB1 > d2.tnx_type;
}

bool operator==(DBTransaction &d1, DBTransaction &d2){
  return d1.tnx_type == d2.tnx_type;
}
bool operator!=(DBTransaction &d1, DBTransaction &d2){
  return d1.tnx_type != d2.tnx_type;
}
bool operator>(DBTransaction &d1, DBTransaction &d2){
  return d1.tnx_type < d2.tnx_type;
}
bool operator<(DBTransaction &d1, DBTransaction &d2){
  return d1.tnx_type > d2.tnx_type;
}
