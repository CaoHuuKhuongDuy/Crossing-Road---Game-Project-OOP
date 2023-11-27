#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

// #define endl '\n'
// #define endl '\n'
#define BLACK 0
#define BLUE (FOREGROUND_BLUE)
#define GREEN (FOREGROUND_GREEN)
#define RED (FOREGROUND_RED)
#define MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define GREY FOREGROUND_INTENSITY
#define LIME (FOREGROUND_INTENSITY | FOREGROUND_GREEN)
#define CYAN (FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

// Standard background colors
#define BG_BLACK 0
#define BG_BLUE BACKGROUND_BLUE
#define BG_GREEN BACKGROUND_GREEN
#define BG_RED BACKGROUND_RED
#define BG_MAGENTA (BACKGROUND_RED | BACKGROUND_BLUE)
#define BG_YELLOW (BACKGROUND_RED | BACKGROUND_GREEN)
#define BG_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define BG_GREY BACKGROUND_INTENSITY
#define BG_LIME (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define BG_CYAN (BACKGROUND_GREEN | BACKGROUND_BLUE)
#define BG_ORANGE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define BG_DEFAULT (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)



#define DEFAULT_BACKGROUD BG_DEFAULT


class Console {
    public:
        void setFont(const wchar_t* fontType = L"Consolas");

        void setFontSize();

        void setWindowSize();

        void init();

        void setTextColor(int colorCode);

        void setBackgroundColor(int colorCode);

        void setFullscreenBackgroundColor(int colorCode);
        
        int getBackgroundColor();
    
        COORD getWindowSize();

        void setCursorPosition(COORD pos);

        void SetBackgroundColor(int color); 

        void writeAt(std::string text, int colorText, COORD posCursor = {-1, -1}, int colorBackground = -1);

        COORD getCursorPosition();

        void clear(COORD p1 = {-1, -1}, COORD p2 = {-1, -1}); 

        void closeConsole();

        void test(char character, int color, int left, int top, int right, int bottom);

        bool getRunning() { return running;}

    private:
        COORD calculateFontSize();
        bool running;
        static BOOL CtrlHandler(DWORD fdwCtrlType);
        HANDLE hConsole;
        HWND szConsole;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        CONSOLE_CURSOR_INFO cursorInfo;
        int currentTextColor, currentBackgroundColor;
        COORD size;
};
