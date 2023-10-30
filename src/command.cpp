#include "command.h"
#include "screen.h"

void Command::changeScreen(Screen *&mainScreen, Screen *nxtScreen) {
    delete mainScreen;
    mainScreen = nxtScreen;
}

void EnterGameCommand::excute(Screen *&mainScreen) {
    changeScreen(mainScreen, new GameScreen());
}