#include "practiceQuestions.h"
#include "../config/libraries.h"
#include "title.h"

struct Question {
    int number;
    std::string text;
    std::string options[4];
    char answer;
};

static std::vector<Question> loadQuestions() {
    std::vector<Question> questions;
    std::ifstream file("visuals/practiceQuestions.txt");
    if (!file.is_open()) return questions;

    std::string line;
    Question current;
    bool inQuestion = false;

    while (std::getline(file, line)) {
        if (line.rfind("Question #", 0) == 0) {
            if (inQuestion) questions.push_back(current);
            current = Question{};
            current.number = std::stoi(line.substr(10));
            inQuestion = true;
        } else if (inQuestion && current.text.empty() && line.rfind("A)", 0) != 0
                   && line.rfind("Answer:", 0) != 0 && !line.empty()) {
            current.text = line;
        } else if (inQuestion && line.rfind("A) ", 0) == 0) {
            current.options[0] = line.substr(3);
        } else if (inQuestion && line.rfind("B) ", 0) == 0) {
            current.options[1] = line.substr(3);
        } else if (inQuestion && line.rfind("C) ", 0) == 0) {
            current.options[2] = line.substr(3);
        } else if (inQuestion && line.rfind("D) ", 0) == 0) {
            current.options[3] = line.substr(3);
        } else if (inQuestion && line.rfind("Answer: ", 0) == 0 && line.size() >= 9) {
            current.answer = line[8];
        }
    }

    if (inQuestion) questions.push_back(current);
    return questions;
}

static void runQuestion(const std::vector<Question>& questions, int startIndex) {
    int index = startIndex;

    while (index >= 0 && index < (int)questions.size()) {
        // --- Show question ---
        while (true) {
            system("cls");
            displayTitle();
            std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
            std::cout << "\033[1m\033[38;5;208m│   PRACTICE QUESTIONS    │\033[0m" << std::endl;
            std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;

            const Question& q = questions[index];
            std::cout << "\033[1m\033[38;5;120mQuestion #" << q.number << "\033[0m\n" << std::endl;
            std::cout << "\033[38;5;223m" << q.text << "\033[0m\n" << std::endl;
            std::cout << "\033[38;5;223mA) " << q.options[0] << "\033[0m" << std::endl;
            std::cout << "\033[38;5;223mB) " << q.options[1] << "\033[0m" << std::endl;
            std::cout << "\033[38;5;223mC) " << q.options[2] << "\033[0m" << std::endl;
            std::cout << "\033[38;5;223mD) " << q.options[3] << "\033[0m\n" << std::endl;
            std::cout << "\033[38;5;223m0. Back to Menu\033[0m" << std::endl;
            std::cout << "\033[38;5;208m• Answer (A/B/C/D or 0): \033[0m";

            std::string input;
            std::cin >> input;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            if (input == "0") return;

            if (input.size() == 1 && std::isalpha((unsigned char)input[0])) {
                char userAnswer = std::toupper((unsigned char)input[0]);
                if (userAnswer < 'A' || userAnswer > 'D') {
                    std::cout << "\033[31mInvalid input! Please enter A, B, C, D or 0.\033[0m" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(900));
                    continue;
                }

                bool correct = (userAnswer == q.answer);

                // --- Show result ---
                system("cls");
                displayTitle();
                std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
                std::cout << "\033[1m\033[38;5;208m│   PRACTICE QUESTIONS    │\033[0m" << std::endl;
                std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;

                std::cout << "\033[1m\033[38;5;120mQuestion #" << q.number << "\033[0m\n" << std::endl;
                std::cout << "\033[38;5;223m" << q.text << "\033[0m\n" << std::endl;

                if (correct) {
                    std::cout << "\033[1m\033[38;5;120m+ Correct! The answer is " << q.answer << ".\033[0m\n" << std::endl;
                } else {
                    std::cout << "\033[1m\033[31m- Incorrect. You answered " << userAnswer
                              << ". The correct answer is " << q.answer << ".\033[0m\n" << std::endl;
                }

                bool hasNext = (index + 1 < (int)questions.size());
                if (hasNext) {
                    std::cout << "\033[38;5;223m1. Next Question\033[0m" << std::endl;
                }
                std::cout << "\033[38;5;223m0. Back to Menu\033[0m" << std::endl;
                std::cout << "\033[38;5;208m• Choice: \033[0m";

                int afterChoice;
                if (!(std::cin >> afterChoice)) {
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    break;
                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                if (afterChoice == 1 && hasNext) {
                    index++;
                    break;
                }
                return;
            } else {
                std::cout << "\033[31mInvalid input! Please enter A, B, C, D or 0.\033[0m" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
            }
        }
    }
}

void practiceQuestions() {
    std::vector<Question> questions = loadQuestions();

    while (true) {
        system("cls");
        displayTitle();
        std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m│   PRACTICE QUESTIONS    │\033[0m" << std::endl;
        std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;

        if (questions.empty()) {
            std::cout << "\033[31mNo questions found.\033[0m\n" << std::endl;
        } else {
            for (int i = 0; i < (int)questions.size(); i++) {
                std::cout << "\033[38;5;223m" << (i + 1) << ". Question #"
                          << questions[i].number << "\033[0m" << std::endl;
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
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        if (choice == 0) return;
        if (choice >= 1 && choice <= (int)questions.size()) {
            runQuestion(questions, choice - 1);
        } else {
            std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    }
}
