#include "../../s21_3d_viewer.h"

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
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    } else {
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    }
  }
}

void UpdateTransformPanel(App *app) {
  // handle tab pressed
  handleTransformPanelTabPressed(app);
  // position
  HandleInputText(&app->ui.transform_position_x, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_position_y, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_position_z, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_position_x, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_position_y, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_position_z, app->ui.currentInputText);
  // rotation
  HandleInputText(&app->ui.transform_rotation_x, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_rotation_y, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_rotation_z, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_rotation_x, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_rotation_y, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_rotation_z, app->ui.currentInputText);
  // scale
  HandleInputText(&app->ui.transform_scale_x, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_scale_y, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_scale_z, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_scale_x, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_scale_y, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_scale_z, app->ui.currentInputText);
}

void drawTransformPosition(App *app, int left, int top) {
  DrawText("Position", left + 15, top + 25, 14, Fade(BLACK, 0.5f));
  DrawInputText(&app->ui.transform_position_x, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_position_y, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_position_z, &app->ui.currentInputText);
}

void drawTransformRotation(App *app, int left, int top) {
  DrawText("Rotation", left + 15, top + 25, 14, Fade(BLACK, 0.5f));
  DrawInputText(&app->ui.transform_rotation_x, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_rotation_y, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_rotation_z, &app->ui.currentInputText);
}

void drawTransformScale(App *app, int left, int top) {
  DrawText("Scale", left + 15, top + 25, 14, Fade(BLACK, 0.5f));
  DrawInputText(&app->ui.transform_scale_x, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_scale_y, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_scale_z, &app->ui.currentInputText);
}

void DrawTransformPanel(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int height = TRANSFORM_PANEL_HEIGHT;
  int left = GetScreenWidth() - 20 - width;
  int top = 20;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("TRANSFORM", left + 5, top + 5, 14, BLACK);
  drawTransformPosition(app, left, top);
  drawTransformRotation(app, left, top + 50);
  drawTransformScale(app, left, top + 100);
}

void initTransformPosition(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 65;

  InitInputText(
    &app->ui.transform_position_x,
    TRANSFORM_POSITION_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - TRANSFORM_PANEL_WIDTH + 5, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  InitInputText(
    &app->ui.transform_position_y,
    TRANSFORM_POSITION_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - inputTextWidth) + 30, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  InitInputText(
    &app->ui.transform_position_z,
    TRANSFORM_POSITION_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - (inputTextWidth * 2)) + 55, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void initTransformRotation(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 115;

  InitInputText(
    &app->ui.transform_rotation_x,
    TRANSFORM_ROTATION_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - TRANSFORM_PANEL_WIDTH + 5, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  InitInputText(
    &app->ui.transform_rotation_y,
    TRANSFORM_ROTATION_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - inputTextWidth) + 30, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  InitInputText(
    &app->ui.transform_rotation_z,
    TRANSFORM_ROTATION_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - (inputTextWidth * 2)) + 55, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void initTransformScale(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 165;

  InitInputText(
    &app->ui.transform_scale_x,
    TRANSFORM_SCALE_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - TRANSFORM_PANEL_WIDTH + 5, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  InitInputText(
    &app->ui.transform_scale_y,
    TRANSFORM_SCALE_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - inputTextWidth) + 30, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  InitInputText(
    &app->ui.transform_scale_z,
    TRANSFORM_SCALE_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (TRANSFORM_PANEL_WIDTH - (inputTextWidth * 2)) + 55, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void InitTransformPanel(App *app) {
  initTransformPosition(app);
  initTransformRotation(app);
  initTransformScale(app);
}