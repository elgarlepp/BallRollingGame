#include "util.h"

bool BallGame::CircleLineCollision(Vector2 circlePos, float radius, Vector2 line0, Vector2 line1)
{
    Vector2 closest = ClosestPointToLine(circlePos, radius, line0, line1);
    float distance = DistanceBetween(circlePos, closest);
    return distance <= radius;
}

Vector2 BallGame::ClosestPointToLine(Vector2 circlePos, float radius, Vector2 line0, Vector2 line1)
{
    float A1 = line0.y - line1.y; 
    float B1 = line1.x - line0.x; 
    double C1 = (line0.y - line1.y)*line1.x + (line1.x - line0.x)*line1.y; 
    double C2 = -B1*circlePos.x + A1*circlePos.y; 
    double det = A1*A1 - -B1*B1; 
    double cx = 0; 
    double cy = 0; 
    if (det != 0){ 
        cx = (double)((A1*C1 - B1*C2)/det); 
        cy = (double)((A1*C2 - -B1*C1)/det); 
    } else { 
        cx = circlePos.x; 
        cy = circlePos.y; 
    }

    Vector2 closest = {cx, cy};
    Vector2* low;
    Vector2* high;


    if(line0.x != line1.x)
    {
        if (line0.x < line1.x)
        {
            low = &line0;
            high = &line1;
        }
        else
        {
            low = &line1;
            high = &line0;
        }

        if (low->x > cx) 
        {
            closest = *low;
        }
        else if(high->x < cx)
        {
            closest = *high;
        }
    }
    else
    {
        if(line0.y < line1.y)
        {
            low = &line0;
            high = &line1;
        }
        else
        {
            low = &line1;
            high = &line0;
        }

        if (low->y > cy) 
        {
            closest = *low;
        }
        else if(high->y < cy)
        {
            closest = *high;
        }
    }

    return closest;
}

float BallGame::DistanceBetween(Vector2 point0, Vector2 point1)
{
    return sqrt(pow(point1.x - point0.x, 2) + pow(point1.y - point0.y, 2));
}

//NB! NOT WORKING
Vector2 BallGame::PointAfterDistance(Vector2 start, float angle, float length)
{
    float xLength = sin(angle) * length;
    float yLength = cos(angle) * length;
    return { start.x + xLength, start.y + yLength };
}

Vector2 BallGame::RotateVector(Vector2 endPoint, float angle)
{
    Vector2 newEndPoint;
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    newEndPoint.x = (cosAngle * endPoint.x) - (sinAngle * endPoint.y);
    newEndPoint.y = (sinAngle * endPoint.x) + (cosAngle * endPoint.y);
    return newEndPoint;
}

/**
 * @brief Change given line length by shortening/stretching end point
 * 
 * @param start 
 * @param end 
 * @param length 
 * @return Vector2 Returns new end point
 */
Vector2 BallGame::ChangeLineLength(Vector2 start, Vector2 end, float length)
{
    float c = DistanceBetween(start, end);
    //float a = end.x - start.x;
    float b = end.y - start.y;
    float angle = asin(b / c);

    float newA = length * cos(angle);
    float newB = length * sin(angle);

    return {start.x + newA, start.y + newB};
}