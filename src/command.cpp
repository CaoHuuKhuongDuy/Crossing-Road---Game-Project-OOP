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
    hero->up(1);
}

void MoveDownCommand::execute(Hero *hero)
{
    hero->down(1);
}

void MoveLeftCommand::execute(Hero *hero)
{
    hero->left(1);
}

void MoveRightCommand::execute(Hero *hero)
{
    hero->right(1);
}


// void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {}

// void EnterGameCommand::excute(Screen *&mainScreen) {}