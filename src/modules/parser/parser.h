#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_FACES_PER_F_LINE (16)
#define HASH_TABLE_DEFAULT_SIZE 10
#define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0') < (unsigned int)(10))
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

typedef struct { int v_idx; } vertex_index_t;

typedef struct {
  unsigned int num_vertices;
  unsigned int num_faces;
  unsigned int num_face_num_verts;
  int pad0;
  float *vertices;
  vertex_index_t *faces;
  int *face_num_verts;
} Obj;

typedef enum {
  COMMAND_EMPTY,
  COMMAND_V,
  COMMAND_F,
} CommandType;

typedef struct {
  float vx, vy, vz;
  vertex_index_t f[MAX_FACES_PER_F_LINE];
  unsigned int num_f;
  int f_num_verts[MAX_FACES_PER_F_LINE];
  unsigned int num_f_num_verts;
  CommandType type;
} Command;

typedef struct {
  unsigned int pos;
  unsigned int len;
} LineInfo;

// helpers
int is_line_ending(const char *p, unsigned int i, unsigned int end_i);
void skip_space(const char **token);
void skip_space_and_cr(const char **token);
int until_space(const char *token);
int tryParseDouble(const char *s, const char *s_end, double *result);
float parseFloat(const char **token);
void parseFloat2(float *x, float *y, const char **token);
void parseFloat3(float *x, float *y, float *z, const char **token);
int my_atoi(const char *c);
int fixIndex(int idx, unsigned int n);

// Parse
Obj ParseObj(const char *fileName);
void UnloadObj(Obj *obj);

#endif  // __PARSER_H
