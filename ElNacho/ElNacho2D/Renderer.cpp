#include "Renderer.h"
#include "Maze.h"
#include "GLMazeCell.h"
#include "LOpenGL.h"

Renderer::Renderer()
{
  size_t size = 60;
  maze = new Maze(size, 2 * size);
  maze->Generate();
}

Renderer::~Renderer()
{
  delete maze;
}

bool Renderer::InitGL()
{
  //Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
    return false;
  }

  return true;
}

void Renderer::Update()
{
}

void Renderer::Render()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float padding = 0.5;
  gluOrtho2D(0 - padding, maze->GetWidth() + padding, 0 - padding, maze->GetHeight() + padding);

  //Clear color buffer
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  for (MazeCell* cell : maze->Cells())
  {
    GLMazeCell glCell(maze, cell);

    glPushMatrix();

    glCell.Translate();
    glCell.Draw();

    glPopMatrix();
  }

  glutSwapBuffers();
}
