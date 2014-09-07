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
  glTranslatef(GetTx(), GetTy(), 0.0f);
}

void desenhaTexto(void *font, char *string)
{
  while (*string)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void GlCell::Draw()
{
  //glBegin(GL_LINE_LOOP);
  //  glVertex2i(0, 0);
  //  glVertex2i(0, 1);
  //  glVertex2i(1, 1);
  //  glVertex2i(1, 0);
  //glEnd();

  glLineWidth(2);
  glBegin(GL_LINES);

  if (cell->HasWall(North))
  {
    glColor3f(0., 0., 1.);
    glVertex2i(0, 1);
    glVertex2i(1, 1);
  }

  if (cell->HasWall(South))
  {
    //glColor3f(1., 1., 0.);
    glVertex2i(0, 0);
    glVertex2i(1, 0);
  }

  if (cell->HasWall(West))
  {
    //glColor3f(1., 0., 1.);
    glVertex2i(0, 0);
    glVertex2i(0, 1);
  }

  if (cell->HasWall(East))
  {
    //glColor3f(0., 1., 0.);
    glVertex2i(1, 0);
    glVertex2i(1, 1);
  }
  
  glEnd();

  //glRasterPos2f(0, 0);
  //int i = cell->order;
  //char buffer[33];
  //_itoa_s(i, buffer, 10);

  //desenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, &buffer[0]);

  if (!cell->IsVisited())
  {
    glBegin(GL_LINES);
      glVertex2i(0, 0);
      glVertex2i(1, 1);
      glVertex2i(1, 0);
      glVertex2i(0, 1);
    glEnd();
  }
}
