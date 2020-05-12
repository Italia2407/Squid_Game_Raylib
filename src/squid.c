//
// Created by IGRec on 7 May 2020.
//

#include "squid.h"
#include "raymath.h"

#include <stdio.h>

#define SQUID_WIDTH 64
#define SQUID_HEIGHT 64

#define BASE_DIRECTION (Vector2){0.0f, -1.0f}

static Vector2 GetDirectionByAngle(float angle)
{
	const float angleRadians = DEG2RAD * angle;
	
	Vector2 newDirection;
	newDirection.x = (cosf(angleRadians) * BASE_DIRECTION.x) - (sinf(angleRadians) * BASE_DIRECTION.y);
	newDirection.y = (sinf(angleRadians) * BASE_DIRECTION.x) + (cosf(angleRadians) * BASE_DIRECTION.y);
	
	return newDirection;
}

void InitialiseSquid(GameObject* squidObject, void* startFlags)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	squidData->headColour = ((SquidFlags*)startFlags)->headColour;
	squidData->tentacleColour = ((SquidFlags*)startFlags)->tentacleColour;
	
	squidData->directionAngle = 0.0f;
	squidData->speed = 0.0f;
}

void UpdateSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	// Propulsion
	//------------------------------------------------------------------------------------------------------------------
	const float acceleration = 0.1f;
	const float deceleration = 0.15f;
	const float maxSpeed = 5.0f;
	const float maxBackSpeed = -2.5f;
	if (IsKeyDown(KEY_W) && IsKeyUp(KEY_S))
	{
		if (squidData->speed < 0.0f)
			squidData->speed += (acceleration + deceleration);
		else
			squidData->speed += acceleration;
		
		squidData->speed = Clamp(squidData->speed, maxBackSpeed, maxSpeed);
		
		//squidData->speed = 5.0f;
	} else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_W))
	{
		if (squidData->speed > 0.0f)
			squidData->speed -= (acceleration + deceleration);
		else
			squidData->speed -= acceleration;
		
		squidData->speed = Clamp(squidData->speed, maxBackSpeed, maxSpeed);
		//squidData->speed = -2.0f;
	} else
	{
		if (squidData->speed > 0.0f)
		{
			squidData->speed -= deceleration;
			squidData->speed = Clamp(squidData->speed, 0.0f, maxSpeed);
		} else
		{
			squidData->speed += deceleration;
			squidData->speed = Clamp(squidData->speed, maxBackSpeed, 0.0f);
		}
		//squidData->speed = 0.0f;
	}
	//------------------------------------------------------------------------------------------------------------------
	
	// Steering
	//------------------------------------------------------------------------------------------------------------------
	if (IsKeyDown(KEY_A) && IsKeyUp(KEY_D))
	{
		squidData->directionAngle -= 1.6f;
	} else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_A))
	{
		squidData->directionAngle += 1.6f;
	}
	//------------------------------------------------------------------------------------------------------------------
	
	// Resolve Movement
	//------------------------------------------------------------------------------------------------------------------
	Vector2 velocity = Vector2Scale(GetDirectionByAngle(squidData->directionAngle), squidData->speed);
	squidObject->position = Vector2Add(squidObject->position, velocity);
	//------------------------------------------------------------------------------------------------------------------
}

void RenderSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	// Main Body
	//------------------------------------------------------------------------------------------------------------------
	Texture squidImage = LoadTexture(ASSET_PATH"Inkling_Temp_Sprite.png");
	Rectangle imageSection = (Rectangle){7, 3, 13, 18};
	Rectangle squidRectangle = (Rectangle){squidObject->position.x, squidObject->position.y, 52, 72};
	Vector2 squidCentre = (Vector2){squidRectangle.width / 2, squidRectangle.height / 2};
	
	DrawTexturePro(squidImage, imageSection, squidRectangle, squidCentre, squidData->directionAngle, WHITE);
	/*
	// The dimensions of the squid sprite
	Rectangle squidRectangle = (Rectangle){squidObject->position.x, squidObject->position.y, SQUID_WIDTH, SQUID_HEIGHT};
	// Finds the centre of the squid sprite
	Vector2 squidCentre = (Vector2){squidRectangle.width / 2, squidRectangle.height / 2};
	DrawRectanglePro(squidRectangle, squidCentre, 0.0f, squidData->headColour);
	 */
	
	//------------------------------------------------------------------------------------------------------------------
}