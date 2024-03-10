#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class PasswordManager {
private:
    std::string password;
    std::string username;
    int encryptionKey;
    std::string Encrypt(std::string plainText);
    std::string Decrypt(std::string cipherText);
    bool IsPrime(int number);
public:
    PasswordManager(std::string pw);
    void print();

};