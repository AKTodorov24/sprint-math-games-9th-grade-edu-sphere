#include <iostream>
#include "../config/libraries.h"
#include "title.h"

void displayTitle() {
    std::cout << std::endl;
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    std::vector<std::string> lines = {
        "\033[38;2;184;233;126m ███████ ██████  ██    ██      ███████ ██████  ██   ██ ███████ ██████  ███████ \033[0m",
        "\033[38;2;225;236;120m ██      ██   ██ ██    ██      ██      ██   ██ ██   ██ ██      ██   ██ ██      \033[0m",
        "\033[38;2;255;204;138m █████   ██   ██ ██    ██      ███████ ██████  ███████ █████   ██████  █████   \033[0m",
        "\033[38;2;255;194;133m ██      ██   ██ ██    ██           ██ ██      ██   ██ ██      ██   ██ ██      \033[0m",
        "\033[38;2;255;184;113m ███████ ██████   ██████       ███████ ██      ██   ██ ███████ ██   ██ ███████ \033[0m"
    };

    size_t max_len = 0;
    for (const auto& s : lines) {
        if (s.length() > max_len) max_len = s.length();
    }

    for (size_t col = 0; col < max_len; ++col) {
        std::cout << "\033[H";
        for (const auto& line : lines) {
            if (col < line.length()) {
                std::cout << line.substr(0, col) << std::endl;
            }
            else {
                std::cout << line << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}   