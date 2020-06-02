//
// Created by IGRec on 2 Jun 2020.
//

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef RAYLIB_SQUID_GAME_GLOBALS_H
#define RAYLIB_SQUID_GAME_GLOBALS_H

#define ASSET_PATH "../assets/"

#define BASE_DIRECTION (Vector2){0.0f, -1.0f}
Vector2 GetDirectionByAngle(float angle);

#endif //RAYLIB_SQUID_GAME_GLOBALS_H
