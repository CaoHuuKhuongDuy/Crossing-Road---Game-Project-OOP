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
    	// importImage.drawASCII("score.txt", {130, 15});
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
    importImage.drawImage("coolUfo.txt", {20, 20});
    // Screen *mainScreen = new MenuScreen();
    // while (true) {
    //     mainScreen = handleScreen(mainScreen);   
    //     mainScreen->draw();
    // 	Sleep(1);
    // }
   int x;
   cin >> x;
   return 0;
}
