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
    // HandlerInput *handlerInputMainScreen = new HandlerMenuInput();
    Command *command;
    while (true) {
        mainScreen = handleScreen(mainScreen);   
        command = mainScreen->handleInput();
        if (command) {
            command->excute(mainScreen);
            delete command;
        }
        mainScreen->draw();
    	Sleep(1);
    }
    delete mainScreen;
    // delete handlerInputMainScreen;
    int x;
    cin >> x;
    return 0;
}
