//
// Created by IGRec on 7 May 2020.
//

#include "squid.h"
#include "raymath.h"

#define SQUID_WIDTH 64
#define SQUID_HEIGHT 64

static void ResolveMovement(GameObject* squidObject, Squid* squidData);

void InitialiseSquid(GameObject* squidObject, void* startFlags)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	squidData->headColour = ((SquidFlags*)startFlags)->headColour;
	squidData->tentacleColour = ((SquidFlags*)startFlags)->tentacleColour;
	
	squidData->direction = (Vector2){0.0f, 1.0f};
	squidData->speed = 0.0f;
}

void UpdateSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	if (IsKeyDown(KEY_W))
	{
		squidData->speed = -5.0f;
	} else if (IsKeyDown(KEY_S))
	{
		squidData->speed = 5.0f;
	} else
	{
		squidData->speed = 0.0f;
	}
	
	ResolveMovement(squidObject, squidData);
}

void RenderSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	Rectangle squidRectangle = (Rectangle){squidObject->position.x, squidObject->position.y, SQUID_WIDTH, SQUID_HEIGHT};
	Vector2 squidCentre = (Vector2){squidRectangle.width / 2, squidRectangle.height / 2};
	DrawRectanglePro(squidRectangle, squidCentre, 0.0f, squidData->headColour);
}

void ResolveMovement(GameObject* squidObject, Squid* squidData)
{
	Vector2 velocity = Vector2Scale(squidData->direction, squidData->speed);
	squidObject->position = Vector2Add(squidObject->position, velocity);
}