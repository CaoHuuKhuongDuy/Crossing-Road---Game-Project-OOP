#pragma once 
#include <stack>
#include "screen.h"

using namespace std;

class ScreenStack {
    public:
        ScreenStack();
        ~ScreenStack();
        void init();
        void push(Screen* screen);
        void pop();
        Screen* top();
        int size();
    private:
        stack <Screen*> screens;
};