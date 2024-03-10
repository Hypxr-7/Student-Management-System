#include "passwordManager.hpp"

PasswordManager::PasswordManager(std::string pw) : 
    password(pw),
    encryptionKey(5){
    std::cout << "Password Manager Created" << std::endl;
}

std::string PasswordManager::Encrypt(std::string plainText){
    std::string cipherText;
    for (char s : plainText){
        cipherText += s + encryptionKey;
    }
    return cipherText;
}

std::string PasswordManager::Decrypt(std::string cipherText){
    std::string plainText;
    for (char s : cipherText){
        plainText += s - encryptionKey;
    }
    return plainText;
}

void PasswordManager::print(){
    std::string pt = Encrypt("Hello World");
    std::cout << "Encrypted Message: " << pt << std::endl;
    std::string ct = Decrypt(pt);
    std::cout << "Decrypted Message: " << ct << std::endl; 
}