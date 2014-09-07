#include "Controller.h"
#include "IDrawable.h"

#include "GlCell.h"
#include "GlNacho.h"

#include "Maze.h"
#include "Nacho.h"

#include "OpenGL.h"
#include <vector>

Controller::Controller()
{
  size_t size = 6;
  maze = new Maze(size, 2 * size);
  maze->Generate();

  nacho = new Nacho(maze);
}

Controller::~Controller()
{
  delete maze;
}

bool Controller::InitGL()
{
  //Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
    return false;
  }

  return true;
}

void Controller::InitRender()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float padding = 0.5;
  gluOrtho2D(0 - padding, maze->GetWidth() + padding, 0 - padding, maze->GetHeight() + padding);
  glPushMatrix();
}

void Controller::Display()
{
  this->InitRender();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  std::vector<IDrawable*> drawables;

  for (Cell* cell : maze->Cells())
  {
    drawables.push_back(new GlCell(maze, cell));
  }

  drawables.push_back(new GlNacho(maze, nacho));

  for (IDrawable* drawable : drawables)
  {
    drawable->Render();
  }

  for (IDrawable* drawable : drawables)
    delete drawable;
  
  drawables.clear();
  glutSwapBuffers();
  //glFlush();
}

void Controller::Keyboard(unsigned char, int, int)
{
}

void Controller::SpecialFunc(int key, int, int)
{
  size_t nx = 0, ny = 0;
  bool setX = false, setY = false;
  switch (key)
  {
  case GLUT_KEY_UP:
    nacho->Walk(North);
    break;
 
  case GLUT_KEY_DOWN:
    nacho->Walk(South);
    break;

  case GLUT_KEY_RIGHT:
    nacho->Walk(East);
    break;

  case GLUT_KEY_LEFT:
    nacho->Walk(West);
    break;
  }

  glutPostRedisplay();
}