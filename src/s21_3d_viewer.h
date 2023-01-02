#ifndef __S21_3D_VIEWER_H_
#define __S21_3D_VIEWER_H_

// standart libs
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "configs.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24

// ray libs
#include "libs/raylib/raylib.h"
#include "libs/raygui/raygui.h"
#include "libs/gui_file_dialog/gui_file_dialog.h"

// UI STRUCTS
// ==========================================================================================

typedef struct IconButton {
  bool mouseOn;
  bool isPressed;
  Texture2D icon;
  Rectangle area;
  Color bgColor;
  Color textColor;
} IconButton;

// APP STRUCT
// ==========================================================================================
typedef struct UploadButton {
  IconButton button;
  GuiFileDialogState fileDialogState;
  char fileNameToLoad[512];
} UploadButton;

typedef struct UI {
  UploadButton uploadBtn;
} UI;

typedef struct Icons {
  Texture2D upload;
} Icons;

typedef struct Settings {
  // Font baseFont;
  Icons icons;
} Settings;

typedef struct Scene {
  Model model;
  Camera camera;
  BoundingBox bounds;
  Vector3 position;
  bool selected;
} Scene;

typedef struct App {
  Settings settings;
  UI ui;
  Scene scene;
} App;

// view/ui.c
void InitUI(App *app);
void InitIconButton(Texture2D icon, IconButton *btn, Rectangle area, Color bgColor);
void DrawIconButton(IconButton *btn);

// view/scene.c
void InitScene(App *app);
void DrawScene(App *app);
void HandleScene(App *app);
#endif  // __S21_3D_VIEWER_H_
