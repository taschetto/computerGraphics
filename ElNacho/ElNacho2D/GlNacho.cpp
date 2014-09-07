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
  glColor3f(1, 1, 0);
  glBegin(GL_TRIANGLES);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.5f, 0.8f);
    glVertex2f(0.8f, 0.2f);
  glEnd();
}