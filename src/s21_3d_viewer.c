#include "s21_3d_viewer.h"

void InitApp(App *app) {
  InitWindow(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, APP_TITLE);

  SetExitKey(0);
  SetTargetFPS(60);

  InitScene(app);
  InitUI(app);
}

int main() {
  App app;
  InitApp(&app);
  while (!WindowShouldClose()) {
    // HandleFullscreen(&app);
    UpdateCamera(&app.scene.camera);
    HandleScene(&app);
    
    BeginDrawing();
      // DrawTestPage(&app);
      DrawScene(&app);
    EndDrawing();
  }
  UnloadModel(app.scene.model);
  CloseWindow();
  return 0;
}
