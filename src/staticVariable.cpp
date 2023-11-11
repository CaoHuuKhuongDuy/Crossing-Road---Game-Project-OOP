#include "staticVariable.h"
#include "screen.h"

namespace stValue {
	COORD FIX_SIZE = {211, 54};
    COORD FONT_SIZE = {6, 11};
    int DEFAULT_STEP = 5;
	string GAME_NAME = "Crossing Road";
	Console appConsole;
    ImportImage importImage;
    Screen *mainScreen = nullptr;
    Player *mainPlayer = nullptr;
    ListPlayer listPlayer;
    void init() {
        appConsole.init();
        importImage.init(&appConsole);
        listPlayer.init();
        mainScreen = new MenuScreen();
    }
}