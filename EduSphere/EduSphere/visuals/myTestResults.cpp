#include "myTestResults.h"
#include "../config/libraries.h"
#include "title.h"
#include "../domain/results/resultsStore.h"

static void printResultsHeader() {
    displayTitle();
    std::cout << "\033[1m\033[38;5;208m┍━━━━━━━━━━━━━━━━━━━━━━━━━┑\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m│     MY TEST RESULTS     │\033[0m" << std::endl;
    std::cout << "\033[1m\033[38;5;208m┕━━━━━━━━━━━━━━━━━━━━━━━━━┙\033[0m" << std::endl;
}

void myTestResults(const std::string& username, int userID) {
    while (true) {
        system("cls");
        printResultsHeader();

        std::vector<TestResult> all = loadResults();

        // Filter to current user
        std::vector<TestResult> mine;
        for (const auto& r : all)
            if (r.userID == userID) mine.push_back(r);

        if (mine.empty()) {
            std::cout << "\033[38;5;223mNo test results found for \033[38;5;120m"
                      << username << "\033[38;5;223m yet.\033[0m\n\n";
            std::cout << "\033[38;5;223mComplete a Generated Test to record a result.\033[0m\n\n";
            std::cout << "\033[38;5;223m0. Back\033[0m\n";
            std::cout << "\033[38;5;208m• Choice: \033[0m";
            int c; std::cin >> c;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return;
        }

        // Summary stats
        double total = 0.0, best = 0.0;
        int bestGrade = 0;
        for (const auto& r : mine) {
            total += r.scorePercent;
            if (r.scorePercent > best) { best = r.scorePercent; bestGrade = r.grade; }
        }
        double avg = total / mine.size();

        std::cout << "\033[38;5;120mStudent: " << username
                  << "  \033[90m(ID: " << userID << ")\033[0m\n\n";

        std::cout << "\033[38;5;208m  ── All Attempts ────────────────────────────────────\033[0m\n";
        std::cout << "\033[38;5;223m  #   Date              Score           Grade\033[0m\n";
        for (int i = 0; i < (int)mine.size(); i++) {
            const auto& r = mine[i];
            std::cout << "  \033[38;5;223m" << std::setw(2) << (i + 1) << ".  "
                      << std::left << std::setw(18) << r.date << std::right
                      << std::fixed << std::setprecision(1) << std::setw(6) << r.scorePercent << "%"
                      << "  (" << r.earned << "/" << r.maxPossible << " pts)"
                      << "   Grade \033[38;5;120m" << r.grade << "\033[38;5;223m/6\033[0m\n";
        }

        std::cout << "\n\033[38;5;208m  ── Summary ──────────────────────────────────────────\033[0m\n";
        std::cout << "  \033[38;5;223mAttempts: " << mine.size() << "\033[0m\n";
        std::cout << "  \033[38;5;223mAverage: " << std::fixed << std::setprecision(1) << avg << "%\033[0m\n";
        std::cout << "  \033[38;5;223mBest: " << std::fixed << std::setprecision(1) << best
                  << "%  \033[38;5;120mGrade " << bestGrade << "/6\033[0m\n\n";

        std::cout << "\033[38;5;223m0. Back\033[0m\n";
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
