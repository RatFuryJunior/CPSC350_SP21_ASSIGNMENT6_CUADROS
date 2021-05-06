#include <iostream>
#include <string>
#include <sstream>
#include "DatabaseDriver.h"

using namespace std;
//This is the base creation of the database for when no files exist
DatabaseDriver::DatabaseDriver(){
  f1 = FileProcessor();
  masterStudent = new BST<student>();
  masterFaculty = new BST<faculty>();
  g1 = new GenStack<DBTransaction>();
  rollbackCounter = 0;
}
//This is the creation for loating loading from files
DatabaseDriver::DatabaseDriver(bool studentFile,bool facultyFile){
  f1 = FileProcessor();
  masterStudent = new BST<student>();
  masterFaculty = new BST<faculty>();
  g1 = new GenStack<DBTransaction>();
  rollbackCounter = 0;

  if(studentFile){//if student file exists
    int numberOfStudentsToLoad = stoi(f1.loadForStudent(1));
    int lineNum = 1;
    while(lineNum < numberOfStudentsToLoad+1){
      lineNum += 1;
      masterStudent->insert(loadStudentFromFile(lineNum));
    }
  }

  if(facultyFile){//if faculty file exists
    int numberOfFacultyToLoad = stoi(f1.loadForFaculty(1));
    int lineNum = 1;
    cout<<numberOfFacultyToLoad<<endl;
    while(lineNum < numberOfFacultyToLoad+1){
      lineNum += 1;
      masterFaculty->insert(loadFacultyFromFile(lineNum));
    }
  }
}

//This is the method that is called for inputing a line from the file and creating a student object from the info
student DatabaseDriver::loadStudentFromFile(int lineNumber){
  string line = f1.loadForStudent(lineNumber);
  cout<<"Student #" << lineNumber-1<<" is: "<< line<<endl;

  string studentSegmented [5];
  int segment = 0;
  string del = ",";
  int start = 0;
  int end = line.find(del);
  while (end != -1) {
    studentSegmented [segment] = line.substr(start, end - start);
    start = end + del.size();
    end = line.find(del, start);
    segment = segment + 1;
  }
  studentSegmented [segment] = line.substr(start, end - start);

  //info gathered into array is assigned
  int idToSet = stoi(studentSegmented[0]);
  string nameToSet = studentSegmented[1];
  string levelToSet = studentSegmented[2];
  string majorToSet = studentSegmented[3];
  double gpaToSet= stod(studentSegmented[4]);
  int facIDtoAdd = stoi(studentSegmented[5]);
  //student is made
  student studentToAdd = student(idToSet,nameToSet,levelToSet,majorToSet,gpaToSet,facIDtoAdd);
  cout<<"Added: "<<studentToAdd<<" from the file"<<endl;
  return studentToAdd;
}
//This is the method that is called for inputing a line from the file and creating a faculty object from the info
faculty DatabaseDriver::loadFacultyFromFile(int lineNumber){
  string line = f1.loadForFaculty(lineNumber);
  cout<<"Faculty #" << lineNumber-1<<" is: "<< line<<endl;

  string facultySegmented [30];
  int segment = 0;

  stringstream string_stream(line);
  while(string_stream.good()) // https://www.codespeedy.com/comma-separated-string-to-array-in-cpp/
  {
    string a;
    getline( string_stream, a, ',' );
    facultySegmented[segment]=a;
    segment++;
  }
  //info from line is loaded to array and into variables
  int idToSet = stoi(facultySegmented[0]);
  string nameToSet = facultySegmented[1];
  string levelToSet = facultySegmented[2];
  string depToSet = facultySegmented[3];
  DoublyLinkedList<int> *listOfAdviseesToSet = new DoublyLinkedList<int>();
  //does the rest of the CSV's that remain from line into the list of advisees
  int i = 4;
  while(i<segment){
    listOfAdviseesToSet->insertFront(stoi(facultySegmented[i]));
    i++;
  }

  faculty facultyToAdd = faculty(idToSet,nameToSet,levelToSet,depToSet,listOfAdviseesToSet);

  cout<<"Added: "<<facultyToAdd<<" student Ids "<<facultyToAdd.getStudentIds()<<" from the file"<<endl;

  return facultyToAdd;
}

//destructor
DatabaseDriver::~DatabaseDriver(){
  delete masterStudent;
  delete masterFaculty;
  delete g1;
}

//functon to loop getline untill a user enters a integer and not a string
int DatabaseDriver::getIntFromUser(){
  int toRet = -99999;
  string daString = "";
  while(toRet == -99999){
    try{
      getline (cin,daString);
      toRet = stoi(daString);
    }catch(...){
      cout<<"Please enter an number and not a string"<<endl;
    }
  }
  return toRet;
}
//functon to loop getline untill a user enters a double and not a string
double DatabaseDriver::getDoubFromUser(){
  double toRet = -99999;
  string daString = "";
  while(toRet == -99999){
    try{
      getline (cin,daString);
      toRet = stod(daString);
    }catch(...){
      cout<<"Please enter an number and not a string"<<endl;
    }
  }
  return toRet;
}
//contains the main loop of menu options, loops untill 14 is slected.
void DatabaseDriver::MainMethod(){
  int userChoice = 0;
  while(userChoice!=14){
    ListMenuOptions();//calls listing of options
    cout<<endl<<"What Option do you wish to chose?:: "<<endl;
    userChoice = getIntFromUser();
    int idToFind = 0;
    int idToSet = 0;
    switch(userChoice){//switch case statment containing all options
      case 1://then promts as need to get info then sends into respecrive method for the choice
        printAllStudents();
        break;
      case 2:
        printAllFaculty();
        break;
      case 3:
        idToFind = 0;
        cout<<"What ID number for the student?" <<endl;
        idToFind = getIntFromUser();
        printSpecificStudent(idToFind);
        break;
      case 4:
        idToFind = 0;
        cout<<"What ID number for the Faculty?" <<endl;
        idToFind = getIntFromUser();
        printSpecificFaculty(idToFind);
        break;
      case 5:
        idToFind = 0;
        cout<<"What ID number for the Student?" <<endl;
        idToFind = getIntFromUser();
        printAdvisingFacInfo(idToFind);
        break;
      case 6:
        idToFind = 0;
        cout<<"What ID number for the Faculty?" <<endl;
        idToFind = getIntFromUser();
        printAdviseesInfo(idToFind);
        break;
      case 7:
        addNewStudent();
        break;
      case 8:
        idToFind = 0;
        cout<<"What ID number for the student?" <<endl;
        idToFind = getIntFromUser();
        deleteStudent(idToFind);
        break;
      case 9:
        addNewFaculty();
        break;
      case 10:
        idToFind = 0;
        cout<<"What ID number for the Faculty?" <<endl;
        idToFind = getIntFromUser();
        deleteFaculty(idToFind);
        break;
      case 11:
        idToFind = 0;
        cout<<"What ID number for the student?" <<endl;
        idToFind = getIntFromUser();
        idToSet = 0;
        cout<<"What ID number for the Faculty that is now the advisor?" <<endl;
        idToSet = getIntFromUser();
        changeAdvisor(idToFind,idToSet);
        break;
      case 12:
        idToFind = 0;
        cout<<"What ID number for the student?" <<endl;
        idToFind = getIntFromUser();
        removeAdvisee(idToFind);
        break;
      case 13:
        cout<<"Rolling Back"<<endl;
        rollback();
        break;
      case 14:
        // if(!masterFaculty->isEmpty() && !masterStudent->isEmpty()){
          outputDatabaseToFile();
        // }
        break;
      case 15:
        idToFind = 0;
        cout<<"What ID number for the student?" <<endl;
        idToFind = getIntFromUser();
        changeStudentMajor(idToFind);
        break;
      case 16:
        idToFind = 0;
        cout<<"What ID number for the faculty?" <<endl;
        idToFind = getIntFromUser();
        changeFacultyDepartment(idToFind);
        break;
      default:
        cout<<"Please pick from the listed options"<<endl;
        break;
    }
    cout<<endl;
  }
}
//string printout of all options, see above switch case
void DatabaseDriver::ListMenuOptions(){
  cout<<"Please enter a number corresponding to the option you wish to choose"<<endl;
  cout<<"1. Print all students and their information (sorted by ascending id #)"<<endl;
  cout<<"2. Print all faculty and their information (sorted by ascending id #)"<<endl;
  cout<<"3. Find and display student information given the students id"<<endl;
  cout<<"4. Find and display faculty information given the faculty id"<<endl;
  cout<<"5. Given a student’s id, print the name and info of their faculty advisor"<<endl;
  cout<<"6. Given a faculty id, print ALL the names and info of his/her advisees."<<endl;
  cout<<"7. Add a new student"<<endl;
  cout<<"8. Delete a student given the id"<<endl;
  cout<<"9. Add a new faculty member"<<endl;
  cout<<"10. Delete a faculty member given the id."<<endl;
  cout<<"11. Change a student’s advisor given the student id and the new faculty id."<<endl;
  cout<<"12. Remove an advisee from a faculty member given the ids"<<endl;
  cout<<"13. Rollback"<<endl;
  cout<<"14. Exit"<<endl;
  cout<<"15. Change major of a student given an id #"<<endl;
  cout<<"16. Change department of a faculty given an id #"<<endl;
}
//prints all of the students from the masterStudent
void DatabaseDriver::printAllStudents(){
  masterStudent->print();
}

//prints all of the faculty from the masterFaculty
void DatabaseDriver::printAllFaculty(){
  masterFaculty->print();
}

//prints student info from the specified ID num
void DatabaseDriver::printSpecificStudent(int idNumToSearch){
  try{
    cout<<masterStudent->search(idNumToSearch)<<endl;
  }catch(...){
    cout<<"Something went wrong, couldn't find a student"<<endl;
  }
}

//prints the info of all advisees out from a id of the faculty
void DatabaseDriver::printAdviseesInfo(int idNumToSearch){
  try{
    faculty facultyToPrint = masterFaculty->search(idNumToSearch);
    int i = 0;

    DoublyLinkedList<int> *tempList = new DoublyLinkedList<int>();//temmp DLL
    while(!facultyToPrint.listOfAdvisees->isEmpty()){
      i = i + 1;
      int studentID = facultyToPrint.listOfAdvisees->removeFront();
      tempList->insertFront(studentID);
      cout<<"Student #"<<i<<"is: "<<masterStudent->search(studentID)<<endl;
    }

    while(!tempList->isEmpty()){
      int studentID = tempList->removeFront();
      facultyToPrint.listOfAdvisees->insertFront(studentID);
    }
    delete tempList;
  }catch(...){
    cout<<"Something went wrong, couldn't find a student"<<endl;
  }
}

//prints faculty info from the specified ID num
void DatabaseDriver::printSpecificFaculty(int idNumToSearch){
  try{
    cout<<masterFaculty->search(idNumToSearch)<<" student Ids "<<masterFaculty->search(idNumToSearch).getStudentIds()<<endl;
  }catch(...){
    cout<<"Something went wrong, couldn't find a faculty"<<endl;
  }
}

//Takes a ID for a student and prints out the info of thier advising faculty member
void DatabaseDriver::printAdvisingFacInfo(int idNumToSearch){
  int facIDToPrint = (masterStudent->search(idNumToSearch)).facID;
  cout<< (masterFaculty->search(facIDToPrint)) <<endl;
}

//adds a new student and inserts themm into the BST
void DatabaseDriver::addNewStudent(){
  int idToSet = -1;
  string nameToSet = "";
  string levelToSet = "";
  string majorToSet = "";
  double gpaToSet=-1;
  int facIDtoAdd =-1;
  cout<<"making a new student"<<endl;
  cout<<"What is the Students ID?"<<endl;
  idToSet = getIntFromUser();
  cout<<"What is the Students Name?"<<endl;
  cin>>nameToSet;
  cout<<"What is the Students Grade Level?"<<endl;
  cin>>levelToSet;
  cout<<"What is the Students Major?"<<endl;
  cin>>majorToSet;
  cout<<"What is the Students GPA?"<<endl;
  gpaToSet = getDoubFromUser();
  cout<<"What is the Students Advisors ID #?"<<endl;
  facIDtoAdd = getIntFromUser();
  bool facultyExists = false;
  if(masterFaculty->contains(facIDtoAdd)){//checks that the facId is real (ref integ)
    facultyExists = true;
  }
  if(facultyExists){
    cout<<"Student Added"<<endl;
    g1->push(DBTransaction(1,0,student(idToSet,nameToSet,levelToSet,majorToSet,gpaToSet,facIDtoAdd)));
    increaseRollCounter();
    masterStudent->insert(student(idToSet,nameToSet,levelToSet,majorToSet,gpaToSet,facIDtoAdd));
    masterFaculty->search(facIDtoAdd).listOfAdvisees->insertFront(idToSet);
  }else{
    cout<<"Pleasee enter a ID number for a faculty that exists, you may need to add a faculty first"<<endl;
  }
}

//deletes a student from the BST if thier ID exists
void DatabaseDriver::deleteStudent(int idNumToSearch){
  try{
    int facultysID = masterStudent->search(idNumToSearch).facID;

    faculty facultyToLose = masterFaculty->search(facultysID);


    int numOFAddvisees = facultyToLose.listOfAdvisees->getSize();
    //delets based off of number of advisses in list
    if(numOFAddvisees >= 3){
      facultyToLose.listOfAdvisees->remove(idNumToSearch);//removes student from that faculty list
    }else if(numOFAddvisees == 2){
      if(facultyToLose.listOfAdvisees->peekFront() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeFront();
      }else if(facultyToLose.listOfAdvisees->peekRear() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeBack();
      }
    }else{
      facultyToLose.listOfAdvisees->removeFront();
    }

    g1->push(DBTransaction(0,0,masterStudent->search(idNumToSearch)));
    increaseRollCounter();
    masterStudent->deleteNode(idNumToSearch);
  }catch(...){
    cout<<"Something went wrong, couldn't find a student for that ID"<<endl;
  }
}

//adds a new facuty and inserts themm into the BST
void DatabaseDriver::addNewFaculty(){
  int idToSet = -1;
  string nameToSet = "";
  string levelToSet = "";
  string depToSet = "";
  int numberOfAdvisees = 0;
  int idOfStudent = 0;
  DoublyLinkedList<int> *listOfAdviseesToSet = new DoublyLinkedList<int>();
  cout<<"making a new faculty"<<endl;
  cout<<"What is the Faculty's ID?"<<endl;
  idToSet = getIntFromUser();
  cout<<"What is the Faculty's Name?"<<endl;
  cin>>nameToSet;
  cout<<"What is the Faculty's Level?"<<endl;
  cin>>levelToSet;
  cout<<"What is the Faculty's Department?"<<endl;
  cin>>depToSet;

  faculty facultyToInsert = faculty(idToSet,nameToSet,levelToSet,depToSet,listOfAdviseesToSet);
  g1->push(DBTransaction(1,1,facultyToInsert));
  increaseRollCounter();
  masterFaculty->insert(facultyToInsert);
}

//deletes a faculty from the BST if thier ID exists
void DatabaseDriver::deleteFaculty(int idNumToSearch){
  try{
    if(masterFaculty->search(idNumToSearch).listOfAdvisees->isEmpty()){//this is broken
      g1->push(DBTransaction(0,1,masterFaculty->search(idNumToSearch)));
      increaseRollCounter();
      masterFaculty->deleteNode(idNumToSearch);
    }else{
      cout<<"please change all of the advises for this faculty to a diffrent faculty before removing them"<<endl;
    }
  }catch(...){
    cout<<"Something went wrong, couldn't find a faculty"<<endl;
  }
}

//changes a students adivisor to be another if that faculty advisor exists aswell
void DatabaseDriver::changeAdvisor(int idNumToSearch,int idForAdvisor){
  bool facAndStudExist = false;
  if(masterStudent->contains(idNumToSearch) && masterFaculty->contains(idForAdvisor)){
    facAndStudExist = true;
  }
  if(facAndStudExist){
    student studentToChange = masterStudent->search(idNumToSearch);
    faculty facultyToGain = masterFaculty->search(idForAdvisor);
    facultyToGain.listOfAdvisees->insertFront(idNumToSearch);//adds student to facultys list
    int facultyToLoseID = studentToChange.facID;
    faculty facultyToLose = masterFaculty->search(facultyToLoseID);
    studentToChange.setFacID(idForAdvisor);
    int numOFAddvisees = facultyToLose.listOfAdvisees->getSize();
    //delets based off of number of advisses in list
    if(numOFAddvisees >= 3){
      facultyToLose.listOfAdvisees->remove(idNumToSearch);//removes student from that faculty list
    }else if(numOFAddvisees == 2){
      if(facultyToLose.listOfAdvisees->peekFront() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeFront();
      }else if(facultyToLose.listOfAdvisees->peekRear() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeBack();
      }
    }else{
      facultyToLose.listOfAdvisees->removeFront();
    }

    masterStudent->deleteNode(idNumToSearch);
    masterStudent->insert(studentToChange);
    g1->push(DBTransaction(2,idNumToSearch,idForAdvisor,facultyToLoseID));//2,student,new,old
    increaseRollCounter();
  }else{
    cout<<"Please enter a ID number for the faculty that exists and ID for student that exists"<<endl;
  }

}

//removes a advisee from a faculty and puts the student for a new advisor
void DatabaseDriver::removeAdvisee(int idNumToSearch){
  bool facAndStudExist = false;
  if(masterStudent->contains(idNumToSearch)){
    facAndStudExist = true;
  }
  if(facAndStudExist){
    student studentToChange = masterStudent->search(idNumToSearch);
    int idForAdvisor = studentToChange.facID;
    faculty facultyToLose = masterFaculty->search(idForAdvisor);


    bool newFacExists = false;
    bool shouldbreak = false;
    int facultyToGainID;

    while(!newFacExists){
      cout<<"What is the students new advisor's ID?"<<endl;
      facultyToGainID = getIntFromUser();
      if(facultyToGainID == -1){
        shouldbreak= true;
      }
      newFacExists = masterFaculty->contains(facultyToGainID);
      if(newFacExists){
        faculty facultyToGain = masterFaculty->search(facultyToGainID);
        facultyToGain.listOfAdvisees->insertFront(idNumToSearch);
        studentToChange.setFacID(facultyToGainID);
      }else{
        cout<<"Please use a faculty that exists, or type -1 to exit"<<endl;
      }
    }
    if(shouldbreak == 1){
      return;
    }
    //delets based off of number of advisses in list
    int numOFAddvisees = facultyToLose.listOfAdvisees->getSize();
    if(numOFAddvisees >= 3){
      facultyToLose.listOfAdvisees->remove(idNumToSearch);
    }else if(numOFAddvisees == 2){
      if(facultyToLose.listOfAdvisees->peekFront() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeFront();
      }else if(facultyToLose.listOfAdvisees->peekRear() == idNumToSearch){
        facultyToLose.listOfAdvisees->removeBack();
      }
    }else{
      facultyToLose.listOfAdvisees->removeFront();
    }

    masterStudent->deleteNode(idNumToSearch);
    masterStudent->insert(studentToChange);
    g1->push(DBTransaction(2,idNumToSearch,facultyToGainID,facultyToLose.IDnum));//student,new,old
    increaseRollCounter();
  }else{
    cout<<"Please enter a ID number for the faculty that exists and ID for student that exists"<<endl;
  }

}

//rolls back up to the previous 5 actions that were done for delete or adding of faculty or students
void DatabaseDriver::rollback(){
  if(g1->count > 0 && rollbackCounter > 0){
    rollbackCounter--;
    rolled = DBTransaction(g1->pop());
    int type = rolled.tnx_type;
    int objType = rolled.objType;
    if(type == 0){
      if(objType == 0){
        masterStudent->insert(rolled.studentObject);

        int FacIDGaining = rolled.studentObject.facID;
        faculty facGaining = masterFaculty->search(FacIDGaining);
        facGaining.listOfAdvisees->insertFront(rolled.studentObject.IDnum);
        cout<<"Inserted: ";
        cout<<rolled.studentObject<<endl;
      }else if(objType == 1){
        masterFaculty->insert(rolled.facultyObject);
        cout<<"Inserted: ";
        cout<<rolled.facultyObject<<endl;

      }
    }else if(type == 1){
      if(objType == 0){
        masterStudent->deleteNode(rolled.studentObject.IDnum);

        int facultyToLoseID = rolled.studentObject.facID;
        faculty facultyToLose = masterFaculty->search(facultyToLoseID);
        int numOFAddvisees = facultyToLose.listOfAdvisees->getSize();
        //delets based off of number of advisses in list
        if(numOFAddvisees >= 3){
          facultyToLose.listOfAdvisees->remove(rolled.studentObject.IDnum);
        }else if(numOFAddvisees == 2){
          if(facultyToLose.listOfAdvisees->peekFront() == rolled.studentObject.IDnum){
            facultyToLose.listOfAdvisees->removeFront();
          }else if(facultyToLose.listOfAdvisees->peekRear() == rolled.studentObject.IDnum){
            facultyToLose.listOfAdvisees->removeBack();
          }
        }else{
          facultyToLose.listOfAdvisees->removeFront();
        }
        cout<<"Removed: ";
        cout<<rolled.studentObject<<endl;
      }else if(objType == 1){
        masterFaculty->deleteNode(rolled.facultyObject.IDnum);
        cout<<"Removed: ";
        cout<<rolled.facultyObject<<endl;
      }
    }else if(type == 2){
      //student object gets oldFacultyID advisor
      student studentToInsert = masterStudent->search(rolled.studentID);
      studentToInsert.facID = rolled.oldFacultyID;
      masterStudent->deleteNode(rolled.studentID);
      masterStudent->insert(studentToInsert);
      //facultyObject loses advisse of studentsID
      faculty facultyToLose = masterFaculty->search(rolled.newFacultyID);
      int numOFAddvisees = facultyToLose.listOfAdvisees->getSize();
      if(numOFAddvisees >= 3){
        facultyToLose.listOfAdvisees->remove(studentToInsert.IDnum);
      }else if(numOFAddvisees == 2){
        if(facultyToLose.listOfAdvisees->peekFront() == studentToInsert.IDnum){
          facultyToLose.listOfAdvisees->removeFront();
        }else if(facultyToLose.listOfAdvisees->peekRear() == studentToInsert.IDnum){
          facultyToLose.listOfAdvisees->removeBack();
        }
      }else{
        facultyToLose.listOfAdvisees->removeFront();
      }
      //oldFacultyID searches for masterFaculty and gets studentID as advisee
      faculty facultyToGain = masterFaculty->search(rolled.oldFacultyID);
      facultyToGain.listOfAdvisees->insertFront(rolled.studentID);
    }
  }
  else{
    cout<<"There is nothing in the rollback history"<<endl;
  }

}

//Runs when program is done, puts faculty and student info into files studentTable and facultyTable
//line one is the number of those faculty or students and then all of the other lines are CSVS of thier info.
void DatabaseDriver::outputDatabaseToFile(){
  f1.makeOutFiles();
  int lineNumber = 0;
  string numberOfStud = to_string(masterStudent->numOfNodes);
  f1.printToStudentFile(numberOfStud);
  while(true){
    if(!masterStudent->isEmpty()){
      break;
    }
    student studentToPrint = masterStudent->root->key;
    string IDNumToStore = to_string(studentToPrint.IDnum);
    string nameToStore = studentToPrint.name;
    string levelToStore = studentToPrint.level;
    string majorToStore = studentToPrint.major;
    string gpaToStore = to_string(studentToPrint.gpa);
    string facultyIDtoStore = to_string(studentToPrint.facID);

    string toOutput = IDNumToStore + "," + nameToStore + "," + levelToStore + "," + majorToStore + "," + gpaToStore + "," + facultyIDtoStore;
    f1.printToStudentFile(toOutput);
    masterStudent->deleteNode(studentToPrint.IDnum);
  }

  string numberOfFac = to_string(masterFaculty->numOfNodes);
  f1.printToFacultyFile(numberOfFac);
  while(true){
    if(!masterFaculty->isEmpty()){
      break;
    }
    faculty facultyToPrint = masterFaculty->root->key;
    string IDNumToStore = to_string(facultyToPrint.IDnum);
    string nameToStore = facultyToPrint.name;
    string levelToStore = facultyToPrint.level;
    string depToStore = facultyToPrint.department;
    string toOutput = IDNumToStore + "," + nameToStore + "," + levelToStore + "," + depToStore; //+ ","
    while(!facultyToPrint.listOfAdvisees->isEmpty()){
      toOutput = toOutput + "," + to_string(facultyToPrint.listOfAdvisees->removeFront());
    }
    f1.printToFacultyFile(toOutput);
    masterFaculty->deleteNode(facultyToPrint.IDnum);
  }
}

//changes students major given a ID num
void DatabaseDriver::changeStudentMajor(int idNumToSearch){
  if(masterStudent->contains(idNumToSearch)){
    string newMajor = "";
    cout<<"What major do you wish to change it to"<<endl;
    cin>> newMajor;
    student newVersion = masterStudent->search(idNumToSearch);
    masterStudent->deleteNode(idNumToSearch);
    newVersion.major = newMajor;
    masterStudent->insert(newVersion);
  }else{
    cout<<"Wasn't able to change the Major, ID does not exist in database"<<endl;
  }
}

//changes a facultys department given a ID num
void DatabaseDriver::changeFacultyDepartment(int idNumToSearch){
  if(masterFaculty->contains(idNumToSearch)){
    string newDep = "";
    cout<<"What department do you wish to change it to"<<endl;
    cin>> newDep;
    faculty newVersion = masterFaculty->search(idNumToSearch);
    masterFaculty->deleteNode(idNumToSearch);
    newVersion.department = newDep;
    masterFaculty->insert(newVersion);
  }else{
    cout<<"Wasn't able to change the Department, ID does not exist in database"<<endl;
  }
}

void DatabaseDriver::increaseRollCounter(){
  if(rollbackCounter <5){
    rollbackCounter=rollbackCounter + 1;
  }
}
