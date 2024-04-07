#include "passwordManager.hpp"

int main(){
    PasswordManager pm("../data/login.csv");
    pm.RegisterUser();
    pm.PrintUserList();
    return 0;
}