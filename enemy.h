#include "raylib.h"
#include "base.h"
#include "character.h"
class Enemy : public Base
{

public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);

    virtual void tick(float) override;
    virtual Vector2 getScreenPos() override { return screenPosition;};
    void setTarget(Character* character )
    {
        target = character;
    }
 
   // ~Enemy(){};

private:
    Character* target{nullptr};
    float damage_per_second{10.f};
    float radiustostop{25.f};
    //Vector2 vel{};
   
};