#include "resultsStore.h"
#include "../../config/libraries.h"

static const std::string RESULTS_DIR  = "domain/results";
static const std::string RESULTS_FILE = "domain/results/results.json";

// Loads all test results from the JSON file.
std::vector<TestResult> loadResults() {
    std::vector<TestResult> results;
    std::ifstream file(RESULTS_FILE);
    if (!file.is_open()) return results;

    json j;
    try { file >> j; }
    catch (...) { return results; }

    if (!j.contains("results")) return results;

    for (const auto& r : j["results"]) {
        TestResult tr;
        tr.userID       = r.value("userID",       0);
        tr.username     = r.value("username",     "");
        tr.date         = r.value("date",         "");
        tr.scorePercent = r.value("scorePercent", 0.0);
        tr.grade        = r.value("grade",        2);
        tr.earned       = r.value("earned",       0);
        tr.maxPossible  = r.value("maxPossible",  1);

        if (r.contains("answers")) {
            for (const auto& a : r["answers"]) {
                AnswerRecord ar;
                ar.questionID = a.value("questionID", 0);
                ar.topic      = a.value("topic",      "");
                ar.difficulty = a.value("difficulty", 1);
                ar.correct    = a.value("correct",    false);
                tr.answers.push_back(ar);
            }
        }
        results.push_back(tr);
    }
    return results;
}

// Appends a test result to the JSON file.
void saveResult(const TestResult& result) {
    std::filesystem::create_directories(RESULTS_DIR);

    std::vector<TestResult> all = loadResults();
    all.push_back(result);

    json j;
    j["results"] = json::array();
    for (const auto& tr : all) {
        json r;
        r["userID"]       = tr.userID;
        r["username"]     = tr.username;
        r["date"]         = tr.date;
        r["scorePercent"] = tr.scorePercent;
        r["grade"]        = tr.grade;
        r["earned"]       = tr.earned;
        r["maxPossible"]  = tr.maxPossible;
        r["answers"]      = json::array();
        for (const auto& ar : tr.answers) {
            json a;
            a["questionID"] = ar.questionID;
            a["topic"]      = ar.topic;
            a["difficulty"] = ar.difficulty;
            a["correct"]    = ar.correct;
            r["answers"].push_back(a);
        }
        j["results"].push_back(r);
    }

    std::ofstream file(RESULTS_FILE);
    file << j.dump(4);
}
