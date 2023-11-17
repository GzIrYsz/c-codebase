#pragma once

#include <stdbool.h>

#include "types.h"

bool cg_line_is_invisible(uint8_t p0_code, uint8_t pn_code);

void cg_line_clipping(cg_point_f_t *p0, cg_point_f_t *pn, cg_clipping_area_f_t clipping_area, void (*draw_line)(cg_point_f_t*, cg_point_f_t*));