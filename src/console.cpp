#include "console.h"
#include "staticVariable.h"

// Console::Console() : currentBackgroundColor(0), currentTextColor(0) {}

void Console::setFont(const wchar_t* fontType) {
    CONSOLE_FONT_INFOEX cfi;
    wcscpy_s(cfi.FaceName, fontType); // Font name (you can change this)
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

COORD Console::calculateFontSize() {
    COORD size;
    HWND desktopWindow = GetDesktopWindow();

   // Get the screen dimensions
    RECT desktopRect;
    GetClientRect(desktopWindow, &desktopRect);
   // Calculate the width and height of the screen
    int screenWidth = desktopRect.right;
    int screenHeight = desktopRect.bottom;
    size.X = screenWidth / stValue::FIX_SIZE.X;
    size.Y = screenHeight / stValue::FIX_SIZE.Y - 2;
    return size;
}

void Console::setFontSize() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize = stValue::FONT_SIZE;
    // cfi.dwFontSize = calculateFontSize();
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Console::setWindowSize() {
     // Set the buffer size
    if (!SetConsoleScreenBufferSize(hConsole, stValue::FIX_SIZE))
        throw std::runtime_error("Unable to set console screen buffer size.");
    setFontSize();
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(stValue::FIX_SIZE.X - 1), static_cast<SHORT>(stValue::FIX_SIZE.Y - 1) };
    if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
        throw std::runtime_error("Unable to set console window size.");
}

void Console::init() {
    running = true;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    szConsole = GetConsoleWindow();
    setConsolePos();
    LONG style = GetWindowLong(szConsole, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(szConsole, GWL_STYLE, style);
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    size = stValue::FIX_SIZE;
    setWindowSize();
};

void Console::setConsolePos() {
    // set the window to the center of the screen
    HWND desktopWindow = GetDesktopWindow();
    RECT desktopRect;
    GetClientRect(desktopWindow, &desktopRect);

    // Calculate the width and height of the screen
    int screenWidth = desktopRect.right;
    int screenHeight = desktopRect.bottom;
    int posX = (screenWidth - stValue::FIX_SIZE.X * stValue::FONT_SIZE.X) / 2;
    int posY = (screenHeight - stValue::FIX_SIZE.Y * stValue::FONT_SIZE.Y) / 2;
    SetWindowPos(szConsole, 0, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

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
    if (text.size() == 1) {
        int color;
        if (colorBackground != -1) color = colorBackground;
        else {
            if(GetConsoleScreenBufferInfo(hConsole, &csbi)) color = (csbi.wAttributes & 0xF0) + (colorText & 0x0F);
        
        }
        test(text[0], color, posCursor.X, posCursor.Y, posCursor.X, posCursor.Y);
        return;
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
    // std::string replace = "";
    // for (int i = p1.X; i <= p2.X; i++)
    //     replace += " ";
    for (int i = p1.Y; i <= p2.Y; i++) {
        for (int j = p1.X; j <= p2.X; j++)
            writeAt(" ", -1, {SHORT(j), SHORT(i)}, currentBackgroundColor);
    }
}

BOOL Console::CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
    case CTRL_CLOSE_EVENT:
        std::cin.get();
        return TRUE;
    default:
        return FALSE;
    }
}

void Console::closeConsole() {
 //   SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
    //if (szConsole) SendMessage(szConsole, WM_CLOSE, 0, 0);
    running = false;
}

void Console::test(char character, int color, int left, int top, int right, int bottom) {
    // Set the console screen buffer's text and background color
    // SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
    // setTextColor(textColor);

    // Get the console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    // Ensure the coordinates are within bounds
    left = max(0, min(left, bufferInfo.dwSize.X - 1));
    top = max(0, min(top, bufferInfo.dwSize.Y - 1));
    right = max(left + 1, min(right, (int)bufferInfo.dwSize.X));
    bottom = max(top + 1, min(bottom, (int)bufferInfo.dwSize.Y));

    // Fill the rectangle with the new character and color
    for (int y = top; y < bottom; ++y) {
        COORD position = { static_cast<SHORT>(left), static_cast<SHORT>(y) };
        DWORD count;

        // Fill the character and color
        FillConsoleOutputCharacter(hConsole, character, right - left, position, &count);
        FillConsoleOutputAttribute(hConsole, color, right - left, position, &count);
    }

    // Reset the text attribute to the original state
    SetConsoleTextAttribute(hConsole, currentBackgroundColor);
}


// (3, 0) (0, 3) => (0, 0) (3, 3)

// (0, 3) (3, 0)
