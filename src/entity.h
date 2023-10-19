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
    public: 
        void up(int step);
        void down(int step);
};

class Hero : public Entity {
    public:
    
};

class Rocket : public Entity {
    public:
        Rocket(COORD pos1, COORD size, int ascii1Pixel = 1);
        void draw();
};