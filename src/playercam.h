//
// Created by IGRec on 13 May 2020.
//

#include "raylib.h"
#include "gameobject.h"

#ifndef RAYLIB_SQUID_GAME_PLAYERCAM_H
#define RAYLIB_SQUID_GAME_PLAYERCAM_H

typedef struct playercamStruct
{
	GameObject* target;
	Camera2D camera;
	
	Vector2 velocity;
} PlayerCam;

typedef struct playercamflagsStruct
{
	GameObject* target;
	
	Vector2 offset;
} PlayerCamFlags;

void InitialisePlayerCam(GameObject* playercamObject, void* startFlags);

void UpdatePlayerCam(GameObject* playercamObject);

#endif //RAYLIB_SQUID_GAME_PLAYERCAM_H
