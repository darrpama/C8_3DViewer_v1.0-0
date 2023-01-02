#include "../s21_3d_viewer.h"

void DrawIconButton(IconButton *btn) {
  DrawRectangle(btn->area.x,btn->area.y,btn->area.width,btn->area.height, btn->bgColor);
  DrawTexture(btn->icon, btn->area.x+8, btn->area.y+8, WHITE);
}

void InitIconButton(Texture2D icon, IconButton *btn, Rectangle area, Color bgColor) {
  btn->mouseOn = false;
  btn->isPressed = false;
  btn->area = area;
  btn->bgColor = bgColor;
  btn->icon = icon;
}

void InitUI(App *app) {
  app->ui.uploadBtn.fileDialogState = InitGuiFileDialog(GetWorkingDirectory());
  app->ui.uploadBtn.fileNameToLoad[0] = '\0';
  Texture2D icon = LoadTexture("./assets/icons/upload.png");
  InitIconButton(icon, &app->ui.uploadBtn.button, (Rectangle){50,40,64,64}, ColorAlpha(GRAY, 0.2));
  app->ui.uploadBtn.fileDialogState = InitGuiFileDialog(GetWorkingDirectory());
}
