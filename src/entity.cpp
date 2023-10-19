#include "entity.h"

Entity::Entity(COORD pos1, COORD size, int ascii1Pixel = 1) : startPos(pos1) {
    endPos = {SHORT(startPos.X + size.X * ascii1Pixel - 1), SHORT(startPos.Y + size.Y - 1)};
}

Rocket::Rocket(COORD pos1, COORD size, int ascii1Pixel = 1) : Entity(pos1, size, ascii1Pixel) {}

void Rocket::draw() {
    importImage.draw("rocket.txt", startPos);
}