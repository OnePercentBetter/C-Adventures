
//  MyParser.hpp
//  Project 2
//
//  Created by Sal on 3/29/22.
//

#ifndef MyParser_hpp
#define MyParser_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
class Student
{
public:
  Student ();
    Student (int Student_ID, std::string name, unsigned short age);
  unsigned int getStudent_ID () const;

  std::string getName () const;

  unsigned short getAge () const;
  private:
  unsigned int Student_ID;
  std::string name;
  unsigned short age;
};
/////////////////////////////////////////////////////////


/* Idea for parser is to run through all of the operations after being saved, and the individually parse them after the user has stopped input. This will mease the burden of parsing strings right at runtime but instead at the end of runtime*/
class Myparser
{
public:
  char space = ' ';
  char tab = '\t';
    std::vector < std::string > tokens;
    Myparser () = default;
  // Format is Method ID Name age
    std::vector < std::string > operator  () (std::string command);
};
class DiskManagement
{
public:
    DiskManagement();
    std::vector<Student> createfile(std::string filename = "text.txt");
    void printfile(const std::vector<Student>& container,std::string filename = "text.txt");
};
//After being parsed, runs through the string and assigns the variables to the data member
// uses all the other classes to first parse, then use the parser
class MyManager
{
public:
  MyManager ();
  ~MyManager();
  std::vector<Student>Scontainer;
  DiskManagement manage;
    bool ADD (std::vector < std::string > str);
            // switch case for types of operators such as < > =
    void FIND (std::vector < std::string > str);//
                    // switch case for types of operators such as < >
    void REMOVE (std::vector < std::string > str);
    bool STOP(std::vector < std::string > str);
// switch case for types of operators such as < > =    // Stops everything, calls disk management class to sync all the information into the file
  bool processor(std::vector<std::string> str);
};
/* Idea */


#endif /* MyParser_hpp */



/* After the input is parsed into a vector of tokens, we take that vector and dissect it in the MyManager function.*/
