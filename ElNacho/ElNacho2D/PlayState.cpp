#include <vector>
#include "PlayState.h"
#include "GlCell.h"
#include "GlInitial.h"
#include "GlGoal.h"
#include "GlNacho.h"
#include "GlBattery.h"
#include "IDrawable.h"
#include "Maze.h"
#include "Nacho.h"
#include "OpenGL.h"
#include "WinState.h"

PlayState *PlayState::instance = 0;

void PlayState::Init()
{
  maze = new Maze(level + 4);
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

void PlayState::HandleEvents(GameEngine* engine)
{
  Cell* goal = maze->GetGoal();

  if (nacho->GetX() == goal->GetX() && nacho->GetY() == goal->GetY())
  {
    Cleanup();
    level++;
    Init();

    engine->ChangeState(WinState::Instance());
    ::glutPostRedisplay();
  }

  // posteriormente substituir o vector de batteries por uma estrutura de dados mais adequada
  // quem sabe um dicionário com chave sendo uma tupla?
  for (Cell* cell : maze->GetBatteries())
  {
    if (nacho->GetX() == cell->GetX() && nacho->GetY() == cell->GetY())
    {
      maze->RemoveBattery(cell);
      nacho->SetRadius(nacho->GetRadius() * 2);
      ::glutPostRedisplay();
    }
  }
}

void PlayState::Draw()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  const float padding = 0.5;
  const float left = 0, bottom = 0;
  const float right = (float)maze->GetWidth(), top = (float)maze->GetHeight();

  gluOrtho2D(left - padding, right + padding, bottom - padding, top + padding);

  std::vector<IDrawable*> drawables;
  for (Cell* cell : maze->Cells()) drawables.push_back(new GlCell(maze, cell));

  for (Cell* cell : maze->GetBatteries()) drawables.push_back(new GlBattery(maze, cell));
  drawables.push_back(new GlInitial(maze, maze->GetInitial()));
  drawables.push_back(new GlGoal(maze, maze->GetGoal()));
  drawables.push_back(new GlNacho(maze, nacho, left, right, bottom, top));

  for (IDrawable* drawable : drawables)
  {
    glPushMatrix();
    drawable->Translate();
    drawable->Scale();
    drawable->Draw();
    glPopMatrix();
  }

  for (IDrawable* drawable : drawables)
    delete drawable;
  drawables.clear();
  
  glutSwapBuffers();
}

void PlayState::Keyboard(GameEngine*, unsigned char, int, int)
{
}

void PlayState::SpecialFunc(GameEngine*, int key, int, int)
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
}