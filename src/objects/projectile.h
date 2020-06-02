//
// Created by IGRec on 21 May 2020.
//

#include "../globals.h"
#include "gameobject.h"
#include "../management/spritemanager.h"

#ifndef RAYLIB_SQUID_GAME_PROJECTILE_H
#define RAYLIB_SQUID_GAME_PROJECTILE_H

typedef struct projectile
{
	Vector2 velocity;
	Rectangle boundingBox;
	
	Sprite sprite;
} Projectile;

typedef struct projectile_flags
{
	Vector2 initialVelocity;
} ProjectileFlags;

void InitialiseProjectile(GameObject* projectileObject, void* startFlags);
void UpdateProjectile(GameObject* projectileObject);
void RenderProjectile(GameObject* projectileObject);

#endif //RAYLIB_SQUID_GAME_PROJECTILE_H
