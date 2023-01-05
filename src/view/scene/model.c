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

void drawDots(App *app, float size, Color color) {
  Model *model = &app->scene.model.rModel;
  Mesh *mesh = &model->meshes[0];
  if (model->meshCount == 1) {
    for (int i = 0; i < model->meshes[0].vertexCount * 3; i += 3) {
      Vector3 pointVector = {mesh->vertices[i], mesh->vertices[i+1], mesh->vertices[i+2]};
      // DrawPoint3D(pointVector, GREEN);
      DrawCube(pointVector, size, size, size, color);
    }
  }
}

void drawSpheres(App *app, float radius, Color color) {
  Model *model = &app->scene.model.rModel;
  Mesh *mesh = &model->meshes[0];
  if (model->meshCount == 1) {
    for (int i = 0; i < model->meshes[0].vertexCount * 3; i += 3) {
      Vector3 pointVector = {mesh->vertices[i], mesh->vertices[i+1], mesh->vertices[i+2]};
      DrawSphere(pointVector, radius, color);
    }
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
  // drawDots(app, 0.5f, GREEN);
  // drawSpheres(app, 0.05f, BLUE);
  
  DrawModelDotsEx(
    app->scene.model.rModel, 
    app->scene.model.position, 
    app->scene.model.rotation, 
    app->scene.model.rotationAngle, 
    app->scene.model.scale, 
    ColorAlpha(BLACK, 1)
  );

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
  model = LoadModel("assets/models/tyan.obj");
  Vector3 default_val = { 0.0f, 0.0f, 0.0f };
  Vector3 scale = { 1.0f, 1.0f, 1.0f };
  BoundingBox bounds = { 0 };
  app->scene.model.rModel = model;
  app->scene.model.position = default_val;
  app->scene.model.rotation = default_val;
  app->scene.model.rotationAngle = 0.0f;
  app->scene.model.scale = scale;
  app->scene.model.bounds = bounds;
}