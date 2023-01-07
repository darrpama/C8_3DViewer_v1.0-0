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
    SaveGif(app, 4);
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

void SaveGif(App *app, int frames) {
  /* Need to add function to hide ui here */
  for (int i = 0; i < frames; i++) {
    Image image = LoadImageFromScreen();
    char filename[20];
    sprintf(filename, "%d", i);
    strncat(filename, ".png", 5);
    ExportImage(image, filename);
    UnloadImage(image);
    /* Need to add move camera or rotate model here */
    app->scene.camera.fovy += 5.0f;
    UpdateCamera(&app->scene.camera);
  }

  /* Here we collect our .png's to .gif file */
}