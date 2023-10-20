#include "entity.h"

Entity::Entity(COORD pos1, COORD pos2) : startPos(pos1), endPos(pos2) {}

Rocket::Rocket(COORD pos1, COORD pos2) : Entity(pos1, pos2) {}

Jupiter::Jupiter(COORD pos1, COORD pos2) : Entity(pos1, pos2) {}

Sartun::Sartun(COORD pos1, COORD pos2) : Entity(pos1, pos2) {}

Venus::Venus(COORD pos1, COORD pos2) : Entity(pos1, pos2) {}


void Rocket::draw() {
    importImage.drawImage("rocket.txt", startPos);
}

void Jupiter::draw()
{
    importImage.drawImage("jupiter.txt", startPos);
}

void Sartun::draw()
{
    importImage.drawImage("sartun.txt", startPos);
}

void Venus::draw()
{
    importImage.drawImage("venus.txt", startPos);
}