::ReadMe::
Nathaniel Cuadros
002343116
Cuadros@chapman.edu
CPSC 350 Spring 2021
Assignment #6

Contents:
  main.cpp
  DatabaseDriver.h
  DatabaseDriver.cpp
  GenStack.h
  DoublyLinkedList.h
  ListNode.h
  TreeNode.h
  BST.h
  DB_transaction.h
  DB_transaction.cpp
  FileProcessor.cpp
  FileProcessor.h
  faculty.h
  faculty.cpp
  person.h
  person.cpp
  student.h
  student.cpp
  Makefile
References:
  Used office hours.
  Talked with Ian as a pseudo-partner on certain parts but not as a full code partner
  used thinking of this https://www.codespeedy.com/comma-separated-string-to-array-in-cpp/ for loading back faculty
Instructions:
  makefile creates an executable or just run g++ *.cpp -o output.out
  Database saves and loads to the files "studentTable.txt" and "facultyTable.txt"
ExtraCredit:
  Option 15 Change Major
  Option 16 Change Department
  Rollback works for option 11
  Rollback works for option 12
KnownErrors:
  Seg fault in faculty output to file whenever too many rollbacks are done (5+)
