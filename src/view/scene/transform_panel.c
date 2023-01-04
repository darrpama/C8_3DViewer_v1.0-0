#include "../../s21_3d_viewer.h"

void handleTransformPanelTabPressed(App *app) {
  if (IsKeyPressed(KEY_TAB) == true) {
    if (app->ui.currentInputText == TRANSFORM_POSITION_X) {
      app->ui.currentInputText = TRANSFORM_POSITION_Y;
    } else if (app->ui.currentInputText == TRANSFORM_POSITION_Y) {
      app->ui.currentInputText = TRANSFORM_POSITION_Z;
    } else if (app->ui.currentInputText == TRANSFORM_POSITION_Z) {
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    } else {
      app->ui.currentInputText = TRANSFORM_POSITION_X;
    }
  }
}

void UpdateTransformPanel(App *app) {
  // handle tab pressed
  handleTransformPanelTabPressed(app);
  // handle select
  HandleInputText(&app->ui.transform_pos_x, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_pos_y, &app->ui.currentInputText);
  HandleInputText(&app->ui.transform_pos_z, &app->ui.currentInputText);
  // handle key pressed
  HandleKeys(app, &app->ui.transform_pos_x, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_pos_y, app->ui.currentInputText);
  HandleKeys(app, &app->ui.transform_pos_z, app->ui.currentInputText);
}

void DrawTransformPanel(App *app) {
  int width = 400;
  int height = 150;
  int left = GetScreenWidth() - 20 - width;
  int top = 20;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("TRANSFORM", left + 5, top + 5, 14, BLACK);
  DrawText("Position", left + 15, top + 25, 14, Fade(BLACK, 0.5f));
  DrawInputText(&app->ui.transform_pos_x, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_pos_y, &app->ui.currentInputText);
  DrawInputText(&app->ui.transform_pos_z, &app->ui.currentInputText);
  (void) app;
}

void InitTransformPanel(App *app) {
  int panelWidth = 400;
  int inputTextWidth = 100;
  int inputTextTop = 65;
  
  // position
  InitInputText(
    &app->ui.transform_pos_x,
    TRANSFORM_POSITION_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - panelWidth + 5, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  InitInputText(
    &app->ui.transform_pos_y,
    TRANSFORM_POSITION_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (panelWidth - inputTextWidth) + 30, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  InitInputText(
    &app->ui.transform_pos_z,
    TRANSFORM_POSITION_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - (panelWidth - (inputTextWidth * 2)) + 55, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}