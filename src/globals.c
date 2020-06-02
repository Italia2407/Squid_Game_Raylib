//
// Created by IGRec on 2 Jun 2020.
//

#include "globals.h"

Vector2 GetDirectionByAngle(float angle)
{
	const float angleRadians = DEG2RAD * angle;
	
	Vector2 newDirection;
	newDirection.x = (cosf(angleRadians) * BASE_DIRECTION.x) - (sinf(angleRadians) * BASE_DIRECTION.y);
	newDirection.y = (sinf(angleRadians) * BASE_DIRECTION.x) + (cosf(angleRadians) * BASE_DIRECTION.y);
	
	return newDirection;
}