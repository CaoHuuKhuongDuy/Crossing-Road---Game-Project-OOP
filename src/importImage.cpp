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

int ImportImage::convertTextColor2BGColor(int colorText) {
    switch (colorText) {
        case BLACK: return BG_BLACK;
        case BLUE: return BG_BLUE;
        case GREEN: return BG_GREEN;
        case RED: return BG_RED;
        case MAGENTA: return BG_MAGENTA;
        case YELLOW: return BG_YELLOW;
        case WHITE: return BG_WHITE;
        case GREY: return BG_GREY;
        case LIME: return BG_LIME;
        case CYAN: return BG_CYAN;
        case ORANGE: return BG_ORANGE;
        default: return BG_BLACK; // Default to black background color
    }
}


void ImportImage:: drawImage(string pathFile, COORD pos, int colorSpecial) {
    pathFile = pathColorCode + pathFile;
    // cout << pathFile << endl;
    ifstream fi(pathFile, ios::binary);
    int tmpY = pos.Y;
    int x = -1, y, colorCode;
    int numbers[4];
    char charDisplay;
    char newline;
    while (fi.read(reinterpret_cast<char*>(numbers), sizeof(numbers))) {
        // && fi.read(reinterpret_cast<char*>(&newline), sizeof(char))) {
        int preX = x;
        x = numbers[0];
        y = numbers[1];
        charDisplay = numbers[2];
        colorCode = numbers[3];
        if (preX != -1 && x != preX) {
            pos.Y = tmpY;
            pos.X++;
        }
        else if (x == preX) {
            pos.Y++;
        }
        if (colorCode == BG_MAGENTA) {
            appConsole->writeAt(" ", -1, pos, appConsole->getBackgroundColor());
            continue;
        }
        bool colorBG = (charDisplay == 32);
        if (colorBG) {
            colorCode = (colorSpecial == -1 ? colorCode : convertTextColor2BGColor(colorSpecial));
            appConsole->writeAt(string(1, charDisplay), -1, pos, colorCode);
        }
        else appConsole->writeAt(string(1, charDisplay),convertBGColor2TextColor(colorCode), pos);
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

void ImportImage::drawCustomImage(string pathImage, COORD pos, bool numberSpecial, int specicalColor) {
    for (int i = 0; i < pathImage.length(); i++) {
        if (!numberSpecial) drawImage(string(1,pathImage[i]) + ".txt", {SHORT(pos.X += 6), SHORT(pos.Y)}, specicalColor);
        else drawImage("number" + string(1, pathImage[i]) + ".txt", {SHORT(pos.X += 4), pos.Y}, specicalColor);
    }
}
