//
// Created by IGRec on 13 May 2020.
//

#include "playercam.h"
#include "raymath.h"

static const float SMOOTH_SPEED = 0.125f;

void InitialisePlayerCam(GameObject* playercamObject, void* startFlags)
{
	PlayerCam* playerCamData = (PlayerCam*)playercamObject->objectData;
	
	playerCamData->target = ((PlayerCamFlags*)startFlags)->target;
	
	playerCamData->camera = (Camera2D){0};
	playerCamData->camera.target = playerCamData->target->position;
	playerCamData->camera.offset = ((PlayerCamFlags*)startFlags)->offset;
	playerCamData->camera.rotation = 0.0f;
	playerCamData->camera.zoom = 1.0f;
}

void UpdatePlayerCam(GameObject* playercamObject)
{
	PlayerCam* playerCamData = (PlayerCam*)playercamObject->objectData;
	
	Vector2 desiredPosition = playerCamData->target->position;
	Vector2 smoothedPosition = Vector2Lerp(playerCamData->camera.target, desiredPosition, SMOOTH_SPEED);
	playerCamData->camera.target = smoothedPosition;
}