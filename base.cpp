#include "base.h"
#include "raymath.h"
Base::Base(){};
void Base::undomovement()
{
    worldPosition = worldPositionLASTTT;
}
Rectangle Base::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}


void Base::tick(float deltaTime)
{
    worldPositionLASTTT = worldPosition;
    runtime += deltaTime;
    if(runtime >= updateTime)
    {
       frame++;
       runtime = 0.f;
       if(frame > maxFrame) frame = 0;
    }
        //charakter a na gorze mapa, rysowanie charakteru
    Rectangle source{frame * rightleftRotation*width, 0.f, rightleftRotation*width, height};
    Rectangle dest{screenPosition.x, screenPosition.y, scale*width, scale*height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

