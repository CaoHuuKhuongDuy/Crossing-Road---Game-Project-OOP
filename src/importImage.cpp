#include "importImage.h"
#include "screen.h"



ImportImage::ImportImage() : pathColorCode("../media/colorCode_"), pathASCIICode("../media/asciiCode_") {}

void ImportImage::init(Console *appConsole) {
    this->appConsole = appConsole;
}

int ImportImage::convertBGColor2TextColor(int colorBackground) {
    switch (colorBackground) {
        case BG_BLACK: return BLACK;
        case BG_BLUE: return BLUE;
        case BG_GREEN: return GREEN;
        case BG_RED: return RED;
        case BG_MAGENTA: return MAGENTA;
        case BG_YELLOW: return YELLOW;
        case BG_WHITE: return WHITE;
        case BG_GREY: return GREY;
        case BG_LIME: return LIME;
        case BG_CYAN: return CYAN;
        case BG_ORANGE: return ORANGE;
        default: return WHITE; // Default to white text color
    }
}

void ImportImage:: drawImage(string pathFile, COORD pos, string defaultText, bool colorBG) {
    pathFile = pathColorCode + pathFile;
    ifstream fi(pathFile, ios::binary);
    int tmpY = pos.Y;
    int x = -1, y, colorCode;
    int numbers[3];

    while (fi.read(reinterpret_cast<char*>(numbers), sizeof(numbers))) {
        int preX = x;
        x = numbers[0];
        y = numbers[1];
        colorCode = numbers[2];
        if (preX != -1 && x != preX) {
            pos.Y = tmpY;
            pos.X += (SHORT)defaultText.size();
        }
        else if (x == preX) pos.Y++;
        if (colorCode == BG_MAGENTA) {
            appConsole->writeAt(" ", -1, pos, appConsole->getBackgroundColor());
            continue;
        }
        if (colorBG) appConsole->writeAt(defaultText, -1, pos, colorCode);
        else appConsole->writeAt(defaultText, convertBGColor2TextColor(colorCode), pos);
    }
    fi.close();
}

void ImportImage::drawASCII(string pathFile, COORD pos, int textColor) {
    pathFile = pathASCIICode + pathFile;
    ifstream fi(pathFile);

    if (!fi.is_open()) {
        cerr << "Error: Unable to open ASCII file: " << pathFile << endl;
        return;
    }

    SHORT x = pos.X;
    SHORT y = pos.Y;

    unsigned char character;
    while (fi.read(reinterpret_cast<char*>(&character), sizeof(character))) {
        if (character == '\n') {
            x = pos.X;
            y++;
        } else {
            if (character != ' ') appConsole->writeAt(string(1, character), textColor, {x, y});
            x++;
        }
    }
    fi.close();
}
