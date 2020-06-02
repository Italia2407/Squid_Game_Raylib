//
// Created by IGRec on 6 May 2020.
//

#include "../globals.h"

#ifndef RAYLIB_TEMPLATE_GAMEOBJECT_H
#define RAYLIB_TEMPLATE_GAMEOBJECT_H

#define POOL_SIZE 2048

typedef enum gameobject_states
{
	GO_DESTROYED = -1,
	GO_INACTIVE = 0,
	GO_ACTIVE = 1
} GameObjectStates;

typedef struct gameobject
{
	int id;
	Vector2 position;
	GameObjectStates currentState;
	
	void (*startBehaviour)(struct gameobject*, void* flags);
	void (*updateBehaviour)(struct gameobject*);
	void (*renderBehaviour)(struct gameobject*);
	
	void* objectData;
} GameObject;

void InitObjectSystem();

GameObject* GetObjectByID(int id);
GameObject* CreateObject(Vector2 position, void (*startBehaviour)(struct gameobject*, void*), void (*updateBehaviour)(GameObject*), void (*renderBehaviour)(GameObject*), void* startFlags, int sizeOfData);

void UpdateObjects();
void RenderObjects();

#endif //RAYLIB_TEMPLATE_GAMEOBJECT_H
