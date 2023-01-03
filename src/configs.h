#include "s21_3d_viewer.h"

#define APP_TITLE "3d Viewer v1.0 (based on raygui and raylib)"

// FONTS (deprecated)
#define BASE_FONT "./assets/fonts/RobotoSlab-Regular.ttf"

// CALC
#ifdef __linux__
  #define APP_SCREEN_WIDTH 1366
  #define APP_SCREEN_HEIGHT 768
#else
  #define APP_SCREEN_WIDTH 1460
  #define APP_SCREEN_HEIGHT 800
#endif


// KEYBOARDS
#define SHIFT_NOT_PRESSED \
  (!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0
#define SHIFT_PRESSED \
  (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 1 : 0
