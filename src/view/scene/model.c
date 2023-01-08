#include "../../s21_3d_viewer.h"

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

static void updateDotSize(App *app) {
  if (app->ui.dotSize.input.updated == true) {
    app->scene.model.vertices.size = GetDoubleValueFromInputText(app->ui.dotSize.input);
    app->ui.dotSize.input.updated = false;
  }
}

void DrawModelOnScene(App *app) {
  
  if (app->scene.model.vertices.visible == true) {
    DrawModelDotsEx(
      app->scene.model.rModel, app->scene.model.position, app->scene.model.rotation, 0.0f,
      app->scene.model.scale, app->scene.model.vertices.color, app->scene.model.vertices.size, 
      app->scene.model.vertices.viewType
    );
  }

  if (app->scene.model.wires.visible == true) {
    DrawModelWiresEx(
      app->scene.model.rModel, 
      app->scene.model.position, 
      app->scene.model.rotation, 
      0.0f,
      app->scene.model.scale, 
      ColorAlpha(BLACK, 0.4)
    );
  }

  if (app->scene.model.wires.visible == true) {
    DrawModelEx(
      app->scene.model.rModel, 
      app->scene.model.position, 
      app->scene.model.rotation, 
      0.0f,
      app->scene.model.scale, 
      ColorAlpha(PINK, 1)
    );
  }
}

void UpdateModel(App *app) {
  updateModelPosition(app);
  updateModelRotation(app);
  updateModelScale(app);
  updateDotSize(app);
}

void InitModel(App *app) {
  Vector3 default_val = { 0.0f, 0.0f, 0.0f };
  Vector3 scale = { 25.0f, 25.0f, 25.0f };
  // MODEL GENERAL
  Model model = { 0 };
  model = LoadModel("assets/models/cube.obj");
  app->scene.model.rModel = model;
  app->scene.model.edgeCount = GetEdgesCount("assets/models/cube.obj");
  // app->scene.model.bounds = bounds;
  app->scene.model.selected = false;
  // MODEL TRANSFORMATION
  app->scene.model.position = default_val;
  app->scene.model.rotation = default_val;
  app->scene.model.scale = scale;
  // MODEL VERTICES
  app->scene.model.vertices.color = ColorAlpha(DARKPURPLE, 0.5);
  app->scene.model.vertices.size = 20;
  app->scene.model.vertices.viewType = CIRCLE_POINTS;
  app->scene.model.vertices.visible = true;
  // MODEL WIRES
  app->scene.model.wires.color = LIGHTGRAY;
  app->scene.model.wires.viewType = SOLID_LINES;
  app->scene.model.wires.visible = false;
}