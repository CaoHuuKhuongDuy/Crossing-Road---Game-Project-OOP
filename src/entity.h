#include "staticVariable.h"

using namespace stValue;
// enum class EntityType { Hero, Boss, TreeBoss, BusBoss, CarBoss, Rocket };

class Entity {
    public:
        Entity(COORD pos1, COORD size, int ascii1Pixel = 1);
        virtual void draw() = 0;
    protected:
        // EntityType type;
        COORD startPos, endPos;
};

class DynamicEntity : public Entity {
    protected: 
        DynamicEntity(COORD pos1, COORD size, int ascii1Pixel = 1);
        void up(int step);
        void down(int step);
        void left(int step);
        void right(int step);
        COORD remainStartPos, remainEndPos;
};

class Hero : public DynamicEntity {
    public:
    
};

class Rocket : public DynamicEntity {
    public:
        Rocket(COORD pos1, COORD size, int ascii1Pixel = 1);
        void draw();
};