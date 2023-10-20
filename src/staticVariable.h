#pragma once


#include "Windows.h"
#include "console.h"
#include "importImage.h"
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



// typedef enum
// {
// 	MOVE_RIGHT,
// 	MOVE_LEFT
// } DIRECTION;

// typedef enum
// {
// 	MOVE_LEFT,
// 	MOVE_RIGHT,
// 	MOVE_UP,
// 	MOVE_DOWN,
// 	PAUSE_GAME,
// 	SAVE_GAME, 
// 	LOAD_GAME
// } COMMAND;



namespace stValue {
	extern int FIX_WIDTH, FIX_HEIGHT;
    extern int DEFAULT_STEP;
	extern string GAME_NAME, PATH_PROJECT;
    extern Console appConsole;  // special variable (not upcase)
    extern ImportImage importImage;
}