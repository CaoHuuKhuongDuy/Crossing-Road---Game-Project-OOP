#include "handlerInput.h"

int HandlerInput::getUserInput() {
    if (!_kbhit()) return -1;
    return _getch();
}


HandlerMenuInput::HandlerMenuInput()
{
    enterGame = new EnterGameCommand();
}
HandlerMenuInput::~HandlerMenuInput() {
    delete enterGame;
}



Command *HandlerMenuInput::handlerInput(ButtonList &buttonList) {
    int userInput = getUserInput();
    if (userInput == -1) return nullptr;
    if (userInput == 72) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() - 1);
    if (userInput == 80) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() + 1);
    if (userInput == 13) {
        int buttonId = buttonList.getIdButtonChoosen();
        if (buttonId == 0) return enterGame;
    }
    return nullptr;
}


HandlerGameInput::HandlerGameInput(Hero *&hero) {
    buttonUP = new MoveUpCommand(hero);
    buttonDOWN = new MoveDownCommand(hero);
    buttonLEFT = new MoveLeftCommand(hero);
    buttonRIGHT = new MoveRightCommand(hero);
}

HandlerGameInput::~HandlerGameInput() 
{
    delete buttonUP;
    delete buttonDOWN;
    delete buttonLEFT;
    delete buttonRIGHT;
}

Command *HandlerGameInput::handlerInput()
{
    int userInput = getUserInput();
    if (userInput == -1)
        return nullptr;

    if (userInput == 119)
    {
        return buttonUP;
    }
    if (userInput == 115)
    {
        return buttonDOWN;
    }
    if (userInput == 97)
    {
        return buttonLEFT;
    }
    if (userInput == 100)
    {
        return buttonRIGHT;
    }

    return nullptr;
}

Command *HandlerLoadInput::handlerInput(ButtonList &buttonList) {
    return nullptr;
}


// Up Arrow: 72
// Down Arrow: 80
// Left Arrow: 75
// Right Arrow: 77