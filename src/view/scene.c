#include "../s21_3d_viewer.h"

void InitScene(App *app) {
  Camera camera = { 0 };
  camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
  BoundingBox bounds = { 0 };
  Model model = { 0 };
  Vector3 position = { 0.0f, 0.0f, 0.0f };  
  app->scene.camera = camera;
  app->scene.bounds = bounds;
  app->scene.model = model;
  app->scene.position = position;

  SetCameraMode(app->scene.camera, CAMERA_FREE); 
}

void drawHelpInfo() {
  DrawRectangle(20, 80, 320, 133, Fade(SKYBLUE, 0.3f));
  DrawRectangleLines( 20, 80, 320, 133, BLUE);
  DrawText("Free camera default controls:", 30, 100, 10, BLACK);
  DrawText("- Mouse Wheel to Zoom in-out", 40, 120, 10, DARKGRAY);
  DrawText("- Mouse Wheel Pressed to Pan", 40, 140, 10, DARKGRAY);
  DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 160, 10, DARKGRAY);
  DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 180, 10, DARKGRAY);
  DrawText("- Z to zoom to (0, 0, 0)", 40, 200, 10, DARKGRAY);
}

void DrawScene(App *app) {
  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

  BeginMode3D(app->scene.camera);
    DrawModel(app->scene.model, app->scene.position, 1.0f, BLACK);   // Draw 3d model with texture
    DrawGrid(20, 10.0f);                            // Draw a grid
    if (app->scene.selected) {
      DrawBoundingBox(app->scene.bounds, GREEN);
    }
  EndMode3D();
  
  DrawText(app->ui.uploadBtn.fileNameToLoad, 208, GetScreenHeight() - 20, 10, GRAY);
  DrawFPS(20, 10);
  drawHelpInfo();

  if (app->ui.uploadBtn.fileDialogState.windowActive) GuiLock();

  DrawIconButton(&app->ui.uploadBtn.button);
  
  GuiUnlock();
  GuiFileDialog(&app->ui.uploadBtn.fileDialogState);

}

void uploadFileHandler(App *app) {
  if (app->ui.uploadBtn.fileDialogState.SelectFilePressed) {
    if (IsFileExtension(app->ui.uploadBtn.fileDialogState.fileNameText, ".obj")) {
      strcpy(app->ui.uploadBtn.fileNameToLoad, TextFormat("%s/%s", app->ui.uploadBtn.fileDialogState.dirPathText, app->ui.uploadBtn.fileDialogState.fileNameText));
      UnloadModel(app->scene.model);
      app->scene.model = LoadModel(app->ui.uploadBtn.fileNameToLoad);
      app->scene.bounds = GetMeshBoundingBox(app->scene.model.meshes[0]);   // Set model bounds
    }
    app->ui.uploadBtn.fileDialogState.SelectFilePressed = false;
  }
}

void uploadButtonHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.uploadBtn.button.area))
    app->ui.uploadBtn.button.mouseOn = true;
  else
    app->ui.uploadBtn.button.mouseOn = false;
  if (app->ui.uploadBtn.button.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->ui.uploadBtn.fileDialogState.windowActive = true;
  }
}

void selectModelHandler(App *app) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), app->scene.camera), app->scene.bounds).hit) {
      app->scene.selected = !app->scene.selected;
    } else {
      app->scene.selected = false;
    }
  }
}

void HandleScene(App *app) {
  uploadButtonHandler(app);
  uploadFileHandler(app);
  selectModelHandler(app);
}