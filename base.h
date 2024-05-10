#include "raylib.h"
#include "raymath.h"

#ifndef BASE_H
#define BASE_H
class Base
{
public:
    Base();
    Vector2 getWorlspos() { return worldPosition;}
    void undomovement();
   
    virtual void tick(float) = 0; 
    virtual Vector2 getScreenPos() = 0;
    Rectangle getCollisionRec();
    bool getAlive()
    {
        return is_alive;
    }
    void setAlive(bool isAlive)
    {
        is_alive = isAlive;
    }
    ~Base(){};
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{}; //centrum okna - tam gdzie tworzymy chatakter
    Vector2 worldPosition{}; // swiat sie przemieszcza = charakter sie przemieszcza
    Vector2  worldPositionLASTTT{}; //za to nie wychodzimy na mapie 
    //animacje
    float rightleftRotation{1.f}; // 1 patrzymy w prawo, -1 patrzymy w lewo
    float runtime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f/12.f}; // 12 razy na sekunde bedzie sie reaktywowac nasza aplikacja
    float speed{4.f}; // skaluje szybkosc ruchu planszy

    //dla konstruktora
    float width{};
    float height{};
    float scale{4.0f};
    
private:
    bool is_alive{true};

};
#endif