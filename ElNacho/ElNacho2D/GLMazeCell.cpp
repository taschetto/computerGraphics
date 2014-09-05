#include "GLMazeCell.h"
#include "LOpenGL.h"
#include <stdlib.h>

GLMazeCell::GLMazeCell(Maze* maze, MazeCell* mazeCell)
  : maze(maze)
  , mazeCell(mazeCell)
{
}

GLMazeCell::~GLMazeCell()
{
}

float GLMazeCell::GetTx()
{
  return (float)mazeCell->GetX();
}

float GLMazeCell::GetTy()
{
  return maze->GetHeight() - (float)mazeCell->GetY() - 1;
}

void GLMazeCell::Translate()
{
  glTranslatef(GetTx(), GetTy(), 0.0f);
}

void desenhaTexto(void *font, char *string)
{
  while (*string)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void GLMazeCell::Draw()
{
  //glBegin(GL_LINE_LOOP);
  //  glVertex2i(0, 0);
  //  glVertex2i(0, 1);
  //  glVertex2i(1, 1);
  //  glVertex2i(1, 0);
  //glEnd();

  glLineWidth(2);
  glBegin(GL_LINES);

  if (mazeCell->HasWall(North))
  {
    glColor3f(0., 0., 1.);
    glVertex2i(0, 1);
    glVertex2i(1, 1);
  }

  if (mazeCell->HasWall(South))
  {
    //glColor3f(1., 1., 0.);
    glVertex2i(0, 0);
    glVertex2i(1, 0);
  }

  if (mazeCell->HasWall(West))
  {
    //glColor3f(1., 0., 1.);
    glVertex2i(0, 0);
    glVertex2i(0, 1);
  }

  if (mazeCell->HasWall(East))
  {
    //glColor3f(0., 1., 0.);
    glVertex2i(1, 0);
    glVertex2i(1, 1);
  }
  
  glEnd();

  //glRasterPos2f(0, 0);
  //int i = mazeCell->order;
  //char buffer[33];
  //_itoa_s(i, buffer, 10);

  //desenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, &buffer[0]);

  if (!mazeCell->IsVisited())
  {
    glBegin(GL_LINES);
      glVertex2i(0, 0);
      glVertex2i(1, 1);
      glVertex2i(1, 0);
      glVertex2i(0, 1);
    glEnd();
  }
}
