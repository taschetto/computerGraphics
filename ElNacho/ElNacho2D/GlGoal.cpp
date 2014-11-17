#include "GlGoal.h"
#include "OpenGL.h"
#include "TextureManager.h"
#include "GameEngine.h"

GlGoal::GlGoal(Maze* maze, Cell* cell)
  : GlCell(maze, cell)
{
}

GlGoal::~GlGoal()
{
}

void GlGoal::Draw()
{
}