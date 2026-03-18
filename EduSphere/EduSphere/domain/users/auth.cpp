#include "auth.h"
#include "../../config/libraries.h"
#include "../../visuals/title.h"

// Returns a hex string hash of the given password.
std::string hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    size_t hashed = hasher(password);
    std::stringstream ss;
    ss << std::hex << hashed;
    return ss.str();
}

// Loads the accounts JSON file, returning an empty user list on failure.
json loadAccounts() {
    std::ifstream file("accounts.json");
    if (!file.is_open()) return json{ {"users", json::array()} };
    json j;
    try {
        file >> j;
    }
    catch (...) {
        j = json{ {"users", json::array()} };
    }
    return j;
}

// Writes the accounts JSON to accounts.json, overwriting existing content.
void saveAccounts(const json& j) {
    std::ofstream file("accounts.json", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "\033[31mFailed to ope n accounts.json\033[0m" << std::endl;
        return;
    }
    file << std::setw(4) << j << std::endl;
    file.close();
}

// Prompts for a new username/password, creates the account, and logs in.
bool registerUser(std::string& loggedUsername, int& loggedUserID) {
    displayTitle();
    json accounts = loadAccounts();
    std::string username, password;
    std::cout << "\033[38;5;208mEnter new username: \033[0m";
    std::cin >> username;

    for (auto& u : accounts["users"])
        if (u["username"] == username) {
            std::cout << "\033[31mUsername is already taken!\033[0m" << std::endl;
            return false;
        }

    std::cout << "\033[38;5;208mEnter password: \033[0m";
    std::cin >> password;

    int maxID = 0;
    for (auto& u : accounts["users"])
        if (u["id"].is_number() && u["id"] > maxID) maxID = u["id"];

    int newID = maxID + 1;
    json newUser = {
        {"id", newID},
        {"username", username},
        {"password", hashPassword(password)}
    };

    accounts["users"].push_back(newUser);
    saveAccounts(accounts);
    loggedUsername = username;
    loggedUserID = newID;
    std::cout << "\033[38;5;120m• Registration successful! Logged in as " << username << "\033[0m" << std::endl;
    return true;
}

// Validates credentials and sets the logged-in user if correct.
bool loginUser(std::string& loggedUsername, int& loggedUserID) {
    displayTitle();
    json accounts = loadAccounts();
    std::string username, password;
    std::cout << "\033[38;5;208mEnter username: \033[0m";
    std::cin >> username;
    std::cout << "\033[38;5;208mEnter password: \033[0m";
    std::cin >> password;
    std::string hashed = hashPassword(password);

    for (auto& u : accounts["users"])
        if (u["username"] == username && u["password"] == hashed) {
            loggedUsername = username;
            loggedUserID = u["id"].get<int>();
            std::cout << "\033[38;5;120m• Login successful! Welcome, " << username << "\033[0m" << std::endl;
            return true;
        }

    std::cout << "\033[31m• Invalid username or password!\033[0m" << std::endl;
    std::cout << std::endl;
    return false;
}

// Loops the login/register menu until the user successfully authenticates.
void authMenu(std::string& loggedUsername, int& loggedUserID) {
    bool logged = false;
    while (!logged) {
        std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m│  AUTHENTICATION   │\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
        std::cout << "\033[38;5;223m1. Register\033[0m" << std::endl;
        std::cout << "\033[38;5;223m2. Login\033[0m" << std::endl;
        std::cout << "\033[38;5;223m0. Exit\033[0m" << std::endl;
        std::cout << "\033[38;5;208m• Choice: \033[0m";
        int choice;
        std::cin >> choice;
        system("cls");

        switch (choice) {
        case 1: logged = registerUser(loggedUsername, loggedUserID); break;
        case 2: logged = loginUser(loggedUsername, loggedUserID); break;
        case 0: exit(0);
        default: std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
        }
    }
}