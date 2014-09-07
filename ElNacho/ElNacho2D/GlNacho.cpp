#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"

GlNacho::GlNacho(Maze* maze, Nacho* nacho)
: maze(maze)
, nacho(nacho)
{
}

GlNacho::~GlNacho()
{
}

void GlNacho::Scale()
{
}

float GlNacho::GetTx()
{
  return (float)nacho->GetX();
}

float GlNacho::GetTy()
{
  return maze->GetHeight() - (float)nacho->GetY() - 1;
}

void GlNacho::Translate()
{
  glTranslatef(GetTx(), GetTy(), 0.f);
}

void GlNacho::Draw()
{
  glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 1);
    glVertex2i(1, 1);
    glVertex2i(1, 0);
  glEnd();
}