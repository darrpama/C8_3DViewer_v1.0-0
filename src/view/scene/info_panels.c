#include "../../s21_3d_viewer.h"

void drawHelpInfo() {
  DrawRectangle(20, 110, 320, 133, Fade(SKYBLUE, 0.3f));
  DrawRectangleLines( 20, 110, 320, 133, BLUE);
  DrawText("Free camera default controls:", 30, 120, 10, BLACK);
  DrawText("- Mouse Wheel to Zoom in-out", 40, 140, 10, DARKGRAY);
  DrawText("- Mouse Wheel Pressed to Pan", 40, 160, 10, DARKGRAY);
  DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 180, 10, DARKGRAY);
  DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 200, 10, DARKGRAY);
  DrawText("- Z to zoom to (0, 0, 0)", 40, 220, 10, DARKGRAY);
}

void drawCameraInfo(App *app) {
  (void)app;
  DrawRectangle(20, 260, 320, 133, Fade(SKYBLUE, 0.3f));
  DrawRectangleLines( 20, 260, 320, 133, BLUE);
  
  DrawText("Camera position:", 30, 250+20, 14, BLACK);
  char position[256];
  sprintf(position, " x:%f; y:%f; z:%f", app->scene.camera.position.x, app->scene.camera.position.y, app->scene.camera.position.z);
  DrawText(position, 40, 250+40, 12, DARKGRAY);

  DrawText("Camera target", 30, 250+60, 14, BLACK);
  char target[256];
  sprintf(target, " x:%f; y:%f; z:%f", app->scene.camera.target.x, app->scene.camera.target.y, app->scene.camera.target.z);
  DrawText(target, 40, 250+80, 12, DARKGRAY);

  DrawText("Camera up", 30, 250+100, 14, DARKGRAY);
  char up[256];
  sprintf(up, " x:%f; y:%f; z:%f", app->scene.camera.up.x, app->scene.camera.up.y, app->scene.camera.up.z);
  DrawText(up, 40, 250+120, 10, DARKGRAY);
}

void drawFileInfo(App *app) {
  int left = 20;
  int top = 410;
  DrawRectangle(left, top, 320, 133, Fade(SKYBLUE, 0.3f));
  DrawRectangleLines(left, top, 320, 133, BLUE);
  DrawText("Uploaded File information:", 30, top + 10, 10, BLACK);
  DrawText("FILENAME:", 108, top + 30, 10, DARKGRAY);
  DrawText(basename(app->ui.uploadBtn.fileNameToLoad), 170, top + 28, 14, BLACK);
  
  DrawText("NUMBER OF VERTICES:", 40, top + 50, 10, DARKGRAY);
  char vertices[64];
  vertices[0] = '\0';
  sprintf(vertices, "%d", app->scene.model.rModel.vertexCount);
  DrawText(vertices, 170, top + 48, 14, BLACK);
  
  DrawText("NUMBER OF EDGES:", 59, top + 70, 10, DARKGRAY);
  char edges[64];
  edges[0] = '\0';
  sprintf(edges, "%d", app->scene.model.edgeCount);
  DrawText(edges, 170, top + 68, 14, BLACK);
}

void DrawInfo(App *app) {
  DrawFPS(GetScreenWidth()-100, GetScreenHeight()-25);
  drawHelpInfo();
  drawCameraInfo(app);
  drawFileInfo(app);
}
