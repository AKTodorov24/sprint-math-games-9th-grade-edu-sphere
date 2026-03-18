#include "studentStatistics.h"
#include "../config/libraries.h"
#include "title.h"
#include "../domain/results/resultsStore.h"

// Prints the "STUDENT STATISTICS" section header.
static void printStatsHeader() {
    displayTitle();
    std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m│   STUDENT STATISTICS    │\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
}

// Displays global test stats, top students by best score, and per-topic success rates.
void studentStatistics() {
    while (true) {
        system("cls");
        printStatsHeader();

        std::vector<TestResult> all = loadResults();

        if (all.empty()) {
            std::cout << "\033[38;5;223mNo test results on record yet.\033[0m\n\n";
            std::cout << "\033[38;5;223m0. Back\033[0m\n";
            std::cout << "\033[38;5;208m• Choice: \033[0m";
            int c; std::cin >> c;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return;
        }

        double totalPct = 0.0;
        for (const auto& r : all) totalPct += r.scorePercent;
        double globalAvg = totalPct / all.size();

        int avgGrade = 2;
        if      (globalAvg >= 80.0) avgGrade = 6;
        else if (globalAvg >= 70.0) avgGrade = 5;
        else if (globalAvg >= 60.0) avgGrade = 4;
        else if (globalAvg >= 50.0) avgGrade = 3;

        std::cout << "\033[38;5;208m  ── Global Overview ────────────────────────────────\033[0m\n";
        std::cout << "  \033[38;5;223mTotal tests taken : " << all.size() << "\033[0m\n";
        std::cout << "  \033[38;5;223mAverage score     : "
                  << std::fixed << std::setprecision(1) << globalAvg
                  << "%  \033[38;5;120m(Grade " << avgGrade << "/6)\033[0m\n\n";

        struct StudentBest {
            std::string username;
            double      bestPct;
            int         bestGrade;
        };
        std::map<int, StudentBest> byUser;
        for (const auto& r : all) {
            auto it = byUser.find(r.userID);
            if (it == byUser.end()) {
                byUser[r.userID] = { r.username, r.scorePercent, r.grade };
            } else {
                if (r.scorePercent > it->second.bestPct) {
                    it->second.bestPct   = r.scorePercent;
                    it->second.bestGrade = r.grade;
                }
            }
        }

        std::vector<std::pair<int, StudentBest>> ranked(byUser.begin(), byUser.end());
        std::sort(ranked.begin(), ranked.end(),
            [](const auto& a, const auto& b) {
                return a.second.bestPct > b.second.bestPct;
            });

        std::cout << "\033[38;5;208m  ── Top Students (by Best Score) ───────────────────\033[0m\n";
        int show = (std::min)((int)ranked.size(), 10);
        for (int i = 0; i < show; i++) {
            const auto& s = ranked[i].second;
            std::string marker = (i == 0) ? "\033[38;5;208m[#1]\033[0m " : "     ";
            std::cout << "  " << marker
                      << "\033[38;5;120m" << std::left << std::setw(16) << s.username << "\033[0m"
                      << std::right << std::fixed << std::setprecision(1) << std::setw(6) << s.bestPct << "%"
                      << "  Grade \033[38;5;120m" << s.bestGrade << "\033[38;5;223m/6\033[0m\n";
        }
        std::cout << "\n";

        struct TopicStat { int correct = 0; int total = 0; };
        std::map<std::string, TopicStat> topics;
        for (const auto& r : all) {
            for (const auto& a : r.answers) {
                auto& ts = topics[a.topic];
                ts.total++;
                if (a.correct) ts.correct++;
            }
        }

        std::vector<std::pair<std::string, TopicStat>> topicVec(topics.begin(), topics.end());
        std::sort(topicVec.begin(), topicVec.end(),
            [](const auto& a, const auto& b) {
                double ra = (a.second.total > 0) ? (double)a.second.correct / a.second.total : 0.0;
                double rb = (b.second.total > 0) ? (double)b.second.correct / b.second.total : 0.0;
                return ra < rb;
            });

        std::cout << "\033[38;5;208m  ── Topic Success Rates ─────────────────────────────\033[0m\n";
        for (int i = 0; i < (int)topicVec.size(); i++) {
            const auto& [name, stat] = topicVec[i];
            double rate = (stat.total > 0) ? (double)stat.correct / stat.total * 100.0 : 0.0;

            std::string tag;
            if (i == 0)                          tag = "  \033[31m[Lowest]\033[0m";
            else if (i == (int)topicVec.size()-1) tag = "  \033[38;5;120m[Highest]\033[0m";

            std::cout << "  \033[38;5;223m" << std::left << std::setw(36) << name << "\033[0m"
                      << std::right << std::fixed << std::setprecision(1) << std::setw(6) << rate << "%"
                      << "  (" << stat.correct << "/" << stat.total << ")"
                      << tag << "\n";
        }

        std::cout << "\n\033[38;5;223m0. Back\033[0m\n";
        std::cout << "\033[38;5;208m• Choice: \033[0m";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        if (choice == 0) return;
    }
}
