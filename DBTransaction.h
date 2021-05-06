#include "student.h"
#include "faculty.h"

using namespace std;

//DBtransaction stores type of action and type of faculty or student aswell as the object for the given type
//implemented upon in database driver to be used in a stack for the rollback
class DBTransaction{
  public:
    DBTransaction();
    DBTransaction(int transaction, bool type, student studentSubject);
    DBTransaction(int transaction, bool type, faculty facultySubject);
    DBTransaction(int transaction, int studID, int newFacID, int oldFacID);
    ~DBTransaction();
    int tnx_type; //0 for delete 1 for insert 2 for modify
    bool objType; //0 for student 1 for faculty
    student studentObject;
    faculty facultyObject;
    int oldFacultyID;
    int newFacultyID;
    int studentID;

    friend bool operator==(int intDB1, DBTransaction &d2);
    friend bool operator!=(int intDB1, DBTransaction &d2);
    friend bool operator>(int intDB1, DBTransaction &d2);
    friend bool operator<(int intDB1, DBTransaction &d2);

    friend bool operator==(DBTransaction &d1, DBTransaction &d2);
    friend bool operator!=(DBTransaction &d1, DBTransaction &d2);
    friend bool operator>(DBTransaction &d1, DBTransaction &d2);
    friend bool operator<(DBTransaction &d1, DBTransaction &d2);

};
