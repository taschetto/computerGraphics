#include "GlCell.h"
#include "OpenGL.h"
#include <stdlib.h>

GlCell::GlCell(Maze* maze, Cell* cell)
  : maze(maze)
  , cell(cell)
{
}

GlCell::~GlCell()
{
}

float GlCell::GetTx()
{
  return (float)cell->GetX();
}

float GlCell::GetTy()
{
  return maze->GetHeight() - (float)cell->GetY() - 1;
}

void GlCell::Scale()
{
}

void GlCell::Translate()
{
  glTranslatef(GetTx(), 0.f, GetTy());
}

void GlCell::Draw()
{
  glColor3f(0.5f, 0.5f, 0.5f);

  glBegin(GL_POLYGON);
  glVertex3f(1, 0, 1);
  glVertex3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1);
  glEnd();


  if (cell->HasWall(North))
  {
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 1, 1);
    glEnd();
  }

  if (cell->HasWall(South))
  {
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
  }

  if (cell->HasWall(West))
  {
    glColor3f(0.5, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 1, 1);
    glEnd();
  }

  if (cell->HasWall(East))
  {
    glColor3f(0, 0, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 1, 1);
    glEnd();
  }
}
