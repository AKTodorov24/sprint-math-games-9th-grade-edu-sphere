#include "homework.h"
#include "../config/libraries.h"
#include "title.h"

enum class LessonStatus { None, Viewed, Done };

static LessonStatus lessonStatus[5] = {};

struct HWQuestion {
    std::string text;
    std::string options[4];
    char answer;
    bool hard;
};

static const std::string lessonTitles[5] = {
    "Lesson 1: Introduction to Strings",
    "Lesson 2: Basic String Operations",
    "Lesson 3: Processing Strings with Loops",
    "Lesson 4: Reading Full Lines with Strings",
    "Lesson 5: Comparing Strings",
};

static const HWQuestion questions[5][7] = {
    {{
        "What is a string in C++?",
        {"A numeric data type", "A sequence of characters for storing text",
         "A boolean value", "A loop structure"},
        'B', false
    },{
        "Which header must be included to use std::string?",
        {"<iostream>", "<vector>", "<string>", "<cstring>"},
        'C', false
    },{
        "How do you declare a string `city` with value \"Paris\"?",
        {"int city = \"Paris\";", "string city = \"Paris\";",
         "char city = \"Paris\";", "text city = \"Paris\";"},
        'B', false
    },{
        "Which of the following is a valid string literal in C++?",
        {"'Hello'", "Hello", "\"Hello\"", "#Hello"},
        'C', false
    },{
        "Strings in C++ can store:",
        {"Only letters", "Only digits",
         "Only spaces", "Any sequence of characters"},
        'D', false
    },{
        "What is the output of:  string s = \"Hi\";  cout << s + s;",
        {"Hi", "HiHi", "Hi Hi", "Compile error"},
        'B', true
    },{
        "Given string name = \"\"; which statement is true?",
        {"name has undefined behavior", "name stores one space",
         "name is an empty string with length 0",
         "name cannot be used until assigned"},
        'C', true
    }},

    {{
        "What does .length() return for a string?",
        {"The first character", "The last character",
         "The number of characters", "The memory address"},
        'C', false
    },{
        "String indexing in C++ starts at:",
        {"1", "0", "-1", "2"},
        'B', false
    },{
        "What is the result of  \"Hello\" + \" \" + \"World\" ?",
        {"HelloWorld", "Hello World", "Error", "\"Hello World\""},
        'B', false
    },{
        "How do you access the first character of  string s = \"Test\" ?",
        {"s[1]", "s.first()", "s[0]", "s.begin()"},
        'C', false
    },{
        "Which operator is used to concatenate (join) two strings?",
        {"*", "&", "+", "|"},
        'C', false
    },{
        "Output of:  string s = \"Code\";  cout << s[1] << s[3];",
        {"Cd", "oe", "Co", "de"},
        'B', true
    },{
        "string a=\"abc\"; string b=a; b[0]='z'; cout<<a;  — what prints?",
        {"zbc", "abc", "zbcabc", "Compile error"},
        'B', true
    }},

    {{
        "What does  for(int i=0; i<text.length(); i++)  iterate over?",
        {"Words in a string", "Each character by index",
         "Each line", "Each digit only"},
        'B', false
    },{
        "Why is text.length() used in the loop condition?",
        {"To set the starting index", "To limit the loop to valid indexes",
         "To print the string", "To reverse the string"},
        'B', false
    },{
        "What does  cout << text[i];  print inside a loop?",
        {"The index i", "The entire string",
         "The character at position i", "Nothing"},
        'C', false
    },{
        "Loops over strings are useful for:",
        {"Declaring variables", "Searching and modifying characters",
         "Loading files", "Sorting numbers"},
        'B', false
    },{
        "string s=\"abc\" — how many times does  for(int i=0;i<s.length();i++)  run?",
        {"2", "4", "3", "1"},
        'C', false
    },{
        "string s=\"Hello\"; int c=0; for(...) if(s[i]=='l') c++; cout<<c;  — output?",
        {"1", "3", "2", "0"},
        'C', true
    },{
        "To reverse-print  string s=\"abc\" , which loop is correct?",
        {"for(int i=0; i<s.length(); i++) cout<<s[i];",
         "for(int i=s.length()-1; i>=0; i--) cout<<s[i];",
         "for(int i=1; i<=s.length(); i++) cout<<s[i];",
         "for(int i=s.length(); i>0; i--) cout<<s[i];"},
        'B', true
    }},

    {{
        "What does  cin >>  stop reading at?",
        {"End of file", "A newline character",
         "A space character", "A comma"},
        'C', false
    },{
        "Which function reads an entire line including spaces?",
        {"cin.read()", "getline()", "scanf()", "cin.get()"},
        'B', false
    },{
        "What is the correct syntax for getline?",
        {"getline(text, cin)", "cin.getline(text)",
         "getline(cin, text)", "readline(cin, text)"},
        'C', false
    },{
        "User types \"Hello World\", you use  cin >> text . What is in text?",
        {"Hello World", "Hello", "World", "Hello World\\n"},
        'B', false
    },{
        "getline() is most useful when reading:",
        {"Single digits", "Single words",
         "Full sentences with spaces", "Numbers"},
        'C', false
    },{
        "After  cin >> x , calling getline(cin,line) reads empty because:",
        {"getline() is broken",
         "The newline left by cin>> is still in the buffer",
         "line was not initialized",
         "cin and getline are incompatible"},
        'B', true
    },{
        "Which code correctly reads a full name after reading an integer age?",
        {"cin>>age; cin>>name;",
         "cin>>age; getline(cin,name);",
         "cin>>age; cin.ignore(); getline(cin,name);",
         "getline(cin,name); cin>>age;"},
        'C', true
    }},

    {{
        "Which operator compares two strings for equality in C++?",
        {"=", "==", "!=", "<>"},
        'B', false
    },{
        "What does  if(a == b)  check when a and b are strings?",
        {"If they point to the same memory", "If they have the same length",
         "If their characters match exactly", "If a is shorter than b"},
        'C', false
    },{
        "String comparison in C++ is:",
        {"Case insensitive", "Case sensitive",
         "Only for numbers", "Only for single characters"},
        'B', false
    },{
        "What does  if(input != password)  check?",
        {"If input is longer than password",
         "If the two strings are different",
         "Assigns password to input",
         "Converts both to lowercase"},
        'B', false
    },{
        "Which value does  \"hello\" == \"Hello\"  evaluate to?",
        {"true", "Depends on the compiler", "false", "Compile error"},
        'C', false
    },{
        "string a=\"apple\"; string b=\"banana\"; cout<<(a<b); — what prints?",
        {"0", "1", "apple", "Compile error"},
        'B', true
    },{
        "To compare strings case-insensitively in C++, you should:",
        {"Use == directly",
         "Convert both to lowercase then compare with ==",
         "Use strcmp()",
         "Use integer casting"},
        'B', true
    }},
};

static std::string statusTag(LessonStatus s) {
    switch (s) {
        case LessonStatus::Viewed: return "  \033[38;5;120m[Viewed]\033[0m";
        case LessonStatus::Done:   return "  \033[38;5;120m[Done]\033[0m";
        default:                   return "";
    }
}

static void printHeader() {
    displayTitle();
    std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m│        HOMEWORK         │\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
}

static void runHomeworkLesson(int lessonIdx) {
    if (lessonStatus[lessonIdx] != LessonStatus::Done)
        lessonStatus[lessonIdx] = LessonStatus::Viewed;

    for (int qi = 0; qi < 7; qi++) {
        const HWQuestion& q = questions[lessonIdx][qi];

        while (true) {
            system("cls");
            printHeader();
            std::cout << "\033[1m\033[38;5;120m" << lessonTitles[lessonIdx] << "\033[0m\n\n";
            std::cout << "\033[38;5;208mQuestion " << (qi + 1) << " of 7";
            if (q.hard)
                std::cout << "  \033[38;5;208m[★ Increased Difficulty]\033[0m";
            std::cout << "\033[0m\n\n";

            std::cout << "\033[38;5;223m" << q.text << "\033[0m\n\n";
            const char labels[] = {'A', 'B', 'C', 'D'};
            for (int i = 0; i < 4; i++)
                std::cout << "\033[38;5;223m" << labels[i] << ") " << q.options[i] << "\033[0m\n";

            std::cout << "\n\033[38;5;223m0. Exit Homework\033[0m" << std::endl;
            std::cout << "\033[38;5;208m• Answer (A/B/C/D or 0): \033[0m";

            std::string input;
            std::cin >> input;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            if (input == "0") return;

            if (input.size() == 1 && std::isalpha((unsigned char)input[0])) {
                char userAnswer = std::toupper((unsigned char)input[0]);
                if (userAnswer < 'A' || userAnswer > 'D') {
                    std::cout << "\033[31mInvalid input! Enter A, B, C, D or 0.\033[0m" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(900));
                    continue;
                }

                bool correct = (userAnswer == q.answer);
                bool isLast  = (qi == 6);

                system("cls");
                printHeader();
                std::cout << "\033[1m\033[38;5;120m" << lessonTitles[lessonIdx] << "\033[0m\n\n";
                std::cout << "\033[38;5;223m" << q.text << "\033[0m\n\n";

                if (correct)
                    std::cout << "\033[1m\033[38;5;120m+ Correct! The answer is " << q.answer << ".\033[0m\n\n";
                else
                    std::cout << "\033[1m\033[31m- Incorrect. You answered " << userAnswer
                              << ". The correct answer is " << q.answer << ".\033[0m\n\n";

                if (!isLast)
                    std::cout << "\033[38;5;223m1. Next Question\033[0m" << std::endl;
                else
                    std::cout << "\033[38;5;223m1. Finish Homework\033[0m" << std::endl;
                std::cout << "\033[38;5;223m0. Exit Homework\033[0m" << std::endl;
                std::cout << "\033[38;5;208m• Choice: \033[0m";

                int afterChoice;
                if (!(std::cin >> afterChoice)) {
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    return;
                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                if (afterChoice == 1) {
                    if (isLast) {
                        lessonStatus[lessonIdx] = LessonStatus::Done;
                        system("cls");
                        printHeader();
                        std::cout << "\033[1m\033[38;5;120mHomework Complete!\033[0m\n\n";
                        std::cout << "\033[38;5;223m" << lessonTitles[lessonIdx]
                                  << " \342\200\224 marked as Done.\033[0m\n\n";
                        std::cout << "\033[38;5;223mPress Enter to return...\033[0m";
                        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                        return;
                    }
                    break;
                }
                return;
            } else {
                std::cout << "\033[31mInvalid input! Enter A, B, C, D or 0.\033[0m" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
            }
        }
    }
}

void homework() {
    while (true) {
        system("cls");
        printHeader();

        for (int i = 0; i < 5; i++) {
            std::cout << "\033[38;5;223m" << (i + 1) << ". " << lessonTitles[i]
                      << "\033[0m" << statusTag(lessonStatus[i]) << "\n";
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
        if (choice >= 1 && choice <= 5) {
            runHomeworkLesson(choice - 1);
        } else {
            std::cout << "\033[31mInvalid choice!\033[0m" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    }
}
