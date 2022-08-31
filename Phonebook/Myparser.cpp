 //
//  Myparser.cpp
//  Project 2
//
//  Created by Sal on 4/3/22.
//

#include <stdio.h>
#include <vector>
#include "MyParser.hpp"
std::vector<std::string>Myparser::operator()(std::string command){
    tokens.clear();
    bool empt;
    for(int i = 0; i < command.length();i++){
        if(command[i] == ' ' || command[i] == '\t'){
            empt = true;
        }else{
            empt = false;
            break;
        }
    }
    if(empt == true){
        tokens.push_back("Empty");
        tokens.push_back("Empty");
        tokens.push_back("Empty");
        tokens.push_back("Empty");
        return tokens;
    }
    std::string temporary;
    tokens.clear();
    std::string test;
    int counter = 0;
    for (int i = 0; i < command.length (); ++i)
      {
    if (command[i] == '"')
      {
        counter++;
        int secondQuote = (int) command.find ('"', i + 1);
        counter++;
        int nameSize = secondQuote - i - 1;
          test = command.substr (i + 1, nameSize);
          tokens.push_back (test);
          test.clear ();
          i = secondQuote + 1;
          if(counter > 3){
              std::cout << "bad command!!!" << std::endl;
              return {};
          }
      }
    if (command[i] == space || command[i] == tab){
        if(test.empty()){
            continue;
        }
        tokens.push_back (test);
        test.clear ();
        continue;
      }
    if (command[i] == '<' || command[i] == '>' || command[i] == '='){
        if(isalpha(command[i-1])){
            tokens.push_back(test);
            test.clear();
        }
        std::string op = " ";
        op[0] = command[i];
        tokens.push_back (op);
        continue;
      }
    else
      {
        test += command[i];
        if (i == command.length () - 1)
          {
            tokens.push_back (test);
            test.clear ();
          }
      } 
    }
    return tokens;
}
