#include "entity.h"
void display(COORD pos) {
    cout << pos.X << " " << pos.Y << endl;
}

void Entity::verify() {
    COORD sizeScreen = appConsole.getWindowSize();
    sizeScreen.Y--;
    startPos.X = max(startPos.X, SHORT(0));
    startPos.X = min(startPos.X, SHORT(sizeScreen.X - size.X));
    startPos.Y = max(startPos.Y, SHORT(0));
    startPos.Y = min(startPos.Y, SHORT(sizeScreen.Y - size.Y));
}

// X + size - 1 < sizeScren
// x <= sizeScreen + 1 - size

Entity::Entity(string entityName_, COORD pos1, COORD size_, string defaultValue_, bool colorBG_) 
    : entityName(entityName_), startPos(pos1), size(size_), defaultValue(defaultValue_), colorBG(colorBG_) {
    size.X *= SHORT(defaultValue.size());
    remainStartPos = remainEndPos = {-1, -1};
    verify();
}

void Entity::draw() {
    if (remainStartPos.X != -1) {
        appConsole.clear(remainStartPos, remainEndPos);
        remainStartPos = remainEndPos = {-1, -1};
    }
   importImage.drawImage(entityName, startPos, defaultValue, colorBG);
}

DynamicEntity::DynamicEntity(string entityName_, COORD pos1, COORD size_, string defaultValue_, bool colorBG_) 
    : Entity(entityName_, pos1, size_, defaultValue_, colorBG_) {};


void DynamicEntity::caculateRemainFrame(COORD oldPos) {

    if (startPos.Y > oldPos.Y) {
        remainStartPos = oldPos;
        remainEndPos = {SHORT(oldPos.X + size.X - 1), min(SHORT(oldPos.Y + size.Y - 1), SHORT(startPos.Y - 1))};
    }
    if (startPos.Y < oldPos.Y) {
        remainEndPos = {SHORT(oldPos.X + size.X - 1), SHORT(oldPos.Y + size.Y - 1)};
        remainStartPos = {oldPos.X, max(SHORT(startPos.Y + size.Y), oldPos.Y)};
    }

    if (startPos.X > oldPos.X) {
        remainStartPos = oldPos;
        remainEndPos = {min(SHORT(oldPos.X + size.X - 1), SHORT(startPos.X - 1)), SHORT(oldPos.Y + size.Y - 1)};
    }

    if (startPos.X < oldPos.X) {
        remainEndPos = {SHORT(oldPos.X + size.X - 1), SHORT(oldPos.Y + size.Y - 1)};
        remainStartPos = {max(oldPos.X, SHORT(startPos.X + size.X)), oldPos.Y};
    }
}

void DynamicEntity::teleport(COORD pos) {
    COORD oldPos = startPos;
    startPos = pos;
    verify();
    caculateRemainFrame(oldPos);
}

void DynamicEntity::left(int step) {
    teleport({SHORT(startPos.X - step), startPos.Y});
}

void DynamicEntity::right(int step) {
    teleport({SHORT(startPos.X + step), startPos.Y});
}

void DynamicEntity::up(int step) {
    teleport({startPos.X, SHORT(startPos.Y - step)});
}

void DynamicEntity::down(int step) {
    teleport({startPos.X, SHORT(startPos.Y + step)});
}