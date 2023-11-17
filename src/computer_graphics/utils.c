#ifdef __APPLE__
    #include <OpenGL/gl.h>
#elif _WIN32
    #include <GL/gl.h>
#elif _linux
    #include <GL/gl.h>
#endif

#include <math.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

void cg_point_f_alloc(cg_point_f_t **p) {
    *p = malloc(sizeof(cg_point_f_t));
}

void cg_point_f_free(cg_point_f_t **p) {
    free(*p);
    *p = NULL;
}

void cg_point_f_init(cg_point_f_t *p) {
    p->x = 0;
    p->y = 0;
}

GLfloat cg_point_f_get_x(cg_point_f_t *p) {
    return p->x;
}

GLfloat cg_point_f_get_y(cg_point_f_t *p) {
    return p->y;
}

bool cg_point_f_equals(cg_point_f_t *p1, cg_point_f_t *p2) {
    return (p1 == p2) || ((cg_point_f_get_x(p1) == cg_point_f_get_x(p2)) && cg_point_f_get_y(p1) && cg_point_f_get_y(p2));
}

float cg_point_f_dist(cg_point_f_t *p1, cg_point_f_t *p2) {
    return sqrtf(powf(cg_line_calc_f_dx(p1, p2), 2) + powf(cg_line_calc_f_dy(p1, p2), 2));
}

void cg_point_i_alloc(cg_point_i_t **p) {
    *p = malloc(sizeof(cg_point_i_t));
}

void cg_point_i_free(cg_point_i_t **p) {
    free(*p);
    *p = NULL;
}

void cg_point_i_init(cg_point_i_t *p) {
    p->x = 0;
    p->y = 0;
}

GLint cg_point_i_get_x(cg_point_i_t *p) {
    return p->x;
}

GLint cg_point_i_get_y(cg_point_i_t *p) {
    return p->y;
}

bool cg_point_i_equals(cg_point_i_t *p1, cg_point_i_t *p2) {
    return (p1 == p2) || ((cg_point_i_get_x(p1) == cg_point_i_get_x(p2)) && cg_point_i_get_y(p1) && cg_point_i_get_y(p2));
}

float cg_point_i_dist(cg_point_i_t *p1, cg_point_i_t *p2) {
    return sqrtf(powf((float) cg_line_calc_i_dx(p1, p2), 2) + powf((float) cg_line_calc_i_dy(p1, p2), 2));
}

void cg_line_params_alloc(cg_linear_equ_params_t **params) {
    *params = malloc(sizeof(cg_linear_equ_params_t));
}

void cg_line_params_free(cg_linear_equ_params_t **params) {
    free(*params);
    *params = NULL;
}

void cg_line_params_init(cg_linear_equ_params_t *params) {
    params->m = 1;
    params->b = 0;
}

float cg_line_params_get_m(cg_linear_equ_params_t *params) {
    return params->m;
}

float cg_line_params_get_b(cg_linear_equ_params_t *params) {
    return params->b;
}

void cg_draw_point_f(cg_point_f_t *p) {
    cg_draw_pixel_f(cg_point_f_get_x(p), cg_point_f_get_y(p));
}

void cg_draw_pixel_f(GLfloat x, GLfloat y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void cg_draw_point_i(cg_point_i_t *p) {
    cg_draw_pixel_i(cg_point_i_get_x(p), cg_point_i_get_y(p));
}

void cg_draw_pixel_i(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

float cg_line_calc_f_dx(cg_point_f_t *p1, cg_point_f_t *p2) {
    return cg_point_f_get_x(p2) - cg_point_f_get_x(p1);
}

float cg_line_calc_f_dy(cg_point_f_t *p1, cg_point_f_t *p2) {
    return cg_point_f_get_y(p2) - cg_point_f_get_y(p1);
}

int cg_line_calc_i_dx(cg_point_i_t *p1, cg_point_i_t *p2) {
    return cg_point_i_get_x(p2) - cg_point_i_get_x(p1);
}

int cg_line_calc_i_dy(cg_point_i_t *p1, cg_point_i_t *p2) {
    return cg_point_i_get_y(p2) - cg_point_i_get_y(p1);
}

void cg_line_calc_m(cg_linear_equ_params_t *params, cg_point_f_t *p1, cg_point_f_t *p2) {
    params->m = cg_line_calc_f_dy(p1, p2) / cg_line_calc_f_dx(p1, p2);
}

void cg_line_calc_b(cg_linear_equ_params_t *params, cg_point_f_t *p1, cg_point_f_t *p2) {
    params->b = cg_point_f_get_y(p1) - cg_line_params_get_m(params) * cg_point_f_get_x(p1);
}

void cg_line_calc_y_from_x(cg_point_f_t *pi, cg_linear_equ_params_t *params, cg_point_f_t *p0, cg_point_f_t *pn) {
    pi->y = cg_line_params_get_m(params) * cg_point_f_get_x(pi) + cg_line_params_get_b(params);
}

void cg_line_calc_x_from_y(cg_point_f_t *pi, cg_linear_equ_params_t *params, cg_point_f_t *p0, cg_point_f_t *pn) {
    pi->x = (cg_point_f_get_y(pi) - cg_line_params_get_b(params)) / cg_line_params_get_m(params);
}

cg_point_f_t* cg_clipping_area_f_get_tl(cg_clipping_area_f_t *clipping_area) {
    return clipping_area->top_left;
}

cg_point_f_t* cg_clipping_area_f_get_tr(cg_clipping_area_f_t *clipping_area) {
    return clipping_area->top_right;
}

cg_point_f_t* cg_clipping_area_f_get_bl(cg_clipping_area_f_t *clipping_area) {
    return clipping_area->bot_left;
}

cg_point_f_t* cg_clipping_area_f_get_br(cg_clipping_area_f_t *clipping_area) {
    return clipping_area->bot_right;
}

cg_point_i_t* cg_clipping_area_i_get_tl(cg_clipping_area_i_t *clipping_area) {
    return clipping_area->top_left;
}

cg_point_i_t* cg_clipping_area_i_get_tr(cg_clipping_area_i_t *clipping_area) {
    return clipping_area->top_right;
}

cg_point_i_t* cg_clipping_area_i_get_bl(cg_clipping_area_i_t *clipping_area) {
    return clipping_area->bot_left;
}

cg_point_i_t* cg_clipping_area_i_get_br(cg_clipping_area_i_t *clipping_area) {
    return clipping_area->bot_right;
}

void cg_polygon_f_alloc(int max_vertices, cg_polygon_f_t **polygon) {
    *polygon = (cg_polygon_f_t*) malloc(sizeof(cg_polygon_f_t));
    (*polygon)->max_vertices = max_vertices;
    (*polygon)->vertices = (cg_point_f_t**) malloc(max_vertices * sizeof(cg_point_f_t*));
}

void cg_polygon_f_free(cg_polygon_f_t **polygon) {
    free((*polygon)->vertices); // TODO : Verifier si PB de pointer
    free(*polygon);
    *polygon = NULL;
}

void cg_polygon_f_init(cg_polygon_f_t *polygon) {
    polygon->nb_vertices = 0;
}

int cg_polygon_f_get_max_vertices(cg_polygon_f_t *polygon) {
    return polygon->max_vertices;
}

int cg_polygon_f_get_nb_vertices(cg_polygon_f_t *polygon) {
    return polygon->nb_vertices;
}

cg_point_f_t** cg_polygon_f_get_vertices(cg_polygon_f_t *polygon) {
    return polygon->vertices;
}

cg_point_f_t* cg_polygon_f_get_vertice(int i, cg_polygon_f_t *polygon) {
    return polygon->vertices[i];
}