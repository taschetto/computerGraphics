#include <stdlib.h>
#include <GL/glut.h>

float translacaoX = 0, translacaoY = 0;
float left, right, top, bottom, panX, panY;

void desenhaEixos()
{

  glColor3f(1, 1, 1);

  glLineWidth(1);
  glBegin(GL_LINES);

  glVertex2f(left, 0.0);
  glVertex2f(right, 0.0);
  glVertex2f(0.0, bottom);
  glVertex2f(0.0, top);

  glEnd();

}

void desenhaCasinha()
{

  glLineWidth(3);
  glBegin(GL_LINE_LOOP);
  glVertex2f(-0.2f, 0.1f);
  glVertex2f(-0.2f, -0.2f);
  glVertex2f(0.2f, -0.2f);
  glVertex2f(0.2f, 0.1f);
  glEnd();


  glBegin(GL_TRIANGLES);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2f(-0.2f, 0.1f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(0.0f, 0.22f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2f(0.2f, 0.1f);
  glEnd();

}

void Desenha(void)
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(left + panX, right + panX, bottom + panY, top + panY);
  glMatrixMode(GL_MODELVIEW);

  // Limpa a janela de visualiza��o com a cor branca
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  glLoadIdentity();

  desenhaEixos();

  glPopMatrix();

  glLoadIdentity();

  glTranslatef(translacaoX, translacaoY, 0);

  desenhaCasinha();

  // Define a cor de desenho: azul
  //glColor3f(1,0,1);

  // Desenha um tri�ngulo no centro da janela
  //	glBegin(GL_TRIANGLES);
  //		glVertex3f(-0.5,-0.5,0);
  //		glVertex3f( 0.0, 0.5,0);
  //		glVertex3f( 0.5,-0.5,0);
  //	glEnd();

  //Executa os comandos OpenGL
  glFlush();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
  if (key == 27)
    exit(0);
}

void TeclasEspecias(int key, int x, int y)
{

  if (key == GLUT_KEY_LEFT)
    translacaoX = translacaoX - 0.1;

  if (key == GLUT_KEY_RIGHT)
    translacaoX = translacaoX + 0.1;

  if (key == GLUT_KEY_UP)
    translacaoY = translacaoY + 0.1;

  if (key == GLUT_KEY_DOWN)
    translacaoY = translacaoY - 0.1;

  if (key == GLUT_KEY_END)
  {
    left -= 0.1;
    right += 0.1;
    top += 0.1;
    bottom -= 0.1;
  }

  if (key == GLUT_KEY_HOME)
  {
    left += 0.1;
    right -= 0.1;
    top -= 0.1;
    bottom += 0.1;
  }

  if (key == GLUT_KEY_F9)
    panX += 0.1;
  if (key == GLUT_KEY_F10)
    panX -= 0.1;
  if (key == GLUT_KEY_F11)
    panY += 0.1;
  if (key == GLUT_KEY_F12)
    panY -= 0.1;

  glutPostRedisplay();
}


// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
  // Define a janela de visualiza��o 2D
  glMatrixMode(GL_PROJECTION);
  left = -1.0;
  right = 1.0;
  top = 1.0;
  bottom = -1.0;
  gluOrtho2D(left + panX, right + panX, bottom + panY, top + panY);
  glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{

  int argc = 0;
  char *argv[] = { (char *)"gl", 0 };

  glutInit(&argc, argv);

  // Define do modo de opera��o da GLUT
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Especifica o tamanho inicial em pixels da janela GLUT
  glutInitWindowSize(500, 500);

  // Cria a janela passando como argumento o t�tulo da mesma
  glutCreateWindow("Desenho de um tri�ngulo em 2D");

  // Registra a fun��o callback de redesenho da janela de visualiza��o
  glutDisplayFunc(Desenha);

  // Registra a fun��o callback para tratamento das teclas ASCII
  glutKeyboardFunc(Teclado);

  glutSpecialFunc(TeclasEspecias);

  // Chama a fun��o respons�vel por fazer as inicializa��es
  Inicializa();

  // Inicia o processamento e aguarda intera��es do usu�rio
  glutMainLoop();

  return 0;
}
