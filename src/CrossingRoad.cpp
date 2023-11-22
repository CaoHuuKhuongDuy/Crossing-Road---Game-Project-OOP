#include "screen.h"
#include "screenStack.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    init();
    Screen *mainScreen;
    Command *command;
    while (true) {
        mainScreen = listScreen.top();
        mainScreen->draw();
        appConsole.test(BG_CYAN, '*', WHITE, 10, 10);
        command = mainScreen->handleInput();
        if (command) command->execute();
    	Sleep(10);
    }
    delete mainScreen;
    return 0;
}
