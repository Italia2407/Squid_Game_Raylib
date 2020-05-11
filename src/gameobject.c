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
	// Blanking Object-Pool
	//------------------------------------------------------------------------------------------------------------------
	// Sets attributes of the default blank object
	blankObject.id = -1;
	blankObject.position = Vector2Zero();
	blankObject.startBehaviour = NULL;
	blankObject.updateBehaviour = NULL;
	blankObject.renderBehaviour = NULL;
	blankObject.currentState = GO_DESTROYED;
	
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objectPool[i] = blankObject;
	}
	//------------------------------------------------------------------------------------------------------------------
}

GameObject* GetObjectByID(int id)
{
	return &objectPool[id];
}

static int GetNextFreeSlot()
{
	// Checks for the first free slot with state GO_DESTROYED
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (objectPool[i].currentState == GO_DESTROYED)
			return i;
	}
	
	return -1;
}

GameObject* CreateObject(Vector2 position, void (*startBehaviour)(struct gameObjectStruct*, void*), void (*updateBehaviour)(GameObject*), void (*renderBehaviour)(GameObject*), void* startFlags, int sizeOfData)
{
	// Checks if there is a free slot available within the object pool, and gets the ID of the first one found
	int nextID = GetNextFreeSlot();
	if (nextID == -1)
		return NULL;
	
	// Game-Object creation
	//------------------------------------------------------------------------------------------------------------------
	GameObject newObject = blankObject;
	newObject.position = position;
	newObject.startBehaviour = startBehaviour;
	newObject.updateBehaviour = updateBehaviour;
	newObject.renderBehaviour = renderBehaviour;
	newObject.currentState = GO_ACTIVE;
	
	// If the object needs to contain data, space is reserved for it
	if (sizeOfData > 0)
		newObject.objectData = malloc(sizeOfData);
	else
		newObject.objectData = NULL;
	
	// New object is added to the pool, and start behaviour is called if present
	objectPool[nextID] = newObject;
	if (startBehaviour != NULL)
	{
		objectPool[nextID].startBehaviour(&objectPool[nextID], startFlags);
	}
	//------------------------------------------------------------------------------------------------------------------
	
	return &objectPool[nextID];
}

void UpdateObjects()
{
	// Loops through all objects in the Pool
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
	// Loops through all objects in the Pool
	for (int i = 0; i < POOL_SIZE; i++)
	{
		GameObject* object = GetObjectByID(i);
		if (object->renderBehaviour != NULL && object->currentState == GO_ACTIVE)
		{
			object->renderBehaviour(object);
		}
	}
}