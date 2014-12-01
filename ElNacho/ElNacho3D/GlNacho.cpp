#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"
#include "GameEngine.h"
#include "TextureManager.h"
#include <vector>

GlNacho::GlNacho(Maze* maze, Nacho* nacho)
: maze(maze)
, nacho(nacho)
{
}

GlNacho::~GlNacho()
{
}

float GlNacho::GetTx(size_t x)
{
  return (float)x;
}

float GlNacho::GetTy(size_t y)
{
  return maze->GetHeight() - (float)y - 1;
}

void GlNacho::Scale()
{
}

void GlNacho::Translate()
{
  ::glTranslatef(GetTx(nacho->GetX()) + 0.5f, 0.4f, GetTy(nacho->GetY()) + 0.5f);
}

void GlNacho::Draw()
{
  glColor3f(1, 1, 0);
  glutSolidSphere(0.2f, 20, 20);
}