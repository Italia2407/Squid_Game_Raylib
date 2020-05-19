//
// Created by IGRec on 7 May 2020.
//

#include "player.h"
#include "raymath.h"

#include <stdio.h>

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

#define BASE_DIRECTION (Vector2){0.0f, -1.0f}

static Vector2 GetDirectionByAngle(float angle)
{
	const float angleRadians = DEG2RAD * angle;
	
	Vector2 newDirection;
	newDirection.x = (cosf(angleRadians) * BASE_DIRECTION.x) - (sinf(angleRadians) * BASE_DIRECTION.y);
	newDirection.y = (sinf(angleRadians) * BASE_DIRECTION.x) + (cosf(angleRadians) * BASE_DIRECTION.y);
	
	return newDirection;
}

void InitialisePlayer(GameObject* playerObject, void* startFlags)
{
	Player* playerData = (Player*)playerObject->objectData;
	
	playerData->headColour = ((PlayerFlags*)startFlags)->headColour;
	playerData->tentacleColour = ((PlayerFlags*)startFlags)->tentacleColour;
	
	playerData->directionAngle = 0.0f;
	playerData->speed = 0.0f;
}

void UpdatePlayer(GameObject* playerObject)
{
	Player* playerData = (Player*)playerObject->objectData;
	
	// Propulsion
	//------------------------------------------------------------------------------------------------------------------
	const float acceleration = 0.2f;
	const float deceleration = 0.3f;
	const float maxSpeed = 10.0f;
	const float maxBackSpeed = -4.5f;
	if (IsKeyDown(KEY_W) && IsKeyUp(KEY_S))
	{
		if (playerData->speed < 0.0f)
			playerData->speed += (acceleration + deceleration);
		else
			playerData->speed += acceleration;
		
		playerData->speed = Clamp(playerData->speed, maxBackSpeed, maxSpeed);
	} else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_W))
	{
		if (playerData->speed > 0.0f)
			playerData->speed -= (acceleration + deceleration);
		else
			playerData->speed -= acceleration;
		
		playerData->speed = Clamp(playerData->speed, maxBackSpeed, maxSpeed);
	} else
	{
		if (playerData->speed > 0.0f)
		{
			playerData->speed -= deceleration;
			playerData->speed = Clamp(playerData->speed, 0.0f, maxSpeed);
		} else
		{
			playerData->speed += deceleration;
			playerData->speed = Clamp(playerData->speed, maxBackSpeed, 0.0f);
		}
	}
	//------------------------------------------------------------------------------------------------------------------
	
	// Steering
	//------------------------------------------------------------------------------------------------------------------
	if (IsKeyDown(KEY_A) && IsKeyUp(KEY_D))
	{
		playerData->directionAngle -= 1.6f;
	} else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_A))
	{
		playerData->directionAngle += 1.6f;
	}
	//------------------------------------------------------------------------------------------------------------------
	
	// Resolve Movement
	//------------------------------------------------------------------------------------------------------------------
	Vector2 velocity = Vector2Scale(GetDirectionByAngle(playerData->directionAngle), playerData->speed);
	playerObject->position = Vector2Add(playerObject->position, velocity);
	//------------------------------------------------------------------------------------------------------------------
}

void RenderPlayer(GameObject* playerObject)
{
	Player* squidData = (Player*)playerObject->objectData;
	
	// Main Body
	//------------------------------------------------------------------------------------------------------------------
	Texture squidImage = LoadTexture(ASSET_PATH"Inkling_Temp_Sprite.png");
	Rectangle imageSection = (Rectangle){7, 3, 13, 18};
	Rectangle squidRectangle = (Rectangle){playerObject->position.x, playerObject->position.y, 52, 72};
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