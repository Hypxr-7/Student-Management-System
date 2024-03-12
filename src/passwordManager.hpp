#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <cassert>
#include <cctype>
#include <format>

class PasswordManager {
private:
    int encryptionKey;
    std::string Encrypt(std::string plainText);
    std::string Decrypt(std::string cipherText);
    bool ValidateUsername(std::string un);
    bool UserExists(std::string un);
    bool ValidatePassword(std::string pw);
    void WriteToFile(std::string fileHandle, std::string line);
    std::string StripString(std::string s);
public:
    PasswordManager();
    void RegisterUser();
    bool Login();
    void PrintUserList();

};