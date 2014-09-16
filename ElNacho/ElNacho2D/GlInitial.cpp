#include "GlInitial.h"
#include "TextureManager.h"
#include "GameEngine.h"

GlInitial::GlInitial(Maze* maze, Cell* cell)
: GlCell(maze, cell)
{
}

GlInitial::~GlInitial()
{
}

void GlInitial::Draw()
{
  glColor4f(1, 1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  TextureManager::Inst()->BindTexture(TEX_BEGIN);
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