#include "importImage.h"


void GotoXY(int x, int y) {
  	COORD coord;
  	coord.X = x;
 	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

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
    ifstream fi(pathFile);
    int tmpY = pos.Y;
    int x = -1, y, colorCode;
    while (!fi.eof()) {
        int preX = x;
        fi >> x >> y >> colorCode;
        if (fi.eof()) break;
        if (preX != -1 && x != preX) {
            pos.Y = tmpY;
            pos.X += (SHORT)defaultText.size();
        }
        else if (x == preX) pos.Y++;
        if (colorCode == BG_MAGENTA) {
            appConsole->writeAt(" ", -1, pos, appConsole->getBackgroundColor());
            continue;
        }
        //  if (colorCode == 176) while (true) {}
        //  if (convertBGColor2TextColor(colorCode) == CYAN) while (true) {}
        if (colorBG) appConsole->writeAt(defaultText, -1, pos, colorCode);
        else appConsole->writeAt(defaultText, convertBGColor2TextColor(colorCode), pos);
    }
    fi.close();
}

void ImportImage::drawASCII(string pathFile, COORD pos, string defaultText, bool colorBG) {
    pathFile = pathASCIICode + pathFile;
    ifstream fi(pathFile);

    if (!fi.is_open()) {
        cerr << "Error: Unable to open ASCII file: " << pathFile << endl;
        return;
    }

    SHORT x = pos.X;
    int y = pos.Y;

    char character;
    while (fi.get(character)) {
        if (character == '\n') {
            x = pos.X;
            y++;
        } else {
            if (colorBG) {
                int textColor = convertBGColor2TextColor(7);
                appConsole->setTextColor(textColor);
            }
            COORD charPos = {x, y };
            GotoXY(x, y);
            appConsole->writeAt(defaultText, convertBGColor2TextColor(character), pos);
            x++;
        }
    }
    fi.close();
}
