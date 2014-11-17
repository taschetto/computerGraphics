#include "GlBattery.h"
#include "TextureManager.h"
#include "GameEngine.h"

GlBattery::GlBattery(Maze* maze, Cell* cell)
: maze(maze)
, cell(cell)
{
}

GlBattery::~GlBattery()
{
}

float GlBattery::GetTx()
{
  return (float)cell->GetX();
}

float GlBattery::GetTy()
{
  return maze->GetHeight() - (float)cell->GetY() - 1;
}

void GlBattery::Scale()
{

}

void GlBattery::Translate()
{
  glTranslatef(GetTx(), GetTy(), 0.0f);
}

void GlBattery::Draw()
{
}
