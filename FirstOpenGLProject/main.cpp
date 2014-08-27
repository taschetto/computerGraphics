#include <stdlib.h>
#include <GL/glut.h>

float translacaoX = 0.5, translacaoY = 0.5;

float panX = 0, panY = 0;

double left, right, bottom, top;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left+panX, right+panX, bottom+panY, top+panY);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1,1,1);

    glLoadIdentity();

    glBegin(GL_LINES);
        glVertex3f(-1, 0, 0);
        glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(0, -1, 0);
        glVertex3f(0, 1, 0);
    glEnd();

    glTranslatef(translacaoX, translacaoY, 0.f);

    glLineWidth(3);
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.2f,0.1f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f,0.22f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.2f,0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.1f);
    glEnd();

	//Executa os comandos OpenGL
	glFlush();
}

void TecladoX (int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) // left
		translacaoX -= 0.1;

    if (key == GLUT_KEY_UP) // up
        translacaoY += 0.1;

    if (key == GLUT_KEY_RIGHT) // right
        translacaoX += 0.1;

    if (key == GLUT_KEY_DOWN) // down
        translacaoY -= 0.1;

    if (key == GLUT_KEY_HOME)
    {
        left *= 2;
        right *= 2;
        bottom *= 2;
        top *= 2;
    }

    if (key == GLUT_KEY_END)
    {
        left /= 2;
        right /= 2;
        bottom /= 2;
        top /= 2;
    }

    if (key == GLUT_KEY_F9)
        panX += 0.1;

            if (key == GLUT_KEY_F10)
        panX -= 0.1;

            if (key == GLUT_KEY_F11)
        panY += 0.1;
            if (key == GLUT_KEY_F12)
        panY -= 0.1;


    if (key == GLUT_KEY_END)
    {
        left /= 2;
        right /= 2;
        bottom /= 2;
        top /= 2;
    }

    glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
    left = -1.0;
    right = 1.0;
    bottom = -1.0;
    top = 1.0;
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(left,right,bottom,top);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho de um tri�ngulo em 2D");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	glutSpecialFunc(TecladoX);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
