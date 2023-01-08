#include "rlwrapper.h"
#include "stdio.h"

// Enable point mode
void rlEnableDotMode(int size)
{
    glPointSize(size);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// Disable point mode
void rlDisableDotMode(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Enable dashed wires mode
void rlEnableDashedMode(void)
{
    glLineWidth(5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_ALIASED_LINE_WIDTH_RANGE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE_STRIP);
}

// Enable dashed wires mode
void rlDisableDashedMode(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void rlEnableSmoothDots(void)
{
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

// Disable line aliasing
void rlDisableSmoothDots(void)
{
    glDisable(GL_POINT_SMOOTH);
}

// Draw a model dots
void DrawModelDots(Model model, Vector3 position, float scale, Color tint, int size, int dotType)
{
    (void)dotType;
    rlEnableDotMode(size);

    DrawModel(model, position, scale, tint);
    
    rlDisableDotMode();
}

// Draw a model dots with extended parameters
void DrawModelDotsEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint, int size, int dotType)
{
    rlEnableDotMode(size);
    if (dotType == 1) { rlEnableSmoothDots(); }
    
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, ColorAlpha(tint,0.9));
    
    if (dotType == 1) { rlDisableSmoothDots(); }
    rlDisableDotMode();
}

// Draw a model wires dashed with extended parameters
void DrawModelDashedWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
{
    rlEnableDashedMode();
    
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, ColorAlpha(tint,0.9));
    
    rlDisableDashedMode();
}
