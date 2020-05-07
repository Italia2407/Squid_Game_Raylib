//
// Created by IGRec on 6 May 2020.
//

#include "gameobject.h"
#include "raymath.h"
#include <stdlib.h>

static GameObject blankObject;
static GameObject objectPool[POOL_SIZE];

void InitObjectSystem()
{
	blankObject.id = -1;
	blankObject.position = Vector2Zero();
	blankObject.updateBehaviour = NULL;
	blankObject.renderBehaviour = NULL;
	blankObject.currentState = GO_DESTROYED;
	
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objectPool[i] = blankObject;
	}
}

GameObject* GetObjectByID(int id)
{
	return &objectPool[id];
}

static int GetNextFreeSlot()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (objectPool[i].currentState == GO_DESTROYED)
			return i;
	}
	
	return -1;
}

GameObject* CreateObject(Vector2 position, void (*startBehaviour)(struct gameObjectStruct*, void*), void (*updateBehaviour)(GameObject*), void (*renderBehaviour)(GameObject*), void* startFlags, int sizeOfData)
{
	int nextID = GetNextFreeSlot();
	if (nextID == -1)
		return NULL;
	
	GameObject newObject = blankObject;
	newObject.position = position;
	newObject.startBehaviour = startBehaviour;
	newObject.updateBehaviour = updateBehaviour;
	newObject.renderBehaviour = renderBehaviour;
	newObject.currentState = GO_ACTIVE;
	
	if (sizeOfData > 0)
		newObject.objectData = malloc(sizeOfData);
	else
		newObject.objectData = NULL;
	
	objectPool[nextID] = newObject;
	
	if (startBehaviour != NULL)
	{
		objectPool[nextID].startBehaviour(&objectPool[nextID], startFlags);
	}
	
	return &objectPool[nextID];
}

void UpdateObjects()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		GameObject* object = GetObjectByID(i);
		if (object->updateBehaviour != NULL && object->currentState == GO_ACTIVE)
		{
			object->updateBehaviour(object);
		}
	}
}

void RenderObjects()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		GameObject* object = GetObjectByID(i);
		if (object->renderBehaviour != NULL && object->currentState == GO_ACTIVE)
		{
			object->renderBehaviour(object);
		}
	}
}