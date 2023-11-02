#include "staticVariable.h"
#include "screen.h"

namespace stValue {
	COORD FIX_SIZE = {240, 123};
    COORD FONT_SIZE = {6, 6};
    int DEFAULT_STEP = 5;
	string GAME_NAME = "Crossing Road";
	Console appConsole;
    ImportImage importImage;
    Screen *mainScreen = nullptr;
}
