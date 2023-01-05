#include "../../s21_3d_viewer.h"

void selectModelHandler(App *app) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), app->scene.camera), app->scene.model.bounds).hit) {
      app->scene.model.selected = !app->scene.model.selected;
    } else {
      app->scene.model.selected = false;
    }
  }
}

void drawBounds(App *app) {
  if (app->scene.model.selected) {
    DrawBoundingBox(app->scene.model.bounds, GREEN);
  }
}

void updateModelPosition(App *app) {
  if (app->ui.transform_position_x.updated == true) {
    app->scene.model.position.x = GetDoubleValueFromInputText(app->ui.transform_position_x);
    app->ui.transform_position_x.updated = false;
  }
  if (app->ui.transform_position_y.updated == true) {
    app->scene.model.position.y = GetDoubleValueFromInputText(app->ui.transform_position_y);
    app->ui.transform_position_y.updated = false;
  }
  if (app->ui.transform_position_z.updated == true) {
    app->scene.model.position.z = GetDoubleValueFromInputText(app->ui.transform_position_z);
    app->ui.transform_position_z.updated = false;
  }
}

void updateModelRotation(App *app) {
  if (app->ui.transform_rotation_x.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.transform_rotation_x);
    app->scene.model.rotation.x = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.transform_rotation_x.updated = false;
  }
  if (app->ui.transform_rotation_y.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.transform_rotation_y);
    app->scene.model.rotation.y = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.transform_rotation_y.updated = false;
  }
  if (app->ui.transform_rotation_z.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.transform_rotation_z);
    app->scene.model.rotation.z = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.transform_rotation_z.updated = false;
  }
}

void updateModelScale(App *app) {
  if (app->ui.transform_scale_x.updated == true) {
    app->scene.model.scale.x = GetDoubleValueFromInputText(app->ui.transform_scale_x);
    app->ui.transform_scale_x.updated = false;
  }
  if (app->ui.transform_scale_y.updated == true) {
    app->scene.model.scale.y = GetDoubleValueFromInputText(app->ui.transform_scale_y);
    app->ui.transform_scale_y.updated = false;
  }
  if (app->ui.transform_scale_z.updated == true) {
    app->scene.model.scale.z = GetDoubleValueFromInputText(app->ui.transform_scale_z);
    app->ui.transform_scale_z.updated = false;
  }
}

void DrawModelOnScene(App *app) {
  drawBounds(app);
  if (app->scene.model.vertices.visible == true) {
    DrawModelDotsEx(
      app->scene.model.rModel, 
      app->scene.model.position, 
      app->scene.model.rotation, 
      0.0f,
      app->scene.model.scale, 
      app->scene.model.vertices.color,
      app->scene.model.vertices.size
    );
  }
}

void UpdateModel(App *app) {
  selectModelHandler(app);
  updateModelPosition(app);
  updateModelRotation(app);
  updateModelScale(app);
}

void InitModel(App *app) {
  Model model = { 0 };
  model = LoadModel("assets/models/tyan.obj");
  Vector3 default_val = { 0.0f, 0.0f, 0.0f };
  Vector3 scale = { 10.0f, 10.0f, 10.0f };
  BoundingBox bounds = { 0 };
  // MODEL GENERAL
  app->scene.model.rModel = model;
  app->scene.model.bounds = bounds;
  app->scene.model.selected = false;
  // MODEL TRANSFORMATION
  app->scene.model.position = default_val;
  app->scene.model.rotation = default_val;
  app->scene.model.scale = scale;
  // MODEL VERTICES
  app->scene.model.vertices.color = DARKPURPLE;
  app->scene.model.vertices.size = 1;
  app->scene.model.vertices.viewType = SQUARE_POINTS;
  app->scene.model.vertices.visible = true;
}