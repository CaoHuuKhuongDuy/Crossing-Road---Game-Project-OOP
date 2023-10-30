#include "command.h"
#include "screen.h"



void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {
    delete mainScreen;
    mainScreen = nxtScreen;
}


void EnterGameCommand::execute(Screen *&mainScreen) {
    changeScreen(mainScreen, new GameScreen());
}

void MoveUpCommand::execute(Hero *hero)
{
    hero->up(5);
}

void MoveDownCommand::execute(Hero *hero)
{
    hero->down(5);
}

void MoveLeftCommand::execute(Hero *hero)
{
    hero->left(5);
}

void MoveRightCommand::execute(Hero *hero)
{
    hero->right(5);
}


// void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {}

// void EnterGameCommand::excute(Screen *&mainScreen) {}
