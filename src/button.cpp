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
    importImage.drawASCII(text, pos, colorButton);
}

ListButton::ListButton() : idButtonChoosen(0) {}

ListButton::~ListButton() {
    for (int i = 0; i < listButton.size(); i++)
        delete listButton[i];
}

int ListButton::getIdButtonChoosen() {
    return idButtonChoosen;
}

void ListButton::changeIdButtonChoosen(int nxtId) {
    int len = listButton.size();
    if (len == 0) return;
    listButton[idButtonChoosen]->toggleHighlight();
    (idButtonChoosen = nxtId) %= len;
    listButton[idButtonChoosen]->toggleHighlight();
}

void ListButton::draw() {
    for (Button *&button : listButton)
        button->draw();
}

void ListButton::addButton(Button *button) {
    listButton.push_back(button);
    if (listButton.size() - idButtonChoosen == 1) listButton[idButtonChoosen]->toggleHighlight();
}