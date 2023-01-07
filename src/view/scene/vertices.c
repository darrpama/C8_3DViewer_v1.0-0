#include "../../s21_3d_viewer.h"

void drawVerticePanel(App *app) {
  (void)app;
  int width = TRANSFORM_PANEL_WIDTH;
  int height = 160;
  int left = GetScreenWidth() - 20 - width;
  int top = 475;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("POINTS", left + 5, top + 5, 14, BLACK);
}

void drawVerticeViewButtons(App *app) {
  DrawSubmitButton(&app->ui.noViewButton);
  DrawSubmitButton(&app->ui.circleViewButton);
  DrawSubmitButton(&app->ui.squareViewButton);
}

void drawDotSizeInput(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int top = 580;
  int left = GetScreenWidth() - 20 - width;
  DrawText("Point size", left + TRANSFORM_PANEL_WIDTH - 120, top, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.dotSize.minusBtn);
  DrawSubmitButton(&app->ui.dotSize.plusBtn);
  DrawInputText(&app->ui.dotSize.input, &app->ui.currentInputText);
}

void noViewButtonHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.noViewButton.area))
    app->ui.noViewButton.mouseOn = true;
  else
    app->ui.noViewButton.mouseOn = false;
  if (app->ui.noViewButton.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.vertices.visible = false;
  }
}
void circleViewButtonHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.circleViewButton.area))
    app->ui.circleViewButton.mouseOn = true;
  else
    app->ui.circleViewButton.mouseOn = false;
  if (app->ui.circleViewButton.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.vertices.visible = true;
    app->scene.model.vertices.viewType = CIRCLE_POINTS;
  }
}

static void updateDotSize(App *app) {
  HandleInputText(&app->ui.dotSize.input, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.dotSize.input, app->ui.currentInputText);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.dotSize.plusBtn, &app->ui.dotSize);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.dotSize.minusBtn, &app->ui.dotSize);
}

void updateDotButtons(App *app) {
  noViewButtonHandler(app);
  circleViewButtonHandler(app);
  // squareViewButtonHandler(app);
}

void initVerticeViewButtons(App *app) {
  int top = 500;
  InitSubmitButton(&app->ui.noViewButton, (Rectangle){GetScreenWidth() - 185, top, 140, 20}, "No", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.circleViewButton, (Rectangle){GetScreenWidth() - 185, top + 25, 140, 20}, "Circle", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.squareViewButton, (Rectangle){GetScreenWidth() - 185, top + 50, 140, 20}, "Square", LIGHTGRAY, BLACK, 12);
}

void initDotSizeUI(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 600;

  InitSubmitButton(&app->ui.dotSize.minusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100, inputTextTop, 24, 24 }, "-", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitSubmitButton(&app->ui.dotSize.plusBtn, (Rectangle){ GetScreenWidth() - inputTextWidth - 100 + 26, inputTextTop, 24, 24 }, "+", ColorAlpha(GRAY, 0.2), BLACK, 12);
  InitInputText(
    &app->ui.dotSize.input,
    POINT_SIZE,
    DOUBLE_NUMBER_INPUT,
    (Rectangle) { GetScreenWidth() - inputTextWidth - 25, inputTextTop, inputTextWidth, 20 },
    " ", "1"
  ); 
}

void UpdateVerticesUI(App *app) {
  updateDotButtons(app);
  updateDotSize(app);
}

void DrawVerticesUI(App *app) {
    drawVerticePanel(app);
    drawVerticeViewButtons(app);
    drawDotSizeInput(app);
}

void InitVerticesUI(App *app) {
    initVerticeViewButtons(app);
    initDotSizeUI(app);
}