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
