#include "staticVariable.h"

using namespace stValue;

class Entity {
    public:
        Entity(string entityName_, COORD pos1, COORD size_);
        Entity() {};
        void draw();
        COORD getPos();
        COORD getEndPos();
    protected:
        COORD remainStartPos, remainEndPos;
        void removeRemainFrame();
        void verify();
        COORD startPos, size;
        string entityName;
};

class DynamicEntity : public Entity
{
public:
    DynamicEntity(string entityName_, COORD pos1, COORD size_);
    bool isAtEdge(SHORT posEdge_X);
    virtual void resetDynamicEntity();
    void spawnDynamicEntity(double speed = 1);
    void up(int step = 1);
    void down(int step = 1);
    void left(int step = 1);
    void right(int step = 1);
    void teleport(COORD pos);
    int getSpeed();
    void setSpeed(const int& speed);

protected:
    void caculateRemainFrame(COORD oldPos);
    int speed;
};


class Hero : public DynamicEntity
{
public:
    Hero(string entityName_, COORD pos1, COORD size_, long int score_);
    SHORT getHeroWidth();
    SHORT getHeroHeight();
    void setHeroLevel(const int&);
    void setHeroScore(const long int&);
    void updateHeroExp();
    void updateHeroExp(const int&);
    void resetDynamicEntity();
    bool isAtEdge(SHORT posEdge_Y);
    bool isCollision(DynamicEntity* enemy);
    int getHeroLevel();
    long int getHeroScore();
private:
    SHORT heroWidth = 13;
    SHORT heroHeight = 5;
    long int score = 0;
    int level = int(floor(score / 300)) + 1;
};



class TrafficLight : public Entity
{
    public:
        TrafficLight(string entityName_, COORD pos1, COORD size_, bool isRed);
        void updateTrafficLight();
        void setTrafficLight(const bool& trafficlight);
        bool isRedOn();
        int stopRow1,stopRow2;

    private:
        bool isRed;
        chrono::high_resolution_clock::time_point startTime;
};