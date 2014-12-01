#include "GlGoal.h"
#include "OpenGL.h"
#include "TextureManager.h"
#include "GameEngine.h"

#include <iostream>

GlGoal::GlGoal(Maze* maze, Cell* cell)
  : GlCell(maze, cell)
{
}

GlGoal::~GlGoal()
{
}

float GlGoal::GetTx()
{
  return GlCell::GetTx() + 0.5;
}

float GlGoal::GetTy()
{
  return GlCell::GetTy() + 0.5;
}

void GlGoal::Translate()
{
  glTranslatef(GetTx(), 0.5, GetTy());
}

void GlGoal::Draw()
{
  if (++count % 15 == 0)
  {
    faces += inc;
    if (faces == 20)
      inc = -1.0f;
    if (faces == 8)
      inc = +1.0f;
  }

  glColor3f(0, 1, 0);
  glRotatef(90, 0.0, 0.0, 1.0);
  glRotatef(270, 0.0, 1.0, 0.0);
  glTranslatef(0, 0, -0.3);
  glutWireCone(0.2, 1.0, faces, faces);
}