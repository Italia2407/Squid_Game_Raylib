//
// Created by IGRec on 21 May 2020.
//

#include "raylib.h"
#include "gameobject.h"

#ifndef RAYLIB_SQUID_GAME_PROJECTILE_H
#define RAYLIB_SQUID_GAME_PROJECTILE_H

typedef struct projectile
{
	Rectangle boundingBox;
} Projectile;

void InitialiseProjectile(GameObject* projectileObject, void* startFlags);
void UpdateProjectile(GameObject* projectileObject);
void RenderProjectile(GameObject* projectileObject);

#endif //RAYLIB_SQUID_GAME_PROJECTILE_H
