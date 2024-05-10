#include "enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldPosition = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 2.5f;
}
void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    // vel = Vector2Subtract(target->getScreenPos(), getScreenPos());
    // if(Vector2Length(vel)< radiustostop) vel = {};

    // bierzemy toTargetfromEnemy wektor
    Vector2 toTargetfromEnemy = Vector2Subtract(target->getScreenPos(), screenPosition) ; //character screen pozycja - enemy screen pozycja wedle mapy
    // normalizujemy wektor do 1 bo przemieszczajac sie charakterem enemy podaza za nami, wektor ma notorycznie
    //rozna wartos dlatego do 1
    toTargetfromEnemy = Vector2Normalize(toTargetfromEnemy);
    //mnozymy nasz wektor przez speed charakteru
    toTargetfromEnemy = Vector2Scale(toTargetfromEnemy, speed);
    //ruszamy enemy do charakteru
    worldPosition = Vector2Add(worldPosition , toTargetfromEnemy);
    screenPosition = Vector2Subtract(worldPosition, target->getWorlspos());

    screenPosition = Vector2Subtract(worldPosition, target->getWorlspos()); 
    // odejmujemy pozycje od naszego character tak, zeby enemy pozostal w lewym gornym i nie szedl z nami
    Base::tick(deltaTime);

    if(CheckCollisionRecs(target->getCollisionRec(),getCollisionRec())) //jezeli dojdzie do zderzenia
    {
        target->takedamge(damage_per_second*deltaTime);
    }
}
