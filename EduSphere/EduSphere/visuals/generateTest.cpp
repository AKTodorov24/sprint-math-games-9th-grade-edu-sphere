#include "generateTest.h"
#include "../config/libraries.h"
#include "title.h"
#include "../domain/results/resultsStore.h"

struct TestQuestion {
    int         id;
    std::string topic;
    int         difficulty;
    std::string text;
    std::string options[4];
    char        answer;
};

// Parses and returns all test questions from the questions file.
static std::vector<TestQuestion> loadTestQuestions() {
    std::vector<TestQuestion> questions;
    std::ifstream file("visuals/testQuestions.txt");
    if (!file.is_open()) return questions;

    std::string line;
    TestQuestion current{};
    bool inQ = false;

    while (std::getline(file, line)) {
        if (line.rfind("TestQuestion #", 0) == 0) {
            if (inQ) questions.push_back(current);
            current = TestQuestion{};
            current.id = std::stoi(line.substr(14));
            inQ = true;
        } else if (inQ && line.rfind("Topic: ", 0) == 0) {
            current.topic = line.substr(7);
        } else if (inQ && line.rfind("Difficulty: ", 0) == 0) {
            current.difficulty = std::stoi(line.substr(12));
        } else if (inQ && line.rfind("A) ", 0) == 0) {
            current.options[0] = line.substr(3);
        } else if (inQ && line.rfind("B) ", 0) == 0) {
            current.options[1] = line.substr(3);
        } else if (inQ && line.rfind("C) ", 0) == 0) {
            current.options[2] = line.substr(3);
        } else if (inQ && line.rfind("D) ", 0) == 0) {
            current.options[3] = line.substr(3);
        } else if (inQ && line.rfind("Answer: ", 0) == 0 && line.size() >= 9) {
            current.answer = line[8];
        } else if (inQ && current.text.empty() && !line.empty()
                   && line.rfind("A) ", 0) != 0 && line.rfind("Answer:", 0) != 0) {
            current.text = line;
        }
    }
    if (inQ) questions.push_back(current);
    return questions;
}

// Converts a percentage score to a grade from 2 to 6.
static int computeGrade(double pct) {
    if (pct >= 80.0) return 6;
    if (pct >= 70.0) return 5;
    if (pct >= 60.0) return 4;
    if (pct >= 50.0) return 3;
    return 2;
}

// Returns the current local date and time as a "YYYY-MM-DD HH:MM" string.
static std::string currentDateTime() {
    std::time_t now = std::time(nullptr);
    struct tm ti;
    localtime_s(&ti, &now);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &ti);
    return std::string(buf);
}

// Prints the "GENERATE TEST" section header.
static void printTestHeader() {
    displayTitle();
    std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m│      GENERATE TEST      │\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
}

// Runs a randomized 30-question test, scores it, and saves the result.
void generateTest(const std::string& username, int userID) {
    std::vector<TestQuestion> pool = loadTestQuestions();
    if (pool.empty()) {
        system("cls");
        printTestHeader();
        std::cout << "\033[31mTest question file not found.\033[0m\n\n";
        std::cout << "\033[38;5;223mPress Enter to return...\033[0m";
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(pool.begin(), pool.end(), rng);
    int count = (std::min)(30, (int)pool.size());
    std::vector<TestQuestion> selected(pool.begin(), pool.begin() + count);

    system("cls");
    printTestHeader();
    std::cout << "\033[38;5;223mTest Overview:\033[0m\n\n";
    std::cout << "\033[38;5;223m  Questions: " << count << "\033[0m\n";
    std::cout << "\033[38;5;208m  Format: \033[38;5;223mMultiple choice (A/B/C/D)\033[0m\n";
    std::cout << "\033[38;5;208m  Scoring: \033[38;5;223mEasy = 1pt\033[38;5;208m,  \033[38;5;223mMedium = 2pts\033[38;5;208m,  \033[38;5;223mHard = 3pts.\033[0m\n";
    std::cout << "\033[38;5;208m  Grades: \033[38;5;223m2 (<50%)\033[38;5;208m,  \033[38;5;223m3 (50-60%)\033[38;5;208m,  \033[38;5;223m4 (60-70%)\033[38;5;208m,  \033[38;5;223m5 (70-80%)\033[38;5;208m,  \033[38;5;223m6 (80%+)\033[0m\n";
    std::cout << "\033[38;5;208m  Answers: \033[38;5;223mShown only after the full test is submitted\033[0m\n\n";
    std::cout << "\033[38;5;223m1. Start Test\033[0m\n";
    std::cout << "\033[38;5;223m0. Back\033[0m\n";
    std::cout << "\033[38;5;208m• Choice: \033[0m";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    if (choice != 1) return;

    std::vector<char> userAnswers(count, ' ');

    for (int qi = 0; qi < count; qi++) {
        const TestQuestion& q = selected[qi];

        while (true) {
            system("cls");
            printTestHeader();

            std::string diffLabel;
            if      (q.difficulty == 2) diffLabel = "  \033[38;5;223m[Medium]\033[0m";
            else if (q.difficulty == 3) diffLabel = "  \033[38;5;208m[\342\230\205 Hard]\033[0m";

            std::cout << "\033[38;5;208mQuestion " << (qi + 1) << " of " << count
                      << diffLabel << "\033[0m\n\n";
            std::cout << "\033[38;5;223m" << q.text << "\033[0m\n\n";

            const char labels[] = {'A', 'B', 'C', 'D'};
            for (int i = 0; i < 4; i++)
                std::cout << "\033[38;5;223m" << labels[i] << ") " << q.options[i] << "\033[0m\n";

            std::cout << "\n\033[38;5;223m0. Abandon Test\033[0m\n";
            std::cout << "\033[38;5;208m• Answer (A/B/C/D or 0): \033[0m";

            std::string input;
            std::cin >> input;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            if (input == "0") {
                system("cls");
                printTestHeader();
                std::cout << "\033[38;5;223mAbandon the test? Progress will NOT be saved. (y/n): \033[0m";
                std::string confirm;
                std::cin >> confirm;
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                if (confirm == "y" || confirm == "Y") return;
                continue;
            }

            if (input.size() == 1 && std::isalpha((unsigned char)input[0])) {
                char ua = std::toupper((unsigned char)input[0]);
                if (ua < 'A' || ua > 'D') {
                    std::cout << "\033[31mEnter A, B, C, D or 0.\033[0m" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    continue;
                }
                userAnswers[qi] = ua;
                break;
            }
            std::cout << "\033[31mEnter A, B, C, D or 0.\033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }

    int earned = 0, maxPossible = 0;
    std::vector<AnswerRecord> records;
    for (int i = 0; i < count; i++) {
        const TestQuestion& q = selected[i];
        bool correct = (userAnswers[i] == q.answer);
        maxPossible += q.difficulty;
        if (correct) earned += q.difficulty;
        records.push_back({ q.id, q.topic, q.difficulty, correct });
    }
    double pct   = (maxPossible > 0) ? (double)earned / maxPossible * 100.0 : 0.0;
    int    grade = computeGrade(pct);

    system("cls");
    printTestHeader();
    std::cout << "\033[1m\033[38;5;120mTest Complete!\033[0m\n\n";

    std::cout << "\033[38;5;223m  Score  : " << earned << " / " << maxPossible
              << " pts  (" << std::fixed << std::setprecision(1) << pct << "%)\033[0m\n";
    std::cout << "\033[38;5;223m  Grade  : \033[1m\033[38;5;120m" << grade << " / 6\033[0m\n";

    std::cout << "\n\033[38;5;208m  ── Question Breakdown ──────────────────────────────\033[0m\n";
    for (int i = 0; i < count; i++) {
        const TestQuestion& q = selected[i];
        bool correct = (userAnswers[i] == q.answer);
        std::string mark = correct ? "\033[38;5;120m+\033[0m" : "\033[31m-\033[0m";
        std::cout << "  " << mark << " Q" << std::setw(2) << (i+1)
                  << "  [D" << q.difficulty << "]  "
                  << (correct ? "Correct " : "Wrong   ")
                  << "\033[90m(correct: " << q.answer << ")\033[0m\n";
    }

    TestResult result;
    result.userID       = userID;
    result.username     = username;
    result.date         = currentDateTime();
    result.scorePercent = pct;
    result.grade        = grade;
    result.earned       = earned;
    result.maxPossible  = maxPossible;
    result.answers      = records;
    saveResult(result);

    std::cout << "\n\033[38;5;120mResult saved.\033[0m\n\n";
    std::cout << "\033[38;5;223mPress Enter to return...\033[0m";
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}