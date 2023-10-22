#include "screen.h"
#include "button.h"
#include <vector>
#include <conio.h>
#include "console.h"

Screen* handleScreen(Screen* curScreen) {
    return curScreen;
}

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    char keyPress = 0;
    int debug = 0;
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
    Screen *mainScreen = new menuScreen();
    while (true) {
        mainScreen = handleScreen(mainScreen);   
        mainScreen->draw();
    	Sleep(10);
    }
    // DynamicEntity *rocket = new DynamicEntity("rocket.txt", {1, 10}, {8, 15}, string(1, char(219)), false);
    // while (true) {
    //     rocket->draw();
    //     rocket->up(1);
    // }
   int x;
   cin >> x;
   return 0;
}
