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
  glColor4f(1, 1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  TextureManager::Inst()->BindTexture(TEX_BATTERY);
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
}
