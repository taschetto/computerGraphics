#include "InitialState.h"
#include "OpenGL.h"
#include "GameEngine.h"
#include "PlayState.h"

InitialState *InitialState::instance = 0;

void InitialState::Init()
{
}

void InitialState::Cleanup()
{
}

void InitialState::Pause()
{
}

void InitialState::Resume()
{
}

void InitialState::Draw()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float padding = 0.5;
  gluOrtho2D(-2, 2, -2, 2);
  glPushMatrix();

  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  glDisable(GL_BLEND);

  glColorMask(0, 0, 0, 1);
  glColor4f(1, 1, 1, 0);

  glBegin(GL_QUADS);
  glVertex2f(-1, -1);
  glVertex2f(-1, 1);
  glVertex2f(1, 1);
  glVertex2f(1, -1);
  glEnd();

  glColorMask(1, 1, 1, 1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_DST_ALPHA, GL_ONE);

  glColor4f(1, 1, 1, 1);

  glBegin(GL_TRIANGLES);
    glVertex2f(-1, -1);
    glVertex2f(0, 1);
    glVertex2f(1, -1);
  glEnd();

  glutSwapBuffers();
}

void InitialState::Keyboard(GameEngine*, unsigned char, int, int)
{
}

void InitialState::SpecialFunc(GameEngine* engine, int key, int, int)
{
  engine->ChangeState(PlayState::Instance());
}