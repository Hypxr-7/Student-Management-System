#pragma once

#include <iostream>
#include <string>
#include <cctype>

class InputHandle{
public:
    int GetUserChoice(int max);
    std::string RemoveSpaces(std::string str);
    bool CheckValidName(std::string name);
    bool CheckValidID(int id);

};