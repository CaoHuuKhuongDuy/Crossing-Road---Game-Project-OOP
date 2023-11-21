#include "staticVariable.h"
#include "screenStack.h"

namespace stValue {
	COORD FIX_SIZE = {211, 54};
    COORD FONT_SIZE = {6, 11};
    int DEFAULT_STEP = 5;
	string GAME_NAME = "Crossing Road";
	Console appConsole;
    ImportImage importImage;
    ScreenStack listScreen;
    ListPlayer listPlayer;
    Player *mainPlayer = nullptr;
    void init() {
        appConsole.init();
        importImage.init(&appConsole);
        listPlayer.init();
        listScreen.init();
    }
}