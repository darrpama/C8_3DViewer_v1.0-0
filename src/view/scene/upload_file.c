#include "../../s21_3d_viewer.h"

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

void DrawUploadFile(App *app) {
    DrawText(app->ui.uploadBtn.fileNameToLoad, 208, GetScreenHeight() - 20, 10, GRAY);
    if (app->ui.uploadBtn.fileDialogState.windowActive) GuiLock();
    DrawIconButton(&app->ui.uploadBtn.button);
    GuiUnlock();
    GuiFileDialog(&app->ui.uploadBtn.fileDialogState);
}

void UpdateUploadFile(App *app) {
  uploadFileHandler(app);
  uploadButtonHandler(app);
}

void InitUploadFile(App *app) {
  app->ui.uploadBtn.fileDialogState = InitGuiFileDialog(GetWorkingDirectory());
  app->ui.uploadBtn.fileNameToLoad[0] = '\0';
  Texture2D icon = LoadTexture("./assets/icons/upload.png");
  InitIconButton(icon, &app->ui.uploadBtn.button, (Rectangle){30,30,64,64}, ColorAlpha(GRAY, 0.2));
  app->ui.uploadBtn.fileDialogState = InitGuiFileDialog(GetWorkingDirectory());
}