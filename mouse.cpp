// rotacao – translação e escala
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 400
#define janela_largura 600
float rotacaoQ = 1;
float rotacaoT = 1;
float rotacaoR = 1;
float zoomQ = 1;
float zoomT = 1;
float zoomR = 1;
float transX = 1;
float transY = 1;
int mousex = 0;
int mousey = 0;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void mouse(int botao, int estado, int x, int y);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // PADRAO DE CORES
	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("rotacao escala e  translacao"); // cria janela

	//glutFullScreen();
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	//glutKeyboardFunc(&keyboard);  // chama teclado
	glutMouseFunc(mouse);
	glutMainLoop(); // redesenhar

	return(0);
}

void mouse(int botao, int estado, int x, int y) {
	printf("\Botao %i\n", botao);
	printf("\nEstado %i\n", estado);
	printf("\nX %i\n", x);
	printf("\nY %i\n", y);
	mousex = x;
	mousey = -y;

}

void keyboard(unsigned char tecla, int x, int y)
{
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda, 2 para direita: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);
	if (tecla == '1')
	{
		rotacaoQ = rotacaoQ + 2;
		printf("\n o valor de rotacao e %.2f\n", rotacaoQ);
	}
	if (tecla == '2')
	{
		rotacaoQ = rotacaoQ - 2;
		printf("\n o valor de escala e %.2f\n", rotacaoQ);
	}

	if (tecla == '3')
	{
		rotacaoT = rotacaoT + 2;
		printf("\n o valor de rotacao e %.2f\n", rotacaoT);
	}
	if (tecla == '4')
	{
		rotacaoT = rotacaoT - 2;
		printf("\n o valor de escala e %.2f\n", rotacaoT);
	}
	
	if (tecla == '5')
	{
		rotacaoR = rotacaoR + 2;
		printf("\n o valor de rotacao e %.2f\n", rotacaoR);
	}
	if (tecla == '6')
	{
		rotacaoR = rotacaoR - 2;
		printf("\n o valor de escala e %.2f\n", rotacaoR);
	}
	if (tecla == '7')
	{
		zoomQ = zoomQ + 0.1;
		printf("\n o valor do zoom e %.2f\n", zoomQ);
	}
	if (tecla == '8')
	{
		zoomT = zoomT + 0.1;
		printf("\n o valor do zoom e %.2f\n", zoomT);
	}
	if (tecla == '9')
	{
		zoomR = zoomR + 0.1;
		printf("\n o valor do zoom e %.2f\n", zoomR);
	}
	if (tecla == '0') {
		zoomR = 1;
		zoomQ = 1;
		zoomT = 1;
	
	}
	if (tecla == 'a') {
		transX = transX - 10;
	}
	if (tecla == 'd') {
		transX = transX + 10;
	}
	if (tecla == 's') {
		transY = transY - 10;
	}
	if (tecla == 'w') {
		transY = transY + 10;
	}

	glutPostRedisplay();


}



void desenhar()
{
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.0);  // cor
		glVertex2f(0, 0);
		glVertex2f( - 30,  - 50);
		glVertex2f( + 30,  - 50);
	glEnd();


	
}

void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA

	// Especificar o local aonde o desenho acontece: bem no centro da janela mais translacao
	//glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glTranslatef(0, janela_altura, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.0);  // cor
		glVertex2f(mousex, mousey);
		glVertex2f(mousex - 30, mousey - 50);
		glVertex2f(mousex + 30, mousey - 50);
	glEnd();

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