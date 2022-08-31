//
//  Student.cpp
//  Project 2
//
//  Created by Sal on 4/3/22.
//

#include <stdio.h>
#include "MyParser.hpp"

Student::Student (int Student_ID, std::string name, unsigned short age)
{                // Constructor for assigning Student information to student object
  this->Student_ID = Student_ID;
  this->name = name;
  this->age = age;
}
unsigned int Student::getStudent_ID() const{
    return Student_ID;
}
unsigned short Student::getAge () const
{
  return age;
}
std::string Student::getName() const {
    return name;
}


