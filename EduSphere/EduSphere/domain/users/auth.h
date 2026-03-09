#ifndef AUTH_H
#define AUTH_H

#include "../../config/libraries.h"

std::string hashPassword(const std::string& password);
bool registerUser(std::string& loggedUsername, int& loggedUserID);
bool loginUser(std::string& loggedUsername, int& loggedUserID);
void authMenu(std::string& loggedUsername, int& loggedUserID);

#endif