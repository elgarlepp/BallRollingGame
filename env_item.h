#include "raylib.h"
#include "raymath.h"
#include <math.h>  

namespace BallGame
{
    class EnvItem {
        Rectangle rect;
        float angle;
        Color color;
        Vector2 corners[4];

        void calculateCorners();
    public:
        EnvItem(Rectangle rectangle, float rotation);
        Rectangle GetRectangle();
        Vector2* GetCorners();
        float GetDegreeAngle();
        float GetAngle();
        void Draw();
    };
}