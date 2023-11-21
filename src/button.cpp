#include "button.h"

Button::Button() {}

Button::Button(std::string text_, COORD pos_, int colorNormal_, int colorClicked_) 
    : text( text_ + ".txt"), pos(pos_), colorButton(colorNormal_), colorNormal(colorNormal_), colorClicked(colorClicked_), highlighted(false){};


void Button::toggleHighlight() {
    highlighted = !highlighted;
}

void Button::changeText() {
    colorButton = (highlighted ? colorClicked : colorNormal);

}

void Button::draw() {
    changeText();
    if (text[0] != '#') {
        importImage.drawASCII(text, pos, colorButton);
    }
    else {
        string tmp = text;
        tmp.erase(0, 1);
        tmp.erase(tmp.size() - 4, 4);
        // importImage.drawCustomImage(tmp, pos, false, (highlighted ? colorClicked : -1));
    }
}

ButtonList::ButtonList() : idButtonChoosen(0) {}

ButtonList::~ButtonList() {
    for (int i = 0; i < buttonList.size(); i++)
        delete buttonList[i];
}

int ButtonList::getIdButtonChoosen() {
    return idButtonChoosen;
}

void ButtonList::changeIdButtonChoosen(int nxtId) {
    int len = buttonList.size();
    if (len == 0) return;
    buttonList[idButtonChoosen]->toggleHighlight();
    (idButtonChoosen = nxtId + len) %= len;
    buttonList[idButtonChoosen]->toggleHighlight();
}

void ButtonList::draw() {
    for (Button *&button : buttonList)
        button->draw();
}

void ButtonList::addButton(Button *button) {
    buttonList.push_back(button);
    if (buttonList.size() - idButtonChoosen == 1) buttonList[idButtonChoosen]->toggleHighlight();
}