#include "screen.h"
#include "button.h"
#include <vector>
#include <conio.h>
#include "console.h"

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    char keyPress = 0;
	appConsole.setBackgroundColor(BG_BLUE);
	int debug = 0;
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
    menuScreen* menu = new menuScreen();
    menu->draw();
    while (true) {
    	
    }
    delete menu;
   int x;
   cin >> x;
   return 0;
}
