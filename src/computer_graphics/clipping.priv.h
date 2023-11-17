#pragma once

#include <stdbool.h>

#include "types.h"

void cg_point_f_is_out_top(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tl, cg_point_f_t *tr);
void cg_point_f_is_out_bot(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *bl, cg_point_f_t *br);
void cg_point_f_is_out_left(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tl, cg_point_f_t *bl);
void cg_point_f_is_out_right(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tr, cg_point_f_t *br);

void cg_point_i_is_out_top(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tl, cg_point_i_t *tr);
void cg_point_i_is_out_bot(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *bl, cg_point_i_t *br);
void cg_point_i_is_out_left(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tl, cg_point_i_t *bl);
void cg_point_i_is_out_right(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tr, cg_point_i_t *br);

void cg_point_f_clipping_calc_code(uint8_t *point_code, cg_point_f_t *p, cg_clipping_area_f_t clipping_area);