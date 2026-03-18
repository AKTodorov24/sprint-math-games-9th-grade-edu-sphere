#include "mainMenu.h"
#include "../config/libraries.h"
#include "title.h"
#include "learningContent.h"
#include "practiceQuestions.h"
#include "homework.h"
#include "generateTest.h"
#include "myTestResults.h"
#include "studentStatistics.h"

static std::string sessionUsername;
static int sessionUserID = 0;

// Displays the main menu and returns the user's selected option.
MenuOption mainMenu(const std::string& username, int userID) {
    sessionUsername = username;
    sessionUserID = userID;

    displayTitle();
    std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m│        MAIN MENU        │\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
    std::cout << "\033[38;5;223mLogged in as: \033[38;5;120m" << sessionUsername
              << "\033[90m  (ID: " << sessionUserID << ")\033[0m\n" << std::endl;

    std::cout << "\033[38;5;223m1. Learning Content\033[0m" << std::endl;
    std::cout << "\033[38;5;223m2. Exercise Tasks\033[0m" << std::endl;
    std::cout << "\033[38;5;223m3. Homework\033[0m" << std::endl;
    std::cout << "\033[38;5;223m4. Generate Test\033[0m" << std::endl;
    std::cout << "\033[38;5;223m5. My Test Results\033[0m" << std::endl;
    std::cout << "\033[38;5;223m6. Student Statistics\033[0m" << std::endl;
    std::cout << "\033[38;5;223m0. Exit\033[0m" << std::endl;
    std::cout << "\033[38;5;208m• Choice: \033[0m";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: return MenuOption::LearningContent;
    case 2: return MenuOption::ExerciseTasks;
    case 3: return MenuOption::Homework;
    case 4: return MenuOption::GenerateTest;
    case 5: return MenuOption::MyTestResults;
    case 6: return MenuOption::Statistics;
    case 0: return MenuOption::Exit;
    default:
        std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
        return mainMenu(sessionUsername, sessionUserID);
    }
}

// Main application loop that dispatches to each feature based on menu selection.
void runApp(const std::string& username, int userID) {
    bool running = true;
    while (running) {
        system("cls");
        switch (mainMenu(username, userID)) {
        case MenuOption::LearningContent:
            learningContent();
            break;
        case MenuOption::ExerciseTasks:
            practiceQuestions();
            break;
        case MenuOption::Homework:
            homework();
            break;
        case MenuOption::GenerateTest:
            generateTest(username, userID);
            break;
        case MenuOption::MyTestResults:
            myTestResults(username, userID);
            break;
        case MenuOption::Statistics:
            studentStatistics();
            break;
        case MenuOption::Exit:
            running = false;
            break;
        }
    }
}
