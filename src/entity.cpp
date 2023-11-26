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

void Entity::setEntityname(string entityname){
    this->entityName = entityname;
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

void DynamicEntity::resetDynamicEntity()
{
    this->teleport({0, this->getPos().Y});
}

int DynamicEntity::getSpeed() {
    return speed;
}

void DynamicEntity::setSpeed(const int& speed)
{
    this->speed = speed;
}

void Enemy::spawm()
{
    this->draw();
    this->right(this->getSpeed());
}

bool Enemy::AtRightEdge(SHORT posEdge_X)
{
    if (this->getEndPos().X >= posEdge_X)
        return true;
    return false;
}

bool Enemy::AtLeftEdge(SHORT posEdge_X)
{
    if (this->getPos().X <= posEdge_X)
        return true;
    return false;
}

Enemy::Enemy(){}

Enemy::Enemy(string entityName_, COORD pos1, COORD size_) : DynamicEntity(entityName_, pos1, size_)
{
    currentState = new MovingRight();
}
Enemy::~Enemy()
{
    delete currentState;
}

void Enemy::setState(EnemyState *newState)
{
    delete currentState;
    currentState = newState;
}

EnemyState *Enemy::getState()
{
    return this->currentState;
}

EnemyStateType MovingRight::getStateType() const
{
    return  EnemyStateType::MovingRight;
}

EnemyStateType MovingLeft::getStateType() const
{
    return EnemyStateType::MovingLeft;
}

EnemyStateType StoppedState::getStateType() const
{
    return EnemyStateType::Stop;
}

void Enemy::updateState(TrafficLight *trafficlight_)
{
    if (trafficlight_->getState()->getStateType() == TrafficLightStateType::Red)
        this->setState(new StoppedState());
    else
    {
        if (trafficlight_->getPos().X <= 50)
            this->setState(new MovingLeft());
        else
            this->setState(new MovingRight());
    }
}

void Enemy::update(TrafficLight *&trafficlight_)
{
    if (currentState == nullptr) return;
    updateState(trafficlight_);
    this->draw();
    currentState->update(this);
    if (  this->currentState->getStateType() == EnemyStateType::MovingRight && this->AtRightEdge(appConsole.getWindowSize().X - 7))
        this->teleport({0, this->getPos().Y});
    else if ( this->currentState->getStateType() == EnemyStateType::MovingLeft  &&  this->AtLeftEdge(7))
        this->teleport({appConsole.getWindowSize().X, this->getPos().Y});
}

EnemyState::EnemyState() {}

NormalState::NormalState() {}

MovingState::MovingState() {}

MovingRight::MovingRight() : MovingState() {}

void MovingRight::update(Enemy* enemy)
{
    enemy->right(enemy->getSpeed());
}

MovingLeft::MovingLeft() : MovingState() {}

void MovingLeft::update(Enemy* enemy)
{
    enemy->left(enemy->getSpeed());
}

StoppedState::StoppedState() {}

void StoppedState::update(Enemy *enemy)
{
    enemy->setSpeed(0);
}

TrafficLight::TrafficLight(){}

TrafficLight::TrafficLight(string entityName_, COORD pos1, COORD size_, TrafficLightState *currentState_) : Entity(entityName_, pos1, size_), currentState(currentState_){}

TrafficLight::~TrafficLight(){delete currentState;}

void TrafficLight::setState(TrafficLightState *newState)
{
    delete currentState;
    currentState = newState;
}

void TrafficLight::update()
{
    if (currentState == nullptr)
        currentState = new GreenState();
    currentState->update(this);
}

bool TrafficLightState::TimeToTransition(int duration)
{
    auto currentTime = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = currentTime - startTime;
    int secondsElapsed = static_cast<int>(chrono::duration_cast<chrono::seconds>(duration1).count());
    return secondsElapsed >= duration;
}

TrafficLightState *TrafficLight::getState() const
{
    return currentState;
}

TrafficLightState::TrafficLightState()
{
    startTime = chrono::high_resolution_clock::now();
    duration = rand() % 8 + 3;
}

RedState::RedState() : TrafficLightState() {}
TrafficLightStateType RedState::getStateType() const
{
    return TrafficLightStateType::Red;
}

void RedState::update(TrafficLight *trafficlight_)
{
    if (TimeToTransition(4))
    {
        trafficlight_->setState(new GreenState());
        chrono::high_resolution_clock::now();
        return;
    }
    importImage.drawImage("red.txt", {SHORT(trafficlight_->getPos().X + 2), SHORT(trafficlight_->getPos().Y + 1)});
}

GreenState::GreenState() {}

TrafficLightStateType GreenState::getStateType() const
{
    return TrafficLightStateType::Green;
}

void GreenState::update(TrafficLight *trafficlight_)
{
    if (TimeToTransition(this->duration))
    {
        trafficlight_->setState(new RedState());
        startTime = chrono::high_resolution_clock::now();
        return;
    }
    importImage.drawImage("green.txt", {SHORT(trafficlight_->getPos().X + 2), SHORT(trafficlight_->getPos().Y + 1)});
}

void Hero::resetDynamicEntity()
{
    this->teleport({SHORT((appConsole.getWindowSize().X - this->getHeroWidth()) / 2), SHORT(appConsole.getWindowSize().Y + 10)});
}

Hero::Hero(string entityName_, COORD pos1, COORD size_, int score_)
    : DynamicEntity(entityName_, pos1, size_), score(score_) {

    }

Hero::~Hero()
{

}

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

void Hero:: changeExist(){
	this->exist = ! this->exist;
}

bool Hero:: getExist(){
	return this->exist;
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

bool Hero::AtEdge(SHORT posEdge_Y)
{
    if (this->getEndPos().Y <= posEdge_Y)
        return true;
    return false;
}

bool Hero::getSkin(){
	return checkSkin;
}

void Hero::SetSkin(bool skin){
	checkSkin = skin;
}

void Hero::verify()
{
    COORD sizeScreen = appConsole.getWindowSize();
    sizeScreen.Y--;
    startPos.X = max(startPos.X, SHORT(7));
    startPos.X = min(startPos.X, SHORT(sizeScreen.X - size.X -7));
    startPos.Y = max(startPos.Y, SHORT(0));
    startPos.Y = min(startPos.Y, SHORT(sizeScreen.Y - size.Y));
}








