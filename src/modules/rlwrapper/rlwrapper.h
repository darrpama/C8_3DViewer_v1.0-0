#ifndef __RLWRAPPER_H
#define __RLWRAPPER_H

// ray libs
#include "../../libs/gui_file_dialog/gui_file_dialog.h"
#include "../../libs/raygui/raygui.h"
#include "../../libs/raylib/raylib.h"
#include "../../libs/raymath/raymath.h"
#include "../../libs/rlgl/rlgl.h"
#include "glad.h"

#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#define GL_POINT_SMOOTH 0x0B10
#define GL_POINT_SMOOTH_HINT 0x0C51
#define GL_POINT_SPRITE 0x8861
#define GL_COORD_REPLACE 0x8862
#define GL_TEXTURE_ENV 0x2300
#define GL_TEXTURE_ENV_MODE 0x2200
#define GL_LINE_STIPPLE 0x0B24

void rlEnableDotMode(int size);
void rlDisableDotMode(void);
void rlEnableSmoothDots(void);
void rlDisableSmoothDots(void);
void rlEnableDashedMode(void);
void rlDisableDashedMode(void);

void DrawModelDots(Model model, Vector3 position, float scale, Color tint,
                   int size, int dotType);
void DrawModelDotsEx(Model model, Vector3 position, Vector3 rotationAxis,
                     float rotationAngle, Vector3 scale, Color tint, int size,
                     int dotType);
void DrawModelSolidWiresEx(Model model, Vector3 position, Vector3 rotationAxis,
                           float rotationAngle, Vector3 scale, Color tint,
                           int size);
void DrawModelDashedWiresEx(Model model, Vector3 position, Vector3 rotationAxis,
                            float rotationAngle, Vector3 scale, Color tint,
                            int size);

#endif  // __RLWRAPPER_H
