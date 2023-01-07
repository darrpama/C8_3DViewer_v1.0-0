#include "../../s21_3d_viewer.h"

void DrawCameraSettingsButtons(App *app) {
  DrawSubmitButton(&app->ui.perspectiveCamera);
  DrawSubmitButton(&app->ui.orthographicCamera);
}

void orthographicCameraHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.orthographicCamera.area))
    app->ui.orthographicCamera.mouseOn = true;
  else
    app->ui.orthographicCamera.mouseOn = false;
  if (app->ui.orthographicCamera.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.camera.projection = CAMERA_ORTHOGRAPHIC;
  }
  if (app->scene.camera.projection == CAMERA_ORTHOGRAPHIC && GetMouseWheelMove() < 0) {
    app->scene.camera.fovy -= 3.0f;
  } else if (app->scene.camera.projection == CAMERA_ORTHOGRAPHIC && GetMouseWheelMove() > 0) {
    app->scene.camera.fovy += 3.0f;
  }
}

void perspectiveCameraHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.perspectiveCamera.area))
    app->ui.perspectiveCamera.mouseOn = true;
  else
    app->ui.perspectiveCamera.mouseOn = false;
  if (app->ui.perspectiveCamera.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    app->scene.camera.projection = CAMERA_PERSPECTIVE;
  }
}

void UpdateCameraSettingsButtons(App *app) {
  orthographicCameraHandler(app);
  perspectiveCameraHandler(app);
}

void InitCameraSettingsButtons(App *app) {
  InitSubmitButton(&app->ui.orthographicCamera, (Rectangle){GetScreenWidth() - 185, 390, 140, 20}, "Orthographic", LIGHTGRAY, BLACK, 12);
  InitSubmitButton(&app->ui.perspectiveCamera, (Rectangle){GetScreenWidth() - 185, 415, 140, 20}, "Perspective", LIGHTGRAY, BLACK, 12);
}

void InitCamera(App *app) {
  Camera camera = { 0 };
  camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
  app->scene.camera = camera;
  SetCameraMode(app->scene.camera, CAMERA_FREE);
  InitCameraSettingsButtons(app);
}