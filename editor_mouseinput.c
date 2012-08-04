#include "editor_mouseinput.h"
#include "globals.h"
#include <GL/glut.h>
#include <SOIL.h>
#include "editor_texture.h"

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			globalMouse.rbuttondown = MOUSE_BUTTON_DOWN;
		else
			globalMouse.rbuttondown = MOUSE_BUTTON_UP;
	}
	else if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			globalMouse.lbuttondown = MOUSE_BUTTON_DOWN;
		else
			globalMouse.lbuttondown = MOUSE_BUTTON_UP;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
    {
		if (state == GLUT_DOWN)
			globalMouse.mbuttondown = MOUSE_BUTTON_DOWN;
		else
			globalMouse.mbuttondown = MOUSE_BUTTON_UP;
    }
}

void mouse_motion(int x, int y)
{
    globalMouse.x = x;
    globalMouse.y = y;
	if (globalMouse.lbuttondown)
    {
		//cout << "Mouse dragged with left button at "
		//<< "(" << x << "," << y << ")" << endl;
    }
}

void mouse_motionPassive(int x, int y)
{
    globalMouse.x = x;
    globalMouse.y = y;
}

void mouse_entry(int state)
{
    /*
	if (state == GLUT_ENTERED)
		//cout << "Mouse Entered" << endl;
	else
		//cout << "Mouse Left" << endl;
    */
}

void mouse_init()
{
    globalMouse.w = 32;
    globalMouse.h = 32;
    globalMouse.texture = GetTexture("editor_data/mp.png");
}

void mouse_render()
{
  glBindTexture(GL_TEXTURE_2D, globalMouse.texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f((float)globalMouse.x,(float)globalMouse.y);
            glTexCoord2f(0.0f, 0.0f); glVertex2f((float)globalMouse.x, (float)globalMouse.y + (float)globalMouse.h);
            glTexCoord2f(1.0f, 0.0f); glVertex2f((float)globalMouse.x + (float)globalMouse.w, (float)globalMouse.y + (float)globalMouse.h);
            glTexCoord2f(1.0f, 1.0f); glVertex2f((float)globalMouse.x + (float)globalMouse.w, (float)globalMouse.y);
  glEnd();
}
