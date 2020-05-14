//
// Created by IGRec on 13 May 2020.
//

#include "playercam.h"
#include "raymath.h"

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
	
	playerCamData->camera.target = playerCamData->target->position;
}