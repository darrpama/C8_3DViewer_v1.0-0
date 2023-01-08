#include "s21_3d_viewer.h"

void InitApp(App *app) {
  InitWindow(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, APP_TITLE);

  SetExitKey(0);
  SetTargetFPS(60);

  InitScene(app);
}

int main() {
  App app;
  InitApp(&app);
  
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  while (!WindowShouldClose()) {
  
    UpdateCamera(&app.scene.camera);
    UpdateScene(&app);
    
    BeginDrawing();
      DrawScene(&app);
    EndDrawing();
  }
  
  // UnloadObj(&app.scene.model.obj);
  UnloadModel(app.scene.model.rModel);

  CloseWindow();
  
  return 0;
}
