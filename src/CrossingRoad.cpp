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

    while (true) {
		Screen* newScreen = new Screen();
		newScreen->draw();
        delete newScreen;
        // break;
    }
   int x;
   cin >> x;
   return 0;
}
