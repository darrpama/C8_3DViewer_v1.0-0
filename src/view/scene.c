#include "../s21_3d_viewer.h"

void handleTransformPanelTabPressed(App *app) {
  if (IsKeyPressed(KEY_TAB) == true) {
    if (app->ui.currentInputText == TRANSFORM_POSITION_X) {
      app->ui.currentInputText = TRANSFORM_POSITION_Y;
    } else if (app->ui.currentInputText == TRANSFORM_POSITION_Y) {
      app->ui.currentInputText = TRANSFORM_POSITION_Z;
    } else if (app->ui.currentInputText == TRANSFORM_POSITION_Z) {
      app->ui.currentInputText = TRANSFORM_ROTATION_X;
    } else if (app->ui.currentInputText == TRANSFORM_ROTATION_X) {
      app->ui.currentInputText = TRANSFORM_ROTATION_Y;
    } else if (app->ui.currentInputText == TRANSFORM_ROTATION_Y) {
      app->ui.currentInputText = TRANSFORM_ROTATION_Z;
    } else if (app->ui.currentInputText == TRANSFORM_ROTATION_Z) {
      app->ui.currentInputText = TRANSFORM_SCALE_X;
    } else if (app->ui.currentInputText == TRANSFORM_SCALE_X) {
      app->ui.currentInputText = TRANSFORM_SCALE_Y;
    } else if (app->ui.currentInputText == TRANSFORM_SCALE_Y) {
      app->ui.currentInputText = TRANSFORM_SCALE_Z;
    } else if (app->ui.currentInputText == TRANSFORM_SCALE_Z) {
      app->ui.currentInputText = POINT_SIZE;
    } else if (app->ui.currentInputText == POINT_SIZE) {
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    } else {
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    }
  }
}

void DrawScene(App *app) {
  ClearBackground(app->settings.bgColor);

  BeginMode3D(app->scene.camera);
  DrawGrid(20, 10.0f);
  DrawModelOnScene(app);
  EndMode3D();

  DrawUploadFile(app);
  DrawInfo(app);
  DrawTransformPanel(app);
  DrawCameraSettingsButtons(app);
  DrawVerticesUI(app);
  DrawWiresUI(app);
  DrawBgColor(app);
  DrawSaveSettings(app);
  DrawSavePicButton(app);  // gif button
}

void UpdateScene(App *app) {
  // handle tab pressed
  handleTransformPanelTabPressed(app);

  UpdateModel(app);
  UpdateTransformPanel(app);
  UpdateUploadFile(app);
  UpdateCameraSettingsButtons(app);
  UpdateVerticesUI(app);
  UpdateWiresUI(app);
  UpdateBgColor(app);
  UpdateSaveSettings(app);
  UpdateSavePicButton(app);  // gif button
}

void InitScene(App *app) {
  InitBgColor(app);
  InitModel(app);
  InitCamera(app);
  InitUploadFile(app);
  InitTransformPanel(app);
  InitVerticesUI(app);
  InitWiresUI(app);
  InitSaveSettings(app);
  LoadSettings(app);
  InitSavePicButton(app);  // gif button
}
