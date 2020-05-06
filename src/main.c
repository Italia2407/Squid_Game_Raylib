#include "raylib.h"

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FPS_CAP (60)

// The default path to all of our assets
#define ASSET_PATH "../assets/"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Squid Game");
    SetTargetFPS(FPS_CAP);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(SKYBLUE);	// Set background colour to
        
        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context

    return 0;
}