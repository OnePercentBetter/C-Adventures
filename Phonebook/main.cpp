//
//  main.cpp
//  Project 2
//
//  Created by Sal on 3/15/22.
//
#include "MyParser.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class MyManager;

int main()
{
    MyManager  engine;

    Myparser  parser;// its ok to not have a parametrized constructor and have a fixed set of separators inside a class
    std::string  userInput;
    bool  shouldStop{false};
    //keep going while should stop is not true
    while(!shouldStop)
    {
          getline(cin, userInput); // pay attention, pure cin doesn't allow spaces or tabs in userInput
          const vector<string>& command = parser(userInput);
          if (command.size() > 0)
          {
              shouldStop = engine.processor(command);
          }
    }

   return 0;
}


