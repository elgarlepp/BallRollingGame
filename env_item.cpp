#include "env_item.h"

using namespace BallGame;

EnvItem::EnvItem(Rectangle rectangle, float rotation)
{
    rect = rectangle;
    color = GRAY;
    angle = rotation;

    calculateCorners();
}

Rectangle EnvItem::GetRectangle()
{
    return rect;
}

Vector2* EnvItem::GetCorners()
{
    return corners;
}

float EnvItem::GetDegreeAngle()
{
    return angle;
}

float EnvItem::GetAngle()
{
    return angle * DEG2RAD;
}

void EnvItem::Draw()
{
    DrawRectanglePro(rect, {0, 0}, angle, GRAY);
}

/**
 * c1           c2
 * ---------------
 * |             |
 * |             |
 * ---------------
 * c4           c3
 * 
 */
void EnvItem::calculateCorners()
{
    float rectWidth = rect.width;
    float rectHeight = rect.height;
    float angleRad = angle * DEG2RAD;
    float oppositeAngleRad = (180 - angle) * DEG2RAD;

    float angleX = rectWidth * cos(angleRad);
    float angleY = rectWidth * sin(angleRad);
    float oppositeAngleX = rectHeight * cos(oppositeAngleRad);
    float oppositeAngleY = rectHeight * sin(oppositeAngleRad);

    float c1x = rect.x;
    float c1y = rect.y;
    corners[0] = {c1x, c1y};

    float c2x = c1x + angleX;
    float c2y = c1y + angleY;
    corners[1] = {c2x, c2y};

    float c3x = c1x + angleX - oppositeAngleX;
    float c3y = c1y + angleY + oppositeAngleY;
    corners[2] = {c3x, c3y};

    float c4x = c1x - oppositeAngleX;
    float c4y = c1y + oppositeAngleY;
    corners[3] = {c4x, c4y};
}