#include "command.h"
#include "screen.h"
#include "screenStack.h"



void Command::pushScreen(Screen *nxtScreen, int numBack) {
    listScreen.push(nxtScreen, numBack);
}

void Command::popScreen() {
    listScreen.pop();
}

void EnterBackScreenCommand::execute() {
    popScreen();
}

void EnterMenuCommand::execute() {
    pushScreen(new MenuScreen());
}

void EnterIntroGameCommand::execute() {
    pushScreen(new IntroGameScreen(), 2);
}

EnterGameCommand::EnterGameCommand(int numBack_) : numBack(numBack_) {}

void EnterGameCommand::execute() {
    pushScreen(new GameScreen(), numBack);
}

void EnterLoadGameCommand::execute() {
    pushScreen(new LoadGameScreen());
}

void EnterCreditCommand::execute() {
    pushScreen(new CreditScreen());
}

void EnterLeaderCommand::execute() {
    pushScreen(new LeaderBoardScreen());
}

void EnterPauseScreenCommand::execute() {
    pushScreen(new PauseGameScreen(), 2);
}

void ExitCommand::execute() {
    appConsole.closeConsole();
}

void LoadSavedGameCommand::execute() {
    mainPlayer = listPlayer.getPlayer(idButtonChoosen);
    pushScreen(new GameScreen());
}

void LoadSavedGameCommand::setIdButtonChoosen(int idButtonChoosen_) {
    idButtonChoosen = idButtonChoosen_;
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

void ResumeGameCommand::execute() {
    listScreen.setNumback(1);
    popScreen();
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

SaveHeroCommand::SaveHeroCommand(Hero*& hero_) : MoveEntityCommand(hero_) {}

void SaveHeroCommand::execute() {
    mainPlayer->setLevel(to_string(hero->getHeroLevel()));
    mainPlayer->setScore(to_string(hero->getHeroScore()));
    listPlayer.savePlayers();
}