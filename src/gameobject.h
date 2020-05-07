//
// Created by IGRec on 6 May 2020.
//

#include "raylib.h"

#ifndef RAYLIB_TEMPLATE_GAMEOBJECT_H
#define RAYLIB_TEMPLATE_GAMEOBJECT_H

#define POOL_SIZE 2048

typedef enum gameObjectStateEnum
{
	GO_DESTROYED = -1,
	GO_INACTIVE,
	GO_ACTIVE
} GameObjectState;

typedef struct gameObjectStruct
{
	int id;
	Vector2 position;
	GameObjectState currentState;
	
	void (*startBehaviour)(struct gameObjectStruct*, void* flags);
	void (*updateBehaviour)(struct gameObjectStruct*);
	void (*renderBehaviour)(struct gameObjectStruct*);
	
	void* objectData;
} GameObject;

void InitObjectSystem();

GameObject* GetObjectByID(int id);
GameObject* CreateObject(Vector2 position, void (*startBehaviour)(struct gameObjectStruct*, void*), void (*updateBehaviour)(GameObject*), void (*renderBehaviour)(GameObject*), void* startFlags, int sizeOfData);

void UpdateObjects();
void RenderObjects();

#endif //RAYLIB_TEMPLATE_GAMEOBJECT_H
