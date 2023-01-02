/*******************************************************************************************
*
*   raygui - custom file dialog to load obj file
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
**********************************************************************************************/

#include "libs/raylib/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "libs/raygui/raygui.h"

#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again

#define GUI_FILE_DIALOG_IMPLEMENTATION
#include "gui_file_dialog.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
  // Initialization
  //---------------------------------------------------------------------------------------
  int screenWidth = 800;
  int screenHeight = 560;

  InitWindow(screenWidth, screenHeight, "3d viewer by myregree, williamc, darrpama");
  SetExitKey(0);

  // Custom file dialog
  GuiFileDialogState fileDialogState = InitGuiFileDialog(GetWorkingDirectory());

  bool exitWindow = false;

  char fileNameToLoad[512] = { 0 };

  // Define the camera to look into our 3d world
  Camera camera = { 0 };
  camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

  Model model = { 0 };                                // Load model
  BoundingBox bounds = { 0 };                         // Set model bounds
  Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position
  bool selected = false;                              // Selected object flag

  SetCameraMode(camera, CAMERA_FREE);                 // Set a free camera mode

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main loop
  while (!exitWindow) {   // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    exitWindow = WindowShouldClose();
    UpdateCamera(&camera);

    if (fileDialogState.SelectFilePressed) {
      // Load image file (if supported extension)
      if (IsFileExtension(fileDialogState.fileNameText, ".obj")) {
        strcpy(fileNameToLoad, TextFormat("%s/%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
        UnloadModel(model);
        model = LoadModel(fileNameToLoad);
        bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds
      }
      fileDialogState.SelectFilePressed = false;
    }

    // Select model on mouse click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Check collision between ray and box
        if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), bounds).hit) selected = !selected;
        else selected = false;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

      BeginMode3D(camera);

        DrawModelWires(model, position, 1.0f, BLACK);   // Draw 3d model with texture
        DrawGrid(20, 10.0f);                            // Draw a grid
        if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

      EndMode3D();

      DrawText(fileNameToLoad, 208, GetScreenHeight() - 20, 10, GRAY);
      
      DrawFPS(20, 10);

      DrawRectangle(20, 80, 320, 133, Fade(SKYBLUE, 0.5f));
      DrawRectangleLines( 20, 80, 320, 133, BLUE);

      DrawText("Free camera default controls:", 30, 100, 10, BLACK);
      DrawText("- Mouse Wheel to Zoom in-out", 40, 120, 10, DARKGRAY);
      DrawText("- Mouse Wheel Pressed to Pan", 40, 140, 10, DARKGRAY);
      DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 160, 10, DARKGRAY);
      DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 180, 10, DARKGRAY);
      DrawText("- Z to zoom to (0, 0, 0)", 40, 200, 10, DARKGRAY);

      // raygui: controls drawing
      //----------------------------------------------------------------------------------
      if (fileDialogState.windowActive) GuiLock();

      if (GuiButton((Rectangle){ 20, 40, 140, 30 }, GuiIconText(ICON_FILE_OPEN, "Open obj file"))) fileDialogState.windowActive = true;

      if (GuiButton((Rectangle){ 20, 225, 140, 30 }, GuiIconText(ICON_BOX_DOTS_BIG, "Draw dots"))) {
        
      }

      GuiUnlock();

      // GUI: Dialog Window
      //--------------------------------------------------------------------------------
      GuiFileDialog(&fileDialogState);
      //--------------------------------------------------------------------------------

      //----------------------------------------------------------------------------------

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(model);     // Unload texture

  CloseWindow();              // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}