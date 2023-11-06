#include "command.h"
#include "screen.h"



void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {
    delete mainScreen;
    mainScreen = nxtScreen;
}

void EnterIntroGameCommand::execute() {
    changeScreen(mainScreen, new IntroGameScreen());
}

void EnterGameCommand::execute() {
    changeScreen(mainScreen, new GameScreen());
}

void EnterLoadGameCommand::execute() {
    changeScreen(mainScreen, new LoadGameScreen());
}

void EnterCreditCommand::execute() {
    changeScreen(mainScreen, new CreditScreen());
}

void EnterLeaderCommand::execute() {
    changeScreen(mainScreen, new LeaderBoardScreen());
}

InputTextCommand::InputTextCommand(string &textInput_) : textInput(textInput_), limChar(6), addChar('*') {}

void InputTextCommand::setAddChar(char c) {
    addChar = c;
}

void InputTextCommand::clearText() {
    while (textInput.size()) textInput.pop_back();
}

void InputTextCommand::execute() {
    if (addChar == '*') return;
    if (addChar == '@') {
        if (textInput.size()) textInput.pop_back();
        return;
    }
    if (textInput.size() < limChar) textInput += addChar;
}

MoveEntityCommand::MoveEntityCommand(Hero *&hero_) : hero(hero_) {}

MoveUpCommand::MoveUpCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveUpCommand::execute()
{
    hero->up(5);
}

MoveDownCommand::MoveDownCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveDownCommand::execute()
{
    hero->down(5);
}

MoveLeftCommand::MoveLeftCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveLeftCommand::execute()
{
    hero->left(5);
}

MoveRightCommand::MoveRightCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveRightCommand::execute()
{
    hero->right(5);
}
