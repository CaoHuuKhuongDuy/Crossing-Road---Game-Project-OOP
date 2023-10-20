#include "screen.h"
#include "button.h"
#include <vector>
#include <conio.h>
#include "console.h"

signed main() {
    stValue::appConsole.init();
    stValue::importImage.init(&stValue::appConsole);
    char keyPress = 0;
    appConsole.setFullscreenBackgroundColor(BG_BLUE);
    DynamicEntity *rocket = new DynamicEntity("rocket.txt", {100, 35}, {8, 15}, string(1, char(219)), false);

    int debug = 0;
    while (true) {
	    rocket->draw();
        debug++;
        rocket->right(1);
        Sleep(10);
        // return 0;
    }
   int x;
   cin >> x;
   return 0;
}
