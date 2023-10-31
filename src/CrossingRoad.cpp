#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    appConsole.init();
    importImage.init(&appConsole);
    // int debug = 0;
    mainScreen = new MenuScreen();
    Command *command;
    while (true) {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command) {
            command->execute();
            delete command;
        }
    	Sleep(10);
    }
    delete mainScreen;
    return 0;
}
