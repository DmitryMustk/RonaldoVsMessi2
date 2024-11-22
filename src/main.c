#include "../raylib/include/raylib.h"
#include "../raylib/include/raymath.h"

bool isOnGround(Vector2 entity, float entityRad, Rectangle ground) {
	return CheckCollisionCircleRec(entity, entityRad, ground);
}

// TODO: decompose by entities
// TODO: add ball
// TODO: add ball & player collision
// TODO: add enemy with ai
// TODO: add player & enemy collision
// TODO: add goals
// TODO: (the most hard thing) add foot on players and kick
// TODO: add music and sounds
// TODO: add score and time
// TODO: add menu
// TODO: add gamemodes (and maybe levels)
// TODO: add pause
// TODO: add textures

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;
	
	const char* windowTitle = "RonaldoVsMessi 2";
	InitWindow(screenWidth, screenHeight, windowTitle);

	SetTargetFPS(60);

	
	const int fieldHeight = 150;
	Rectangle field = {0, screenHeight - fieldHeight, screenWidth, fieldHeight};

	Vector2 player = {200, 0}; 
	Vector2 playerSpeed = {0, 0};
	Vector2 playerAcc = {0, 0};

	float playerRad = 30;

	const float GRAVITY      = 10;
	const float JUMP_SPEED   = -400;
	const float PLAYER_SPEED = 400;
	const float RESISTANCE   = 0.8;

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		
		// Update Acceleration
		if (isOnGround(player, playerRad, field)) {
			playerAcc.y = 0;
			playerSpeed.y = 0;
			player.y = field.y - playerRad;
			
			// Jump
			if (IsKeyDown(KEY_SPACE)) {
				playerAcc.y = JUMP_SPEED;
			}
		} else {
			playerAcc.y += GRAVITY;
		}
			// Movement
		if (IsKeyDown(KEY_A)) {
			playerAcc.x = -PLAYER_SPEED;
		}
		if (IsKeyDown(KEY_D)) {
			playerAcc.x = PLAYER_SPEED;
		}

		playerAcc.x *= RESISTANCE;

		// Colission with walls
		//Left Wall
		Vector2 lwp1 = {0, 0};
		Vector2 lwp2 = {0, screenHeight};
		//Right Wall
		Vector2 rwp1 = {screenWidth, 0};
		Vector2 rwp2 = {screenWidth, screenHeight};

		if (CheckCollisionCircleLine(player, playerRad, lwp1, lwp2)) {
			player.x = playerRad;
			playerSpeed.x = -playerSpeed.x;
		}
		if (CheckCollisionCircleLine(player, playerRad, rwp1, rwp2)) {
			player.x = screenWidth - playerRad;
			playerSpeed.x = -playerSpeed.x;
		}

		// Update Speed
		playerSpeed = Vector2Add(playerSpeed, playerAcc);
		playerSpeed = Vector2Scale(playerSpeed, dt);

		
		// Update Player
		player = Vector2Add(player, playerSpeed);

		BeginDrawing();
			ClearBackground(WHITE);

			// Draw field
			DrawRectangle(field.x, field.y, field.width, field.height, DARKGREEN);

			// Draw Player
			DrawCircle(player.x, player.y, playerRad, BLACK);
		EndDrawing();
	}

}
