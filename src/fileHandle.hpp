#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <format>
#include <sstream>
#include <cassert>
#include "inputHandle.hpp"


class FileHandle{
protected:
    std::string fileName;
    int lastID;
    int IDcount;
public:
    FileHandle(std::string fn);
    virtual void Add();
    virtual void Display();
    virtual void Delete();
};