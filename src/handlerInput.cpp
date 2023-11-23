#include "handlerInput.h"

HandlerInput::HandlerInput() {
    enterBackScreen = new EnterBackScreenCommand();
}

HandlerInput::~HandlerInput() {
    delete enterBackScreen;
}

int HandlerInput::getUserInput() {
    if (fixUserInput != -1) {
        int tmp = fixUserInput;
        fixUserInput = -1;
        return tmp;
    }
    if (!_kbhit()) return -1;
    return _getch();
}

void HandlerInput::setFixUserInput(int fixUserInput) {
    this->fixUserInput = fixUserInput;
}


HandlerMenuInput::HandlerMenuInput()
{
    enterGame = new EnterIntroGameCommand();
    enterLoadGame = new EnterLoadGameCommand();
    enterCredit = new EnterCreditCommand();
    enterLeader = new EnterLeaderCommand();
    exitGame = new ExitCommand;
}
HandlerMenuInput::~HandlerMenuInput() {
    delete enterGame;
    delete enterLoadGame;
    delete enterCredit;
    delete enterLeader;
    delete exitGame;
}



Command *HandlerMenuInput::handlerInput(ButtonList &buttonList) {
    int userInput = getUserInput();
    if (userInput == 72) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() - 1);
    if (userInput == 80) buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() + 1);
    if (userInput == 13) {
        int buttonId = buttonList.getIdButtonChoosen();
        if (buttonId == 0) return enterGame;
        if (buttonId == 1) return enterLoadGame;
        if (buttonId == 2) return enterLeader;
        if (buttonId == 4) return enterCredit;
        if (buttonId == 5) return exitGame;
    }
    return nullptr;
}

HandlerIntroGameInput::HandlerIntroGameInput(string &textInput) {
    enterGame = new EnterGameCommand(2);
    inputChar = new InputTextCommand(textInput);
}

HandlerIntroGameInput::~HandlerIntroGameInput() {
    delete enterGame;
    delete inputChar;
}

Command *HandlerIntroGameInput::handlerInput(ButtonList &buttonList) {
    int userInput = getUserInput();
    if (userInput == 8) {
        inputChar->setAddChar('@');
        return inputChar;
    }
    if ((userInput >= 'a' && userInput <= 'z') || (userInput >= '0' && userInput <= '9')) {
        inputChar->setAddChar(userInput);
        return inputChar;
    }
    if (userInput == 13) {
        inputChar->clearText();
        inputChar->setAddChar('/');
        return inputChar;
    }
    if (userInput == 1) return enterGame;
    if (userInput == 27) return enterBackScreen;
    return nullptr;
}   


HandlerGameInput::HandlerGameInput(Hero *&hero) {
    buttonUP = new MoveUpCommand(hero);
    buttonDOWN = new MoveDownCommand(hero);
    buttonLEFT = new MoveLeftCommand(hero);
    buttonRIGHT = new MoveRightCommand(hero);
    saveHero = new SaveHeroCommand(hero);
    enterPauseScreen = new EnterPauseScreenCommand();
}

HandlerGameInput::~HandlerGameInput() {
    delete buttonUP;
    delete buttonDOWN;
    delete buttonLEFT;
    delete buttonRIGHT;
    delete saveHero;
    delete enterPauseScreen;
}

Command *HandlerGameInput::handlerInput(ButtonList &buttonList)
{
    int userInput = getUserInput();
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
    if (userInput == 27) {
        saveHero->execute();
        return enterPauseScreen;
    }
    return nullptr;
}

HandlerLoadInput::HandlerLoadInput() {
    loadSavedGame = new LoadSavedGameCommand();
}

HandlerLoadInput::~HandlerLoadInput() {
    delete loadSavedGame;
}

Command *HandlerLoadInput::handlerInput(ButtonList &buttonList) {
    // press esc key to back to menu
    int userInput = getUserInput();
    if (userInput == 27) return enterBackScreen;
    // check press left arrow key
    if (userInput == 75) {
        buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() - 1);
    }
    if (userInput == 77) {
        buttonList.changeIdButtonChoosen(buttonList.getIdButtonChoosen() + 1);
    }
    if (userInput == 13) {
        loadSavedGame->setIdButtonChoosen(buttonList.getIdButtonChoosen());
        return loadSavedGame;
    }
    return nullptr;
}

HandlerLeaderBoardInput::HandlerLeaderBoardInput() {}

HandlerLeaderBoardInput::~HandlerLeaderBoardInput() {
}

Command *HandlerLeaderBoardInput::handlerInput(ButtonList &ButtonList) {
    int userInput = getUserInput();
    if (userInput == 27) return enterBackScreen;
    return nullptr;
}

HandlerCreditInput::HandlerCreditInput() {}

HandlerCreditInput::~HandlerCreditInput() {
}

Command *HandlerCreditInput::handlerInput(ButtonList &buttonList) {
    // press esc key to back to menu
    int userInput = getUserInput();
    if (userInput == 27) return enterBackScreen;
    return nullptr;
}

HandlerPauseScreenInput::HandlerPauseScreenInput() {
    resumeGame = new ResumeGameCommand();
}

HandlerPauseScreenInput::~HandlerPauseScreenInput() {
    delete resumeGame;
}

Command *HandlerPauseScreenInput::handlerInput(ButtonList &buttonList) {
    int userInput = getUserInput();
    int buttonId = buttonList.getIdButtonChoosen();
    if (userInput == 72) buttonList.changeIdButtonChoosen(buttonId - 1);
    if (userInput == 80) buttonList.changeIdButtonChoosen(buttonId + 1);
    if (userInput == 13) {
        if (buttonId == 0) return resumeGame;
        if (buttonId == 1) return enterBackScreen;
    }
    return nullptr;
}

// Up Arrow: 72
// Down Arrow: 80
// Left Arrow: 75
// Right Arrow: 77
