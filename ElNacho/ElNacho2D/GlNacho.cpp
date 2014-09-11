#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"

#include <vector>

GlNacho::GlNacho(Maze* maze, Nacho* nacho)
: maze(maze)
, nacho(nacho)
{
}

GlNacho::~GlNacho()
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

void GlNacho::Scale()
{
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

  float centerX = 0.5, centerY = 0.5, radius = nacho->GetRadius();

  glBegin(GL_TRIANGLE_FAN);
    glColor4f(0, 0, 0, 0);
    glVertex2f(centerX, centerY);
    glColor4f(0, 0, 0, 1);
    glVertex2f(centerX - radius, centerY + radius); // v1
    glVertex2f(centerX + radius, centerY + radius); // v2
    glVertex2f(centerX + radius, centerY - radius); // v3
    glVertex2f(centerX - radius, centerY - radius); // v4
    glVertex2f(centerX - radius, centerY + radius); // v1
  glEnd();
}