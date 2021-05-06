#include "FileProcessor.h"

using namespace std;
FileProcessor::FileProcessor(){

}
FileProcessor::~FileProcessor(){

}
//takes the line number entered and gives out the string line at that line num for the student file
string FileProcessor::loadForStudent(int lineNumber){
  ifstream inFile;
  inFile.open("studentTable.txt");
  if (!inFile.is_open()) {
    cout<<"Something went wrong, check the name of the file"<<endl;
  }
  string toRet = "";
  for (int i = 0; i < lineNumber;++i){
    getline(inFile, toRet);
    int pos = 0;
    while ((pos = toRet.find ("\n",pos)) != string::npos) //https://texthandler.com/info/remove-line-breaks-c/
    {
      pos = pos+1;
      toRet.erase ( pos, 2 );
    }

  }
  inFile.close();
  return toRet;
}

//takes the line number entered and gives out the string line at that line num for the faculty file
string FileProcessor::loadForFaculty(int lineNumber){
  ifstream inFile;
  inFile.open("facultyTable.txt");
  if (!inFile.is_open()) {
    cout<<"Something went wrong, check the name of the file"<<endl;
  }
  string toRet = "";
  for (int i = 0; i < lineNumber;++i){
    getline(inFile, toRet);
    int pos = 0;
    while ((pos = toRet.find ("\n",pos)) != string::npos) //https://texthandler.com/info/remove-line-breaks-c/
    {
      pos = pos+1;
      toRet.erase ( pos, 2 );
    }

  }
  inFile.close();
  return toRet;
}

//returns a bool of if the file exists or not
bool FileProcessor::facultyFileExists(){
  ifstream inFile;
  inFile.open("facultyTable.txt");
  if (!inFile.is_open()) {
    return false;
  }else{
    return true;
  }
}

//returns a bool of if the file exists or not
bool FileProcessor::studentFileExists(){
  ifstream inFile;
  inFile.open("studentTable.txt");
  if (!inFile.is_open()) {
    return false;
  }else{
    return true;
  }
}

//makes the files facultyTable and studentTable if they dont exist
void FileProcessor::makeOutFiles(){//creates a new empyy file for dnaoutput
  ofstream outFile;
  ofstream outFile2;
  outFile.open ("facultyTable.txt");
  outFile2.open("studentTable.txt");
  outFile.close();
  outFile2.close();
}

//prints out to the file for student
void FileProcessor::printToStudentFile(string line){//prints to the made file
    ofstream outFile;
    outFile.open ("studentTable.txt",std::ios_base::app);
    outFile<<line<<endl;
    outFile.close();
}

//prints out to the file for faculty
void FileProcessor::printToFacultyFile(string line){//prints to the made file
    ofstream outFile;
    outFile.open ("facultyTable.txt",std::ios_base::app);
    outFile<<line<<endl;
    outFile.close();
}

//returns the number of lines in the given file
int FileProcessor::numberOfLines(string inputFile){//returns number of lines from the given file name
  int lineCount = 0;
  ifstream inFile;
  string line;
  inFile.open (inputFile);
  if(inFile.is_open()){
    while (getline(inFile, line)){
      lineCount++;
    }
    inFile.close();
  }
  return lineCount;
}
