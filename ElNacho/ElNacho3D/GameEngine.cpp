#include "GameEngine.h"
#include "GameState.h"
#include "OpenGL.h"
#include "TextureManager.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init(int argc, char** argv, const size_t screenWidth, const size_t screenHeight, const char* windowTitle)
{
  ::glutInit(&argc, argv);
  ::glutInitContextVersion(3, 1);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  ::glutInitWindowSize(screenWidth, screenHeight);
  ::glutCreateWindow(windowTitle);

  TextureManager::Inst()->LoadTexture("splash.png", TEX_SPLASH, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("initial.png", TEX_BEGIN, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("goal.png", TEX_TARGET, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("battery.png", TEX_BATTERY, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("nacho.png", TEX_NACHO, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("hammer.png", TEX_HAMMER, GL_BGRA_EXT, GL_RGBA);
  TextureManager::Inst()->LoadTexture("tick.png", TEX_TICK, GL_BGRA_EXT, GL_RGBA);
}

bool GameEngine::InitGL()
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

void GameEngine::Cleanup()
{
  while (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }
}

void GameEngine::ChangeState(GameState* state)
{
  if (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }

  states.push_back(state);
  states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
  if (!states.empty()) {
    states.back()->Pause();
  }

  states.push_back(state);
  states.back()->Init();
}

void GameEngine::PopState()
{
  if (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }

  if (!states.empty()) {
    states.back()->Resume();
  }
}

void GameEngine::Draw()
{
  states.back()->Draw();
  states.back()->HandleEvents(this);
  
}

void GameEngine::Keyboard(unsigned char key, int x, int y)
{
  states.back()->Keyboard(this, key, x, y);
}

void GameEngine::SpecialFunc(int key, int x, int y)
{
  states.back()->SpecialFunc(this, key, x, y);
}

void GameEngine::ReshapeFunc(GLsizei width, GLsizei height)
{
  states.back()->ReshapeFunc(this, width, height);
}

void GameEngine::MotionFunc(int x, int y)
{
  states.back()->MotionFunc(this, x, y);
}

void GameEngine::MouseFunc(int button, int state, int x, int y)
{
  states.back()->MouseFunc(this, button, state, x, y);
}