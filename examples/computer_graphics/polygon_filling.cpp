#ifdef __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#include <GL/glut.>
#elif _WIN32
    #include <GLUT/glut.h>
#endif

#include <array>
#include <cstdlib>
#include <iostream>
#include <string>

extern "C" {
#include "../../src/computer_graphics/polygon_filling.h"
#include "../../src/computer_graphics/types.h"
#include "../../src/computer_graphics/utils.h"
}

#define DEBUG 1

using namespace std;

typedef struct {
    array<cg_polygon_f_t *, 100> polygons;
    int n;
} polygons_t;

polygons_t polygons_tab;
bool is_fullscreen = false;

void window_reshape(int width, int height);
void window_display();
void render_scene();
void mouse_click(int button, int state, int x, int y);
void keyboard_press(unsigned char key, int x, int y);
void toggle_fullscreen();
void draw_clipping_border();

int main(int argc, char **argv) {
    int window_width = stoi(argv[1]);
    int window_height = stoi(argv[2]);

    cg_polygon_f_t *f_poly;
    cg_polygon_f_alloc(50, &f_poly);
    cg_polygon_f_init(f_poly);
    polygons_tab.polygons.at(0) = f_poly;
    polygons_tab.n++;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - window_width / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - window_height / 2);
    glutCreateWindow("EXAMPLE: Polygon filling algorithm");
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    glutKeyboardFunc(keyboard_press);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    render_scene();
    glFlush();
}

void render_scene() {
    for (int i = 0; i < polygons_tab.n; i++) {
        cg_polygon_f_t *poly;
            if (cg_polygon_f_get_nb_vertices(polygons_tab.polygons.at(i)) != 0) {
                poly = polygons_tab.polygons.at(i);
                if ((cg_polygon_f_get_vertice(0, poly) == cg_polygon_f_get_vertice(cg_polygon_f_get_nb_vertices(poly) - 1, poly) && cg_polygon_f_get_nb_vertices(poly) > 2)) {
                    glColor3f(1.0, 1.0, 1.0);
                    cg_polygon_filling_f(poly);
                }
            }
    }
}

void mouse_click(int button, int state, int x, int y) {
    if ((state == 0) && (button == GLUT_LEFT_BUTTON)) {
        cg_point_f_t *p;
        cg_polygon_f_t *poly;

        cg_point_f_alloc(&p);

        p->x = (float) x;
        p->y = (float) y;

        poly = polygons_tab.polygons.at(polygons_tab.n - 1);
        poly->vertices[cg_polygon_f_get_nb_vertices(poly)] = p;
        poly->nb_vertices++;
    } else if ((state == 0) && (button == GLUT_RIGHT_BUTTON)) {
        cout << "Right click" << endl;
        cg_polygon_f_t *f_poly;

        f_poly = polygons_tab.polygons.at(polygons_tab.n - 1);
        f_poly->vertices[cg_polygon_f_get_nb_vertices(f_poly)] = cg_polygon_f_get_vertice(0, f_poly);
        f_poly->nb_vertices++;
        cout << "First point: x = " << cg_point_f_get_x(cg_polygon_f_get_vertice(0, f_poly)) << " y = " << cg_point_f_get_y(
                cg_polygon_f_get_vertice(0, f_poly)) << endl;
        cout << "Last point: x = " << cg_point_f_get_x(cg_polygon_f_get_vertice(cg_polygon_f_get_nb_vertices(f_poly) - 1, f_poly)) << " y = " << cg_point_f_get_y(
                cg_polygon_f_get_vertice(cg_polygon_f_get_nb_vertices(f_poly) - 1, f_poly)) << endl;

        cg_polygon_f_alloc(50, &f_poly);
        cg_polygon_f_init(f_poly);
        polygons_tab.polygons.at(polygons_tab.n) = f_poly;
        polygons_tab.n++;
    }
    glutPostRedisplay();
}

void keyboard_press(unsigned char key, int x, int y) {
    bool fullscreen_toggled = false;

    switch (key) {
        case 'f':
            toggle_fullscreen();
            fullscreen_toggled = true;
            break;
    }
    glutPostRedisplay();
}

void toggle_fullscreen() {
    if (is_fullscreen) {
        glutReshapeWindow(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
        glutPositionWindow(glutGet(GLUT_INIT_WINDOW_X), glutGet(GLUT_INIT_WINDOW_Y));
    } else {
        glutFullScreen();
    }
    is_fullscreen = !is_fullscreen;
}

void draw_clipping_border() {
//    cg_point_i_t *tl, *tr, *br, *bl;
//    cg_point_i_alloc(&tl);
//    cg_point_i_alloc(&tr);
//    cg_point_i_alloc(&br);
//    cg_point_i_alloc(&bl);
//
//    tl->x = glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
//    tl->y = glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;
//
//    tr->x = glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
//    tr->y = glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;
//
//    br->x = glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
//    br->y = glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;
//
//    bl->x = glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
//    bl->y = glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;
//
//    glColor3f(1.0, 0, 0);
//    glPointSize(2.0);
//    cg_draw_line_i(tl, tr);
//    cg_draw_line_i(tr, br);
//    cg_draw_line_i(br, bl);
//    cg_draw_line_i(bl, tl);
//
//    cg_point_i_free(&tl);
//    cg_point_i_free(&tr);
//    cg_point_i_free(&br);
//    cg_point_i_free(&bl);
}