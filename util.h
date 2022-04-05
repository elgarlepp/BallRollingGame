#include "raylib.h"
#include <cmath>

//https://ericleong.me/research/circle-line/

namespace BallGame
{
    bool CircleLineCollision(Vector2 circlePos, float radius, Vector2 line0, Vector2 line1);
    Vector2 ClosestPointToLine(Vector2 circlePos, float radius, Vector2 line0, Vector2 line1);
    float DistanceBetween(Vector2 point0, Vector2 point1);
    Vector2 PointAfterDistance(Vector2 start, float angle, float length);
    Vector2 RotateVector(Vector2 endPoint, float angle);
    Vector2 ChangeLineLength(Vector2 start, Vector2 end, float length);
}