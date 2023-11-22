#include "console.h"
#include "staticVariable.h"

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
    cfi.dwFontSize = stValue::FONT_SIZE;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Console::setWindowSize() {
    setFontSize();
    // Adjust buffer size:
    if (!SetConsoleScreenBufferSize(hConsole, size))
        throw std::runtime_error("Unable to resize screen buffer.");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
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
    size = stValue::FIX_SIZE;
    setWindowSize();
};

void Console::setTextColor(int color)
{
	WORD wColor;
     if(GetConsoleScreenBufferInfo(hConsole, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hConsole, wColor);
	}
    currentTextColor = color;
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
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Set the buffer size to match the window size
    COORD newSize;
    newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Width of the window
    newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Height of the window
    SetConsoleScreenBufferSize(hConsole, newSize);
}

int Console::getBackgroundColor() {
    return currentBackgroundColor;
}

COORD Console::getWindowSize() {
    return size;
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
    else {
        setTextColor(colorText);
    }
    DWORD charsWritten;
    // std::cout << text << std::endl;
    WriteConsole(hConsole, text.c_str(), text.size(), &charsWritten,  &charsWritten);
    setTextColor(WHITE);
}

COORD Console::getCursorPosition() {
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord;
    coord.X = csbi.dwCursorPosition.X;
    coord.Y = csbi.dwCursorPosition.Y;
    return coord;
}

void Console::SetBackgroundColor(int color) {
    currentBackgroundColor = color;
}

void Console::clear(COORD p1, COORD p2) {
    if (p1.X == -1 || p1.Y == -1 || p2.X == -1 || p2.Y == -1) {
        system("cls");
        return;
    }
    if (p1.X > p2.X) std::swap(p1.X, p2.X);
    if (p1.Y > p2.Y) std::swap(p1.Y, p2.Y);
    std::string replace = "";
    for (int i = p1.X; i <= p2.X; i++)
        replace += " ";
    for (int i = p1.Y; i <= p2.Y; i++) {
        writeAt(replace, -1, {p1.X, SHORT(i)});
    }
}

void Console::test(int backgroundColor, char character, int textColor, int x, int y) {
    // Set the console screen buffer's background color
    currentBackgroundColor = backgroundColor;
    SetConsoleTextAttribute(hConsole, backgroundColor | FOREGROUND_INTENSITY);

    // Get the current console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    // Set the background color for the entire screen
    COORD bufferSize = { bufferInfo.dwSize.X, bufferInfo.dwSize.Y };
    COORD home = { 0, 0 };
    DWORD cellCount = bufferSize.X * bufferSize.Y;
    DWORD count;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, home, &count);
    FillConsoleOutputAttribute(hConsole, backgroundColor | FOREGROUND_INTENSITY, cellCount, home, &count);

    // Set the text color and character at the specified position
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, position);

    SetConsoleTextAttribute(hConsole, textColor | backgroundColor | FOREGROUND_INTENSITY);
    WriteConsole(hConsole, &character, 1, nullptr, nullptr);

    // Restore the original text attributes
    SetConsoleTextAttribute(hConsole, bufferInfo.wAttributes);
}


// (3, 0) (0, 3) => (0, 0) (3, 3)

// (0, 3) (3, 0)
