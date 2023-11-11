#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    init();
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
