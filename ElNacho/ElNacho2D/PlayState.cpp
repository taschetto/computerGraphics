#include <vector>
#include "PlayState.h"
#include "GlCell.h"
#include "GlSpecialCell.h"
#include "GlNacho.h"
#include "IDrawable.h"
#include "Maze.h"
#include "Nacho.h"
#include "OpenGL.h"

PlayState *PlayState::instance = 0;

void PlayState::Init()
{
  size_t size = 25;
  maze = new Maze(size, 2 * size);
  nacho = new Nacho(maze);
}

void PlayState::Cleanup()
{
  delete maze;
  delete nacho;
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}


void PlayState::Draw()
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
    glPushMatrix();
    drawable->Scale();
    drawable->Translate();
    drawable->Draw();
    glPopMatrix();
  }

  for (IDrawable* drawable : drawables)
    delete drawable;
  drawables.clear();
  
  glutSwapBuffers();
}

void PlayState::Keyboard(unsigned char, int, int)
{
}

void PlayState::SpecialFunc(int key, int, int)
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

void PlayState::InitRender()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float padding = 0.5;
  gluOrtho2D(0 - padding, maze->GetWidth() + padding, 0 - padding, maze->GetHeight() + padding);
  glPushMatrix();
}