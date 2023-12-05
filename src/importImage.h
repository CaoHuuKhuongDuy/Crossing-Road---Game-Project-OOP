#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "pixels.h"
#include "console.h"

using namespace std;

class ImportImage {
    public:
        ImportImage();
        void init(Console *appConsole);
        void drawVectorPixel(vector <Pixel> &pixels, COORD pos, int colorSpecial = -1);
        void drawImage(string pathImage, COORD pos, int colorSpecial = -1);
        void drawASCII(string pathASCII, COORD pos, int textColor = WHITE);
        void drawCustomImage(string pathImage, COORD pos, bool numberSpecial = false, int specicalColor = -1);
    private:
        Console *appConsole;
        string pathColorCode;
        string pathASCIICode;
        int convertBGColor2TextColor(int colorCode);
        int convertTextColor2BGColor(int colorCode);
};