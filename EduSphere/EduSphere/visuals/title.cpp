#include <iostream>
#include "../config/libraries.h"
#include "title.h"

// Prints the EduSphere ASCII art title banner.
void displayTitle() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    std::cout << "\n\n\n";
    std::cout
        << "\033[38;2;184;233;126m ███████ ██████  ██    ██      ███████ ██████  ██   ██ ███████ ██████  ███████ \033[0m\n"
        << "\033[38;2;225;236;120m ██      ██   ██ ██    ██      ██      ██   ██ ██   ██ ██      ██   ██ ██      \033[0m\n"
        << "\033[38;2;255;204;138m █████   ██   ██ ██    ██      ███████ ██████  ███████ █████   ██████  █████   \033[0m\n"
        << "\033[38;2;255;194;133m ██      ██   ██ ██    ██           ██ ██      ██   ██ ██      ██   ██ ██      \033[0m\n"
        << "\033[38;2;255;184;113m ███████ ██████   ██████       ███████ ██      ██   ██ ███████ ██   ██ ███████ \033[0m\n"
        << std::endl;
}