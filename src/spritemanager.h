//
// Created by IGRec on 24 May 2020.
//

#include "raylib.h"

#ifndef RAYLIB_SQUID_GAME_SPRITEMANAGER_H
#define RAYLIB_SQUID_GAME_SPRITEMANAGER_H

typedef struct sprite
{
	Image original;
	Texture image;
	
	int palette_size;
	Color* palette;
} Sprite;

Sprite LoadSprite(const char* asset_file, int palette_size);
Sprite LoadSpriteWithPalette(const char* asset_file, int palette_size, Color* new_palette);

void SetColourPalette(Sprite* sprite, Color* new_palette);
void ResetColourPalette(Sprite* sprite);
Color* GetOriginalPalette(Sprite sprite);

#endif //RAYLIB_SQUID_GAME_SPRITEMANAGER_H
