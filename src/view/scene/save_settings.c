#include "../../s21_3d_viewer.h"
struct settings {
  char filename[512];
  unsigned char bg_color_r;
  unsigned char bg_color_g;
  unsigned char bg_color_b;
  unsigned char bg_color_a;
  int projection;
  float position_x;
  float position_y;
  float position_z;
  float rotation_x;
  float rotation_y;
  float rotation_z;
  float scale_x;
  float scale_y;
  float scale_z;
  bool vertices_visible;
  int vertices_type;
  float vertices_size;
  unsigned char vertices_color_r;
  unsigned char vertices_color_g;
  unsigned char vertices_color_b;
  unsigned char vertices_color_a;
  bool wires_visible;
  int wires_type;
  float wires_size;
  unsigned char wires_color_r;
  unsigned char wires_color_g;
  unsigned char wires_color_b;
  unsigned char wires_color_a;
  int edges_count;
};

void saveSettings(App *app) {
  struct settings setts = {0};
  setts.filename[0] = '\0';
  strcat(setts.filename, app->ui.uploadBtn.fileNameToLoad);
  setts.bg_color_r = app->settings.bgColor.r;
  setts.bg_color_g = app->settings.bgColor.g;
  setts.bg_color_b = app->settings.bgColor.b;
  setts.bg_color_a = app->settings.bgColor.a;
  setts.projection = app->scene.camera.projection;
  setts.position_x = app->scene.model.position.x;
  setts.position_y = app->scene.model.position.y;
  setts.position_z = app->scene.model.position.z;
  setts.rotation_x = app->scene.model.rotation.x;
  setts.rotation_y = app->scene.model.rotation.y;
  setts.rotation_z = app->scene.model.rotation.z;
  setts.scale_x = app->scene.model.scale.x;
  setts.scale_y = app->scene.model.scale.y;
  setts.scale_z = app->scene.model.scale.z;
  setts.vertices_visible = app->scene.model.vertices.visible;
  setts.vertices_type = app->scene.model.vertices.viewType;
  setts.vertices_size = app->scene.model.vertices.size;
  setts.vertices_color_r = app->scene.model.vertices.color.r;
  setts.vertices_color_g = app->scene.model.vertices.color.g;
  setts.vertices_color_b = app->scene.model.vertices.color.b;
  setts.vertices_color_a = app->scene.model.vertices.color.a;
  setts.wires_visible = app->scene.model.wires.visible;
  setts.wires_type = app->scene.model.wires.viewType;
  setts.wires_size = app->scene.model.wires.size;
  setts.wires_color_r = app->scene.model.wires.color.r;
  setts.wires_color_g = app->scene.model.wires.color.g;
  setts.wires_color_b = app->scene.model.wires.color.b;
  setts.wires_color_a = app->scene.model.wires.color.a;
  setts.edges_count = app->scene.model.edgeCount;

  FILE *outfile;
  outfile = fopen("settings.dat", "wb");
  if (outfile == NULL) {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }
  fwrite(&setts, sizeof(struct settings), 1, outfile);
  fclose(outfile);
}

void LoadSettings(App *app) {
  (void)app;
  FILE *infile;
  struct settings setts;
  infile = fopen("settings.dat", "r");
  if (infile != NULL) {
    fread(&setts, sizeof(struct settings), 1, infile);
    // apply settings
    app->ui.uploadBtn.fileNameToLoad[0] = '\0';
    strcat(app->ui.uploadBtn.fileNameToLoad, setts.filename);
    app->scene.model.rModel = LoadModel(setts.filename);
    app->scene.model.edgeCount = setts.edges_count;
    app->settings.bgColor.r = setts.bg_color_r;
    app->settings.bgColor.g = setts.bg_color_g;
    app->settings.bgColor.b = setts.bg_color_b;
    app->settings.bgColor.a = setts.bg_color_a;
    app->scene.camera.projection = setts.projection;
    app->scene.model.position.x = setts.position_x;
    app->scene.model.position.y = setts.position_y;
    app->scene.model.position.z = setts.position_z;
    app->scene.model.rotation.x = setts.rotation_x;
    app->scene.model.rotation.y = setts.rotation_y;
    app->scene.model.rotation.z = setts.rotation_z;
    app->scene.model.scale.x = setts.scale_x;
    app->scene.model.scale.y = setts.scale_y;
    app->scene.model.scale.z = setts.scale_z;
    app->scene.model.vertices.visible = setts.vertices_visible;
    app->scene.model.vertices.viewType = setts.vertices_type;
    app->scene.model.vertices.size = setts.vertices_size;
    app->scene.model.vertices.color.r = setts.vertices_color_r;
    app->scene.model.vertices.color.g = setts.vertices_color_g;
    app->scene.model.vertices.color.b = setts.vertices_color_b;
    app->scene.model.vertices.color.a = setts.vertices_color_a;
    app->scene.model.wires.visible = setts.wires_visible;
    app->scene.model.wires.viewType = setts.wires_type;
    app->scene.model.wires.size = setts.wires_size;
    app->scene.model.wires.color.r = setts.wires_color_r;
    app->scene.model.wires.color.g = setts.wires_color_g;
    app->scene.model.wires.color.b = setts.wires_color_b;
    app->scene.model.wires.color.a = setts.wires_color_a;
    app->scene.model.edgeCount = setts.edges_count;
    fclose(infile);
  }
}

void DrawSaveSettings(App *app) { DrawSubmitButton(&app->ui.saveSettings); }

void UpdateSaveSettings(App *app) {
  if (CheckCollisionPointRec(GetMousePosition(), app->ui.saveSettings.area))
    app->ui.saveSettings.mouseOn = true;
  else
    app->ui.saveSettings.mouseOn = false;
  if (app->ui.saveSettings.mouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    printf("\n\nLET SAVE SETTINGS\n\n");
    saveSettings(app);
  }
}

void InitSaveSettings(App *app) {
  InitSubmitButton(&app->ui.saveSettings, (Rectangle){10, 10, 150, 32},
                   "Save settings", LIGHTGRAY, BLACK, 12);
}