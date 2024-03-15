#include "passwordManager.hpp"

PasswordManager::PasswordManager(std::string lf) : 
    encryptionKey(5){
    loginFile = lf;
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

void PasswordManager::PrintUserList(){
    std::fstream fileHandle;
    fileHandle.open(loginFile, std::ios::in);
    assert(fileHandle.is_open());  // file not found
    std::string line;
    std::getline(fileHandle, line);  // skip header
    std::cout << std::format("|{:^20}|{:^20}|", "Username", "Password") << std::endl;
    while (std::getline(fileHandle, line)){
        std::string un = line.substr(0, line.find(","));
        std::string pw = line.substr(line.find(",") + 1);
        std::cout << std::format("|{:^20}|{:^20}|", un, Decrypt(pw)) << std::endl;
    }
    fileHandle.close();

}

void PasswordManager::RegisterUser(){
    std::fstream fileHandle;
    fileHandle.open(loginFile, std::ios::in);
    assert(fileHandle.is_open());  // file not found 

    std::string un = "-1";
    while (!ValidateUsername(un)){
        std::cout << "Enter your username (no numbers or special characters): ";
        std::getline(std::cin, un);
        if (UserExists(un)){
            std::cout << "Username already exists" << std::endl;
            un = "-1";
        }
    }

    std::string pw;
    do {
        std::cout << "Enter your password: ";
        std::getline(std::cin, pw);
    } while (!ValidatePassword(pw));
    
    std::string encryptedPW = Encrypt(StripString(pw));
    
    WriteToFile(loginFile, StripString(un) + "," + encryptedPW);
    fileHandle.close();
}

bool PasswordManager::ValidateUsername(std::string un){
    for (char s : un)
        if (!isalpha(s) && s != ' ')
            return false;
    return true;
}

bool PasswordManager::UserExists(std::string un){
    std::fstream fileHandle;
    fileHandle.open(loginFile, std::ios::in);
    assert(fileHandle.is_open());  // file not found 

    std::string line;
    std::getline(fileHandle, line);  // skip header
    while (std::getline(fileHandle, line)){
        std::string username = line.substr(0, line.find(","));
        if (username == un)
            return true;
    }
    return false;
}

bool PasswordManager::ValidatePassword(std::string pw){
	bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    for (char s : pw){
        if (islower(s))
            hasLower = true;
        else if (isupper(s))
            hasUpper = true;
        else if (isdigit(s))
            hasDigit = true;
        else if (ispunct(s))
            hasSpecial = true;
    }
    if (pw.length() < 8){
        std::cout << "Password must be at least 8 characters long" << std::endl;
        return false;
    }
    if (!hasLower){
        std::cout << "Password must contain at least one lowercase letter" << std::endl;
        return false;
    }
    if (!hasUpper){
        std::cout << "Password must contain at least one uppercase letter" << std::endl;
        return false;
    }
    if (!hasDigit){
        std::cout << "Password must contain at least one digit" << std::endl;
        return false;
    }
    if (!hasSpecial){
        std::cout << "Password must contain at least one special character" << std::endl;
        return false;
    }
    return true;

}

void PasswordManager::WriteToFile(std::string fileHandle, std::string line){
    std::fstream file;
    file.open(fileHandle, std::ios::app);
    assert(file.is_open());  // file not found 
    file << line << std::endl;
    file.close();
}

std::string PasswordManager::StripString(std::string s){
    std::string stripped;
    for (char c : s){
        if (c != ' ')
            stripped += c;
    }
    return stripped;
}

bool PasswordManager::Login(){
    std::fstream fileHandle;
    fileHandle.open(loginFile, std::ios::in);
    assert(fileHandle.is_open());  // file not found 

    std::string un;
    std::cout << "Enter your username: ";
    std::cin.ignore();
    std::getline(std::cin, un);
    if (!UserExists(un)){
        std::cout << "Username does not exist" << std::endl;
        return false;
    }

    std::string pw;
    std::cout << "Enter your password: ";
    std::getline(std::cin, pw);
    std::string encryptedPW = Encrypt(StripString(pw));
    std::string line;
    std::getline(fileHandle, line);  // skip header
    while (std::getline(fileHandle, line)){
        std::string username = line.substr(0, line.find(","));
        std::string password = line.substr(line.find(",") + 1);
        if (username == un && password == encryptedPW){
            fileHandle.close();
            return true;
        }
    }
    fileHandle.close();
    std::cout << "Incorrect password" << std::endl;
    return false;
}