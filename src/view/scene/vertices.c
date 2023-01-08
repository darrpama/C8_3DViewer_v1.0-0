#include "../../s21_3d_viewer.h"

void drawVerticePanel(App *app) {
  (void)app;
  int width = TRANSFORM_PANEL_WIDTH;
  int height = 200;
  int left = GetScreenWidth() - 20 - width;
  int top = 370;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("POINTS", left + 5, top + 5, 14, BLACK);
}

void drawVerticeViewButtons(App *app) {
  DrawSubmitButton(&app->ui.noPointViewButton);
  DrawSubmitButton(&app->ui.circleViewButton);
  DrawSubmitButton(&app->ui.squareViewButton);
}

void drawDotSizeInput(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int top = 470;
  int left = GetScreenWidth() - 20 - width;
  DrawText("Point size", left + TRANSFORM_PANEL_WIDTH - 120, top, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.dotSize.minusBtn);
  DrawSubmitButton(&app->ui.dotSize.plusBtn);
  DrawInputText(&app->ui.dotSize.input, &app->ui.currentInputText);
}

void drawDotColors(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int top = 515;
  int left = GetScreenWidth() - 20 - width;
  DrawText("Point colors", left + TRANSFORM_PANEL_WIDTH - 120, top, 14, Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.pointColorRed);
  DrawSubmitButton(&app->ui.pointColorGreen);
  DrawSubmitButton(&app->ui.pointColorBlue);
  DrawSubmitButton(&app->ui.pointColorViolet);
  DrawSubmitButton(&app->ui.pointColorGray);
  DrawSubmitButton(&app->ui.pointColorBlack);
}

static void changeViewButtonHandler(App *app, SubmitButton btn, bool visible, int viewType) {
  if (CheckCollisionPointRec(GetMousePosition(), btn.area))
    btn.mouseOn = true;
  else
    btn.mouseOn = false;
  if (btn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.vertices.visible = visible;
    app->scene.model.vertices.viewType = viewType;
  }
}

void paintDot(App *app, SubmitButton btn, Color color) {
  if (CheckCollisionPointRec(GetMousePosition(), btn.area))
    btn.mouseOn = true;
  else
    btn.mouseOn = false;
  if (btn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.vertices.color = color;
  }
}

static void updateDotSize(App *app) {
  HandleInputText(&app->ui.dotSize.input, &app->ui.currentInputText);
  HandleKeys(app, &app->ui.dotSize.input, app->ui.currentInputText);
  HandleIncreaseDecreaseButton(INCREASE_VALUE, &app->ui.dotSize.plusBtn, &app->ui.dotSize);
  HandleIncreaseDecreaseButton(DECREASE_VALUE, &app->ui.dotSize.minusBtn, &app->ui.dotSize);
}

static void updateDotColors(App *app) {
  paintDot(app, app->ui.pointColorRed, RED);
  paintDot(app, app->ui.pointColorGreen, GREEN);
  paintDot(app, app->ui.pointColorBlue, BLUE);
  paintDot(app, app->ui.pointColorViolet, VIOLET);
  paintDot(app, app->ui.pointColorGray, GRAY);
  paintDot(app, app->ui.pointColorBlack, BLACK);
}

void updateDotButtons(App *app) {
  changeViewButtonHandler(app, app->ui.noPointViewButton, false, CIRCLE_POINTS);
  changeViewButtonHandler(app, app->ui.circleViewButton, true, CIRCLE_POINTS);
  changeViewButtonHandler(app, app->ui.squareViewButton, true, SQUARE_POINTS);
}

void initVerticeViewButtons(App *app) {
  int top = 394;
  InitSubmitButton(&app->ui.noPointViewButton, (Rectangle){GetScreenWidth() - 185, top, 140, 20}, "No", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.circleViewButton, (Rectangle){GetScreenWidth() - 185, top + 25, 140, 20}, "Circle", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.squareViewButton, (Rectangle){GetScreenWidth() - 185, top + 50, 140, 20}, "Square", LIGHTGRAY, BLACK, 12);
}

void initDotSizeUI(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 485;

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

void initDotColors(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 535;

  InitSubmitButton(&app->ui.pointColorRed, (Rectangle){ GetScreenWidth() - inputTextWidth - 95, inputTextTop, 24, 24 }, " ", ColorAlpha(RED, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.pointColorGreen, (Rectangle){ GetScreenWidth() - inputTextWidth - 95 + 26, inputTextTop, 24, 24 }, " ", ColorAlpha(GREEN, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.pointColorBlue, (Rectangle){ GetScreenWidth() - inputTextWidth - 95 + 52, inputTextTop, 24, 24 }, " ", ColorAlpha(BLUE, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.pointColorViolet, (Rectangle){ GetScreenWidth() - inputTextWidth - 95 + 78, inputTextTop, 24, 24 }, " ", ColorAlpha(VIOLET, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.pointColorGray, (Rectangle){ GetScreenWidth() - inputTextWidth - 95 + 104, inputTextTop, 24, 24 }, " ", ColorAlpha(GRAY, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.pointColorBlack, (Rectangle){ GetScreenWidth() - inputTextWidth - 95 + 130, inputTextTop, 24, 24 }, " ", ColorAlpha(BLACK, 0.7), BLACK, 12);
}

void UpdateVerticesUI(App *app) {
  updateDotButtons(app);
  updateDotSize(app);
  updateDotColors(app);
}

void DrawVerticesUI(App *app) {
  drawVerticePanel(app);
  drawVerticeViewButtons(app);
  drawDotSizeInput(app);
  drawDotColors(app);
}

void InitVerticesUI(App *app) {
  initVerticeViewButtons(app);
  initDotSizeUI(app);
  initDotColors(app);
}