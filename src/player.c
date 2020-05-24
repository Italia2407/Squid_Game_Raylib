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
	
	// TODO
	// Set properties to be set only once and updated regularly
	Image playerImage = LoadImage(ASSET_PATH"Inkling_Temp_Sprite.png");
	ImageFormat(&playerImage, UNCOMPRESSED_R8G8B8A8);
	Color* pixels = playerImage.data;
	int pixel_count = playerImage.width * playerImage.height;
	
	int palette_size;
	Color* palette = ImageExtractPalette(playerImage, 16, &palette_size);
	Color new_palette[16] = {
			(Color){147, 255, 5, 255},
			(Color){208, 255, 120, 255},
			(Color){2, 232, 14, 255},
			(Color){68, 65, 64, 255},
			(Color){255, 255, 255, 255},
			(Color){0, 217, 105, 255},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
			(Color){0, 0, 0, 0},
	};
	
	for (int y = 0; y < playerImage.height; y++)
	{
		for (int x = 0; x < playerImage.width; x++)
		{
			Color* pixel = &pixels[y * playerImage.width + x];
			for (int i = 0; i < palette_size; i++)
			{
				if (ColorToInt(palette[i]) == ColorToInt(*pixel))
				{
					*pixel = new_palette[i];
					break;
				}
			}
		}
	}
	
	Texture playerTexture = LoadTextureFromImage(playerImage);
	Rectangle imageSection = (Rectangle){7, 3, 13, 18};
	Rectangle playerRectangle = (Rectangle){playerObject->position.x, playerObject->position.y, 52, 72};
	Vector2 playerCentre = (Vector2){playerRectangle.width / 2, playerRectangle.height / 2};
	
	DrawTexturePro(playerTexture, imageSection, playerRectangle, playerCentre, squidData->directionAngle, WHITE);
	/*
	// The dimensions of the squid sprite
	Rectangle squidRectangle = (Rectangle){squidObject->position.x, squidObject->position.y, SQUID_WIDTH, SQUID_HEIGHT};
	// Finds the centre of the squid sprite
	Vector2 squidCentre = (Vector2){squidRectangle.width / 2, squidRectangle.height / 2};
	DrawRectanglePro(squidRectangle, squidCentre, 0.0f, squidData->headColour);
	 */
	//------------------------------------------------------------------------------------------------------------------
}