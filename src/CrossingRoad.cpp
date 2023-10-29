#include "screen.h"
#include "button.h"
#include <vector>
#include <conio.h>
#include "console.h"
#include "handlerInput.h"

Screen* handleScreen(Screen* curScreen) {
    return curScreen;
}

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    char keyPress = 0;
    int debug = 0;
    Screen *mainScreen = new MenuScreen();
    Command *command;
    // LoadGameScreen *screen = new LoadGameScreen;
    while (true) {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command) {
            command->execute(mainScreen);
            delete command;
        }
        // screen->draw();
    	Sleep(1);
    }
    delete mainScreen;
    // delete screen;
    int x;
    cin >> x;
    return 0;
}
