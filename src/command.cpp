#include "command.h"
#include "screen.h"



void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {
    delete mainScreen;
    mainScreen = nxtScreen;
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

MoveEntityCommand::MoveEntityCommand(Hero *&hero_) : hero(hero_) {}

MoveUpCommand::MoveUpCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveUpCommand::execute()
{
    hero->up(hero->getSpeed());
}

MoveDownCommand::MoveDownCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveDownCommand::execute()
{
    hero->down(hero->getSpeed());
}

MoveLeftCommand::MoveLeftCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}


void MoveLeftCommand::execute()
{
    hero->left(hero->getSpeed());
}

MoveRightCommand::MoveRightCommand(Hero *&hero_) : MoveEntityCommand(hero_) {}

void MoveRightCommand::execute()
{
    hero->right(hero->getSpeed());
}

