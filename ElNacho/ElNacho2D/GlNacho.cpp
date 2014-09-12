#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"

#include <vector>

GlNacho::GlNacho(Maze* maze, Nacho* nacho, float left, float right, float bottom, float top)
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
  ::glTranslatef(GetTx(nacho->GetX()), GetTy(nacho->GetY()), 0);

  //float startX = (float)nacho->GetOldX();
  //float startY = (float)nacho->GetOldY();
  //
  //float endX = (float)nacho->GetX();
  //float endY = (float)nacho->GetY();

  //if (startX != endX)
  //{
  //  float stepX = (endX - startX) / 10;
  //  float stepY = (endY - startY) / 10;
  //  for (int i = 0; i < 10; i++)
  //  {
  //    ::glTranslatef(GetTx(stepX), GetTy(stepY), 0);
  //    ::glutPostRedisplay();
  //  }
  //}
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

  glColor4f(0, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex2f(centerX + radius, -1.f*(float)maze->GetHeight());
  glVertex2f(centerX + radius, (float)maze->GetHeight());
  glVertex2f((float)maze->GetWidth() + 1.f, (float)maze->GetHeight());
  glVertex2f((float)maze->GetWidth() + 1.f, -1.f*(float)maze->GetHeight());
  glEnd();

  glColor4f(0, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex2f(centerX - radius, -1.f*(float)maze->GetHeight() - 1);
  glVertex2f(centerX - radius, (float)maze->GetHeight() + 1);
  glVertex2f(-1.f*(float)maze->GetWidth(), (float)maze->GetHeight() + 1);
  glVertex2f(-1.f*(float)maze->GetWidth(), -1.f*(float)maze->GetHeight() - 1);
  glEnd();

  glColor4f(0, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex2f(-1.f*(float)maze->GetWidth() - 1, centerY + radius);
  glVertex2f(-1.f*(float)maze->GetWidth() - 1, (float)maze->GetHeight() + 1);
  glVertex2f((float)maze->GetWidth() + 1, (float)maze->GetHeight() + 1);
  glVertex2f((float)maze->GetWidth() + 1, centerY + radius);
  glEnd();

  glColor4f(0, 0, 0, 1);
  glBegin(GL_QUADS);
  glVertex2f(-1.f*(float)maze->GetWidth() - 1, centerY - radius);
  glVertex2f(-1.f*(float)maze->GetWidth() - 1, -1.f*(float)maze->GetHeight() - 1);
  glVertex2f((float)maze->GetWidth() + 1, -1.f*(float)maze->GetHeight() - 1);
  glVertex2f((float)maze->GetWidth() + 1, centerY - radius);
  glEnd();
}