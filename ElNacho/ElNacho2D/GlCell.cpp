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

void GlCell::Draw()
{
}
