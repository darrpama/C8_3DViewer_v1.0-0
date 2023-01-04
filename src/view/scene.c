#include "../s21_3d_viewer.h"

void DrawScene(App *app) {
  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

  BeginMode3D(app->scene.camera);
    DrawGrid(20, 10.0f);
    DrawModelOnScene(app);
  EndMode3D();
  
  DrawUploadFile(app);
  DrawInfo(app);
  DrawTransformPanel(app);
}

void UpdateScene(App *app) {
  UpdateModel(app);
  UpdateTransformPanel(app);
  UpdateUploadFile(app);
}

void InitScene(App *app) {
  InitModel(app);
  InitCamera(app);
  InitUploadFile(app);
  InitTransformPanel(app);
}
