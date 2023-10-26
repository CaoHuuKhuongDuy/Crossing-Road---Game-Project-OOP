#pragma once 

#include <iostream>
#include <vector>
#include "staticVariable.h"

using namespace stValue;
using namespace std;

class Button {
    public:
        Button();
        Button(std::string text_, COORD pos_, int colorNormal = WHITE, int colorClicked = appConsole.getBackgroundColor());
        void toggleHighlight();
        void draw();
    private:
        std::string text;
        COORD pos;
        int colorButton, colorNormal, colorClicked;
        bool highlighted;
        void changeText();
};

class ButtonList {
    public:
        ButtonList();
        ~ButtonList();
        void addButton(Button* button);
        void changeIdButtonChoosen(int nxtId);
        int getIdButtonChoosen();
        void draw();
    private:
        int idButtonChoosen;
        vector <Button*> buttonList;
};