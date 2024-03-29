#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
// #include <format>
#include <sstream>
#include <iomanip>
// #include <map>

class File{
private:
    std::string path;                   // Path to the file
    std::string fileName;               // Name of the file
    std::vector<std::string> headers;   // Headers of the file
    int IDCounter;                      // Counter for the ID of the lines
    int lastID;                         // ID of the last line
public:
    File(std::string path_, std::string fileName_);
    void AddToFile(std::string text);
    void DisplayFile();
    void DeleteFromFile(int ID);

    void temp_displayAttributes(){
        std::cout << "Path: " << path << std::endl;
        std::cout << "File Name: " << fileName << std::endl;
        std::cout << "ID Counter: " << IDCounter << std::endl;
        std::cout << "Last ID: " << lastID << std::endl;
        std::cout << "Headers: ";
        for (auto header : headers){
            std::cout << header << " ";
        }
    }
};