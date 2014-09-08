#include "GlSpecialCell.h"


GlSpecialCell::GlSpecialCell(Maze* maze, Cell* cell)
: GlCell(maze, cell)
{
}

GlSpecialCell::~GlSpecialCell()
{
}

void GlSpecialCell::Draw()
{
  glColor3f(1, 0, 0);
  glLineWidth(2);
  glBegin(GL_QUADS);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, 0.2f);
  glEnd();
}