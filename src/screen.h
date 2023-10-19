#pragma once 

#include "staticVariable.h"
#include"entity.h"
#include <iostream>

using namespace stValue;
using namespace std;


void GotoXY(int x, int y);


class Screen {
    public:
        Screen(int width = FIX_WIDTH, int height = FIX_HEIGHT);
        void draw();

    private:
        int width, height;
};

