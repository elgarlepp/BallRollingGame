#include "player.h"
#include <stdio.h>

using namespace BallGame;

Player::Player()
{
    position = (Vector2){ 400, 280 };
    radius = 50;
    ySpeed = 0;
    xSpeed = (2 * M_PI * radius) * (PLAYER_ROLL_ANGLE_SPD / 360.0);
    rollingAngle = 0;
    canJump = false;
    moveVector[0] = position;
    moveVector[1] = position;
}

Vector2 Player::GetPosition()
{
    return position;
}

void Player::Update(EnvItem *envItems, int envItemsLength, float delta)
{
    //Vector2 inputXPos = {position.x, position.y};
    Vector2 inputXPos = {0, 0};
    int moved = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT);

    if (IsKeyDown(KEY_LEFT)) {
        inputXPos = {0 - (xSpeed * delta), 0};
        //position.x -= xSpeed * delta;
        //rollingAngle += PLAYER_ROLL_ANGLE_SPD * delta;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        inputXPos = {0 + (xSpeed * delta), 0};
        //position.x += xSpeed * delta;
        //rollingAngle -= PLAYER_ROLL_ANGLE_SPD * delta;
    }

    if (IsKeyDown(KEY_SPACE) && canJump)
    {
        ySpeed = -PLAYER_JUMP_SPD;
        canJump = false;
    }

    //Vector2 hitLineClosestPoint;
    EnvItem *hitEnvItem;
    int hitObstacle = HitsObstacle(envItems, envItemsLength, position, &hitEnvItem);

    if (hitObstacle)
    {
        PositionToBarelyTouch(hitEnvItem);
    }

    int wouldHitObstacle = 0;
    EnvItem *wouldHitEnvItem;
    if(moved)
    {
        Vector2 wantedPosition = {position.x + inputXPos.x, position.y + inputXPos.y};
        wouldHitObstacle = HitsObstacle(envItems, envItemsLength, wantedPosition, &wouldHitEnvItem);
    }

    if (hitObstacle && wouldHitObstacle)
    {
        inputXPos = RotateVector(inputXPos, hitEnvItem->GetAngle());
    }

    if (hitObstacle) // Bounce
    {
        // char buffer [80];
        // sprintf (buffer, "%f %f", inputXPos.x, inputXPos.y);
        // DrawText((const char*) buffer, 20, 20, 40, RED);
        ySpeed = ySpeed > 1 ? -COR * ySpeed : 0;
    }
    else // Move by Y and fall
    {
        ySpeed += G*delta;
    }

    //position = inputXPos;
    position.x += inputXPos.x;
    position.y += ySpeed*delta + inputXPos.y;
    canJump = hitObstacle == 1;
}

int Player::HitsObstacle(EnvItem *envItems, int envItemsLength, Vector2 playerPos, EnvItem **hitEnvItem)
{
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2* corners = ei->GetCorners();

        for(int j = 1; j <= 4; j++)
        {
            int prevIdx = j - 1;
            int idx = j % 4; // Make a looparound to close obstacle

            if(CircleLineCollision(position, radius, corners[prevIdx], corners[idx]))
            {
                *hitEnvItem = ei;
                return 1;
            }
        }
    }

    return 0;
}

void Player::Draw()
{
    //Vector2 playerPos = {position.x, position.y};// - radius};
    DrawCircle(position.x, position.y, radius, RED);
    // DrawCircleSector(playerPos, radius, 0+rollingAngle, 90+rollingAngle, 0, RED);
    // DrawCircleSector(playerPos, radius, 90+rollingAngle, 180+rollingAngle, 0, BLUE);
    // DrawCircleSector(playerPos, radius, 180+rollingAngle, 270+rollingAngle, 0, RED);
    // DrawCircleSector(playerPos, radius, 270+rollingAngle, 360+rollingAngle, 0, BLUE);
}

void Player::PositionToBarelyTouch(EnvItem *hitEnvItem)
{
    Vector2* corners = hitEnvItem->GetCorners();
    Vector2 line0;
    Vector2 line1;

    for(int j = 1; j <= 4; j++)
    {
        int prevIdx = j - 1;
        int idx = j % 4; // Make a looparound to close obstacle

        if(CircleLineCollision(position, radius, corners[prevIdx], corners[idx]))
        {
            line0 = corners[prevIdx];
            line1 = corners[idx];
            break;
        }
    }

    Vector2 collisionPoint = ClosestPointToLine(position, radius, line0, line1);
    position = ChangeLineLength(collisionPoint, position, radius);
}