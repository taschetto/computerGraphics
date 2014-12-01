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
  glTranslatef(GetTx() + 0.5, 0.5f, GetTy() + 0.5);
}

void GlBattery::Draw()
{
  glColor3f(1, 0, 1);
  glutSolidSphere(size, 20, 20);

  size += gain;

  if (size >= 0.5f)
    gain = -0.005f;
  if (size <= 0.15f)
    gain = +0.001;;
}
