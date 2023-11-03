#include "screen.h"
#include <vector>
#include <conio.h>
#include "console.h"

using namespace stValue;

signed main()
{
    appConsole.init();
    importImage.init(&appConsole);
    // appConsole.setFullscreenBackgroundColor(BG_RED);
    // DynamicEntity *shark = new DynamicEntity("shark.txt", {0, 0}, {30, 30});
    // while (true) {
    //     shark->draw();
    //     shark->right(10);
    //     Sleep(10);
    // }
    // importImage.drawImage("shark.txt", {0, 0});
    // cout << appConsole.getWindowSize().X << " " << appConsole.getWindowSize().Y << endl;
    // appConsole.writeAt("heelo", RED, {449, 10});
    // return 0;
    mainScreen = new MenuScreen();
    Command *command;
    while (true)
    {
        mainScreen->draw();
        command = mainScreen->handleInput();
        if (command)
            command->execute();
        Sleep(10);
    }
    delete mainScreen;
    int x;
    cin >> x;
    return 0;
}
