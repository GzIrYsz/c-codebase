#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#elif _WIN32
    #include <GL/gl.h>
#elif _linux
    #include <GL/gl.h>
#endif

#include <stdbool.h>

#include "types.h"

void cg_point_f_alloc(cg_point_f_t **p);
void cg_point_f_free(cg_point_f_t **p);
void cg_point_f_init(cg_point_f_t *p);
GLfloat cg_point_f_get_x(cg_point_f_t *p);
GLfloat cg_point_f_get_y(cg_point_f_t *p);
bool cg_point_f_equals(cg_point_f_t *p1, cg_point_f_t *p2);
float cg_point_f_dist(cg_point_f_t *p1, cg_point_f_t *p2);

void cg_point_i_alloc(cg_point_i_t **p);
void cg_point_i_free(cg_point_i_t **p);
void cg_point_i_init(cg_point_i_t *p);
GLint cg_point_i_get_x(cg_point_i_t *p);
GLint cg_point_i_get_y(cg_point_i_t *p);
bool cg_point_i_equals(cg_point_i_t *p1, cg_point_i_t *p2);
float cg_point_i_dist(cg_point_i_t *p1, cg_point_i_t *p2);

void cg_line_params_alloc(cg_linear_equ_params_t **params);
void cg_line_params_free(cg_linear_equ_params_t **params);
void cg_line_params_init(cg_linear_equ_params_t *params);
float cg_line_params_get_m(cg_linear_equ_params_t *params);
float cg_line_params_get_b(cg_linear_equ_params_t *params);

void cg_draw_point_f(cg_point_f_t *p);
void cg_draw_pixel_f(GLfloat x, GLfloat y);
void cg_draw_point_i(cg_point_i_t *p);
void cg_draw_pixel_i(GLint x, GLint y);

float cg_line_calc_f_dx(cg_point_f_t *p1, cg_point_f_t *p2);
float cg_line_calc_f_dy(cg_point_f_t *p1, cg_point_f_t *p2);
int cg_line_calc_i_dx(cg_point_i_t *p1, cg_point_i_t *p2);
int cg_line_calc_i_dy(cg_point_i_t *p1, cg_point_i_t *p2);
void cg_line_calc_m(cg_linear_equ_params_t *params, cg_point_f_t *p1, cg_point_f_t *p2);
void cg_line_calc_b(cg_linear_equ_params_t *params, cg_point_f_t *p1, cg_point_f_t *p2);
void cg_line_calc_y_from_x(cg_point_f_t *pi, cg_linear_equ_params_t *params, cg_point_f_t *p0, cg_point_f_t *pn);
void cg_line_calc_x_from_y(cg_point_f_t *pi, cg_linear_equ_params_t *params, cg_point_f_t *p0, cg_point_f_t *pn);

cg_point_f_t* cg_clipping_area_f_get_tl(cg_clipping_area_f_t *clipping_area);
cg_point_f_t* cg_clipping_area_f_get_tr(cg_clipping_area_f_t *clipping_area);
cg_point_f_t* cg_clipping_area_f_get_bl(cg_clipping_area_f_t *clipping_area);
cg_point_f_t* cg_clipping_area_f_get_br(cg_clipping_area_f_t *clipping_area);

cg_point_i_t* cg_clipping_area_i_get_tl(cg_clipping_area_i_t *clipping_area);
cg_point_i_t* cg_clipping_area_i_get_tr(cg_clipping_area_i_t *clipping_area);
cg_point_i_t* cg_clipping_area_i_get_bl(cg_clipping_area_i_t *clipping_area);
cg_point_i_t* cg_clipping_area_i_get_br(cg_clipping_area_i_t *clipping_area);

void cg_polygon_f_alloc(int max_vertices, cg_polygon_f_t **polygon);
void cg_polygon_f_free(cg_polygon_f_t **polygon);
void cg_polygon_f_init(cg_polygon_f_t *polygon);
int cg_polygon_f_get_max_vertices(cg_polygon_f_t *polygon);
int cg_polygon_f_get_nb_vertices(cg_polygon_f_t *polygon);
cg_point_f_t** cg_polygon_f_get_vertices(cg_polygon_f_t *polygon);
cg_point_f_t* cg_polygon_f_get_vertice(int i, cg_polygon_f_t *polygon);