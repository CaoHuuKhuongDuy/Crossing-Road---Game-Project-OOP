#pragma once

#include <iostream>
#include <fstream>
#include "console.h"

using namespace std;

class ImportImage {
    public:
        ImportImage();
        void init(Console *appConsole);
        void draw(string pathImage, COORD pos, string defaultText = " ", bool colorBG = true);
    private:
        Console *appConsole;
        string pathColorCode;
        int convertBGColor2TextColor(int colorCode);
};