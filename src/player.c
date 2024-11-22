#include "player.h"
#include "game_consts.h"
#include "utils.h"

const float JUMP_SPEED   = -400;
const float PLAYER_SPEED = 400;

void applyGravity(Player* player) {
    player->acceleration.y += GRAVITY;
}

void processFieldCollision(Player* player, Rectangle field) {
    player->acceleration.y = 0;
	player->speed.y = 0;
	player->pos.y = field.y - player->radius;
}

void jump(Player* player) {
    if (IsKeyDown(KEY_SPACE)) {
        player->acceleration.y = JUMP_SPEED;
    }
}

void processMovement(Player* player) {
    if (IsKeyDown(KEY_A)) {
		player->acceleration.x = -PLAYER_SPEED;
	}
	if (IsKeyDown(KEY_D)) {
		player->acceleration.x = PLAYER_SPEED;
	}
    if (IsKeyDown(KEY_S)) {
        player->acceleration.y = PLAYER_SPEED;
    }
}

void applyResistance(Player* player) {
    player->acceleration.x *= RESISTANCE;
}

void processWallCollision(Player* player) {
	//Left Wall
	Vector2 lwp1 = {0, 0};
	Vector2 lwp2 = {0, SCREEN_HEIGHT};
	//Right Wall
	Vector2 rwp1 = {SCREEN_WIDTH, 0};
	Vector2 rwp2 = {SCREEN_WIDTH, SCREEN_HEIGHT};

	if (CheckCollisionCircleLine(player->pos, player->radius, lwp1, lwp2)) {
		player->pos.x = player->radius;
		player->speed.x = -player->speed.x;
	}
	if (CheckCollisionCircleLine(player->pos, player->radius, rwp1, rwp2)) {
		player->pos.x = SCREEN_WIDTH - player->radius;
		player->speed.x = -player->speed.x;
	}
}

void updatePlayer(Player* player, Rectangle field, float dt) {
    if (isOnGround(player->pos, player->radius, field)) {
		processFieldCollision(player, field);
        jump(player);
	} else {
		applyGravity(player);
	}

    processMovement(player);
    applyResistance(player);
    processWallCollision(player);

    player->speed = Vector2Add(player->speed, player->acceleration);
	player->speed = Vector2Scale(player->speed, dt);

	player->pos = Vector2Add(player->pos, player->speed);
}
