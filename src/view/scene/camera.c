#include "../../s21_3d_viewer.h"

void DrawCameraSettingsButtons(App *app) {
  int width = TRANSFORM_PANEL_WIDTH;
  int height = 85;
  int left = GetScreenWidth() - 25 - (width + width);
  int top = 5;
  DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
  DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
  DrawText("PROJECTION", left + 5, top + 5, 14, BLACK);
  DrawSubmitButton(&app->ui.perspectiveCamera);
  DrawSubmitButton(&app->ui.orthographicCamera);
}

void orthographicCameraHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(),
                             app->ui.orthographicCamera.area))
    app->ui.orthographicCamera.mouseOn = true;
  else
    app->ui.orthographicCamera.mouseOn = false;
  if (app->ui.orthographicCamera.mouseOn &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.camera.projection = CAMERA_ORTHOGRAPHIC;
  }
  if (app->scene.camera.projection == CAMERA_ORTHOGRAPHIC &&
      GetMouseWheelMove() < 0) {
    app->scene.camera.fovy -= 3.0f;
  } else if (app->scene.camera.projection == CAMERA_ORTHOGRAPHIC &&
             GetMouseWheelMove() > 0) {
    app->scene.camera.fovy += 3.0f;
  }
}

void perspectiveCameraHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(),
                             app->ui.perspectiveCamera.area))
    app->ui.perspectiveCamera.mouseOn = true;
  else
    app->ui.perspectiveCamera.mouseOn = false;
  if (app->ui.perspectiveCamera.mouseOn &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.camera.projection = CAMERA_PERSPECTIVE;
  }
}

void UpdateCameraSettingsButtons(App *app) {
  orthographicCameraHandler(app);
  perspectiveCameraHandler(app);
}

void InitCameraSettingsButtons(App *app) {
  int top = 30;
  InitSubmitButton(
      &app->ui.orthographicCamera,
      (Rectangle){GetScreenWidth() - 185 - TRANSFORM_PANEL_WIDTH, top, 140, 20},
      "Orthographic", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.perspectiveCamera,
                   (Rectangle){GetScreenWidth() - 185 - TRANSFORM_PANEL_WIDTH,
                               top + 25, 140, 20},
                   "Perspective", LIGHTGRAY, BLACK, 12);
}

void InitCamera(App *app) {
  Camera camera = {0};
  camera.position = (Vector3){50.0f, 50.0f, 50.0f};  // Camera position
  camera.target = (Vector3){0.0f, 10.0f, 0.0f};      // Camera looking at point
  camera.up = (Vector3){0.0f, 1.0f,
                        0.0f};  // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;          // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type
  app->scene.camera = camera;
  SetCameraMode(app->scene.camera, CAMERA_FREE);
  InitCameraSettingsButtons(app);
}