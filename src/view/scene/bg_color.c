#include "../../s21_3d_viewer.h"

static void drawPanel() {
    int width = TRANSFORM_PANEL_WIDTH;
    int height = 85;
    int left = GetScreenWidth() - 30 - (width + width + width);
    int top = 5;
    DrawRectangle(left, top, width, height, Fade(LIGHTGRAY, 0.4f));
    DrawRectangleLines(left, top, width, height, Fade(LIGHTGRAY, 0.8f));
    DrawText("BACKGROUND", left + 5, top + 5, 14, BLACK);
}


void DrawBgColor(App *app) {
    drawPanel();
    DrawSubmitButton(&app->ui.bgColorPurple);
    DrawSubmitButton(&app->ui.bgColorLavender);
    DrawSubmitButton(&app->ui.bgColorRose);
    DrawSubmitButton(&app->ui.bgColorBeige);
    DrawSubmitButton(&app->ui.bgColorWhite);
}

void paintBg(App *app, SubmitButton btn, Color color) {
    if (CheckCollisionPointRec(GetMousePosition(), btn.area))
        btn.mouseOn = true;
    else
        btn.mouseOn = false;
    if (btn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        app->settings.bgColor = color;
    }
}

void UpdateBgColor(App *app) {
    paintBg(app, app->ui.bgColorPurple, (Color) {247, 222, 246, 255});
    paintBg(app, app->ui.bgColorLavender, (Color) {223, 227, 247, 255});
    paintBg(app, app->ui.bgColorRose, (Color) {247, 228, 223, 255});
    paintBg(app, app->ui.bgColorBeige, (Color) {237, 247, 223, 255});
    paintBg(app, app->ui.bgColorWhite, RAYWHITE);
}

void InitBgColor(App *app) {
    // default
    app->settings.bgColor = RAYWHITE;

    int inputTextWidth = 100;
    int inputTextTop = 40;
    int padd = 470;
    InitSubmitButton(&app->ui.bgColorPurple, (Rectangle){ GetScreenWidth() - inputTextWidth - padd, inputTextTop, 24, 24 }, "1", (Color) {247, 222, 246, 255}, BLACK, 12);
    InitSubmitButton(&app->ui.bgColorLavender, (Rectangle){ GetScreenWidth() - inputTextWidth - padd + 26, inputTextTop, 24, 24 }, "2", (Color) {223, 227, 247, 255}, BLACK, 12);
    InitSubmitButton(&app->ui.bgColorRose, (Rectangle){ GetScreenWidth() - inputTextWidth - padd + 52, inputTextTop, 24, 24 }, "3", (Color) {247, 228, 223, 255}, BLACK, 12);
    InitSubmitButton(&app->ui.bgColorBeige, (Rectangle){ GetScreenWidth() - inputTextWidth - padd + 78, inputTextTop, 24, 24 }, "4", (Color) {237, 247, 223, 255}, BLACK, 12);
    InitSubmitButton(&app->ui.bgColorWhite, (Rectangle){ GetScreenWidth() - inputTextWidth - padd + 104, inputTextTop, 24, 24 }, "5", RAYWHITE, BLACK, 12);
}