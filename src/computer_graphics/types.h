#pragma once

#include <OpenGL/gl.h>

typedef struct {
    GLfloat x;
    GLfloat y;
} cg_point_f_t;

typedef struct {
    GLint x;
    GLint y;
} cg_point_i_t;

typedef struct {
    float m;
    float b;
} cg_linear_equ_params_t;

typedef struct {
    cg_point_f_t *top_left;
    cg_point_f_t *top_right;
    cg_point_f_t *bot_right;
    cg_point_f_t *bot_left;
} cg_clipping_area_f_t;

typedef struct {
    cg_point_i_t *top_left;
    cg_point_i_t *top_right;
    cg_point_i_t *bot_right;
    cg_point_i_t *bot_left;
} cg_clipping_area_i_t;

typedef struct {
    int max_vertices;
    cg_point_f_t **vertices;
    int nb_vertices;
} cg_polygon_f_t;