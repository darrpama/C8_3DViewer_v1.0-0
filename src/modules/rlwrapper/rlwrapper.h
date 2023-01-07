#ifndef __RLWRAPPER_H
#define __RLWRAPPER_H

// ray libs
#include "glad.h"
#include "../../libs/raylib/raylib.h"
#include "../../libs/raygui/raygui.h"
#include "../../libs/gui_file_dialog/gui_file_dialog.h"
#include "../../libs/raymath/raymath.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24

void rlEnableDotMode(void);
void rlDisableDotMode(void);

#endif  // __RLWRAPPER_H
