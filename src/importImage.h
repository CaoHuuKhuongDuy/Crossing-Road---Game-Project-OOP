#pragma once

#include <iostream>
#include <fstream>
#include "console.h"

using namespace std;

class ImportImage {
    public:
        ImportImage();
        void init(Console *appConsole);
        void drawImage(string pathImage, COORD pos, string defaultText = " ", bool colorBG = true);
        void drawASCII(string pathASCII, COORD pos, string defaultText = " ", bool colorBG = true);
    private:
        Console *appConsole;
        string pathColorCode;
        string pathASCIICode;
        int convertBGColor2TextColor(int colorCode);
};