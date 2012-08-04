#ifndef _EDITOR_MOUSEINPUT_
#define _EDITOR_MOUSEINPUT_

#include <GL/GL.h>

#define MOUSE_BUTTON_UP     0
#define MOUSE_BUTTON_DOWN   1

typedef struct edMouse
{
    int x;
    int y;
    int h;
    int w;
    int lbuttondown;
    int rbuttondown;
    int mbuttondown;
    GLint texture;
}edMouse;

void mouse(int button, int state, int x, int y);

void mouse_motion(int x, int y);

void mouse_motionPassive(int x, int y);

void mouse_entry(int state);

void mouse_init();

#endif
