#include "entity.h"

Entity::Entity(COORD pos1, COORD pos2) : startPos(pos1), endPos(pos2) {}

Rocket::Rocket(COORD pos1, COORD pos2) : Entity(pos1, pos2) {}

void Rocket::draw() {
    importImage.draw("rocket.txt", startPos);
}