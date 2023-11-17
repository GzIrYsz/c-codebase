#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "polygon_filling.h"
#include "polygon_filling.priv.h"
#include "utils.h"
#include "types.h"

#define ABS(X) (X < 0 ? -X : X)

void cg_polygon_filling_f_calc_surrounding_rect(cg_polygon_f_t *polygon, cg_polygon_filling_surrounding_rect_f_t *surrounding_rect) {
    surrounding_rect->top_left = (cg_point_f_t*) malloc(sizeof(cg_point_f_t)); // TODO : Déplacer allocations en dehors pour éviter fuites mémoire
    surrounding_rect->top_right = (cg_point_f_t*) malloc(sizeof(cg_point_f_t));
    surrounding_rect->bot_left = (cg_point_f_t*) malloc(sizeof(cg_point_f_t));
    surrounding_rect->top_right = (cg_point_f_t*) malloc(sizeof(cg_point_f_t));

    (surrounding_rect->top_left)->x = (float) INT_MAX;
    (surrounding_rect->top_left)->y = (float) INT_MAX;

    (surrounding_rect->top_right)->x = (float) INT_MIN;
    (surrounding_rect->top_right)->y = (float) INT_MAX;

    (surrounding_rect->bot_left)->x = (float) INT_MAX;
    (surrounding_rect->bot_left)->y = (float) INT_MIN;

    (surrounding_rect->bot_right)->x = (float) INT_MIN;
    (surrounding_rect->bot_right)->y = (float) INT_MIN;

    for (int i = 1; i < cg_polygon_f_get_nb_vertices(polygon); i++) {
        cg_point_f_t *vertice;
        vertice = cg_polygon_f_get_vertice(i, polygon);

        if (cg_point_f_get_x(vertice) < cg_point_f_get_x(cg_clipping_area_f_get_tl(surrounding_rect))) {
            (surrounding_rect->top_left)->x = cg_point_f_get_x(vertice);
            (surrounding_rect->bot_left)->x = cg_point_f_get_x(vertice);
        } else if (cg_point_f_get_x(vertice) > cg_point_f_get_x(cg_clipping_area_f_get_tr(surrounding_rect))) {
            (surrounding_rect->top_right)->x = cg_point_f_get_x(vertice);
            (surrounding_rect->bot_right)->x = cg_point_f_get_x(vertice);
        }

        if (cg_point_f_get_y(vertice) < cg_point_f_get_y(cg_clipping_area_f_get_tl(surrounding_rect))) {
            (surrounding_rect->top_left)->y = cg_point_f_get_y(vertice);
            (surrounding_rect->top_right)->y = cg_point_f_get_y(vertice);
        } else if (cg_point_f_get_y(vertice) > cg_point_f_get_y(cg_clipping_area_f_get_bl(surrounding_rect))) {
            (surrounding_rect->bot_left)->y = cg_point_f_get_y(vertice);
            (surrounding_rect->bot_right)->y = cg_point_f_get_y(vertice);
        }
    }
}

bool cg_polygon_filling_f_point_inside(cg_point_f_t *p, cg_polygon_f_t *polygon) {
    float sum_angles = 0;

    for (int i = 0; i < cg_polygon_f_get_nb_vertices(polygon); i++) {
        cg_point_f_t p1, p2;
        float p1_norm, p2_norm;

        p1.x = cg_point_f_get_x(cg_polygon_f_get_vertice(i, polygon)) - cg_point_f_get_x(p);
        p1.y = cg_point_f_get_y(cg_polygon_f_get_vertice(i, polygon)) - cg_point_f_get_y(p);
        p2.x = cg_point_f_get_x(cg_polygon_f_get_vertice(i+1, polygon)) - cg_point_f_get_x(p);
        p2.y = cg_point_f_get_y(cg_polygon_f_get_vertice(i+1, polygon)) - cg_point_f_get_y(p);

        p1_norm = sqrtf(powf(cg_point_f_get_x(&p1), 2) + powf(cg_point_f_get_y(&p1), 2));
        p2_norm = sqrtf(powf(cg_point_f_get_x(&p2), 2) + powf(cg_point_f_get_y(&p2), 2));

        if ((p1_norm == 0) || (p2_norm == 0)) {
            return true;
        } else {
            float scalar_prod_p1_p2, vector_prod_p1_p2;
            float sinus, cosinus;

            scalar_prod_p1_p2 = cg_point_f_get_x(&p1) * cg_point_f_get_x(&p2) + cg_point_f_get_y(&p1) * cg_point_f_get_y(&p2);
            vector_prod_p1_p2 = cg_point_f_get_x(&p1) * cg_point_f_get_y(&p2) - cg_point_f_get_y(&p1) * cg_point_f_get_x(&p2);
            sinus = vector_prod_p1_p2 / (p1_norm * p2_norm);
            cosinus = scalar_prod_p1_p2 / (p1_norm * p2_norm);
            sum_angles += atanf(cosinus / sinus);
        }
    }

    return ABS(sum_angles) > M_PI;
}

void cg_polygon_filling_f(cg_polygon_f_t *polygon) {
    cg_polygon_filling_surrounding_rect_f_t surrounding_rect;
    cg_polygon_filling_f_calc_surrounding_rect(polygon, &surrounding_rect);

    float x, y;

    x = cg_point_f_get_x(cg_clipping_area_f_get_tl(&surrounding_rect));
    y = cg_point_f_get_y(cg_clipping_area_f_get_tl(&surrounding_rect));
    while (x < cg_point_f_get_x(cg_clipping_area_f_get_bl(&surrounding_rect))) {
        while (y < cg_point_f_get_y(cg_clipping_area_f_get_tr(&surrounding_rect))) {
            cg_point_f_t p;
            p.x = x;
            p.y = y;

            if (cg_polygon_filling_f_point_inside(&p, polygon)) {
                cg_draw_point_f(&p);
            }

            y++;
        }
        x++;
    }
}