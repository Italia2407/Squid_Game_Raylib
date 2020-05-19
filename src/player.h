//
// Created by IGRec on 6 May 2020.
//

#include "raylib.h"
#include "gameobject.h"

#ifndef RAYLIB_TEMPLATE_PLAYER_H
#define RAYLIB_TEMPLATE_PLAYER_H

typedef struct player
{
	float directionAngle;
	float speed;
	
	Color headColour;
	Color tentacleColour;
} Player;

typedef struct player_flags
{
	Color headColour;
	Color tentacleColour;
} PlayerFlags;

void InitialisePlayer(GameObject* playerObject, void* startFlags);
void UpdatePlayer(GameObject* playerObject);
void RenderPlayer(GameObject* playerObject);

#endif //RAYLIB_TEMPLATE_PLAYER_H
