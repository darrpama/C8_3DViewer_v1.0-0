#include "rlwrapper.h"

// Enable point mode
void rlEnableDotMode(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// Disable point mode
void rlDisableDotMode(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Draw a model wires (with texture if set)
void DrawModelDots(Model model, Vector3 position, float scale, Color tint, int size)
{
    rlEnableDotMode();

    glPointSize(size);

    DrawModel(model, position, scale, tint);

    rlDisableDotMode();
}

// Draw a model wires (with texture if set) with extended parameters
void DrawModelDotsEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint, int size)
{
    rlEnableDotMode();

    glPointSize(size);

    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);

    rlDisableDotMode();
}