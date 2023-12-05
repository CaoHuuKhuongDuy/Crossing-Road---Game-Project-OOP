 #include "screenstack.h"
 #include <vector>
 #include <conio.h>
 #include "console.h"
 #include "staticVariable.h"

 using namespace stValue;

 signed main() {
     init();
    //  Entity *rocket = new DynamicEntity("rocket.txt", {1, 25}, {8, 15});
    //  while (true) {
    //     rocket->draw();
    //  }
    //  return 0;
     Screen *mainScreen;
     Command *command;
     while (appConsole.getRunning()) {
         mainScreen = listScreen.top();
         mainScreen->draw();
         mainScreen->playMusic();
         command = mainScreen->handleInput();
         if (command) command->execute();
         Sleep(10);
     }
     return 0;
 }
