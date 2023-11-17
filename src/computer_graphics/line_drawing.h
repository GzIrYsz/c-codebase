#pragma once

#include "types.h"

void cg_draw_line_naive(cg_point_f_t *p0, cg_point_f_t *pn);
void cg_draw_line_incremental(cg_point_f_t *pi, cg_linear_equ_params_t *params, cg_point_f_t *p0, cg_point_f_t *pn);
void cg_draw_line_i(cg_point_i_t *p0, cg_point_i_t *pn);
void cg_draw_line_f(cg_point_f_t *p0, cg_point_f_t *pn);