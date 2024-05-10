#include "character.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;
    screenPosition = {static_cast<float>(winWidth)/2.0f - scale*(0.5f*width),
    static_cast<float>(winHeight)/2.0f - scale*(0.5f*height)
    };

}


void Character::tick(float deltaTime)
{
    if(!getAlive()) return;
    Base::tick(deltaTime);
    Vector2 direction{};
        if(IsKeyDown(KEY_A))
        {
            direction.x -= 1.0; // w lewo;
        }
        if(IsKeyDown(KEY_D))
        { 
            direction.x +=1.0;
        }
        if(IsKeyDown(KEY_W))
        {
            direction.y -= 1.0;
        }
        if(IsKeyDown(KEY_S))
        {
            direction.y += 1.0;
        }
        if(Vector2Length(direction) != 0.0) //normalizujemy do 1, uaktualniamy animacje
        { 
            texture = run;  
            worldPosition = Vector2Add(worldPosition,Vector2Scale(Vector2Normalize(direction), speed) );
            if(direction.x < 0.f)
            {
                rightleftRotation = -1.f;
            }
            else
            {
                rightleftRotation = 1.f;
            }

        }     
        else texture = idle; 
        Vector2 origin{}; 
        Vector2 offset{};
        float rotation{}; //rotacja kwadratu miecz
        if(rightleftRotation > 0.f) // jezeli patrzymy w prawo
        {
            origin = {0.f, weapon.height*scale};
            offset = {35.f, 55.f};
            weaponCollisionRectangle = {
                getScreenPos().x + offset.x, getScreenPos().y  + offset.y - weapon.height*scale,
                weapon.width*scale, weapon.height*scale};
            //rotation = 35.f;
            if(IsKeyDown(KEY_M)) rotation = 35.f; //uginanie sie miecza
            else rotation = 0.f;
        } 
        else
        {
            origin = { weapon.width*scale, weapon.height*scale};
            offset = {25.f, 55.f};
            weaponCollisionRectangle = {
                getScreenPos().x + offset.x - weapon.width*scale, getScreenPos().y  + offset.y - weapon.height*scale,
                weapon.width*scale, weapon.height*scale};
            if(IsKeyDown(KEY_M)) rotation = -35.f;
            else rotation = 0.f;
        }
       Rectangle source{0.f, 0.f, static_cast<float>(weapon.width)*rightleftRotation, static_cast<float>(weapon.height)}; 
       //teraz flipujemy noz dookola
       Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width*scale, weapon.height*scale}; // lewy dolny
       DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
       //narysujmy kwadracik naszego character
       //DrawRectangleLines(weaponCollisionRectangle.x, weaponCollisionRectangle.y, weaponCollisionRectangle.width,
       //weaponCollisionRectangle.height, RED);
}
Rectangle Character::getCollision()
{
    return Rectangle
    {
        screenPosition.x,
        screenPosition.y,
        width*scale,
        height*scale
    };
}

void Character::takedamge(float damage)
{
    health-=damage;
    if(health<=0.f)
    {
        setAlive(false);
    }
}
// Character::~Character()
// {}