#include "learningContent.h"
#include "../config/libraries.h"
#include "title.h"

struct Lesson {
    std::string title;
    std::string content;
};

// Parses and returns all lessons from the lessons file.
static std::vector<Lesson> loadLessons() {
    std::vector<Lesson> lessons;
    std::ifstream file("visuals/lessons.txt");
    if (!file.is_open()) return lessons;

    std::string line;
    Lesson current;
    bool inLesson = false;

    while (std::getline(file, line)) {
        if (line.rfind("Lesson ", 0) == 0) {
            if (inLesson) {
                while (!current.content.empty() && current.content.back() == '\n')
                    current.content.pop_back();
                lessons.push_back(current);
                current = Lesson{};
            }
            current.title = line;
            inLesson = true;
        } else if (inLesson) {
            current.content += line + "\n";
        }
    }

    if (inLesson) {
        while (!current.content.empty() && current.content.back() == '\n')
            current.content.pop_back();
        lessons.push_back(current);
    }

    return lessons;
}

// Prints text word-wrapped to maxWidth characters per line.
static void printWrapped(const std::string& text, int maxWidth) {
    std::istringstream stream(text);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty()) {
            std::cout << "\n";
            continue;
        }
        std::istringstream words(line);
        std::string word, current;
        while (words >> word) {
            if (!current.empty() && (int)(current.size() + 1 + word.size()) > maxWidth) {
                std::cout << "\033[38;5;223m" << current << "\033[0m\n";
                current = word;
            } else {
                if (!current.empty()) current += ' ';
                current += word;
            }
        }
        if (!current.empty())
            std::cout << "\033[38;5;223m" << current << "\033[0m\n";
    }
}

// Displays a single lesson's content and waits for the user to go back.
static void displayLesson(const Lesson& lesson) {
    while (true) {
        system("cls");
        displayTitle();
        std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m│     LEARNING CONTENT    │\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;120m" << lesson.title << "\033[0m\n" << std::endl;
        printWrapped(lesson.content, 70);
        std::cout << "\n";
        std::cout << "\033[38;5;223m0. Back\033[0m" << std::endl;
        std::cout << "\033[38;5;208m• Choice: \033[0m";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }
        if (choice == 0) return;
        std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
    }
}

// Shows the lesson list and opens the selected lesson.
void learningContent() {
    std::vector<Lesson> lessons = loadLessons();

    while (true) {
        system("cls");
        displayTitle();
        std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m│     LEARNING CONTENT    │\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;

        if (lessons.empty()) {
            std::cout << "\033[31mNo lessons found.\033[0m\n" << std::endl;
        } else {
            for (int i = 0; i < (int)lessons.size(); i++) {
                std::cout << "\033[38;5;223m" << (i + 1) << ". " << lessons[i].title << "\033[0m" << std::endl;
            }
        }

        std::cout << "\n\033[38;5;223m0. Back\033[0m" << std::endl;
        std::cout << "\n\033[38;5;208m• Choice: \033[0m";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }

        if (choice == 0) return;
        if (choice >= 1 && choice <= (int)lessons.size()) {
            displayLesson(lessons[choice - 1]);
        } else {
            std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
        }
    }
}
