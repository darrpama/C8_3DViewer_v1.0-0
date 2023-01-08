#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

char *LoadObjFileText(const char *fileName) {
    char *text = NULL;
    FILE *file = fopen(fileName, "rt");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        unsigned int size = (unsigned int)ftell(file);
        fseek(file, 0, SEEK_SET);
        if (size > 0) {
            text = (char *) malloc((size + 1)*sizeof(char));
            unsigned int count = (unsigned int)fread(text, sizeof(char), size, file);
            if (count < size) text = realloc(text, count + 1);
            text[count] = '\0';
            printf("FILEIO: [%s] Text file loaded successfully\n", fileName);
        } else {
            printf("FILEIO: [%s] Failed to read text file\n", fileName);
        }
        fclose(file);
    }
    return text;
}

vertex_index_t parseRawTriple(const char **token) {
    vertex_index_t vi;
    vi.v_idx = (int)(0x80000000);

    vi.v_idx = my_atoi((*token));
    while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
            (*token)[0] != '\t' && (*token)[0] != '\r') {
        (*token)++;
    }
    if ((*token)[0] != '/') {
        return vi;
    }
    (*token)++;
    if ((*token)[0] == '/') {
        (*token)++;
        while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
            (*token)[0] != '\t' && (*token)[0] != '\r') {
            (*token)++;
        }
        return vi;
    }
    while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
            (*token)[0] != '\t' && (*token)[0] != '\r') {
        (*token)++;
    }
    if ((*token)[0] != '/') {
        return vi;
    }
    (*token)++; /* skip '/' */
    while ((*token)[0] != '\0' && (*token)[0] != '/' && (*token)[0] != ' ' &&
            (*token)[0] != '\t' && (*token)[0] != '\r') {
        (*token)++;
    }
    return vi;
}

int parseLine(Command *command, const char *p, unsigned int p_len) {
    char linebuf[4096];
    const char *token;
    assert(p_len < 4095);
    memcpy(linebuf, p, p_len);
    linebuf[p_len] = '\0';
    token = linebuf;
    command->type = COMMAND_EMPTY;
    skip_space(&token);

    assert(token);
    if (token[0] == '\0') { return 0; }
    if (token[0] == '#') { return 0; }
    
    /* vertex */
    if (token[0] == 'v' && IS_SPACE((token[1]))) {
        float x, y, z;
        token += 2;
        parseFloat3(&x, &y, &z, &token);
        command->vx = x;
        command->vy = y;
        command->vz = z;
        command->type = COMMAND_V;
        return 1;
    }

    /* face */
    if (token[0] == 'f' && IS_SPACE((token[1]))) {
        unsigned int num_f = 0;
        vertex_index_t f[MAX_FACES_PER_F_LINE];
        token += 2;
        skip_space(&token);

        while (!IS_NEW_LINE(token[0])) {
            vertex_index_t vi = parseRawTriple(&token);
            skip_space_and_cr(&token);
            f[num_f] = vi;
            num_f++;
        }

        command->type = COMMAND_F;
        
        unsigned int k = 0;
        assert(num_f < MAX_FACES_PER_F_LINE);
        for (k = 0; k < num_f; k++) {
            command->f[k] = f[k];
        }

        command->num_f = num_f;
        command->f_num_verts[0] = (int)num_f;
        command->num_f_num_verts = 1;

        return 1;
    }

    return 0;
}

static void attrib_init(Obj *attrib) {
    attrib->vertices = NULL;
    attrib->num_vertices = 0;
    attrib->faces = NULL;
    attrib->num_faces = 0;
    attrib->face_num_verts = NULL;
    attrib->num_face_num_verts = 0;
}

static int parse_obj_attr(Obj *attrib, const char *fileText, unsigned int dataSize) {
    // count of lines
    unsigned int i;
    unsigned int num_lines = 0;
    unsigned int last_line_ending = 0;
    for (i = 0; i < dataSize; i++) {
        if (is_line_ending(fileText, i, dataSize)) {
            num_lines++;
            last_line_ending = i;
        }
    }
    (void) last_line_ending;
    // fill line infos
    LineInfo *line_infos = NULL;
    line_infos = (LineInfo *) malloc(sizeof(LineInfo) * num_lines);
    unsigned int line_no = 0;
    unsigned int prev_pos = 0;
    for (i = 0; i < dataSize; i++) {
        if (is_line_ending(fileText, i, dataSize)) {
            line_infos[line_no].pos = prev_pos;
            line_infos[line_no].len = i - prev_pos;
            prev_pos = i + 1;
            line_no++;
        }
    }

    Command *commands = NULL;
    commands = (Command *)malloc(sizeof(Command) * num_lines);

    // parse each line
    unsigned int num_v = 0;
    unsigned int num_f = 0;
    unsigned int num_faces = 0;

    for (i = 0; i < num_lines; i++) {
        int ret = parseLine(&commands[i], &fileText[line_infos[i].pos], line_infos[i].len);
        // printf("ret=%d; i=%u\n", ret, i);
        if (ret) {
            if (commands[i].type == COMMAND_V) {
                num_v++;
            } else if (commands[i].type == COMMAND_F) {
                num_f += commands[i].num_f;
                num_faces += commands[i].num_f_num_verts;
            }
        }
    }

    // line_infos are not used anymore
    if (line_infos) {
        free(line_infos);
    }

    // construct attributes
    attrib_init(attrib);
    unsigned int v_count = 0;
    unsigned int f_count = 0;
    unsigned int face_count = 0;
    i = 0;
    
    attrib->vertices = (float *) malloc(sizeof(float) * num_v * 3);
    attrib->num_vertices = (unsigned int)num_v;
    attrib->faces = (vertex_index_t *) malloc(sizeof(vertex_index_t) * num_f);
    attrib->face_num_verts = (int *) malloc(sizeof(int) * num_faces);
    
    attrib->num_faces = (unsigned int)num_faces;
    attrib->num_face_num_verts = (unsigned int)num_f;

    for (i = 0; i < num_lines; i++) {
        if (commands[i].type == COMMAND_EMPTY) {
            continue;
        } else if (commands[i].type == COMMAND_V) {
            attrib->vertices[3 * v_count + 0] = commands[i].vx;
            attrib->vertices[3 * v_count + 1] = commands[i].vy;
            attrib->vertices[3 * v_count + 2] = commands[i].vz;
            v_count++;
        } else if (commands[i].type == COMMAND_F) {
            unsigned int k = 0;
            for (k = 0; k < commands[i].num_f; k++) {
                vertex_index_t vi = commands[i].f[k];
                int v_idx = fixIndex(vi.v_idx, v_count);
                attrib->faces[f_count + k].v_idx = v_idx;
            }
            for (k = 0; k < commands[i].num_f_num_verts; k++) {
                attrib->face_num_verts[face_count + k] = commands[i].f_num_verts[k];
            }
            f_count += commands[i].num_f;
            face_count += commands[i].num_f_num_verts;
        }
    }
    // commands free
    if (commands) {
        free(commands);
    }
    return 0;
}

// Obj need to free manually
Obj ParseObj(const char *fileName) {
    char *fileText = LoadObjFileText(fileName);
    Obj attrib = { 0 };
    unsigned int dataSize = (unsigned int)strlen(fileText);
    parse_obj_attr(&attrib, fileText, dataSize);
    // free fileText
    free(fileText);
    return attrib;
}

void UnloadObj(Obj *obj) {
    if (obj->vertices) free(obj->vertices);
    if (obj->faces) free(obj->faces);
    if (obj->face_num_verts) free(obj->face_num_verts);
}

unsigned intConcat(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

int compare(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

int numPlaces (int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

int GetEdgesCount(const char *fileName) {
    Obj obj = ParseObj(fileName);
    int k = 0;
    int a = 0;
    int b = 0;

    char **edges;
    edges = malloc((obj.num_face_num_verts) * sizeof(char *));
    
    int numSize = 0;

    for (unsigned int i = 0; i < obj.num_faces; i++)
    {
        for (int j = 0; j < obj.face_num_verts[i]; j++)
        {
            a = obj.faces[k].v_idx + 1;
            if (j == obj.face_num_verts[i] -1) {
                b = obj.faces[k - j].v_idx + 1;
            } else {
                b = obj.faces[k + 1].v_idx + 1;
            }

            numSize = numPlaces(a) + numPlaces(b);
            edges[k] = malloc(numSize * sizeof(char));
            char str_num[numSize+1];
            if (a < b) {
                sprintf(str_num, "%d%d", a, b);
            } else {
                sprintf(str_num, "%d%d", b, a);
            }
            strcpy(edges[k], str_num);
            str_num[0] = '\0';
            k++;
        }
    }
    int n = obj.num_face_num_verts;
    qsort(edges, n, sizeof(edges[0]), compare);
    char *current = edges[0];
    int count = 1;
    for (int i = 1; i < n; i++)
    {
        if (strcmp(edges[i], current) != 0)
        {
            current = edges[i];
            count++;
        }
    }    
    return count;
}
