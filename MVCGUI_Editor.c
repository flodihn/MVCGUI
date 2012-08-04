#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "soil.h"

#include "editor_mouseinput.h"

void keyboard(unsigned char key, int x, int y);
void display(void);

GLint test_texture;

edMouse globalMouse;

int main(int argc, char** argv)
{
    int width;
    int height;
  glutInit(&argc, argv);

  //glutInitWindowPosition(, int y);
  glutInitWindowSize(1280, 768);
  glutCreateWindow("GLUT Test");
  glutKeyboardFunc(&keyboard);
  glutSetCursor(GLUT_CURSOR_NONE);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motionPassive);
	glutEntryFunc(mouse_entry);
	glutIdleFunc(display);

  glutDisplayFunc(display);

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, 1280, 768 , 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


  test_texture = GetTexture("editor_data/defaultskin.png");
    mouse_init();

  glutMainLoop();

  return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBindTexture(GL_TEXTURE_2D, test_texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 768.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1280.0f, 768.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(1280.0f, 0.0f);
  glEnd();

  mouse_render();
  glutSwapBuffers();
  //glFlush();
}
