#pragma once

#include <iostream>
#include <string>
#include <cctype>

int GetUserChoice(int max, std::string prompt);
std::string RemoveSpaces(std::string str);
bool CheckValidName(std::string name);
bool CheckValidID(int id);
std::string StripString(std::string str);
