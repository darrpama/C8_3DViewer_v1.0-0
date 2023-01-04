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
  Model *model = &app->scene.model.rModel;
  Mesh *mesh = &model->meshes[0];
  if (model->meshCount == 1) {
    for (int i = 0; i < model->meshes[0].vertexCount; i += 3) {
      Vector3 pointVector = {mesh->vertices[i], mesh->vertices[i+1], mesh->vertices[i+2]};
      // DrawPoint3D(pointVector, GREEN);
      DrawCube(pointVector, 0.05f, 0.05f, 0.05f, GREEN);
    }
  }
  // DrawModelWiresEx(
  //   app->scene.model.rModel, 
  //   app->scene.model.position, 
  //   app->scene.model.rotation, 
  //   app->scene.model.rotationAngle, 
  //   app->scene.model.scale, 
  //   ColorAlpha(BLACK, 0.5)
  // );
}

void UpdateModel(App *app) {
  selectModelHandler(app);
  updateModelPosition(app);
  updateModelRotation(app);
  updateModelScale(app);
}

void InitModel(App *app) {
  Model model = { 0 };
  Vector3 default_val = { 0.0f, 0.0f, 0.0f };
  Vector3 scale = { 10.0f, 10.0f, 10.0f };
  BoundingBox bounds = { 0 };
  app->scene.model.rModel = model;
  app->scene.model.position = default_val;
  app->scene.model.rotation = default_val;
  app->scene.model.rotationAngle = 0.0f;
  app->scene.model.scale = scale;
  app->scene.model.bounds = bounds;
}