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
  glColor3f(1, 0, 0);
}