//
// Created by IGRec on 7 May 2020.
//

#include "player.h"
#include "raymath.h"

#include <stdio.h>

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

#define BASE_DIRECTION (Vector2){0.0f, -1.0f}

static Color new_palette[6] = {
		(Color){147, 255, 5, 255},
		(Color){208, 255, 120, 255},
		(Color){2, 232, 14, 255},
		(Color){68, 65, 64, 255},
		(Color){255, 255, 255, 255},
		(Color){0, 217, 105, 255},
};

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
	
	playerData->directionAngle = 0.0f;
	playerData->speed = 0.0f;
	
	playerData->sprite = LoadSprite(ASSET_PATH"Inkling_Temp_Sprite.png", 18);
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
	
	// Colour Change
	//------------------------------------------------------------------------------------------------------------------
	if (IsKeyPressed(KEY_C))
	{
		SetColourPalette(&playerData->sprite, new_palette);
	} else if (IsKeyReleased(KEY_C))
	{
		ResetColourPalette(&playerData->sprite);
	}
	//------------------------------------------------------------------------------------------------------------------
}

void RenderPlayer(GameObject* playerObject)
{
	Player* playerData = (Player*)playerObject->objectData;
	
	// Main Body
	//------------------------------------------------------------------------------------------------------------------
	Rectangle imageSection = (Rectangle){7, 3, 13, 18};
	Rectangle playerRectangle = (Rectangle){playerObject->position.x, playerObject->position.y, 52, 72};
	Vector2 playerCentre = (Vector2){playerRectangle.width / 2, playerRectangle.height / 2};
	
	DrawTexturePro(playerData->sprite.image, imageSection, playerRectangle, playerCentre, playerData->directionAngle, WHITE);
	//------------------------------------------------------------------------------------------------------------------
	
	for (int i = 0; i < playerData->sprite.palette_size; i++)
	{
		DrawRectangle(i * 16, GetScreenHeight() - 16, 16, 16, GetOriginalPalette(playerData->sprite)[i]);
	}
}