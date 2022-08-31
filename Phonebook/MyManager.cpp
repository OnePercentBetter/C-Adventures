//
//  MyManager.cpp
//  Project 2
//
//  Created by Sal on 4/3/22.
//

#include "MyParser.hpp"
#include <stdio.h>
#include <string>

MyManager::MyManager()
{
    Scontainer = manage.createfile();
}

MyManager::~MyManager()
{
    manage.printfile(Scontainer);
}

bool MyManager::ADD(std::vector<std::string>str){
    if(str.size() > 4){
        return false;
    }
    if(str.empty()){
        return false;
    }
    if(!stoi(str[3])){
        return false;
    }
    int id = std::stoi (str[1]);
    int age = std::stoi (str[3]);
    std::string name = str[2];
    if (id < 1)
      {
    return false;
      }
    if (age < 1)
      {
    return false;
      }
    if (name.empty ())
      {
    return false;
      }
    
    Student Object {id, name, (unsigned short) age};    // c-style cast;
    Scontainer.push_back (Object);
    return true;
}
void MyManager::FIND(std::vector<std::string > str){
    if(str.size() > 4){
        std::cout << "bad command!!!" << std::endl;
        return;
    }
    if(str[1] == "age"){
        if(str[2] == ">"){
            for (size_t i = 0; i < Scontainer.size(); i++) {
                if (Scontainer[i].getAge() > stoi(str[3])) {
                    std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge() << std::endl;
                }
            }
            if(stoi(str[3])){
                
            }
        }
        if(str[2] == "<"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getAge() < stoi(str[3])){
                        std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge()<< std::endl;
                    }
                }
            }
        }
        if(str[2] == "="){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getAge() == stoi(str[3])){
                        std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge() << std::endl;
                    }
                }
            }
        }
    }
    
    
    if(str[1] == "name"){
        for(size_t i = 0; i < Scontainer.size();i++){
            if(Scontainer[i].getName() == str[3]){
                std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge() << std::endl;
            }
        }
    }
    
    if(str[1] == "id"){
        if(str[2] == ">"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() > stoi(str[3])){
                        std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge()<< std::endl;
                    }
                }
            }
        }
        if(str[2] == "<"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() < stoi(str[3])){
                        std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge()<< std::endl;
                    }
                }
            }
        }
        if(str[2] == "="){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() == stoi(str[3])){
                        std::cout << Scontainer[i].getStudent_ID() << " " << Scontainer[i].getName() << " " << Scontainer[i].getAge() << std::endl;
                        
                    }
                }
            }
        }
    }
} // switch case for types of operators

void MyManager::REMOVE(std::vector <std::string> str){
    if(str.size() > 4){
        std::cout << "bad command!!!" << std::endl;
        return;
    }
    if(str[1] == "age"){
        if(str[2] == ">"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getAge() > stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }else{
                std::cout << "bad command!!!" << std::endl;
                return;
            }
        }
        if(str[2] == "<"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getAge() < stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }else{
                std::cout << "bad command!!!" << std::endl;
                return;
            }
        }
        if(str[2] == "="){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getAge() == stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }else{
                std::cout << "bad command!!!" << std::endl;
                return;
            }
        }
    }
    
    
    if(str[1] == "name"){
        for(size_t i = 0; i < Scontainer.size();i++){
            if(Scontainer[i].getName() == str[3]){
                Scontainer.erase(Scontainer.begin() + i);
            }
        }
    }
    
    if(str[1] == "id"){
        if(str[2] == ">"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() > stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }
        }
        if(str[2] == "<"){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() < stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }else{
                std::cout << "bad command!!!" << std::endl;
                return;
                
            }
        }
        if(str[2] == "="){
            if(stoi(str[3])){
                for(size_t i = 0; i < Scontainer.size();i++){
                    if(Scontainer[i].getStudent_ID() == stoi(str[3])){
                        Scontainer.erase(Scontainer.begin() + i);
                    }
                }
            }
        }
    }
}
bool MyManager::STOP(std::vector < std::string >str){
    return false;
}

//the return value of this is (shouldStop = processor)
bool MyManager::processor(std::vector<std::string>str){
    if(str.empty()){
        std::cout<< "bad command!!!" << std::endl;
        return false;
    }
    if(str[0] == "Empty"){
        std::cout<< "bad command!!!" << std::endl;
        return false;
    }
    if(str[0] == "ADD"){
        if(ADD(str) == true){
            return false;
        }
        //return false;
    }else if(str[0] == "FIND"){
        FIND(str);
        return false;
    }else if(str[0] == "REMOVE"){
        REMOVE(str);
        return false;
    }else if(str[0] == "STOP"){
        STOP(str);
        return true;
    }else{
        std::cout<<"bad command!!!"<<std::endl;
        return false;
    }

}
