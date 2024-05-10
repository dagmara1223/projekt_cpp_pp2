#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "raymath.h"
#include "base.h"

class Character : public Base
{
    
public:
    Character(int , int );
    virtual void tick(float) override;
    virtual Vector2 getScreenPos() override {return screenPosition;}
    Rectangle getweaponcollision()
    {
      return weaponCollisionRectangle;
    }
    Rectangle getCollision();
    float getHealth() const
    { 
        return health;
    }
    void takedamge(float);
  //  ~Character();
private:
    int windowWidth{};
    int windowHeigth{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRectangle{};
    float health{100.f};

};
#endif