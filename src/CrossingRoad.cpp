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
    // LoadGameScreen *screen = new LoadGameScreen;
    while (true)
    {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command)
        {
            command->execute(mainScreen);
            delete command;
        }
        // screen->draw();
    	Sleep(10);
    }
    delete mainScreen;
    // delete screen;
    int x;
    cin >> x;
    return 0;
}
