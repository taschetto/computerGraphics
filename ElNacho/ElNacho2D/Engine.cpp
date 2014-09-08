#include <vector>
#include "Engine.h"
#include "GlCell.h"
#include "GlSpecialCell.h"
#include "GlNacho.h"
#include "IDrawable.h"
#include "Maze.h"
#include "Nacho.h"
#include "OpenGL.h"

Engine::Engine()
{
  size_t size = 25;
  maze = new Maze(size, 2 * size);
  nacho = new Nacho(maze);
}

Engine::~Engine()
{
  delete maze;
  delete nacho;
}

void Engine::InitRender()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float padding = 0.5;
  gluOrtho2D(0 - padding, maze->GetWidth() + padding, 0 - padding, maze->GetHeight() + padding);
  glPushMatrix();
}

bool Engine::InitGL()
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

void Engine::Display()
{
  this->InitRender();
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  std::vector<IDrawable*> drawables;

  for (Cell* cell : maze->Cells())
  {
    drawables.push_back(new GlCell(maze, cell));
  }

  drawables.push_back(new GlSpecialCell(maze, maze->GetInitial()));
  drawables.push_back(new GlSpecialCell(maze, maze->GetGoal()));
  drawables.push_back(new GlNacho(maze, nacho));

  for (IDrawable* drawable : drawables)
  {
    Draw(drawable);
  }

  for (IDrawable* drawable : drawables)
    delete drawable;
  drawables.clear();
  
  glutSwapBuffers();
}

void Engine::Keyboard(unsigned char, int, int)
{
}

void Engine::SpecialFunc(int key, int, int)
{
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

void Engine::Draw(IDrawable* drawable)
{
  glPushMatrix();
  drawable->Scale();
  drawable->Translate();
  drawable->Draw();
  glPopMatrix();
}