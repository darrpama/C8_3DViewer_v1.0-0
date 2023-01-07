#include "../../s21_3d_viewer.h"

void saveGifHandler(App *app) {
  if (app->ui.uploadBtn.fileDialogState.SelectFilePressed) {
    if (IsFileExtension(app->ui.uploadBtn.fileDialogState.fileNameText, ".obj")) {
      strcpy(app->ui.uploadBtn.fileNameToLoad, TextFormat("%s/%s", app->ui.uploadBtn.fileDialogState.dirPathText, app->ui.uploadBtn.fileDialogState.fileNameText));
      // UnloadObj(&app->scene.model.obj);
      UnloadModel(app->scene.model.rModel);
      app->scene.model.rModel = LoadModel(app->ui.uploadBtn.fileNameToLoad);
      app->scene.model.edgeCount = GetEdgesCount(app->ui.uploadBtn.fileNameToLoad);
      // app->scene.model.bounds = GetMeshBoundingBox(app->scene.model.rModel.meshes[0]);   // Set model bounds
    }
    app->ui.uploadBtn.fileDialogState.SelectFilePressed = false;
  }
}

void saveGifButtonHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.saveGifBtn.area))
    app->ui.saveGifBtn.mouseOn = true;
  else
    app->ui.saveGifBtn.mouseOn = false;
  if (app->ui.saveGifBtn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Image image = LoadImageFromScreen();
    ExportImage(image, "aboba.png");
    UnloadImage(image);
  }
}

void DrawSaveGifButton(App *app) {
  DrawIconButton(&app->ui.saveGifBtn);
}

void UpdateSaveGifButton(App *app) {
  saveGifHandler(app);
  saveGifButtonHandler(app);
}

void InitSaveGifButton(App *app) {
  Texture2D icon = LoadTexture("./assets/icons/upload.png");
  InitIconButton(
    icon,
    &app->ui.saveGifBtn,
    (Rectangle){20, APP_SCREEN_HEIGHT - 84 - 84, 64, 64},
    ColorBrightness(SKYBLUE, -0.1)
  );
}