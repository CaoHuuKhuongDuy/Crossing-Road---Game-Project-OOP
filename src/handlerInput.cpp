#include "handlerInput.h"

int HandlerInput::getUserInput() {
    if (!_kbhit()) return -1;
    return _getch();
}

void HandlerInput::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {
    delete mainScreen;
    mainScreen = nxtScreen;
}

HandlerMenuInput::HandlerMenuInput() {
    enterGame = new EnterGameCommand();
}

Command *HandlerMenuInput::handlerInput(Screen *&mainScreen, ButtonList &buttonList) {
    int userInput = getUserInput();
    if (userInput == -1) return nullptr;
    if (userInput == 72) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() - 1);
    if (userInput == 80) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() + 1);
    if (userInput == 13) {
        int buttonId = buttonList.getIdButtonChoosen();
        if (buttonId == 0) changeScreen(mainScreen, new GameScreen());
    }
    return nullptr;
}

// Up Arrow: 72
// Down Arrow: 80
// Left Arrow: 75
// Right Arrow: 77