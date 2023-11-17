#include "circle_drawing.h"
#include "circle_drawing.priv.h"
#include "utils.h"
#include "types.h"

void cg_draw_circle_pixel_f(cg_point_f_t *p, cg_point_f_t *center) {
    cg_draw_pixel_f(cg_point_f_get_x(p) + cg_point_f_get_x(center), cg_point_f_get_y(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(cg_point_f_get_x(p) + cg_point_f_get_x(center), -cg_point_f_get_y(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(-cg_point_f_get_x(p) + cg_point_f_get_x(center), cg_point_f_get_y(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(-cg_point_f_get_x(p) + cg_point_f_get_x(center), -cg_point_f_get_y(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(cg_point_f_get_y(p) + cg_point_f_get_x(center), cg_point_f_get_x(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(cg_point_f_get_y(p) + cg_point_f_get_x(center), -cg_point_f_get_x(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(-cg_point_f_get_y(p) + cg_point_f_get_x(center), cg_point_f_get_x(p) + cg_point_f_get_y(center));
    cg_draw_pixel_f(-cg_point_f_get_y(p) + cg_point_f_get_x(center), -cg_point_f_get_x(p) + cg_point_f_get_y(center));
}

void cg_draw_circle(cg_point_f_t *center, GLfloat r) {
    cg_point_f_t *p;
    cg_point_f_alloc(&p);
    p->x = 0;
    p->y = r;
    float d = 1 - r;
    cg_draw_circle_pixel_f(p, center);

    while (cg_point_f_get_y(p) > cg_point_f_get_x(p)) {
        if (d < 0) {
            d += 2 * cg_point_f_get_x(p) + 3;
        } else {
            d += 2 * cg_point_f_get_x(p) - 2 * cg_point_f_get_y(p) + 5;
            p->y--;
        }
        p->x++;
        cg_draw_circle_pixel_f(p, center);
    }
    cg_point_f_free(&p);
}