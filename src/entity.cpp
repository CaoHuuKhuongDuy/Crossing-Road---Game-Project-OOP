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

COORD Entity::getSize()
{
    return {size.X, size.Y};
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
    : Entity(entityName_, pos1, size_), speed(5) {};


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

void DynamicEntity::slip(int step) {
    teleport({SHORT(startPos.X - step), SHORT(startPos.Y + step)});
}

void DynamicEntity::spawnDynamicEntity(double speed)
{
    this->draw();
    this->right(speed);
}
void DynamicEntity::resetDynamicEntity()
{
    this->teleport({0, this->getPos().Y});
}

bool DynamicEntity::isAtEdge(SHORT posEdge_X)
{
    if(this->getEndPos().X >= SHORT(posEdge_X))
        return true;
    return false;
}

int DynamicEntity::getSpeed() {
    return speed;
}

void DynamicEntity::setSpeed(const int& speed)
{
    this->speed = speed;
}


void Hero::resetDynamicEntity()
{
    this->teleport({SHORT((appConsole.getWindowSize().X - this->getHeroWidth()) / 2), SHORT(appConsole.getWindowSize().Y + 10)});
}

Hero::Hero(string entityName_, COORD pos1, COORD size_, int score_)
    : DynamicEntity(entityName_, pos1, size_), score(score_){}
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
int Hero::getHeroScore()
{
    return this->score;
}

void Hero::setHeroLevel(const int& level)
{
    this->level = level;
}

void Hero::setHeroScore(const int& score)
{
    this->score = score;
}

void Hero::updateHeroExp()
{
    this->score += 100;
    this->level = int(floor(this->score / 300)) + 1;
}

void Hero::updateHeroExp(const int& score)
{
    this->score = score;
    this->level = int(floor(this->score / 300)) + 1;
}


bool Hero::isCollision(DynamicEntity* enemy)
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

bool Hero::isAtEdge(SHORT posEdge_Y)
{
    if (this->getEndPos().Y <= posEdge_Y)
        return true;
    return false;
}

void Hero::verify()
{
    COORD sizeScreen = appConsole.getWindowSize();
    sizeScreen.Y--;
    startPos.X = max(startPos.X, SHORT(0));
    startPos.X = min(startPos.X, SHORT(sizeScreen.X - size.X -7));
    startPos.Y = max(startPos.Y, SHORT(0));
    startPos.Y = min(startPos.Y, SHORT(sizeScreen.Y - size.Y));
}

TrafficLight::TrafficLight(bool isRed_) : isRed(isRed_){}

TrafficLight::TrafficLight(string entityName_, COORD pos1, COORD size_, bool isRed_) : Entity(entityName_, pos1, size_), isRed(isRed_){
}

void TrafficLight::freezeEnemy(DynamicEntity* &enemy)
{
    enemy->setSpeed(0);
}


void TrafficLight::freezeRowEnemy(DynamicEntity** &enemy, const int& rowIndex)
{
    if (rowIndex == -1) return;
    for(int i = 0; i < 3; ++i)
    {
        this->freezeEnemy(enemy[rowIndex * 3 + i]);
    }
    this->setLight(true);

}

void TrafficLight::setLight(const bool& isRed)
{
    this->isRed = isRed;
}

void TrafficLight::updateLight()
{
    COORD posLight = {SHORT(this->getPos().X + 2), SHORT(this->getPos().Y + 1)};
    if (this->isRed)
        importImage.drawImage("red.txt", posLight);
    else 
        importImage.drawImage("green.txt", posLight);
}

void ControlTrafficLight::setTrafficLight(const bool& trafficlight)
{
    this->isRed = trafficlight;
}

bool ControlTrafficLight::isRedOn()
{
    return this->isRed;
}

void ControlTrafficLight::updateTrafficLight()
{
    auto currentTime = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = currentTime - startTime;
    int secondsElapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(duration).count());
    if (this->isRedOn()) {
        if (secondsElapsed >= 4) {
            isRed = false;
            startTime = chrono::high_resolution_clock::now();
        }
    }
    else
    {
        if (secondsElapsed >= 5)
        {
            isRed = true;
            startTime =  chrono::high_resolution_clock::now();

        }
        this->stopRow1 = (rand() % 11) % 5;
        this->stopRow2 = (this->stopRow1 + rand()) % 5;
    }
}
ControlTrafficLight::ControlTrafficLight(bool isRed_ ) : TrafficLight(isRed){}
