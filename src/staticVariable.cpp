#include "staticVariable.h"
#include "screen.h"

namespace stValue {
	COORD FIX_SIZE = {211, 51};
    COORD FONT_SIZE = {7, 16};
    int DEFAULT_STEP = 5;
	string GAME_NAME = "Crossing Road";
	Console appConsole;
    ImportImage importImage;
    Screen *mainScreen = nullptr;
}