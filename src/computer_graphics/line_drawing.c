#include <stdio.h>

#include "line_drawing.h"
#include "types.h"
#include "utils.h"

void cg_draw_line_naive(cg_point_f_t *p0, cg_point_f_t *pn) {
    cg_linear_equ_params_t *params;
    cg_line_params_alloc(&params);
    cg_line_calc_m(params, p0, pn);
    cg_line_calc_b(params, p0, pn);

    cg_point_f_t *pi;
    cg_point_f_alloc(&pi);

    if (cg_point_f_get_x(pn) < cg_point_f_get_x(p0)) {
        cg_point_f_t *tmp;
        tmp = p0;
        p0 = pn;
        pn = tmp;
    }

    float i = cg_point_f_get_x(p0);
    while (i <= cg_point_f_get_x(pn)) {
        pi->x = i;
        cg_line_calc_y_from_x(pi, params, p0, pn);
        cg_draw_point_f(pi);

        i += 0.01f;
    }

//    for (int i = (int) cg_point_f_get_x(p0); i <= (int) cg_point_f_get_x(pn); i++) {
//        pi->x = (float) i;
//        cg_line_calc_y_from_x(pi, params, p0, pn);
//        cg_draw_point_f(pi);
//    }
    cg_point_f_free(&pi);
    cg_line_params_free(&params);
}

void cg_draw_line_incremental(cg_point_f_t *pi, cg_linear_equ_params_t  *params, cg_point_f_t *p0, cg_point_f_t *pn) {
    if (params == NULL) {
        cg_line_params_alloc(&params);
        cg_line_calc_m(params, p0, pn);
    }

    if (pi == NULL) {
//        if (cg_point_f_get_x(pn) > cg_point_f_get_x(p0)) {
//            cg_point_f_t *tmp;
//            tmp = p0;
//            p0 = pn;
//            pn = tmp;
//        }

        cg_draw_point_f(p0);
        cg_point_f_alloc(&pi);
        pi->x = cg_point_f_get_x(p0) + 1;
        pi->y = cg_point_f_get_y(p0) + cg_line_params_get_m(params);
        cg_draw_line_incremental(pi, params, p0, pn);
    } else if (cg_point_f_get_x(pi) < cg_point_f_get_x(pn) && cg_point_f_get_y(pi) < cg_point_f_get_y(pn)) {
        cg_draw_point_f(pi);
        pi->x = cg_point_f_get_x(pi) + 1;
        pi->y = cg_point_f_get_y(pi) + cg_line_params_get_m(params);
        cg_draw_line_incremental(pi, params, p0, pn);
    } else {
        cg_line_params_free(&params);
    }
}

void cg_draw_line_i(cg_point_i_t *p0, cg_point_i_t *pn) {
    int dx = cg_line_calc_i_dx(p0, pn);
    int dy = cg_line_calc_i_dy(p0, pn);
    int incr_x;
    int incr_y;

    if (dx > 0) {
        incr_x = 1;
    } else {
        incr_x = -1;
        dx = -dx;
    }

    if (dy > 0) {
        incr_y = 1;
    } else {
        incr_y = -1;
        dy = -dy;
    }

    cg_point_i_t *pi;
    cg_point_i_alloc(&pi);

    int dp = 2 * dy - dx;
    pi->x = cg_point_i_get_x(p0);
    pi->y = cg_point_i_get_y(p0);

    if (dx >= dy) {
        int incr_e = 2 * dy;
        int incr_ne = 2 * (dy - dx);
        while (cg_point_i_get_x(pi) != cg_point_i_get_x(pn)) {
            cg_draw_point_i(pi);
            if (dp <= 0) {
                dp += incr_e;
            } else {
                pi->y += incr_y;
                dp += incr_ne;
            }
            pi->x += incr_x;
        }
    } else {
        int incr_e = 2 * dx;
        int incr_ne = 2 * (dx - dy);
        while (cg_point_i_get_y(pi) != cg_point_i_get_y(pn)) {
            cg_draw_point_i(pi);
            if (dp <= 0) {
                dp += incr_e;
            } else {
                pi->x += incr_x;
                dp += incr_ne;
            }
            pi->y += incr_y;
        }
    }
}

void cg_draw_line_f(cg_point_f_t *p0, cg_point_f_t *pn) {
    cg_point_i_t *tmp0, *tmpn;
    cg_point_i_alloc(&tmp0);
    cg_point_i_alloc(&tmpn);

    tmp0->x = (int) cg_point_f_get_x(p0);
    tmp0->y = (int) cg_point_f_get_y(p0);

    tmpn->x = (int) cg_point_f_get_x(pn);
    tmpn->y = (int) cg_point_f_get_y(pn);

    cg_draw_line_i(tmp0, tmpn);
    cg_point_i_free(&tmp0);
    cg_point_i_free(&tmpn);
}