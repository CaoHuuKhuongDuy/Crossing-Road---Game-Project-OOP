#include "button.h"

Button::Button() {}

Button::Button(std::string text_, COORD pos_, int colorNormal_, int colorClicked_) 
    : text("   " + text_ + "   "), pos(pos_), colorButton(colorNormal_), colorNormal(colorNormal_), colorClicked(colorClicked_), highlighted(false){};


void Button::toggleHighlight() {
    highlighted = !highlighted;
}

void Button::changeText() {
    text[0] = (highlighted ? '>' : ' ');
    text[1] = (highlighted ? '>' : ' ');
    text[(int)text.size() - 1] = (highlighted ? '<' : ' ');
    text[(int)text.size() - 2] = (highlighted ? '<' : ' ');
    colorButton = (highlighted ? colorClicked : colorNormal);

}

void Button::draw() {
    changeText();
    appConsole.writeAt(text, colorButton, pos);
}