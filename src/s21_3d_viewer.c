#include "s21_3d_viewer.h"

void InitApp(App *app) {
  InitWindow(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, APP_TITLE);

  SetExitKey(0);
  SetTargetFPS(60);

  InitScene(app);
}

void ClearMemory(App *app) {
  UnloadModel(app->scene.model.rModel);
  UnloadTexture(app->ui.saveGifBtn.icon);
  UnloadTexture(app->ui.uploadBtn.button.icon);
  UnloadTexture(app->ui.saveGifBtn.icon);
}

int main() {
  App app;
  InitApp(&app);

  while (!WindowShouldClose()) {
  
    UpdateCamera(&app.scene.camera);
    UpdateScene(&app);
    
    BeginDrawing();
      DrawScene(&app);
    EndDrawing();
  }
  
  ClearMemory(&app);
  CloseWindow();
  
  return 0;
}
