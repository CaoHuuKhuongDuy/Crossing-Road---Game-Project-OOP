#pragma once 
#include <stack>
#include "screen.h"

using namespace std;
typedef pair <Screen*, int> ScreenPair;

class ScreenStack {
    public:
        ScreenStack();
        ~ScreenStack();
        void init();
        void push(Screen* screen, int numBack = 1);
        void setNumback(int numBack);
        void pop();
        Screen* top();
        int size();
    private:
        stack <ScreenPair> screens;
};