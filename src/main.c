#include "raylib.h"
#include "gameobject.h"
#include "player.h"
#include "playercam.h"
#include <stdio.h>

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FPS_CAP (60)

void DrawBackgroundGrid(int horSpace, int verSpace, int horSpan, int verSpan, Color colour);

int main(void)
{
    // Initialization
    //------------------------------------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Squid Game");
	// Set our game to run at desired frame-rate
    SetTargetFPS(FPS_CAP);
    InitObjectSystem();
    
    PlayerFlags playerFlags = {
    		.headColour = BEIGE,
    		.tentacleColour = BROWN
    };
    GameObject* player = CreateObject((Vector2){GetScreenWidth()  / 2, GetScreenHeight() / 2},
									  &InitialisePlayer, &UpdatePlayer, &RenderPlayer, &playerFlags, sizeof(Player));
    
    PlayerCameraFlags playerCamFlags = {
    		.target = player,
    		.offset = (Vector2) {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}
    };
    PlayerCamera* playerCamera = InitialisePlayerCamera(playerCamFlags);
    //------------------------------------------------------------------------------------------------------------------

    // Main game loop
    //------------------------------------------------------------------------------------------------------------------
	// Detects whether the window close button or ESC key have been pressed
    while (!WindowShouldClose())
	{
		// Update
		//--------------------------------------------------------------------------------------------------------------
		UpdateObjects();
		UpdateCameraMovement(playerCamera);
		//--------------------------------------------------------------------------------------------------------------
	
		// Draw
		//--------------------------------------------------------------------------------------------------------------
		BeginDrawing();
		// Set background colour of the game
		ClearBackground(RAYWHITE);
		BeginMode2D(playerCamera->camera);
		
		DrawBackgroundGrid(16, 16, 16, 16, SKYBLUE);
        RenderObjects();

        EndMode2D();
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

void DrawBackgroundGrid(int horSpace, int verSpace, int horSpan, int verSpan, Color colour)
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		DrawLine(i * horSpace, 0, i * horSpace, SCREEN_HEIGHT * horSpan, colour);
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		DrawLine(0, i * verSpace, SCREEN_WIDTH * verSpan, i * verSpace, colour);
	}
}