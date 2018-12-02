#include <stdlib.h>
#include <GL/glut.h>

GLfloat jumpMax = 2.3f;
GLfloat jumpSpeed = 0.05f;
GLfloat player_posY = -4.0f;
GLfloat player_posX = -6.0f;
GLfloat posMax = -2.0f;
GLfloat posMin = -4.0f;
GLfloat cone_posX = 4.0f;
GLint jump_count = 1;

static int window_width, window_height;


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void jump(int);
static void cone_move(int);

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);


    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    
    glutTimerFunc(25, cone_move, 0);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    case 'w':
	if(jump_count == 1)
		glutTimerFunc(0,jump, 0);
	break;
    }
}

static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;
}

static void jump(int value){
	
	if(player_posY <= posMax && jump_count == 1){
		player_posY += 0.1f;
	}
	else if(player_posY >= posMax){
		jump_count = 0;
	}
	
	if(player_posY >= posMin && jump_count == 0)
		player_posY -= 0.1f ;
	else if(player_posY <= posMin){
		player_posY = posMin;
		jump_count = 1;
		return;
	}

	glutPostRedisplay();
	glutTimerFunc(1000/60, jump, 0);
}

static void cone_move(int value){
	if(cone_posX >= -4.0){
		cone_posX -= 0.1;
		glutPostRedisplay();
		glutTimerFunc(25,cone_move, 0);
	}
}
static void on_display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            60,
            window_width/(float)window_height,
            1, 25);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 0, 15,
            0, 0, 0,
            0, 1, 0 
        );
	
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();

    //igrac
    glColor3f(0, 0.3,0.7);
    glPushMatrix();
    glTranslatef(player_posX, player_posY, 0);
    glutSolidCube(1);
    glPopMatrix();
    
    //prepreka
    glColor3f(0,1,0);
    glPushMatrix();
    glTranslatef(cone_posX,0,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(0.3,1,10,1);
    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();
}
