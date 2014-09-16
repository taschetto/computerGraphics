#include "InitialState.h"
#include "GameEngine.h"
#include "PlayState.h"
#include "OpenGL.h"
#include <FreeImage.h>
#include "TextureManager.h"

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

void InitialState::HandleEvents(GameEngine*)
{
}

void InitialState::Draw()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluOrtho2D(-1, 1, -1, 1);
  glPushMatrix();

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  TextureManager::Inst()->BindTexture(TEX_SPLASH);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void InitialState::Keyboard(GameEngine* engine, unsigned char, int, int)
{
  SpecialFunc(engine, 0, 0, 0);
}

void InitialState::SpecialFunc(GameEngine* engine, int, int, int)
{
  engine->ChangeState(PlayState::Instance());
  ::glutPostRedisplay();
}