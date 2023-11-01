#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    appConsole.init();
    importImage.init(&appConsole);
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
