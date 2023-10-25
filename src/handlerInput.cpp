#include "handlerInput.h"

int HandlerInput::getUserInput() {
    if (!_kbhit()) return -1;
    return _getch();
}

HandlerMenuInput::HandlerMenuInput() {
    enterGame = new EnterGameCommand();
}

Command *HandlerMenuInput::handlerInput() {
    int userInput = getUserInput();
    if (userInput == -1) return nullptr;
}