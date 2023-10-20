#include "entity.h"

Entity::Entity(COORD pos1, COORD size, int ascii1Pixel = 1) : startPos(pos1) {
    endPos = {SHORT(startPos.X + size.X * ascii1Pixel - 1), SHORT(startPos.Y + size.Y - 1)};
}

DynamicEntity::DynamicEntity(COORD pos1, COORD size, int ascii1Pixel = 1) 
    : Entity(pos1, size, ascii1Pixel), remainStartPos ({-1, -1}), remainEndPos({-1, -1}) {};

void DynamicEntity::left(int step) {

}

Rocket::Rocket(COORD pos1, COORD size, int ascii1Pixel = 1) : DynamicEntity(pos1, size, ascii1Pixel) {}

void Rocket::draw() {
    importImage.draw("rocket.txt", startPos);
}