#include "console.h"

// Console::Console() : currentBackgroundColor(0), currentTextColor(0) {}

void Console::setFont(const wchar_t* fontType) {
    CONSOLE_FONT_INFOEX cfi;
    wcscpy_s(cfi.FaceName, fontType); // Font name (you can change this)
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Console::setFontSize() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize = {8, 17};
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Console::setWindowSize() {
    szConsole = GetConsoleWindow();
    ShowWindow(szConsole, SW_MAXIMIZE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD bufferSize = { csbi.dwMaximumWindowSize.X, csbi.dwMaximumWindowSize.Y };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
   setFontSize();
}

void Console::init() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    szConsole = GetConsoleWindow();
    LONG style = GetWindowLong(szConsole, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(szConsole, GWL_STYLE, style);
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    setWindowSize();
};

void Console::setTextColor(int colorCode) {
	SetConsoleTextAttribute(hConsole, colorCode);
    currentTextColor = colorCode;
}

void Console::setBackgroundColor(int colorCode) {
    SetConsoleTextAttribute(hConsole, colorCode);
}



void Console::setFullscreenBackgroundColor(int colorCode) {

    // Define the desired background color (e.g., blue)

    // Set the console screen buffer's background color
    currentBackgroundColor = colorCode;
    SetConsoleTextAttribute(hConsole, currentBackgroundColor);

    // Clear the console screen with the new background color
    COORD bufferSize;
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    bufferSize.X = bufferInfo.dwSize.X;
    bufferSize.Y = bufferInfo.dwSize.Y;

    DWORD cellCount = bufferSize.X * bufferSize.Y;
    COORD home = { 0, 0 };
    DWORD count;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, home, &count);
    FillConsoleOutputAttribute(hConsole, currentBackgroundColor, cellCount, home, &count);

    SetConsoleTextAttribute(hConsole, bufferInfo.wAttributes);

     CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // Set the buffer size to match the window size
    COORD newSize;
    newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Width of the window
    newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Height of the window
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);
}

int Console::getBackgroundColor() {
    return currentBackgroundColor;
}

void Console::setCursorPosition(COORD pos) {
    SetConsoleCursorPosition(hConsole, pos);
}

void Console::writeAt(std::string text, int colorText, COORD posCursor, int colorBackground) {
    if (posCursor.X == -1 || posCursor.Y == -1) {
        posCursor = getCursorPosition();
    }
    if (colorBackground == -1) colorBackground = currentBackgroundColor;
    setCursorPosition(posCursor);
    if (colorText == -1) setBackgroundColor(colorBackground);
    else setBackgroundColor(colorText);
    std::cout << text << std::endl;
    setTextColor(WHITE);
}

COORD Console::getCursorPosition() {
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord;
    coord.X = csbi.dwCursorPosition.X;
    coord.Y = csbi.dwCursorPosition.Y;
    return coord;
}

void Console::clear(COORD p1, COORD p2) {
    if (p1.X == -1 || p1.Y == -1 || p2.X == -1 || p2.Y == -1) {
        system("cls");
        return;
    }
    if (p1.X > p2.X) std::swap(p1.X, p2.X);
    if (p1.Y > p2.Y) std::swap(p1.Y, p2.Y);
    for (int i = p1.X; i <= p2.X; i++)
        for (int j = p1.Y; j <= p2.Y; j++)
            writeAt(" ", BLACK, {(SHORT)i, (SHORT)j});
}


// (3, 0) (0, 3) => (0, 0) (3, 3)

// (0, 3) (3, 0)
