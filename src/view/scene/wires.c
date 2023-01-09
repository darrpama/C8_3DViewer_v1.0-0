#include "../../s21_3d_viewer.h"

void drawWiresPanel(App *app) {
  (void)app;
  int width = TRANSFORM_PANEL_WIDTH;
  int height = 160;
  int left = GetScreenWidth() - 20 - width;
  int top = 575;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("WIRES", left + 5, top + 5, 14, BLACK);
}

void drawWiresViewButtons(App *app) {
  DrawSubmitButton(&app->ui.noWireViewButton);
  DrawSubmitButton(&app->ui.solidViewButton);
  DrawSubmitButton(&app->ui.dashedViewButton);
}

void drawWireColors(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int top = 675;
  int left = GetScreenWidth() - 20 - width;
  DrawText("Wire colors", left + TRANSFORM_PANEL_WIDTH - 120, top, 14,
           Fade(BLACK, 0.5f));
  DrawSubmitButton(&app->ui.wireColorRed);
  DrawSubmitButton(&app->ui.wireColorGreen);
  DrawSubmitButton(&app->ui.wireColorBlue);
  DrawSubmitButton(&app->ui.wireColorViolet);
  DrawSubmitButton(&app->ui.wireColorGray);
  DrawSubmitButton(&app->ui.wireColorBlack);
}

static void changeViewButtonHandler(App *app, SubmitButton btn, bool visible,
                                    int viewType) {
  if (CheckCollisionPointRec(GetMousePosition(), btn.area))
    btn.mouseOn = true;
  else
    btn.mouseOn = false;
  if (btn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.wires.visible = visible;
    app->scene.model.wires.viewType = viewType;
  }
}

void paintWires(App *app, SubmitButton btn, Color color) {
  if (CheckCollisionPointRec(GetMousePosition(), btn.area))
    btn.mouseOn = true;
  else
    btn.mouseOn = false;
  if (btn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.model.wires.color = color;
  }
}

static void updateWireColors(App *app) {
  paintWires(app, app->ui.wireColorRed, RED);
  paintWires(app, app->ui.wireColorGreen, GREEN);
  paintWires(app, app->ui.wireColorBlue, BLUE);
  paintWires(app, app->ui.wireColorViolet, VIOLET);
  paintWires(app, app->ui.wireColorGray, GRAY);
  paintWires(app, app->ui.wireColorBlack, BLACK);
}

void updateWireButtons(App *app) {
  changeViewButtonHandler(app, app->ui.noWireViewButton, false, SOLID_LINES);
  changeViewButtonHandler(app, app->ui.solidViewButton, true, SOLID_LINES);
  changeViewButtonHandler(app, app->ui.dashedViewButton, true, DASHED_LINES);
}

void initWireColors(App *app) {
  int inputTextWidth = 100;
  int inputTextTop = 695;

  InitSubmitButton(
      &app->ui.wireColorRed,
      (Rectangle){GetScreenWidth() - inputTextWidth - 95, inputTextTop, 24, 24},
      " ", ColorAlpha(RED, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.wireColorGreen,
                   (Rectangle){GetScreenWidth() - inputTextWidth - 95 + 26,
                               inputTextTop, 24, 24},
                   " ", ColorAlpha(GREEN, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.wireColorBlue,
                   (Rectangle){GetScreenWidth() - inputTextWidth - 95 + 52,
                               inputTextTop, 24, 24},
                   " ", ColorAlpha(BLUE, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.wireColorViolet,
                   (Rectangle){GetScreenWidth() - inputTextWidth - 95 + 78,
                               inputTextTop, 24, 24},
                   " ", ColorAlpha(VIOLET, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.wireColorGray,
                   (Rectangle){GetScreenWidth() - inputTextWidth - 95 + 104,
                               inputTextTop, 24, 24},
                   " ", ColorAlpha(GRAY, 0.7), BLACK, 12);
  InitSubmitButton(&app->ui.wireColorBlack,
                   (Rectangle){GetScreenWidth() - inputTextWidth - 95 + 130,
                               inputTextTop, 24, 24},
                   " ", ColorAlpha(BLACK, 0.7), BLACK, 12);
}

void initWiresViewButtons(App *app) {
  int top = 600;
  InitSubmitButton(&app->ui.noWireViewButton,
                   (Rectangle){GetScreenWidth() - 185, top, 140, 20}, "No",
                   LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.solidViewButton,
                   (Rectangle){GetScreenWidth() - 185, top + 25, 140, 20},
                   "Solid", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.dashedViewButton,
                   (Rectangle){GetScreenWidth() - 185, top + 50, 140, 20},
                   "Dashed", LIGHTGRAY, BLACK, 12);
}

void UpdateWiresUI(App *app) {
  updateWireButtons(app);
  updateWireColors(app);
}

void DrawWiresUI(App *app) {
  drawWiresPanel(app);
  drawWiresViewButtons(app);
  drawWireColors(app);
}

void InitWiresUI(App *app) {
  initWiresViewButtons(app);
  initWireColors(app);
}