#include <stdio.h>  
#include <stdlib.h> 
#include <GL/glut.h>  
#include <math.h> 

#define janela_altura 480  
#define janela_largura 640  
int on = 1;
float x = 0.0, y = 0.0, z = 0.0;
void reshape(GLsizei largura, GLsizei altura);
void display();
void keyboard(unsigned char key, int a, int b);
void conf_luz();

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Ligar GLUT 
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer  
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela  
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela  
	glutCreateWindow("iluminacao"); // Criar Janela 
	conf_luz(); // configuração de luz 
	glutDisplayFunc(display); // imagem 
	glutReshapeFunc(reshape); // config telas 
	glutKeyboardFunc(keyboard); // funcoes de teclado 
	glutMainLoop(); // loop 
	return 0;
}
void conf_luz(void)
{
	float ambiente[] = { 0.0, 0.0, 0.0, 1.0 };
	//float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float posicao1[] = { 0.0 + sin(x * 2 * 3.14 / 360), 3.0, 2.0 + sin(x * 2 * 3.14 / 360), 0.0 };   
	float lmodel_ambiente[] = { 0.4, 0.4, 0.4, 1.0 };
	float local_view[] = { 0.0 };

	GLfloat lightColor1[] = { 0.86, 0.86, 0.86, 1.0f };


	//luz 1
	GLfloat silverLightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/*GLfloat silverLightPosition[] = { 0.0f, 1.0f, 1.0f, 0.0f };*/
	GLfloat silverLightPosition[] = { 0.0 + sin(x * 2 * 3.14 / 360), 3.0, 2.0 + sin(x * 2 * 3.14 / 360), 0.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, silverLightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, silverLightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, silverLightPosition);

	//luz 2
	GLfloat copperLightColor[] = { 0.8f, 0.4f, 0.2f, 1.0f };
	//GLfloat copperLightPosition[] = { 2.0f, 1.0f, 1.0f, 0.0f };
	GLfloat copperLightPosition[] = { 1.0 + sin(x * 2 * 3.14 / 360), 3.0, 2.0 + sin(x * 2 * 3.14 / 360), 0.0 };

	glLightfv(GL_LIGHT1, GL_DIFFUSE, copperLightColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, copperLightColor);
	glLightfv(GL_LIGHT1, GL_POSITION, copperLightPosition);

	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

}
void reshape(GLsizei largura, GLsizei altura)
{

	if (altura == 0) altura = 1; // previne a divisão por zero  
	GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;  


	glViewport(0, 0, largura, altura);

	glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção  
	glLoadIdentity(); // zerando a matriz 
	gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia  
	glEnable(GL_DEPTH_TEST); // alunos devem testar 
	glShadeModel(GL_SMOOTH); // acabamento com suavização 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva 
}  
void display()
{
	//float padrao[] = { 0.0, 0.0, 0.0, 1.0 };
	//float mat_ambientee[] = { 0.82, 0.82, 0.82, 1.0 };
	//float mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	//float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//float alto_brilho[] = { 25.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza  
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos   


	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f); // posiciona a piramide   
	GLfloat materialAmbient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
	GLfloat materialDiffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat materialSpecular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	GLfloat shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);


	glutSolidSphere(1.0, 60, 60);


	glTranslatef(3.0f, 0.0f, 0.0f);
	glutSolidCube(1.5);

	glutSwapBuffers(); // trocar a matriz da tela por esta aqui.  
}  

void keyboard(unsigned char key, int a, int b)
{
	switch (key)
	{
		case 'x':
		{
			x += 10.0;
			conf_luz();
			glutPostRedisplay();
		} break;
		case 'o':
		{
			if (on)
			{
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				on = 0;
			}
			else
			{
				glEnable(GL_LIGHT0);   
				glDisable(GL_LIGHT1);
				on = 1;
			}
			glutPostRedisplay();   
		} 
	break;
	}
}
