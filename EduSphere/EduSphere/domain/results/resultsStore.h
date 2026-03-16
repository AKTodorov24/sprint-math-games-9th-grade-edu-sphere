#ifndef RESULTSSTORE_H
#define RESULTSSTORE_H

#include <string>
#include <vector>

struct AnswerRecord {
    int  questionID;
    std::string topic;
    int  difficulty;
    bool correct;
};

struct TestResult {
    int  userID;
    std::string username;
    std::string date;
    double scorePercent;
    int  grade;
    int  earned;
    int  maxPossible;
    std::vector<AnswerRecord> answers;
};

std::vector<TestResult> loadResults();
void saveResult(const TestResult& result);

#endif
