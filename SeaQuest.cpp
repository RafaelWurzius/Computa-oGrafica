///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h> 
#include <GL/glut.h> 
#include <math.h> 
#define PI 3.1415926535898  

#define janela_altura 400
#define janela_largura 600

// variaveis que armazenam a translacao no quadro
float tx = 0.0;
float ty = 0.0;
// incremento em variaveis.
float xStep = 10;
float yStep = 10;

float transX = 0;
float transY = 0;
bool direita = false;
bool fogo = false;
bool continuarD = true;
bool continuarE = true;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void animaTorpedoD(int valor);
void animaTorpedoE(int valor);

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

void animaTorpedoD(int valor) {
	
	if (continuarD) {
		tx += xStep;

		glutPostRedisplay();
		glutTimerFunc(50, animaTorpedoD, 1);
	}

}

void animaTorpedoE(int valor) {

	if (continuarE) {
		tx -= xStep;
	
		glutPostRedisplay();
		glutTimerFunc(50, animaTorpedoE, 1);
	}
}


void keyboard(unsigned char tecla, int x, int y)
{
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
	if (tecla == ' ') {
		fogo = true;
	
		glutTimerFunc(50, animaTorpedoD, 1);
		glutTimerFunc(50, animaTorpedoE, 1);


		if (direita) {
			tx = transX + 110;
			ty = transY;

			continuarE = false;
			continuarD = true;
			exit;
		}
		else {
			tx = transX - 10;
			ty = transY;
			continuarD = false;
			continuarE = true;
			exit;
		}
		printf("FOGO!");

	}


	glutPostRedisplay();


}



void desenhar()
{
	//torpedo
	if (fogo) {

		glPushMatrix();

			//glTranslatef(50, 0, 0);
			glTranslatef(tx, ty, 0);
			glBegin(GL_QUADS);
				glColor3f(1.0, 0.0, 0.0);  // cor
				glVertex2f(-10, 10);
				glVertex2f(40, 10);
				glVertex2f(40, -10);
				glVertex2f(-10, -10);
			glEnd();
		glPopMatrix();

	}

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

	//TUBARAIO
	glPushMatrix();
	glTranslatef(-40, 0, 0);
		glPushMatrix();
			glColor3f(0.0, 1.0, 0.0);  // cor
			glTranslatef(-13, 0, 0);
			raioX = 40.0f, raioY = 10.0f;
			glBegin(GL_POLYGON);
			for (int i = 0; i < circ_pnt; i++)
			{
				ang = (2 * PI * i) / circ_pnt;
				glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
			}
			glEnd();
		glPopMatrix();
		//barbatana emcima
		glPushMatrix();

		glTranslatef(0, 10, 0);
			glColor3f(0.0, 1.0, 0.0);  // cor
			glBegin(GL_TRIANGLES);
				glVertex2f(-5, 15);
				glVertex2f(-10, -10);
				glVertex2f(10, -10);
			glEnd();

		glPopMatrix();

		//boca
		glPushMatrix();
			glTranslatef(-2, 6, 0);
			glColor3f(0.0, 1.0, 0.0);  // cor
			glBegin(GL_TRIANGLES);
				glVertex2f(-6, -25);
				glVertex2f(-8, -10);
				glVertex2f(8, -10);
			glEnd();

		glPopMatrix();

		//rabo1
		glPushMatrix();
			glTranslatef(-45, 5, 0);
			glColor3f(0.0, 1.0, 0.0);  // cor
			glBegin(GL_TRIANGLES);
				glVertex2f(-15, 20);
				glVertex2f(-10, -8);
				glVertex2f(10, -8);
			glEnd();

		glPopMatrix();

		//rabo2
		glPushMatrix();
			glTranslatef(-45, 5, 0);
			glColor3f(0.0, 1.0, 0.0);  // cor
			glBegin(GL_TRIANGLES);
				glVertex2f(-10, -15);
				glVertex2f(-10, -8);
				glVertex2f(10, -8);
			glEnd();

		glPopMatrix();

		//boca
		glPushMatrix();
			glTranslatef(15, -7, 0);
			glColor3f(0.0, 1.0, 0.0);  // cor
			glBegin(GL_TRIANGLES);
				glVertex2f(-10, 3);
				glVertex2f(12, -3);
				glVertex2f(5, 5);
			glEnd();

		glPopMatrix();

		//boca
		glPushMatrix();
			glTranslatef(25, -2, 0);
			glColor3f(0.0, 0.0, 0.0);  // cor
			glPointSize(3.0f);
			glBegin(GL_POINTS);

				glVertex2f(-10, 3);
			glEnd();

		glPopMatrix();
	glPopMatrix();

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