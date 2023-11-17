#pragma once

#include <stdbool.h>

#include "types.h"

typedef cg_clipping_area_f_t cg_polygon_filling_surrounding_rect_f_t;

void cg_polygon_filling_f_calc_surrounding_rect(cg_polygon_f_t *polygon, cg_polygon_filling_surrounding_rect_f_t *surrounding_rect);
bool cg_polygon_filling_f_point_inside(cg_point_f_t *p, cg_polygon_f_t *polygon);