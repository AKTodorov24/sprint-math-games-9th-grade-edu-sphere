#ifndef AUTH_H
#define AUTH_H

#include "../../config/libraries.h"

std::string hashPassword(const std::string& password);
bool registerUser(std::string& loggedUsername);
bool loginUser(std::string& loggedUsername);
void authMenu(std::string& loggedUsername);

#endif