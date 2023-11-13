#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main() {
    init();
    appConsole.setFullscreenBackgroundColor(BG_CYAN);
    importImage.drawImage("esc.txt", {0, 0});
    return 0;
    mainScreen = new MenuScreen();
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
