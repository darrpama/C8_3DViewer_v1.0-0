#include "../../s21_3d_viewer.h"

void DrawVerticeViewButtons(App *app) {
  DrawSubmitButton(&app->ui.noViewButton);
  DrawSubmitButton(&app->ui.circleViewButton);
  DrawSubmitButton(&app->ui.squareViewButton);
}

// void orthographicCameraHandler(App *app) {
//   if (CheckCollisionPointRec(GetMousePosition(), app->ui.orthographicCamera.area))
//     app->ui.orthographicCamera.mouseOn = true;
//   else
//     app->ui.orthographicCamera.mouseOn = false;
//   if (app->ui.orthographicCamera.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//     app->scene.camera.projection = CAMERA_ORTHOGRAPHIC;
//   }
// }

// void perspectiveCameraHandler(App *app) {
//   if (CheckCollisionPointRec(GetMousePosition(), app->ui.perspectiveCamera.area))
//     app->ui.perspectiveCamera.mouseOn = true;
//   else
//     app->ui.perspectiveCamera.mouseOn = false;
//   if (app->ui.perspectiveCamera.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//     app->scene.camera.projection = CAMERA_PERSPECTIVE;
//   }
// }

// void UpdateVerticeViewButtons(App *app) {
//   orthographicCameraHandler(app);
//   perspectiveCameraHandler(app);
// }

void initVerticeViewButtons(App *app) {
  InitSubmitButton(&app->ui.noViewButton, (Rectangle){GetScreenWidth() - 485, 390, 140, 20}, "No", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.circleViewButton, (Rectangle){GetScreenWidth() - 485, 415, 140, 20}, "Circle", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.squareViewButton, (Rectangle){GetScreenWidth() - 485, 440, 140, 20}, "Square", LIGHTGRAY, BLACK, 12);
}
void DrawVerticesUI(App *app) {
    DrawVerticeViewButtons(app);
}
void InitVerticesUI(App *app) {
    initVerticeViewButtons(app);
}