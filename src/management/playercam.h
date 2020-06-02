//
// Created by IGRec on 13 May 2020.
//

#include "../globals.h"
#include "../objects/gameobject.h"

#ifndef RAYLIB_SQUID_GAME_PLAYERCAM_H
#define RAYLIB_SQUID_GAME_PLAYERCAM_H

typedef struct player_camera
{
	GameObject* target;
	Camera2D camera;
} PlayerCamera;

typedef struct player_camera_flags
{
	GameObject* target;
	Vector2 offset;
} PlayerCameraFlags;

PlayerCamera* InitialisePlayerCamera(PlayerCameraFlags startFlags);
void UpdateCameraMovement(PlayerCamera* playerCamera);

#endif //RAYLIB_SQUID_GAME_PLAYERCAM_H
