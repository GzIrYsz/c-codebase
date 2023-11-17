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
#include "../../src/computer_graphics/circle_drawing.h"
#include "../../src/computer_graphics/clipping.h"
#include "../../src/computer_graphics/clipping.priv.h"
#include "../../src/computer_graphics/line_drawing.h"
#include "../../src/computer_graphics/types.h"
#include "../../src/computer_graphics/utils.h"
}

#define DEBUG 1
#define CLIPPING_FRAME_SCALE 0.2

using namespace std;

typedef struct {
    array<cg_point_f_t *, 1000> points;
    int n;
} points_t;

points_t points_tab;
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - window_width / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - window_height / 2);
    glutCreateWindow("EXAMPLE: Clipping algorithm");
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
    if (DEBUG)
        draw_clipping_border();
    render_scene();
    glFlush();
}

void render_scene() {
    cg_point_f_t *tl, *tr, *br, *bl;
    cg_clipping_area_f_t clipping_area;

    cg_point_f_alloc(&tl);
    cg_point_f_alloc(&tr);
    cg_point_f_alloc(&br);
    cg_point_f_alloc(&bl);

    tl->x = glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
    tl->y = glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;

    tr->x = glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
    tr->y = glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;

    br->x = glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
    br->y = glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;

    bl->x = glutGet(GLUT_WINDOW_WIDTH) * CLIPPING_FRAME_SCALE;
    bl->y = glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * CLIPPING_FRAME_SCALE;

    clipping_area.top_left = tl;
    clipping_area.top_right = tr;
    clipping_area.bot_left = bl;
    clipping_area.bot_right = br;

    glColor3f(1.0, 0, 0);
    glPointSize(2.0);
    cg_draw_line_f(tl, tr);
    cg_draw_line_f(tr, br);
    cg_draw_line_f(br, bl);
    cg_draw_line_f(bl, tl);

    for (int i = 0; i < points_tab.n - 1; i += 2) {
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(1.0);
        cg_line_clipping(points_tab.points.at(i), points_tab.points.at(i + 1), clipping_area, cg_draw_line_f);
    }

    cg_point_f_free(&tl);
    cg_point_f_free(&tr);
    cg_point_f_free(&br);
    cg_point_f_free(&bl);
}

void mouse_click(int button, int state, int x, int y) {
    if (state == 0) {
        cg_point_f_t *p;
        cg_point_f_alloc(&p);

        p->x = (float) x;
        p->y = (float) y;

        points_tab.points.at(points_tab.n) = p;
        points_tab.n++;
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
        case 'c':
            points_tab.n = 0;
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