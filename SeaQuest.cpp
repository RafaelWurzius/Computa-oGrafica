///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h> 
#include <GL/glut.h> 
#include <math.h> 
#define PI 3.1415926535898  

#define janela_altura 400
#define janela_largura 600

float transX = 0;
float transY = 0;
bool direita = false;
void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("colisao_quadrado"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutMainLoop(); // redesenhar

	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);
	if (tecla == 'a')
	{
		direita = false;
		transX = transX - 5;
		printf("\n o valor de translacao e %.2f\n", transX);
	}
	if (tecla == 'd')
	{
		direita = true;
		transX = transX + 5;
		printf("\n o valor de translacao e %.2f\n", transX);
	}
	if (tecla == 'w')
	{
		transY = transY + 5;
		printf("\n o valor de translacao e %.2f\n", transY);
	}
	if (tecla == 's')
	{
		transY = transY - 5;
		printf("\n o valor de translacao e %.2f\n", transY);
	}


	glutPostRedisplay();


}



void desenhar()
{
	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 10.0f, raioY = 10.0f;
	glTranslatef(0, 0, 0);

	glBegin(GL_QUADS);

	glColor3f(1.0, 0.0, 0.0);  // cor
	glVertex2f(-100, 100);
	glVertex2f(-5, 100);
	glVertex2f(-5, 0);
	glVertex2f(-100, 0);

	glEnd();

	glTranslatef(transX, 0, 0);
	glTranslatef(0, transY, 0);

	if (direita) {
		//SUBMARINO 
		glPushMatrix();

		glTranslatef(50, 0, 0);
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 0.0);  // cor
		glVertex2f(-10, 10);
		glVertex2f(40, 10);
		glVertex2f(40, -10);
		glVertex2f(-10, -10);
		glEnd();

		//ponta
		glPushMatrix();
		glTranslatef(43, 0, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		//quadrado em cima
		glPushMatrix();
		glTranslatef(27, 14, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 4);
		glVertex2f(10, 4);
		glVertex2f(10, -4);
		glVertex2f(-10, -4);
		glEnd();
		glPopMatrix();

		//quadrado em cima
		glPushMatrix();
		glTranslatef(30, 21, 0);
		glBegin(GL_QUADS);
		glVertex2f(-5, 4);
		glVertex2f(5, 4);
		glVertex2f(5, -4);
		glVertex2f(-5, -4);
		glEnd();
		glPopMatrix();

		//Hélices
		glPushMatrix();
		glTranslatef(-20, 10, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-20, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-20, -10, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		//janela
		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);  // cor
		glTranslatef(43, 0, 0);
		raioX = 5.0f, raioY = 5.0f;
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
	else {
		//SUBMARINO 
		glPushMatrix();

		glTranslatef(50, 0, 0);
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 0.0);  // cor
		glVertex2f(-10, 10);
		glVertex2f(40, 10);
		glVertex2f(40, -10);
		glVertex2f(-10, -10);
		glEnd();

		//ponta
		glPushMatrix();
		glTranslatef(-13, 0, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		//quadrado em cima
		glPushMatrix();
		glTranslatef(5, 14, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 4);
		glVertex2f(10, 4);
		glVertex2f(10, -4);
		glVertex2f(-10, -4);
		glEnd();
		glPopMatrix();

		//quadradinho em cima
		glPushMatrix();
		glTranslatef(2, 21, 0);
		glBegin(GL_QUADS);
		glVertex2f(-5, 4);
		glVertex2f(5, 4);
		glVertex2f(5, -4);
		glVertex2f(-5, -4);
		glEnd();
		glPopMatrix();

		//Hélices
		glPushMatrix();
		glTranslatef(50, 10, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(50, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(50, -10, 0);
		glBegin(GL_QUADS);
		glVertex2f(-10, 3);
		glVertex2f(10, 3);
		glVertex2f(10, -3);
		glVertex2f(-10, -3);
		glEnd();
		glPopMatrix();

		//janela
		glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);  // cor
		glTranslatef(-13, 0, 0);
		raioX = 5.0f, raioY = 5.0f;
		glBegin(GL_POLYGON);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
			//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
}

void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	//tratando colisão
	if (transX > -10)
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo

	}
	else if (transX < -95 * 2 - 10)
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	}
	else if (transY > 100) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	}
	else if (transY < -100) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	}
	else
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor do fundo
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