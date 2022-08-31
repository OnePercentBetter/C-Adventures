//
//  DiskManagement.cpp
//  Project 2
//
//  Created by Sal on 4/3/22.
//

#include <stdio.h>
#include "MyParser.hpp"
#include <string>

DiskManagement::DiskManagement()
{

}

std::vector<Student> DiskManagement::createfile(std::string filename){
    Myparser parser;
    std::string input; //input data from file
    std::vector<Student> Container;
    
    std::fstream my_file;
    my_file.open(filename);
    if (!my_file.is_open())
        return Container;

    if(my_file.fail()){
        std::ofstream my_file(filename);
    }
    //my_file.open(filename);
    while(!my_file.eof()){
        std::vector<std::string> currentd;
        getline(my_file,input);
        //if input is empty, the file is empty
        if (input.empty())
            break;
        currentd = parser(input);
        int id = std::stoi(currentd[0]);
        std::string name = currentd [1];
        unsigned short age_ID= std::stoi(currentd[2]);
        Student Object { id,name,age_ID};
        Container.push_back(Object);
    }
    return Container;
}
void DiskManagement::printfile(const std::vector<Student>& container,std::string filename){
       std::ofstream ofs(filename, std::ofstream::trunc);
       for(size_t i = 0; i < container.size();i++){
           ofs << container[i].getStudent_ID() << " " << "\""<< container[i].getName() << "\"" << " " << container[i].getAge() << std::endl;
       }
}
