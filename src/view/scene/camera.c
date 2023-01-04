#include "../../s21_3d_viewer.h"

void InitCamera(App *app) {
  Camera camera = { 0 };
  camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
  app->scene.camera = camera;
  SetCameraMode(app->scene.camera, CAMERA_FREE);
}