#pragma once


#include "Windows.h"
#include "console.h"
#include "importImage.h"
#include "player.h"
#include <iostream>
#include <string>
#include <io.h>
#include <random>
#include <conio.h>
#include <tchar.h>
#include <fstream>
#include <fcntl.h>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

using namespace std;

#define MAX_NAME_LENGTH 50


class ScreenStack;
class Screen;

namespace stValue {
	extern COORD FIX_SIZE, FONT_SIZE;
    extern int DEFAULT_STEP;
	extern string GAME_NAME, PATH_PROJECT;
    extern Console appConsole;  // special variable (not upcase)
    extern ImportImage importImage;
    extern ScreenStack listScreen;
    // extern Screen *mainScreen;
    extern Player *mainPlayer;
    extern ListPlayer listPlayer;
    void init();
}