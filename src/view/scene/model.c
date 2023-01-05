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
  if (app->ui.position_x.input.updated == true) {
    app->scene.model.position.x = GetDoubleValueFromInputText(app->ui.position_x.input);
    app->ui.position_x.input.updated = false;
  }
  if (app->ui.position_y.input.updated == true) {
    app->scene.model.position.y = GetDoubleValueFromInputText(app->ui.position_y.input);
    app->ui.position_y.input.updated = false;
  }
  if (app->ui.position_z.input.updated == true) {
    app->scene.model.position.z = GetDoubleValueFromInputText(app->ui.position_z.input);
    app->ui.position_z.input.updated = false;
  }
}

void updateModelRotation(App *app) {
  if (app->ui.rotation_x.input.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.rotation_x.input);
    app->scene.model.rotation.x = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.rotation_x.input.updated = false;
  }
  if (app->ui.rotation_y.input.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.rotation_y.input);
    app->scene.model.rotation.y = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.rotation_y.input.updated = false;
  }
  if (app->ui.rotation_z.input.updated == true) {
    double val = GetDoubleValueFromInputText(app->ui.rotation_z.input);
    app->scene.model.rotation.z = val;
    app->scene.model.rModel.transform = MatrixRotateXYZ(app->scene.model.rotation);
    app->ui.rotation_z.input.updated = false;
  }
}

void updateModelScale(App *app) {
  if (app->ui.scale_x.input.updated == true) {
    app->scene.model.scale.x = GetDoubleValueFromInputText(app->ui.scale_x.input);
    app->ui.scale_x.input.updated = false;
  }
  if (app->ui.scale_y.input.updated == true) {
    app->scene.model.scale.y = GetDoubleValueFromInputText(app->ui.scale_y.input);
    app->ui.scale_y.input.updated = false;
  }
  if (app->ui.scale_z.input.updated == true) {
    app->scene.model.scale.z = GetDoubleValueFromInputText(app->ui.scale_z.input);
    app->ui.scale_z.input.updated = false;
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
  Vector3 scale = { 1.0f, 1.0f, 1.0f };
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