#include "screenStack.h"

ScreenStack::ScreenStack() {}

ScreenStack::~ScreenStack() {
    while (screens.size()) {
        delete screens.top().first;
        screens.pop();
    }
}

void ScreenStack::init() {
    screens.push({new MenuScreen(), 1});
}

void ScreenStack::push(Screen* screen, int numBack) {
    screens.push({screen, numBack});
}

void ScreenStack::pop() {
    if (screens.size() == 1) return;
    delete screens.top().first;
    screens.pop();
    top()->setAgain();
    int numPopScreen = 0;
    do {
        numPopScreen = max(numPopScreen, screens.top().second) - 1;
        screens.pop();
    } while (numPopScreen > 0 && screens.size() > 1);
}

Screen* ScreenStack::top() {
    return screens.top().first;
}

void ScreenStack::setNumback(int numBack) {
    screens.top().second = numBack;
}

int ScreenStack::size() {
    return screens.size();
}