#include "../../s21_3d_viewer.h"

void UpdateTransformPanel(App *app) {
  // position
  HandleInputText(&app->ui.position_x.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.position_y.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.position_z.input, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.position_x.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.position_y.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.position_z.input, app->ui.currentInputText);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.position_x.plusBtn, &app->ui.position_x);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.position_x.minusBtn, &app->ui.position_x);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.position_y.plusBtn, &app->ui.position_y);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.position_y.minusBtn, &app->ui.position_y);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.position_z.plusBtn, &app->ui.position_z);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.position_z.minusBtn, &app->ui.position_z);
  // rotation
  HandleInputText(&app->ui.rotation_x.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.rotation_y.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.rotation_z.input, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.rotation_x.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.rotation_y.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.rotation_z.input, app->ui.currentInputText);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.rotation_x.plusBtn, &app->ui.rotation_x);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.rotation_x.minusBtn, &app->ui.rotation_x);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.rotation_y.plusBtn, &app->ui.rotation_y);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.rotation_y.minusBtn, &app->ui.rotation_y);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.rotation_z.plusBtn, &app->ui.rotation_z);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.rotation_z.minusBtn, &app->ui.rotation_z);
  // scale
  HandleInputText(&app->ui.scale_x.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.scale_y.input, &app->ui.currentInputText);
  HandleInputText(&app->ui.scale_z.input, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.scale_x.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.scale_y.input, app->ui.currentInputText);
  HandleKeys(app, &app->ui.scale_z.input, app->ui.currentInputText);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.scale_x.plusBtn, &app->ui.scale_x);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.scale_x.minusBtn, &app->ui.scale_x);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.scale_y.plusBtn, &app->ui.scale_y);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.scale_y.minusBtn, &app->ui.scale_y);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.scale_z.plusBtn, &app->ui.scale_z);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.scale_z.minusBtn, &app->ui.scale_z);
}

void drawTransformPosition(App *app, int left, int top) {
  DrawText("Position", left + TRANSFORM_PANEL_WIDTH - 120, top + 25, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.position_x.minusBtn);
  DrawSubmitButton(&app->ui.position_x.plusBtn);
  DrawSubmitButton(&app->ui.position_y.minusBtn);
  DrawSubmitButton(&app->ui.position_y.plusBtn);
  DrawSubmitButton(&app->ui.position_z.minusBtn);
  DrawSubmitButton(&app->ui.position_z.plusBtn);
  DrawInputText(&app->ui.position_x.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.position_y.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.position_z.input, &app->ui.currentInputText);
}

void drawTransformRotation(App *app, int left, int top) {
  DrawText("Rotation", left + TRANSFORM_PANEL_WIDTH - 120, top + 25, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.rotation_x.minusBtn);
  DrawSubmitButton(&app->ui.rotation_x.plusBtn);
  DrawSubmitButton(&app->ui.rotation_y.minusBtn);
  DrawSubmitButton(&app->ui.rotation_y.plusBtn);
  DrawSubmitButton(&app->ui.rotation_z.minusBtn);
  DrawSubmitButton(&app->ui.rotation_z.plusBtn);
  DrawInputText(&app->ui.rotation_x.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.rotation_y.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.rotation_z.input, &app->ui.currentInputText);
}

void drawTransformScale(App *app, int left, int top) {
  DrawText("Scale", left + TRANSFORM_PANEL_WIDTH - 120, top + 25, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.scale_x.minusBtn);
  DrawSubmitButton(&app->ui.scale_x.plusBtn);
  DrawSubmitButton(&app->ui.scale_y.minusBtn);
  DrawSubmitButton(&app->ui.scale_y.plusBtn);
  DrawSubmitButton(&app->ui.scale_z.minusBtn);
  DrawSubmitButton(&app->ui.scale_z.plusBtn);
  DrawInputText(&app->ui.scale_x.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.scale_y.input, &app->ui.currentInputText);
  DrawInputText(&app->ui.scale_z.input, &app->ui.currentInputText);
}

void DrawTransformPanel(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int height = TRANSFORM_PANEL_HEIGHT;
  int left = GetScreenWidth() - 20 - width;
  int top = 5;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("TRANSFORM", left + 5, top + 5, 14, BLACK);
  drawTransformPosition(app, left, top);
  drawTransformRotation(app, left, top + 110);
  drawTransformScale(app, left, top + 220);
}

void initTransformPosition(App *app) {

  int inputTextWidth = 100;
  int inputTextTop = 50;

  InitSubmitButton(&app->ui.position_x.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.position_x.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.position_x.input,
    TRANSFORM_POSITION_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  inputTextTop += 30;
  InitSubmitButton(&app->ui.position_y.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.position_y.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.position_y.input,
    TRANSFORM_POSITION_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  inputTextTop += 30;
  InitSubmitButton(&app->ui.position_z.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.position_z.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.position_z.input,
    TRANSFORM_POSITION_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void initTransformRotation(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 160;

  InitSubmitButton(&app->ui.rotation_x.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.rotation_x.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.rotation_x.input,
    TRANSFORM_ROTATION_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );

  inputTextTop += 30;
  InitSubmitButton(&app->ui.rotation_y.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.rotation_y.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.rotation_y.input,
    TRANSFORM_ROTATION_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  inputTextTop += 30;
  InitSubmitButton(&app->ui.rotation_z.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.rotation_z.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.rotation_z.input,
    TRANSFORM_ROTATION_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void initTransformScale(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 270;
  
  InitSubmitButton(&app->ui.scale_x.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.scale_x.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);

  InitInputText(
    &app->ui.scale_x.input,
    TRANSFORM_SCALE_X,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "x", "0"
  );
  inputTextTop += 30;
  InitSubmitButton(&app->ui.scale_y.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.scale_y.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.scale_y.input,
    TRANSFORM_SCALE_Y,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "y", "0"
  );

  inputTextTop += 30;
  InitSubmitButton(&app->ui.scale_z.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.scale_z.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.scale_z.input,
    TRANSFORM_SCALE_Z,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    "z", "0"
  ); 
}

void InitTransformPanel(App *app) {
  initTransformPosition(app);
  initTransformRotation(app);
  initTransformScale(app);
}