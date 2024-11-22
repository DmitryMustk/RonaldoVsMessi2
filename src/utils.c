#include <raylib.h>
#include <raymath.h>

#include "utils.h"

bool isOnGround(Vector2 entity, float entityRad, Rectangle ground) {
	return CheckCollisionCircleRec(entity, entityRad, ground);
}
