#pragma once

#include <iostream>
#include <fstream>
#include "console.h"

using namespace std;

class ImportImage
{
public:
    ImportImage();
    void init(Console *appConsole);
    void drawImage(string pathImage, COORD pos);
    void drawASCII(string pathASCII, COORD pos, int textColor = WHITE);
    void drawCustomImage(string pathImage, COORD pos, bool numberSpecial = false);

private:
    Console *appConsole;
    string pathColorCode;
    string pathASCIICode;
    int convertBGColor2TextColor(int colorCode);
};