#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    appConsole.init();
    importImage.init(&appConsole);
    mainScreen = new GameScreen();
    // appConsole.setFullscreenBackgroundColor(BG_CYAN);
    // while (true) {
    //     mainScreen->draw();
    // }
    // int x;
    // cin >> x;
    // cout << "Hello";
    // return 0;
    Command *command;
    while (true) {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command) command->execute();
    	Sleep(10);
    }
    delete mainScreen;
    return 0;
}
