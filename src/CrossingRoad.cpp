#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    int debug = 0;
    Screen *mainScreen = new MenuScreen();
    Command *command;
    while (true) {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command) {
            command->excute(mainScreen);
            delete command;
        }
    	Sleep(1);
    }
    delete mainScreen;
    int x;
    cin >> x;
    return 0;
}
