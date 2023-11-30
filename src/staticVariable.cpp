#include "staticVariable.h"
#include "screenStack.h"

namespace stValue {
	COORD FIX_SIZE = {211, 54};
    COORD FONT_SIZE = {12, 16};
    int DEFAULT_STEP = 5;
	string GAME_NAME = "Crossing Road";
	Console appConsole;
    ImportImage importImage;
    ScreenStack listScreen;
    ListPlayer listPlayer;
    Player *mainPlayer = nullptr;
    Sound sound;
    bool typeHero = 0;
    int idPlayer = 5; 
    void init() {
        appConsole.init();
        importImage.init(&appConsole);
        listPlayer.init();
        listScreen.init();
    }
}
