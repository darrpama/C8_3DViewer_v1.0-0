#include "s21_3d_viewer.h"

#define APP_TITLE "3d Viewer v1.0 (based on raygui and raylib)"

#define INPUT_MAX 32

// STYLES
#define TRANSFORM_PANEL_WIDTH 190
#define TRANSFORM_PANEL_HEIGHT 360

// FONTS (deprecated)
#define BASE_FONT "./assets/fonts/RobotoSlab-Regular.ttf"

// SIZES
#ifdef __linux__
  #define APP_SCREEN_WIDTH 1366
  #define APP_SCREEN_HEIGHT 768
#else
  #define APP_SCREEN_WIDTH 1366
  #define APP_SCREEN_HEIGHT 768
#endif

#define GIF_SCREEN_WIDTH 640
#define GIF_SCREEN_HEIGHT 480


// KEYBOARDS
#define SHIFT_NOT_PRESSED \
  (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0
#define SHIFT_PRESSED \
  (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0

#define CTRL_NOT_PRESSED (!IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_CONTROL)) ? 1 : 0
#define CTRL_PRESSED (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) ? 1 : 0