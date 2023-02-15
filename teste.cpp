// aula 3 ----- primitivas programa minimo
//////////////////////////////////////////

#include <stdlib.h>
#include <GL/glut.h>


void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);

#define janela_altura 400
#define janela_largura 400


int main(int argc, char** argv)///esses argmentos q o proprio windos vai pasar pro opnegl
{
    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA
    ///GLUT_SINGLE a tela é feita na ram e depois apresetada, poderia ser GLUT_DOUBLE quando uma tá sendo apresentada e outra tá sendo contruida simultaneamente na memoria ram
    glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela

    //glutFullScreen();  // full screen

    glutInitWindowPosition(10, 300); // posicao inicial da janela

    glutCreateWindow("GLUT Test wagner---- exercicio de glut");   /// cria a janela

    glutKeyboardFunc(&keyboard);

    glutReshapeFunc(&resize); // 

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    }
}

void resize(GLsizei w, GLsizei h)
{

    if (h == 0) h = 1;  // Evita a divisao por zero

    glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);///matriz fantasma
    glLoadIdentity();///limpe a memoria


    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)
    {
        gluOrtho2D(0.0f, janela_largura, 0.0f, janela_altura * h / w);
    }
    else
    {
        gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
    }
    glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    
}

void display()
{
    glMatrixMode(GL_MODELVIEW);///matriz de modelagem
    glLoadIdentity();
   // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);  // cor do fundo
    glClearColor(0, 191, 255, 0);
    ///  f de float poderia glClearColor(1, 0, 0, 1); ou variavel

    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo (setada na linha de cima)

    ///desenho do quadrado
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(-50.0, 50);
        glVertex2f(50, 50);
        glVertex2f(50, -50.0);
        glVertex2f(-50, -50);
    glEnd();
    ///desenho da porta
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-50.0, -50);
        glVertex2f(-30, -50);
        glVertex2f(-30, -30.0);
        glVertex2f(-50, -30);
    glEnd();

    ///desenho da janela
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0, 0);
        glVertex2f(0, 30);
        glVertex2f(-30, 30.0);
        glVertex2f(-30, 0);
    glEnd();

    //desenho de pontos
    glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        
        glVertex2f(10, 20);
        glVertex2f(20, 20);
        glVertex2f(10, 10);
        glVertex2f(20, 10);
    glEnd();

    //desenho do triangulo
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2f(-50, 50);
        glVertex2f(50, 50);
        glVertex2f(0, 80);
    glEnd();

    //desenho de linas
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);

        glVertex2f(100, 200);
        glVertex2f(100, 300);

        glVertex2f(120, 200);
        glVertex2f(120, 300);
    glEnd();

    //linhas ligadas
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);

        glVertex2f(130, 200);
        glVertex2f(130, 300);

        glVertex2f(150, 200);
        glVertex2f(150, 300);

        glVertex2f(200, 300);
    glEnd();

   
    glFlush(); // executa o desenho quando o programa é single, se for double é o glSuap()
    


}

