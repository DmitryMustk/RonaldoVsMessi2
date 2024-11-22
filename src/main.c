#include <raylib.h>
#include <raymath.h>

#include "player.h"

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
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 450;
	
	const char* windowTitle = "RonaldoVsMessi 2";
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle);

	SetTargetFPS(60);
	
	const int fieldHeight = 150;
	Rectangle field = {0, SCREEN_HEIGHT - fieldHeight, SCREEN_WIDTH, fieldHeight};
	Player player = {{50, 50}, {0, 0}, {0, 0}, 30};

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
	
		updatePlayer(&player, field, dt);

		BeginDrawing();
			ClearBackground(WHITE);

			// Draw field
			DrawRectangle(field.x, field.y, field.width, field.height, DARKGREEN);

			// Draw Player
			DrawCircle(player.pos.x, player.pos.y, player.radius, BLACK);
		EndDrawing();
	}

}
