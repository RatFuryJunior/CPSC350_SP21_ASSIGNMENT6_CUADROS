#include <iostream>
#include "DatabaseDriver.h"
#include "FileProcessor.h"
int main(int argc, char **argv) {

  FileProcessor f1 = FileProcessor();
  bool StudentExists = f1.studentFileExists();
  bool FacultyExists = f1.facultyFileExists();

  DatabaseDriver d1 = DatabaseDriver();
  if(StudentExists || FacultyExists){
    DatabaseDriver d1 = DatabaseDriver(StudentExists,FacultyExists);
    d1.MainMethod();
  }else{
    d1.MainMethod();
  }

  return 0;
}
