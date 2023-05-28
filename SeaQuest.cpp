#include <stdio.h> 
#include <stdlib.h> 
#include <GL/glut.h> 
#include <math.h> 
#define PI 3.1415926535898  

#define janela_altura 800
#define janela_largura 800

// velocidade do tubarão e do torpedo
float velocidadeTubarao = 1000;
float velocidadeTorpedo = 500;

//colisoes de cada objeto
int colisoes[] = { 0, 0, 0, 0 };

// posição do torpedo
float toX = 0.0;
float toY = 0.0;

// posição dos tubarões
float tuXD = 0.0;
float tuXE = 0.0;
float tuYD = 0.0;
float tuYE = 0.0;

//barra de oxigenio
float oxigenio = 300.0;

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
void animaTubaraoD(int valor);
void animaTubaraoE(int valor);
void animaOxigenio(int valor);
float calculaDistancia(int x1, int x2, int y1, int y2);

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
	glutTimerFunc(velocidadeTubarao, animaTubaraoD, 1);
	glutTimerFunc(velocidadeTubarao, animaTubaraoE, 1);
	glutTimerFunc(50, animaOxigenio, 1);

	glutMainLoop(); // redesenhar

	return(0);
}

void animaTorpedoD(int valor) {

	if (continuarD) {
		toX += xStep;

		glutPostRedisplay();
		glutTimerFunc(velocidadeTorpedo, animaTorpedoD, 1);
	}

}

void animaTorpedoE(int valor) {

	if (continuarE) {
		toX -= xStep;

		glutPostRedisplay();
		glutTimerFunc(velocidadeTorpedo, animaTorpedoE, 1);
	}
}

void animaTubaraoD(int valor) {
	tuXD += 10;
	
	glutPostRedisplay();
	glutTimerFunc(velocidadeTubarao, animaTubaraoD, 1);
}

void animaTubaraoE(int valor) {
	tuXE -= 10;

	glutPostRedisplay();
	glutTimerFunc(velocidadeTubarao, animaTubaraoE, 1);
}

void animaOxigenio(int valor) {
	if (oxigenio > -300) {
		oxigenio -= 1;
	}
	else {
		//aqui trata quando o oxigenio acaba
	}


	glutPostRedisplay();
	glutTimerFunc(50, animaOxigenio, 1);

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

		glutTimerFunc(velocidadeTorpedo, animaTorpedoD, 1);
		glutTimerFunc(velocidadeTorpedo, animaTorpedoE, 1);


		if (direita) {
			toX = transX + 110;
			toY = transY;
			continuarE = false;
			continuarD = true;
			exit;
		}
		else {
			toX = transX - 10;
			toY = transY;
			continuarD = false;
			continuarE = true;
			exit;
		}
		printf("FOGO!");

	}


	glutPostRedisplay();


}

void desenharTubaraoD(int posicaoX, int posicaoY) {
	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 40.0f, raioY = 10.0f;
	glTranslatef(posicaoX, posicaoY, 0);

	//TUBARAIO
	glPushMatrix();
	glTranslatef(-40, 0, 0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);  // cor
	glTranslatef(-13, 0, 0);

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

void desenharTubaraoE(int posicaoX, int posicaoY) {
	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 40.0f, raioY = 10.0f;
	glTranslatef(posicaoX, posicaoY, 0);

	//TUBARAIO
	glPushMatrix();
	glTranslatef(-40, 0, 0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);  // cor
	glTranslatef(-13, 0, 0);

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
	glVertex2f(-20, -10);
	glVertex2f(0, -10);
	glEnd();

	glPopMatrix();

	//barbatana de baixo 
	glPushMatrix();
	glTranslatef(-2, 6, 0);
	glColor3f(0.0, 1.0, 0.0);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(-6, -25);
	glVertex2f(-16, -10);
	glVertex2f(0, -10);
	glEnd();

	glPopMatrix();

	//rabo1
	glPushMatrix();
	glTranslatef(20, 5, 0);
	glColor3f(0.0, 1.0, 0.0);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(18, 20);
	glVertex2f(10, -8);
	glVertex2f(-10, -8);
	glEnd();

	glPopMatrix();

	//rabo2
	glPushMatrix();
	glTranslatef(30, -5, 0);
	glColor3f(0.0, 1.0, 0.0);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(-17, 0);
	glVertex2f(0, -8);
	glVertex2f(0, 8);
	glEnd();

	glPopMatrix();

	//boca
	glPushMatrix();
	glTranslatef(-35, -7, 0);
	glColor3f(0.0, 1.0, 0.0);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(10, 0);
	glVertex2f(-15, -5);
	glVertex2f(-5, 5);
	glEnd();
	glPopMatrix();

	//olho
	glPushMatrix();
	glTranslatef(-25, -2, 0);
	glColor3f(0.0, 0.0, 0.0);  // cor
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glVertex2f(-10, 3);
	glEnd();

	glPopMatrix();
	glPopMatrix();
}

void desenhaSubmarino() {
	GLfloat circ_pnt = 300;
	GLfloat ang, raioX = 10.0f, raioY = 10.0f;
	glTranslatef(0, 0, 0);



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
		}
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
}

void desenhar()
{
	//Ponto do meio da tela
	glColor3f(1.0, 0.0, 0.0);  // cor
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex2f(0, 0);
	glEnd();

	//tela de cima
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-400, 400);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-400, 250);
		glVertex2f(400, 250);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(400, 400);
	glEnd();

	//tela de baixo
	glBegin(GL_QUADS);
		glColor3f(0.66, 0.66, 0.66);
		glVertex2f(-400, -400);
		glVertex2f(-400, -250);
		glVertex2f(400, -250);
		glVertex2f(400, -400);
	glEnd();

	//barra de oxigenio total
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(-300, -350);
		glVertex2f(-300, -320);
		glVertex2f(300, -320);
		glVertex2f(300, -350);
	glEnd();

	//barra de oxigenio restante
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(-300, -350);
		glVertex2f(-300, -320);
		glVertex2f(oxigenio, -320);
		glVertex2f(oxigenio, -350);
	glEnd();

	//torpedo
	if (fogo) {

		glPushMatrix();

		//glTranslatef(50, 0, 0);
			glTranslatef(toX, toY, 0);
			glBegin(GL_QUADS);
				glColor3f(1.0, 0.0, 0.0);  // cor
				glVertex2f(-10, 4);
				glVertex2f(30, 4);
				glVertex2f(30, -4);
				glVertex2f(-10, -4);
			glEnd();
		glPopMatrix();

	}

	glPushMatrix();
		desenhaSubmarino();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(tuXD, tuYD, 0);
		if (calculaDistancia(tuXD - 400, toX, tuYD + 200, toY) < 15) {
			colisoes[0] = 1;
		}
		if (colisoes[0] == 0) {
			desenharTubaraoD(-300, 200);
		}
		
		
	glPopMatrix();

	glPushMatrix();
		glTranslatef(tuXD, tuYD, 0);
		if (calculaDistancia(tuXD - 400, toX, tuYD - 200, toY) < 15) {
			colisoes[1] = 1;
		}
		if (colisoes[1] == 0) {
			desenharTubaraoD(-300, -200);
		}
	
		
	glPopMatrix();

	glPushMatrix();
		glTranslatef(tuXE, tuYE, 0);
		if (calculaDistancia(tuXE + 200, toX, tuYE + 100, toY) < 15) {
			colisoes[2] = 1;
		}
		if (colisoes[2] == 0) {
			desenharTubaraoE(300, 100);
		}
		
	

	glPopMatrix();

	glPushMatrix();
		glTranslatef(tuXE, tuYE, 0);

		if (calculaDistancia(tuXE + 200, toX, tuYE - 100, toY) < 15) {
			colisoes[3] = 1;
		}
		if (colisoes[3] == 0) {
			desenharTubaraoE(300, -100);
		}
		

			
		
		
	glPopMatrix();
}

float calculaDistancia(int x1, int x2, int y1, int y2) {
	float distX = x2 - x1;
	float distY = y2 - y1;
	float distancia = sqrt(pow(distX, 2) + pow(distY, 2));
	printf("A distancia eh de : %f \n", distancia);
	if (distancia < 15) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	return distancia;
}

void Verificacolisao() {
	
}


void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	//tratando colisão
	//if (transX > -10)
	//{
	//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo

	//}
	//else if (transX < -95 * 2 - 10)
	//{
	//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	//}
	//else if (transY > 100) {
	//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	//}
	//else if (transY < -100) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	//}
	//else
	//{
	//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor do fundo
	//}

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPEZA

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


	//TODO
	//
	//colisão com tubarões
	//pessoinha e colisão com ela
	//vida
	//esgotar tempo e morrer



}