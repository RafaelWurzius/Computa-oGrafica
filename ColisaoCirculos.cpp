///  colisao de circulos
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>

#define janela_altura 400
#define janela_largura 600
#define PI 3.1415926535898 

GLfloat circ_pnt = 100;
GLfloat ang, raioX, raioY;

float transx1 = 0;
float transy1 = 0;

float transx2 = 0;
float transy2 = 0;

float distancia = 0;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void specialKeys(int key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("colisao_circulos"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	glutMainLoop(); // redesenhar

	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	if (tecla == 'a')
	{
		transx1 = transx1 - 1;

	}
	if (tecla == 'd')
	{
		transx1 = transx1 + 1;
		//printf("\n o valor de translacao e %.2f\n", trans);
	}
	if (tecla == 'w') {
		transy1 = transy1 + 1;
	}
	if (tecla == 's') {
		transy1 = transy1 - 1;
	}

	glutPostRedisplay();


}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
	{
		transx2 = transx2 - 1;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		transx2 = transx2 + 1;
	}
	if (key == GLUT_KEY_UP) {
		transy2 = transy2 + 1;
	}
	if (key == GLUT_KEY_DOWN) {
		transy2 = transy2 - 1;
	}
	glutPostRedisplay();

}



void desenhar()
{
	glLineWidth(2); // grossura da linha

	glTranslatef(-100, 0, 0);

	circ_pnt = 100;
	raioX = 50.0f;
	raioY = 50.0f;

	glPushMatrix();
		glTranslatef(transx2, transy2, 0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circ_pnt; i++)
		{
			glColor3f(1.0, 0.0, 0.0);  // cor
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();

		glBegin(GL_LINES);  /// linha para ter a base
		glVertex3f(0, 0, 0);
		glVertex3f(raioX, 0, 0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(transx1, transy1, 0);

		circ_pnt = 100;
		raioX = 50.0;
		raioY = 50.0;

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circ_pnt; i++)
		{
			glColor3f(1.0, 1.0, 0.0);  // cor
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();

		glBegin(GL_LINES);  // linha para ter a base
		glVertex3f(0, 0, 0);
		glVertex3f((raioX * (-1)), 0, 0);
		glEnd();

	glPopMatrix();



}


void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();
	//
	float dx = transx2 - transx1;
	float dy = transy2 - transy1;
	distancia = sqrt((dx * dx) + (dy * dy));

	printf("A distancia eh de: %f \n", distancia);
	//
	if (distancia > (raioX*2))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo azul

	}
	else
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor do fundo braco
	}

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA

	// Especificar o local aonde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();


	glFlush();  // execute o desenho

}

void tela(GLsizei w, GLsizei h)
{


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);


	glMatrixMode(GL_MODELVIEW);

}
