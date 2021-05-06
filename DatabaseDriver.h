#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include "faculty.h"
#include "student.h"
#include "BST.h"

#include "DBTransaction.h"
#include "GenStack.h"

#include "FileProcessor.h"

#include <iostream>


using namespace std;

//handles the majority of database happenings
class DatabaseDriver{
  public:
    DatabaseDriver();
    DatabaseDriver(bool studentFile, bool facultyFile);
    ~DatabaseDriver();

    student loadStudentFromFile(int lineNumber);
    faculty loadFacultyFromFile(int lineNumber);

    void MainMethod();
    void ListMenuOptions();
    void printAllStudents();
    void printAllFaculty();
    void printSpecificStudent(int idNumToSearch);
    void printSpecificFaculty(int idNumToSearch);
    void printAdvisingFacInfo(int idNumToSearch);
    void printAdviseesInfo(int idNumToSearch);

    void addNewStudent();
    void deleteStudent(int idNumToSearch);

    void addNewFaculty();
    void deleteFaculty(int idNumToSearch);

    void changeAdvisor(int idNumToSearch,int idForAdvisor);
    void removeAdvisee(int idNumToSearch);

    void rollback(); //monka

    void outputDatabaseToFile();

    void changeStudentMajor(int idNumToSearch);
    void changeFacultyDepartment(int idNumToSearch);

    int getIntFromUser();
    double getDoubFromUser();

    void increaseRollCounter();

    BST<student> *masterStudent;
    BST<faculty> *masterFaculty;
    GenStack<DBTransaction> *g1;

    DBTransaction rolled;

    FileProcessor f1;
    int rollbackCounter;
};

#endif
