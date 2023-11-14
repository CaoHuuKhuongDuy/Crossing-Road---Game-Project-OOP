#include "screenStack.h"

ScreenStack::ScreenStack() {}

ScreenStack::~ScreenStack() {
    while (screens.size()) {
        delete screens.top();
        screens.pop();
    }
}

void ScreenStack::init() {
    screens.push(new MenuScreen());
}

void ScreenStack::push(Screen* screen) {
    screens.push(screen);
}

void ScreenStack::pop() {
    if (screens.size() == 1) return;
    delete screens.top();
    screens.pop();
    screens.top()->setAgain();
}

Screen* ScreenStack::top() {
    return screens.top();
}

int ScreenStack::size() {
    return screens.size();
}