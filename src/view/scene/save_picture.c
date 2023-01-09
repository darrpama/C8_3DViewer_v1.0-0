#include "../../s21_3d_viewer.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include "../../libs/stb/stb_image.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "../../libs/stb/stb_image_write.h"
static int screenshotCounter = 0;

void savePicHandler(App *app) {
  // int x, y, n;
  SavePic(app, ".jpg");
  // app->scene.camera.fovy += 0.01f;
  // int out_w = APP_SCREEN_WIDTH;
  // int out_h = APP_SCREEN_HEIGHT;
  // unsigned char *out_data = rlReadScreenPixels(out_w, out_h);
  // // unsigned char *out_data = stbi_load("screenshot000.png", &x, &y, &n, 3);
  // if (out_data != NULL) {
  //   // stbi_write_jpg("aboba.jpg", out_w, out_h, 3, out_data, out_w * sizeof(int));
  //   // stbi_write_bmp("aboba.bmp", out_w, out_h, 3, out_data);
  //   // stbi_image_free(data);
  //   ExportImage
  //   free(out_data);
  // }
}

void savePicButtonHandler(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.saveGifBtn.area))
    app->ui.saveGifBtn.mouseOn = true;
  else
    app->ui.saveGifBtn.mouseOn = false;
  if (app->ui.saveGifBtn.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    savePicHandler(app);
  }
}

void DrawSavePicButton(App *app) {
  DrawIconButton(&app->ui.saveGifBtn);
}

void UpdateSavePicButton(App *app) {
  // savePicHandler(app);
  savePicButtonHandler(app);
}

void InitSavePicButton(App *app) {
  Texture2D icon = LoadTexture("./assets/icons/upload.png");
  InitIconButton(
    icon,
    &app->ui.saveGifBtn,
    (Rectangle){20, APP_SCREEN_HEIGHT - 84 - 84, 64, 64},
    ColorBrightness(SKYBLUE, -0.1)
  );
}

void SavePic(App *app, char *extention) {
  /* Need to add function to hide ui here */
    Image image = LoadImageFromScreen();
    app->scene.camera.fovy += 0.01;
    app->scene.camera.fovy -= 0.01;
    char filename[20];
    sprintf(filename, "screenshot%d", screenshotCounter);
    screenshotCounter++;
    strncat(filename, extention, 5);

    // unsigned char *imgData = rlReadScreenPixels(APP_SCREEN_HEIGHT, APP_SCREEN_WIDTH);
    // Image image = {imgData, APP_SCREEN_HEIGHT, APP_SCREEN_WIDTH, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    ExportImage(image, filename);
    // free(imgData);
}