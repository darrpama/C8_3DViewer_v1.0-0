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
#include <libgen.h>

#include "configs.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24

// ray libs
#include "libs/raylib/raylib.h"
#include "libs/raygui/raygui.h"
#include "libs/gui_file_dialog/gui_file_dialog.h"
#include "libs/raymath/raymath.h"

// modules
#include "modules/parser/parser.h"

// UI STRUCTS
// ==========================================================================================
enum inputTextCategories {
  DOUBLE_NUMBER_INPUT,
  INT_NUMBER_INPUT,
  DATE_DAY_INPUT,
  DATE_MONTH_INPUT,
  DATE_YEAR_INPUT,
  TEXT_INPUT
};

typedef struct IconButton {
  bool mouseOn;
  Texture2D icon;
  Rectangle area;
  Color bgColor;
  Color textColor;
} IconButton;

typedef struct SubmitButton {
  bool mouseOn;
  Rectangle area;
  float fontSize;
  char text[32];
  Vector2 textPosition;
  Color bgColor;
  Color textColor;
} SubmitButton;

typedef struct InputText {
  int type;
  int category;
  bool mouseOn;
  bool updated;
  Rectangle area;
  float fontSize;
  char text[128];
  char label[128];
  Vector2 textPosition;
  Vector2 labelPosition;
} InputText;

// APP STRUCT
// ==========================================================================================
enum textInputs {
  NO_ACTIVE_INPUT,
  TRANSFORM_POSITION_X,
  TRANSFORM_POSITION_Y,
  TRANSFORM_POSITION_Z,
  TRANSFORM_ROTATION_X,
  TRANSFORM_ROTATION_Y,
  TRANSFORM_ROTATION_Z,
  TRANSFORM_SCALE_X,
  TRANSFORM_SCALE_Y,
  TRANSFORM_SCALE_Z,
};

enum pointTypes {
  SQUARE_POINTS,
  SPHERE_POINTS,
};

enum transformButtonTypes {
  INCREASE_VALUE,
  DECREASE_VALUE,
};

typedef struct UploadButton {
  IconButton button;
  GuiFileDialogState fileDialogState;
  char fileNameToLoad[512];
} UploadButton;

typedef struct TransformValue {
  InputText input;
  SubmitButton minusBtn;
  SubmitButton plusBtn;
} TransformValue;

typedef struct UI {
  int currentInputText;
  UploadButton uploadBtn;
  TransformValue position_x;
  TransformValue position_y;
  TransformValue position_z;
  TransformValue rotation_x;
  TransformValue rotation_y;
  TransformValue rotation_z;
  TransformValue scale_x;
  TransformValue scale_y;
  TransformValue scale_z;
} UI;

typedef struct Icons {
  Texture2D upload;
} Icons;

typedef struct Settings {
  // Font baseFont;
  Icons icons;
} Settings;

typedef struct Vertices {
  bool visible;
  int viewType;
  Color color;
  int size;
} Vertices;

typedef struct s21_model {
  // Obj obj;
  Model rModel;
  bool selected;
  // BoundingBox bounds;
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;
  Vertices vertices;
  int edgeCount;
} s21_model;

typedef struct Scene {
  s21_model model;
  Camera camera;
} Scene;

typedef struct App {
  Settings settings;
  UI ui;
  Scene scene;
} App;


// view/ui.c
// SubmitButton
void DrawSubmitButton(SubmitButton *btn);
void InitSubmitButton(SubmitButton *btn, Rectangle area, const char *label, Color bgColor, Color textColor);
void HandleTransformButton(int type, SubmitButton *btn, TransformValue *transform);
// IconButton
void InitIconButton(Texture2D icon, IconButton *btn, Rectangle area, Color bgColor);
void DrawIconButton(IconButton *btn);
// InputText
void InitInputText(InputText *inputText, int type, int category, Rectangle area, char *label, char *text);
void DrawInputText(InputText *inputText, int *currentInputText);
void HandleInputText(InputText *inputText, int *currentInputText);
void HandleKeys(App *app, InputText *input, int currentInputText);
void RemoveLastCharFromInputText(int currentInputText, InputText *input);
void CleanInputText(int currentInputText, InputText *input);
double GetDoubleValueFromInputText(InputText input);

// view/scene.c
void InitScene(App *app);
void DrawScene(App *app);
void UpdateScene(App *app);

// view/scene/model.c
void InitModel(App *app);
void DrawModelOnScene(App *app);
void UpdateModel(App *app);

// view/scene/camera.c
void InitCamera(App *app);

// view/scene/upload_file.c
void InitUploadFile(App *app);
void DrawUploadFile(App *app);
void UpdateUploadFile(App *app);

// view/scene/info_panels.c
void DrawInfo(App *app);

// view/scene/transform_panel.c
void InitTransformPanel(App *app);
void DrawTransformPanel(App *app);
void UpdateTransformPanel(App *app);

#endif  // __S21_3D_VIEWER_H_
