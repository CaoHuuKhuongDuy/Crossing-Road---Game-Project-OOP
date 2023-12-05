#include "staticVariable.h"
#include "pixels.h"

using namespace stValue;


class Enemy;
class EnemyState;
class Entity;
class DynamicEntity;
class TrafficLight;
class TrafficLightState;
class Hero;
class GreenState;
class RedState;
class NormalState;
class StoppedState;
enum class TrafficLightStateType;

class Entity {
    public:
        Entity(){};
        Entity(string entityName_, COORD pos1, COORD size_);
        void draw();
        COORD getPos();
        COORD getEndPos();
        COORD getSize();
        void setEntityname(string );
    protected:
        void loadEntity();
        COORD remainStartPos, remainEndPos;
        void removeRemainFrame();
        virtual void verify();
        COORD startPos, size;
        string entityName;
        vector <Pixel> pixels;
};

class DynamicEntity : public Entity
{
public:
    DynamicEntity() {};
    DynamicEntity(string entityName_, COORD pos1, COORD size_);
    virtual void resetDynamicEntity();
    void up(int step = 1);
    void down(int step = 1);
    void left(int step = 1);
    void right(int step = 1);
    void slip(int step = 1);
    void teleport(COORD pos);
    int getSpeed();
    void setSpeed(const int& speed);

protected:
    void caculateRemainFrame(COORD oldPos);
    int speed;
};

class Enemy : public DynamicEntity
{
public:
    Enemy();
    Enemy(string entityName_, COORD pos1, COORD size_);
    ~Enemy();

    bool AtRightEdge(SHORT );
    bool AtLeftEdge(SHORT );

    void spawm();

    EnemyState* getState();
    void setState(EnemyState* newState);
    void updateState(TrafficLight*);

    void update(TrafficLight*&);

private:
    EnemyState* currentState;
};

enum class EnemyStateType
{
    MovingRight,
    MovingLeft,
    Stop,
};

class EnemyState
{
public:
    EnemyState();
    virtual EnemyStateType getStateType() const = 0;
    virtual void update(Enemy*) = 0;
protected:
};

class NormalState : public EnemyState
{
public:
    NormalState();
    virtual EnemyStateType getStateType() const = 0;
    virtual void update(Enemy*) = 0;
};

class MovingState : public NormalState
{
public:
    MovingState();
    virtual EnemyStateType getStateType() const = 0;
    virtual void update(Enemy* ) = 0;
};

class MovingRight : public MovingState
{
    public:
    MovingRight();
    EnemyStateType getStateType() const override;
    void update(Enemy* ) override;
};

class MovingLeft : public MovingState
{
    public:
    MovingLeft();
    EnemyStateType getStateType() const override;
    void update(Enemy* ) override;

};


class StoppedState: public EnemyState 
{
public:
    StoppedState();
    EnemyStateType getStateType() const override;
    void update(Enemy*) override;
};

class TrafficLight : public Entity
{
    public:
        TrafficLight();
        TrafficLight(string entityName_, COORD pos1, COORD size_, TrafficLightState* currentState_);
        ~TrafficLight();
        TrafficLightState* getState() const;
        void setState(TrafficLightState* newState);
        void update();
    protected:
        TrafficLightState* currentState;
};

class TrafficLightState
{
    public:
        TrafficLightState();
        virtual TrafficLightStateType getStateType() const = 0;
        bool TimeToTransition(int duration);
        virtual void update(TrafficLight* ) = 0;
    protected:
        int duration;
        chrono::high_resolution_clock::time_point startTime;

};

enum class TrafficLightStateType
{
    Red, 
    Green,
};

class RedState : public TrafficLightState
{
    public:
        RedState();
        TrafficLightStateType getStateType() const override;
        void update(TrafficLight*) override;
};

class GreenState : public TrafficLightState
{
    public:
        GreenState();
        TrafficLightStateType getStateType() const override;
        void update(TrafficLight*) override;
};


class Hero : public DynamicEntity
{
public:
    Hero(string entityName_, COORD pos1, COORD size_, int score_);
    ~Hero();
    void verify() override;

    SHORT getHeroWidth();
    SHORT getHeroHeight();
    void setHeroLevel(const int&);
    void setHeroScore(const int&);
    void updateHeroExp();
    void updateHeroExp(const int&);
    void resetDynamicEntity();
    bool AtEdge(SHORT posEdge_Y);
    bool isCollision(DynamicEntity* enemy);
    int getHeroLevel();
    int getHeroScore();
    void changeExist();
    bool getExist();
    bool getSkin();
    void SetSkin(bool skin);

private:    
    SHORT heroWidth = 13;
    SHORT heroHeight = 5;
    int score = 0;
    int level = int(floor(score / 300)) + 1;
    bool exist = true;
    bool checkSkin = 0;
};
