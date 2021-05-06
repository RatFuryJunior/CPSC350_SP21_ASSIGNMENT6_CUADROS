#ifndef FILEPPROCESSOR_H
#define FILEPPROCESSOR_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
//handles reading and writing for the class
class FileProcessor{
  public:
    FileProcessor();
    ~FileProcessor();
    string loadForStudent(int lineNumber);
    string loadForFaculty(int lineNumber);
    bool facultyFileExists();
    bool studentFileExists();

    void makeOutFiles();
    void printToStudentFile(string line);
    void printToFacultyFile(string line);
    int numberOfLines(string inputFile);
};

#endif
