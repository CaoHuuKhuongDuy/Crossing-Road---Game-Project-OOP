#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    appConsole.init();
    importImage.init(&appConsole);
    // int debug = 0;
    // SHORT spawnHero_COORDX = (appConsole.getWindowSize().X - 13) / 2;
    // SHORT spawnHero_COORDY = (appConsole.getWindowSize().Y);
    // Hero *hero = new Hero("phoenix.txt", {spawnHero_COORDX, spawnHero_COORDY}, {11, 5}, 0, 0);
    // HandlerInput *handlerGameInput = new HandlerGameInput(hero);
    // appConsole.setFullscreenBackgroundColor(BG_CYAN);
    // mainScreen = new GameScreen();
    // while (true) {
    //     hero->draw();
    //     Command *command = handlerGameInput->handlerInput();
    //     if (command) command->execute();
    //     delete command;
    //     Sleep(100);
    // }
    // return 0;
    mainScreen = new MenuScreen();
    Command *command;
    while (true) {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command) command->execute();
    	Sleep(10);
    }
    delete mainScreen;
    int x;
    cin >> x;
    return 0;
}
