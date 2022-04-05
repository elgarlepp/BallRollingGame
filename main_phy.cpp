#include <stdio.h>
#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "extras/physac.h"

#define VELOCITY    0.5f
//#define RAD2DEG  (180.0f/PHYSAC_PI)

typedef struct Player {
    PhysicsBody body;
    float radius;
} Player;

void DrawPlayer(Player* player);
void DrawRegularPhysicsBody(PhysicsBody body, int vertexCount);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Ball rolling game");

    // Initialize physics and default physics bodies
    InitPhysics();

    // Create floor and walls rectangle physics body
    PhysicsBody floor = CreatePhysicsBodyRectangle((Vector2){ screenWidth/2.0f, (float)screenHeight }, (float)screenWidth, 100, 10);
    PhysicsBody platformLeft = CreatePhysicsBodyRectangle((Vector2){ screenWidth*0.25f, screenHeight*0.8f }, screenWidth*0.25f, 10, 10);
    PhysicsBody platformRight = CreatePhysicsBodyRectangle((Vector2){ screenWidth*0.75f, screenHeight*0.8f }, screenWidth*0.25f, 10, 10);
    //PhysicsBody wallLeft = CreatePhysicsBodyRectangle((Vector2){ -5, screenHeight/2.0f }, 10, (float)screenHeight, 10);
    //PhysicsBody wallRight = CreatePhysicsBodyRectangle((Vector2){ (float)screenWidth + 5, screenHeight/2.0f }, 10, (float)screenHeight, 10);

    // Disable dynamics to floor and walls physics bodies
    floor->enabled = false;
    platformLeft->enabled = false;
    platformRight->enabled = false;
    //wallLeft->enabled = false;
    //wallRight->enabled = false;

    float playerRadius = 50;
    PhysicsBody playerBody = CreatePhysicsBodyCircle((Vector2){ screenWidth/2.0f, screenHeight/2.0f }, playerRadius, 1);
    Player player;
    player.body = playerBody;
    player.radius = playerRadius;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdatePhysics();              // Update physics system

        if (IsKeyPressed(KEY_R))      // Reset physics input
        {
            // Reset movement physics body position, velocity and rotation
            playerBody->position = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            playerBody->velocity = (Vector2){ 0, 0 };
            SetPhysicsBodyRotation(playerBody, 0);
        }

        // Horizontal movement input
        if (IsKeyDown(KEY_RIGHT))
        {
            playerBody->velocity.x = VELOCITY;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            playerBody->velocity.x = -VELOCITY;
        }

        // Vertical movement input checking if player physics body is grounded
        if (IsKeyDown(KEY_UP) && playerBody->isGrounded) playerBody->velocity.y = -VELOCITY*4;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            DrawFPS(screenWidth - 90, screenHeight - 30);

            // Draw created physics bodies
            int bodiesCount = GetPhysicsBodiesCount();
            for (int i = 0; i < bodiesCount; i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if(body->id == playerBody->id)
                {
                    DrawPlayer(&player);
                }
                else
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    DrawRegularPhysicsBody(body, vertexCount);
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    ClosePhysics();       // Unitialize physics

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void DrawPlayer(Player* player)
{
    PhysicsBody body = player->body;
    float angleOffset = -(body->orient * RAD2DEG);
    Vector2 playerPos = body->position;
    float radius = player->radius;

    DrawCircleSector(playerPos, radius, 0+angleOffset, 90+angleOffset, 0, RED);
    DrawCircleSector(playerPos, radius, 90+angleOffset, 180+angleOffset, 0, BLUE);
    DrawCircleSector(playerPos, radius, 180+angleOffset, 270+angleOffset, 0, RED);
    DrawCircleSector(playerPos, radius, 270+angleOffset, 360+angleOffset, 0, BLUE);
}

void DrawRegularPhysicsBody(PhysicsBody body, int vertexCount)
{
    for (int j = 0; j < vertexCount; j++)
    {
        // Get physics bodies shape vertices to draw lines
        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

        DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
    }
}