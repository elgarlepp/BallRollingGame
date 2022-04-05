#include "cmath"
#include "raylib.h"
#include "raymath.h"
#include "env_item.h"
#include "util.h"


namespace BallGame
{
    #define G 400
    #define COR 0.3f
    #define PLAYER_JUMP_SPD 350.0f
    //#define PLAYER_HOR_SPD 200.0f
    #define PLAYER_ROLL_ANGLE_SPD 120.0f

    class Player
    {
        Vector2 position;
        float radius;
        Vector2 moveVector[2];
        float ySpeed;
        float xSpeed;
        float rollingAngle;
        bool canJump;
    public:
        Player();
        Vector2 GetPosition();
        void Update(BallGame::EnvItem *envItems, int envItemsLength, float delta);
        int HitsObstacle(EnvItem *envItems, int envItemsLength, Vector2 playerPos, EnvItem **hitEnvItem);
        void PositionToBarelyTouch(EnvItem *hitEnvItem);
        void Draw();
    };
}