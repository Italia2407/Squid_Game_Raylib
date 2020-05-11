#include "raylib.h"
#include "gameobject.h"
#include "squid.h"
#include <stdio.h>

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FPS_CAP (60)

int main(void)
{
    // Initialization
    //------------------------------------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Squid Game");
	// Set our game to run at desired frame-rate
    SetTargetFPS(FPS_CAP);
    InitObjectSystem();
    
    SquidFlags squidFlags = (SquidFlags){BEIGE, BROWN};
    CreateObject((Vector2){GetScreenWidth()  / 2, GetScreenHeight() / 2},
    				&InitialiseSquid, &UpdateSquid, &RenderSquid, &squidFlags, sizeof(Squid));
    //------------------------------------------------------------------------------------------------------------------

    // Main game loop
    //------------------------------------------------------------------------------------------------------------------
	// Detects whether the window close button or ESC key have been pressed
    while (!WindowShouldClose())
    {
        // Update
        //--------------------------------------------------------------------------------------------------------------
        UpdateObjects();
        //--------------------------------------------------------------------------------------------------------------
        
        // Draw
        //--------------------------------------------------------------------------------------------------------------
        BeginDrawing();
		// Set background colour of the game
        ClearBackground(SKYBLUE);
        
        RenderObjects();

        EndDrawing();
        //--------------------------------------------------------------------------------------------------------------
    }
    //------------------------------------------------------------------------------------------------------------------

    // De-Initialization
    //------------------------------------------------------------------------------------------------------------------
    CloseWindow();		// Close window and OpenGL context
	//------------------------------------------------------------------------------------------------------------------
    
    return 0;
}