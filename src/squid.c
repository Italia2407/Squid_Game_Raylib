//
// Created by IGRec on 7 May 2020.
//

#include "squid.h"

void InitialiseSquid(GameObject* squidObject, SquidFlags* startFlags)
{
	Squid* squidData = (Squid*)squidObject->objectData;
	
	squidData->headColour = startFlags->headColour;
	squidData->tentacleColour = startFlags->tentacleColour;
}

void UpdateSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
}

void RenderSquid(GameObject* squidObject)
{
	Squid* squidData = (Squid*)squidObject->objectData;
}