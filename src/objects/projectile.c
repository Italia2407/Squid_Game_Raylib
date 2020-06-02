//
// Created by IGRec on 21 May 2020.
//

#include "projectile.h"

void InitialiseProjectile(GameObject* projectileObject, void* startFlags)
{
	Projectile* projectileData = (Projectile*)projectileObject->objectData;
	
	projectileData->velocity = ((ProjectileFlags*)startFlags)->initialVelocity;
}

void UpdateProjectile(GameObject* projectileObject)
{
	Projectile* projectileData = (Projectile*)projectileObject->objectData;
	
	// Movement
	//------------------------------------------------------------------------------------------------------------------
	projectileObject->position = Vector2Add(projectileObject->position, projectileData->velocity);
	//------------------------------------------------------------------------------------------------------------------
}

void RenderProjectile(GameObject* projectileObject)
{
	Projectile* projectileData = (Projectile*)projectileObject->objectData;
}