#include "../../s21_3d_viewer.h"

void selectModelHandler(App *app) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), app->scene.camera), app->scene.model.bounds).hit) {
      app->scene.selected = !app->scene.selected;
    } else {
      app->scene.selected = false;
    }
  }
}

void drawBounds(App *app) {
  if (app->scene.selected) {
    DrawBoundingBox(app->scene.model.bounds, GREEN);
  }
}

void updateModelPosition(App *app) {
  if (app->ui.transform_pos_x.updated == true) {
    app->scene.model.position.x = GetDoubleValueFromInputText(app->ui.transform_pos_x);
    app->ui.transform_pos_x.updated = false;
  }
  if (app->ui.transform_pos_y.updated == true) {
    app->scene.model.position.y = GetDoubleValueFromInputText(app->ui.transform_pos_y);
    app->ui.transform_pos_y.updated = false;
  }
  if (app->ui.transform_pos_z.updated == true) {
    app->scene.model.position.z = GetDoubleValueFromInputText(app->ui.transform_pos_z);
    app->ui.transform_pos_z.updated = false;
  }
}

void DrawModelOnScene(App *app) {
  drawBounds(app);
  DrawModelEx(app->scene.model.rModel, app->scene.model.position, app->scene.model.rotation, 45.0, app->scene.model.scale, ColorAlpha(BLACK, 0.5));
}

void UpdateModel(App *app) {
  selectModelHandler(app);
  updateModelPosition(app);
}

void InitModel(App *app) {
  Model model = { 0 };
  Vector3 default_val = { 0.0f, 0.0f, 0.0f };
  Vector3 scale = { 10.0f, 10.0f, 10.0f };
  BoundingBox bounds = { 0 };
  app->scene.model.rModel = model;
  app->scene.model.position = default_val;
  app->scene.model.rotation = default_val;
  app->scene.model.scale = scale;
  app->scene.model.bounds = bounds;
}