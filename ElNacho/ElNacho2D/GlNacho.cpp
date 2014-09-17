#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"
#include "GameEngine.h"
#include "TextureManager.h"
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
  ::glTranslatef(GetTx(nacho->GetX()), GetTy(nacho->GetY()), 0.0f);
}

void GlNacho::Draw()
{
  glColor4f(1, 1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  TextureManager::Inst()->BindTexture(TEX_NACHO);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex2f(0.2f, 0.2f);
  glTexCoord2f(1.0f, 0.0f); glVertex2f(0.8f, 0.2f);
  glTexCoord2f(1.0f, 1.0f); glVertex2f(0.8f, 0.8f);
  glTexCoord2f(0.0f, 1.0f); glVertex2f(0.2f, 0.8f);
  glEnd();
  glDisable(GL_TEXTURE_2D);

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

  glDisable(GL_BLEND);
}