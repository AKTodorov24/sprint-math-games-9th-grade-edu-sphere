#include "centering.h"
#include <iostream>
#include <string>
#include <windows.h>

static int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 80;
}

static int visibleLength(const std::string& s) {
    int len = 0;
    bool inEscape = false;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (c == '\033') { inEscape = true; i++; continue; }
        if (inEscape) { if (s[i] == 'm') inEscape = false; i++; continue; }
        if      ((c & 0x80) == 0x00) { len++; i += 1; }
        else if ((c & 0xE0) == 0xC0) { len++; i += 2; }
        else if ((c & 0xF0) == 0xE0) { len++; i += 3; }
        else if ((c & 0xF8) == 0xF0) { len++; i += 4; }
        else                          {        i += 1; }
    }
    return len;
}

class CenteringStreambuf : public std::streambuf {
    std::streambuf* orig;
    std::string buf;

    void outputCentered() {
        if (buf.empty()) return;
        int width = getConsoleWidth();
        int visible = visibleLength(buf);
        int pad = (width - visible) / 2;
        if (pad > 0) {
            std::string padding(pad, ' ');
            orig->sputn(padding.c_str(), pad);
        }
        orig->sputn(buf.c_str(), buf.size());
        buf.clear();
    }

protected:
    int overflow(int c) override {
        if (c == EOF) return EOF;
        if (c == '\n') {
            outputCentered();
            orig->sputc('\n');
        } else {
            buf += static_cast<char>(c);
        }
        return c;
    }

    std::streamsize xsputn(const char* s, std::streamsize n) override {
        for (std::streamsize i = 0; i < n; i++)
            overflow(static_cast<unsigned char>(s[i]));
        return n;
    }

    int sync() override {
        outputCentered();
        return orig->pubsync();
    }

public:
    CenteringStreambuf(std::streambuf* original) : orig(original) {}
};

void enableCenteredOutput() {
    static CenteringStreambuf centeringBuf(std::cout.rdbuf());
    std::cout.rdbuf(&centeringBuf);
    std::cout << "\n\n\n";
}
