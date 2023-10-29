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

Entity::Entity(string entityName_, COORD pos1, COORD size_) 
    : entityName(entityName_), startPos(pos1), size(size_){
    remainStartPos = remainEndPos = {-1, -1};
    verify();
}

COORD Entity::getPos() {
    return startPos;
}

COORD Entity::getEndPos() {
    COORD endPos = startPos;
    endPos.X += size.X - 1;
    endPos.Y += size.Y - 1;
    return endPos;
}


void Entity::removeRemainFrame() {
    if (remainStartPos.X != -1) {
        appConsole.clear(remainStartPos, remainEndPos);
        remainStartPos = remainEndPos = {-1, -1};
    }
}

void Entity::draw() {
    removeRemainFrame();
    importImage.drawImage(entityName, startPos);
}

DynamicEntity::DynamicEntity(string entityName_, COORD pos1, COORD size_) 
    : Entity(entityName_, pos1, size_) {};


void DynamicEntity::caculateRemainFrame(COORD oldPos) {
    removeRemainFrame();
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

void DynamicEntity::down(int step)
{
    teleport({startPos.X, SHORT(startPos.Y + step)});
}

Hero::Hero(string entityName_, COORD pos1, COORD size_, long int score_, int level_)
    : DynamicEntity(entityName_, pos1, size_), score(score_), level(level_) {}
SHORT Hero::getHeroWidth()
{
    return this->heroWidth;
}
SHORT Hero::getHeroHeight()
{
    return this->heroHeight;
}
int Hero::getHeroLevel()
{
    return this->level;
}
long int Hero::getHeroScore()
{
    return this->score;
}

void Hero::setHeroLevel(const int& level)
{
    this->level = level;
}

void Hero::setHeroScore(const long int& score)
{
    this->score = score;
}

void Hero::updateHeroExp()
{
    this->level = int(floor(this->score / 1000)) + 1;
    this->score += 100;
}

bool Hero::checkCollision(DynamicEntity* enemy)
{
    if (enemy == nullptr) return false;
    COORD startPos1 = enemy->getPos();
    COORD endPos1 = enemy->getEndPos();
    COORD startPos2 = this->getPos();
    COORD endPos2 = this->getEndPos();

    if (startPos1.X <= endPos2.X && endPos1.X >= startPos2.X &&
        startPos1.Y <= endPos2.Y && endPos1.Y >= startPos2.Y)
        return true;
    return false;

}