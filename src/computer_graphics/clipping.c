#include <stdbool.h>

#include "clipping.h"
#include "clipping.priv.h"
#include "utils.h"

void cg_point_f_is_out_top(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tl, cg_point_f_t *tr) {
//    cg_linear_equ_params_t *params;
//    cg_point_f_t *test_p;
//    cg_line_params_alloc(&params);
//    cg_point_f_alloc(&test_p);
//
//    cg_line_calc_m(params, tl, tr);
//    cg_line_calc_b(params, tl, tr);
//
//    test_p->x = cg_point_f_get_x(p);
//
//    cg_line_calc_y_from_x(test_p, params, tl, tr);
//
//    if (cg_point_f_get_y(p) < cg_point_f_get_y(test_p)) {
//        *point_code |= 1 << 3;
//    }
    if (cg_point_f_get_y(p) < cg_point_f_get_y(tl)) {
        *point_code |= 1 << 3;
    }
}

void cg_point_f_is_out_bot(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *bl, cg_point_f_t *br) {
//    cg_linear_equ_params_t *params;
//    cg_point_f_t *test_p;
//    cg_line_params_alloc(&params);
//    cg_point_f_alloc(&test_p);
//
//    cg_line_calc_m(params, bl, br);
//    cg_line_calc_b(params, bl, br);
//
//    test_p->x = cg_point_f_get_x(p);
//
//    cg_line_calc_y_from_x(test_p, params, bl, br);
//
//    if (cg_point_f_get_y(p) > cg_point_f_get_y(test_p)) {
//        *point_code |= 1 << 2;
//    }
    if (cg_point_f_get_y(p) > cg_point_f_get_y(bl)) {
        *point_code |= 1 << 2;
    }
}

void cg_point_f_is_out_left(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tl, cg_point_f_t *bl) {
    if (cg_point_f_get_x(p) < cg_point_f_get_x(tl)) {
        *point_code |= 1;
    }
}

void cg_point_f_is_out_right(uint8_t *point_code, cg_point_f_t *p, cg_point_f_t *tr, cg_point_f_t *br) {
    if (cg_point_f_get_x(p) > cg_point_f_get_x(tr)) {
        *point_code |= 1 << 1;
    }
}

void cg_point_i_is_out_top(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tl, cg_point_i_t *tr);
void cg_point_i_is_out_bot(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *bl, cg_point_i_t *br);
void cg_point_i_is_out_left(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tl, cg_point_i_t *bl);
void cg_point_i_is_out_right(uint8_t *point_code, cg_point_i_t *p, cg_point_i_t *tr, cg_point_i_t *br);

void cg_point_f_clipping_calc_code(uint8_t *point_code, cg_point_f_t *p, cg_clipping_area_f_t clipping_area) {
    *point_code = 0;

    cg_point_f_is_out_top(point_code, p, cg_clipping_area_f_get_tl(&clipping_area), cg_clipping_area_f_get_tr(&clipping_area));
    cg_point_f_is_out_bot(point_code, p, cg_clipping_area_f_get_bl(&clipping_area), cg_clipping_area_f_get_br(&clipping_area));
    cg_point_f_is_out_left(point_code, p, cg_clipping_area_f_get_tl(&clipping_area), cg_clipping_area_f_get_bl(&clipping_area));
    cg_point_f_is_out_right(point_code, p, cg_clipping_area_f_get_tr(&clipping_area), cg_clipping_area_f_get_br(&clipping_area));
}

bool cg_line_is_invisible(uint8_t p0_code, uint8_t pn_code) {
    return (p0_code & pn_code) != 0;
}

bool cg_line_is_totally_visible(uint8_t p0_code, uint8_t pn_code) {
    return (p0_code == 0) && (pn_code == 0);
}

void cg_line_clipping(cg_point_f_t *p0, cg_point_f_t *pn, cg_clipping_area_f_t clipping_area, void (*draw_line)(cg_point_f_t*, cg_point_f_t*)) {
    uint8_t p0_code, pn_code;
    bool end, is_visible;
    cg_linear_equ_params_t *params;

    cg_point_f_clipping_calc_code(&p0_code, p0, clipping_area);
    cg_point_f_clipping_calc_code(&pn_code, pn, clipping_area);

    cg_line_params_alloc(&params);

    cg_line_calc_m(params, p0, pn);
    cg_line_calc_b(params, p0, pn);

    end = false;
    is_visible = false;

    do {
        if (cg_line_is_totally_visible(p0_code, pn_code)) {
            is_visible = true;
            end = true;
        } else if (cg_line_is_invisible(p0_code, pn_code)) {
            end = true;
        } else {
            uint8_t out_code;
            out_code = p0_code;
            cg_point_f_t *tmp;

            cg_point_f_alloc(&tmp);

            if (p0_code == 0) {
                out_code = pn_code;
            }

            if (out_code == (out_code | 1 << 3)) {
                tmp->y = cg_point_f_get_y(cg_clipping_area_f_get_tl(&clipping_area));
                cg_line_calc_x_from_y(tmp, params, p0, pn);
            } else if (out_code == (out_code | 1 << 2)) {
                tmp->y = cg_point_f_get_y(cg_clipping_area_f_get_bl(&clipping_area));
                cg_line_calc_x_from_y(tmp, params, p0, pn);
            } else if (out_code == (out_code | 1 << 1)) {
                tmp->x = cg_point_f_get_x(cg_clipping_area_f_get_tr(&clipping_area));
                cg_line_calc_y_from_x(tmp, params, p0, pn);
            } else if (out_code == (out_code | 1)) {
                tmp->x = cg_point_f_get_x(cg_clipping_area_f_get_tl(&clipping_area));
                cg_line_calc_y_from_x(tmp, params, p0, pn);
            }

            if (out_code == p0_code) {
                p0->x = cg_point_f_get_x(tmp);
                p0->y = cg_point_f_get_y(tmp);
                cg_point_f_clipping_calc_code(&p0_code, p0, clipping_area);
            } else {
                pn->x = cg_point_f_get_x(tmp);
                pn->y = cg_point_f_get_y(tmp);
                cg_point_f_clipping_calc_code(&pn_code, pn, clipping_area);
            }

            cg_point_f_free(&tmp);
        }
    } while (!end);

    if (is_visible) {
        draw_line(p0, pn);
    }
}