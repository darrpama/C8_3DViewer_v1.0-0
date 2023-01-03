#include "s21_3d_viewer.h"

#define APP_TITLE "3d Viewer v1.0 (based on raygui and raylib)"

#define INPUT_MAX 32

// FONTS (deprecated)
#define BASE_FONT "./assets/fonts/RobotoSlab-Regular.ttf"

// GENERAL
#define APP_SCREEN_WIDTH 1680
#define APP_SCREEN_HEIGHT 900

// KEYBOARDS
#define SHIFT_NOT_PRESSED \
  (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0
#define SHIFT_PRESSED \
  (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0

#define CTRL_NOT_PRESSED (!IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_CONTROL)) ? 1 : 0
#define CTRL_PRESSED (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) ? 1 : 0