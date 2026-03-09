#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>

enum class MenuOption {
    LearningContent = 1,
    ExerciseTasks,
    Homework,
    GenerateTest,
    MyTestResults,
    Statistics,
    Exit = 0
};

MenuOption mainMenu(const std::string& username, int userID);
void runApp(const std::string& username, int userID);

#endif
