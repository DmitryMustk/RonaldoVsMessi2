#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include <raymath.h>

typedef struct {
    Vector2 pos;
    Vector2 speed;
    Vector2 acceleration;
    float   radius;
} Player;

void updatePlayer(Player* player, Rectangle field, float dt);
// void jump(Player player);
// void movePlayer(Player player, int keyCode);

#endif //PLAYER_H
