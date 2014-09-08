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

float GlNacho::GetTx()
{
  return (float)nacho->GetX();
}

float GlNacho::GetTy()
{
  return maze->GetHeight() - (float)nacho->GetY() - 1;
}

void GlNacho::DrawCircle(float centerX, float centerY, float radius, int segments)
{
  glBegin(GL_LINE_LOOP);
  for (int ii = 0; ii < segments; ii++)
  {
    float theta = 2.0f * 3.1415926f * float(ii) / float(segments);//get the current angle

    float x = radius * cosf(theta);//calculate the x component
    float y = radius * sinf(theta);//calculate the y component

    glVertex2f(x + centerX, y + centerY);//output vertex

  }
  glEnd();
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

  DrawCircle(0.5, 0.5, nacho->GetRadius(), 35);
}