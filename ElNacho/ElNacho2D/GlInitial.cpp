#include "GlInitial.h"


GlInitial::GlInitial(Maze* maze, Cell* cell)
: GlCell(maze, cell)
{
}

GlInitial::~GlInitial()
{
}

void GlInitial::Draw()
{
  glColor3f(0, 0, 1);
  glLineWidth(2);
  glBegin(GL_QUADS);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, 0.2f);
  glEnd();
}