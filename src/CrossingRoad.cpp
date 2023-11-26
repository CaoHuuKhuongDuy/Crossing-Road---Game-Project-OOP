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
        mainScreen->playMusic();
        command = mainScreen->handleInput();
        if (command) command->execute();
        Sleep(10);
    }
    return 0;
}
