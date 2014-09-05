#include <iostream>
#include "LOpenGL.h"
#include "Maze.h"
#include "Renderer.h"

void doRendering(void);

Renderer* renderer;

int main(int argc, char* args[])
{
  glutInit(&argc, args);
  glutInitContextVersion(3, 1);

  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("OpenGL");

  renderer = new Renderer();
  if (!renderer->InitGL())
  {
    printf("Unable to initialize graphics library!\n");
    return 1;
  }

  glutDisplayFunc(doRendering);
  glutMainLoop();

  return 0;
}

void doRendering(void)
{
  renderer->Render();
}