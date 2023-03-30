// animação
////////////////////////////////////////////////////////////////////////
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
float angulo = 0;
bool virar = false;
// incremento em variaveis.
float xStep = 4;
float yStep = 4;
void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void anima(int valor);
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // suporte a janelas
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("animação"); // cria janela
	//glutFullScreen();
	glutReshapeFunc(tela); // configura a tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama teclado
	glutTimerFunc(1, anima, 1);
	glutTimerFunc(1, afunda, 1);
	glutMainLoop(); // redesenhar
	return(0);
}
void afunda(int valor) {

	if (virar) {
		angulo = 1;
	}
	if (a) {

	}


	glutPostRedisplay();
	glutTimerFunc(150, afunda, 1);
}
void anima(int valor)
{
	if ((tx) > (300 + 10) || (tx) < (-1))
	{
		xStep = -xStep;
	}
	//if ((ty) > (200-50) || (ty) < (-100))
	//{
	//	yStep = -yStep;
	//}
	tx += xStep;
	//ty += yStep;
/*	printf("\n topo %.2f pe %.2f direita %.2f esquerda% .2f\n",((janela_altura)/2),
		(((janela_altura) / 2) * -1),
		((janela_largura) / 2),
		(((janela_largura) / 2) * -1));
	printf("\n step x %.2f step y %.2f\n", xStep, yStep);
	printf("\n tx %.2f ty %.2f\n", tx, ty)*/;
	glutPostRedisplay();
	glutTimerFunc(150, anima, 1);
}
void keyboard(unsigned char tecla, int x, int y)
{
	//printf("\ntecla %c\n", tecla);
	//printf("\n\nDigite 1 translacao x, 2 translacao y: ");
	//printf("\ntecla %c\n", tecla);
	//printf("\no mouse estava em %d x %d\n", x, y);
}

void desenhar()
{
	glLoadIdentity();
	glTranslatef(50, 0, 0);

	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 200.0f, raioY = 120.0f;
	glColor3f(1.0, 0.5, 1.0); // cor 


	//PEDRA
	glPushMatrix();
	glTranslatef(500, 80, 0);
	raioX = 60.0f, raioY = 60.0f;
	glColor3f(0.5, 0.5, 0.5); // cor 
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
	glPopMatrix();

	//MAR
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0); // cor
	glVertex2f(0, 0);
	glVertex2f(550, 0);
	glVertex2f(550, 70);
	glVertex2f(0, 70);
	glEnd();

	//ILHA
	ang, raioX = 200.0f, raioY = 120.0f;
	//glColor3b(139, 69, 19); // cor 
	glColor3f(0.54, 0.27, 0.07); // cor 
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	//SOL
	glPushMatrix();
	glTranslatef(450, 300, 0);
	raioX = 60.0f, raioY = 60.0f;
	glColor3f(1, 1, 0); // cor 
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		//printf("%f %f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	
	glPopMatrix();
	glTranslatef(50, 0, 0);
	glTranslatef(tx, ty, 0.0f);

	//BARCO
	glRotatef(angulo, 1, 0, 0);
	glColor3f(0.6, 0, 0); // cor 
	glBegin(GL_POLYGON);
	glVertex2f(150, 70);
	glVertex2f(200, 70);
	glVertex2f(210, 80);
	glVertex2f(140, 80);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(177, 80);
	glVertex2f(177, 120);
	glVertex2f(174, 120);
	glVertex2f(174, 80);
	glEnd();

	glColor3f(1, 1, 1); // cor 

	glBegin(GL_TRIANGLES);
	glVertex2f(177, 120);
	glVertex2f(195, 100);
	glVertex2f(177, 100);
	glEnd();
	// Especificar o local aonde o desenho acontece: bem no centro da janela

	//glBegin(GL_QUADS);
	//glColor3f(1.0, 1.0, 0.0); // cor
	//	glVertex2f(-30, 30);
	//	glVertex2f(-10, 30);
	//	glVertex2f(-10, 50);
	//	glVertex2f(-30, 50);
	//glEnd();
}

void display()
{
	glMatrixMode(GL_MODELVIEW); //coordenadas de desenho
	glLoadIdentity();

	printf("Valor de tx: %f\n", tx);

	if (tx > 200) {
		angulo = 180;

	}
	else {
		// cor do fundo
	}
	glClearColor(0.0f, 0.75f, 1.0f, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA
	// Especificar o local aonde o desenho acontece: bem no centro da janela mais translacao
		//glTranslatef(janela_largura / 2, janela_altura/2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();
	glFlush(); // execute o desenho
}
void tela(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);
}