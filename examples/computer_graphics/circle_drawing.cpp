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
#include "../../src/computer_graphics/types.h"
#include "../../src/computer_graphics/utils.h"
}

#define DEBUG 1

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

int main(int argc, char **argv) {
    int window_width = stoi(argv[1]);
    int window_height = stoi(argv[2]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - window_width / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - window_height / 2);
    glutCreateWindow("EXAMPLE: Circle drawing algorithm");
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
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
    for (int i = 0; i < points_tab.n - 1; i += 2) {
        float dist = cg_point_f_dist(points_tab.points.at(i), points_tab.points.at(i+1));

        if (DEBUG) {
            glColor3f(1.0, 0, 0);
            glPointSize(5.0);
            cg_draw_point_f(points_tab.points.at(i));
        }

        glPointSize(1.0);
        glColor3f(1.0, 1.0, 1.0);
        cg_draw_circle(points_tab.points.at(i), dist);
    }
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