//
// Created by IGRec on 6 May 2020.
//

#include "raylib.h"
#include "gameobject.h"

#ifndef RAYLIB_TEMPLATE_SQUID_H
#define RAYLIB_TEMPLATE_SQUID_H

typedef struct squidStruct
{
	Vector2 direction;
	float velocity;
	
	Color headColour;
	Color tentacleColour;
} Squid;

typedef struct squidFlagsStruct
{
	Color headColour;
	Color tentacleColour;
} SquidFlags;

void InitialiseSquid(GameObject* squidObject, SquidFlags* startFlags);
void UpdateSquid(GameObject* squidObject);
void RenderSquid(GameObject* squidObject);

#endif //RAYLIB_TEMPLATE_SQUID_H
