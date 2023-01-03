#include "../../s21_3d_viewer.h"

void selectModelHandler(App *app) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), app->scene.camera), app->scene.bounds).hit) {
      app->scene.selected = !app->scene.selected;
    } else {
      app->scene.selected = false;
    }
  }
}

void drawBounds(App *app) {
  if (app->scene.selected) {
    DrawBoundingBox(app->scene.bounds, GREEN);
  }
}

void updateModelPosition(App *app) {
  if (app->ui.transform_pos_x.updated == true) {
    app->scene.position.x = GetDoubleValueFromInputText(app->ui.transform_pos_x);
    app->ui.transform_pos_x.updated = false;
  }
  if (app->ui.transform_pos_y.updated == true) {
    app->scene.position.y = GetDoubleValueFromInputText(app->ui.transform_pos_y);
    app->ui.transform_pos_y.updated = false;
  }
  if (app->ui.transform_pos_z.updated == true) {
    app->scene.position.z = GetDoubleValueFromInputText(app->ui.transform_pos_z);
    app->ui.transform_pos_z.updated = false;
  }
}

void DrawModelOnScene(App *app) {
  drawBounds(app);
  DrawModel(app->scene.model, app->scene.position, 20.0f, ColorAlpha(BLACK, 0.5));
}

void UpdateModel(App *app) {
  selectModelHandler(app);
  updateModelPosition(app);
}

void InitModel(App *app) {
  Model model = { 0 };
  Vector3 position = { 0.0f, 0.0f, 0.0f };
  app->scene.model = model;
  app->scene.position = position;
  BoundingBox bounds = { 0 };
  app->scene.bounds = bounds;
}