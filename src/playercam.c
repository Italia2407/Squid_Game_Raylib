//
// Created by IGRec on 13 May 2020.
//

#include "playercam.h"
#include "raymath.h"

#include <stdlib.h>

static const float SMOOTH_SPEED = 0.125f;

PlayerCamera* InitialisePlayerCamera(PlayerCameraFlags startFlags)
{
	PlayerCamera* playerCamera = (PlayerCamera*)malloc(sizeof(PlayerCamera));
	Camera2D camera2D = (Camera2D){0};
	
	playerCamera->target = startFlags.target;
	
	camera2D.target = playerCamera->target->position;
	camera2D.offset = startFlags.offset;
	camera2D.rotation = 0.0f;
	camera2D.zoom = 1.0f;
	playerCamera->camera = camera2D;
	
	return playerCamera;
}

void UpdateCameraMovement(PlayerCamera* playerCamera)
{
	Vector2 currentPosition = playerCamera->camera.target;
	Vector2 desiredPosition = playerCamera->target->position;
	Vector2 smoothedPosition = Vector2Lerp(currentPosition, desiredPosition, SMOOTH_SPEED);
	
	playerCamera->camera.target = smoothedPosition;
}