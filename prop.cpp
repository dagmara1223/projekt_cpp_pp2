#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 posit, Texture2D tex)
    :worldPositionOfProp{posit}, texture{tex}
{

}
void Prop::Rendering(Vector2 knpos)
{
    Vector2 screenPos{Vector2Subtract(worldPositionOfProp, knpos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}