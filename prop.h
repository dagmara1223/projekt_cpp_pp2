#include "raylib.h"
#include "raymath.h"
class Prop
{
public:
    Prop(Vector2, Texture2D);
    void Rendering(Vector2);
private:
    Texture2D texture{};
    Vector2 worldPositionOfProp{};
    float scale{4.0f};
};