// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#define PI 3.14159
#define DTR PI/180

int x = 0, y = 0;

void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // Block
        glColor3f(0.0, 1.0, 0.0);   // Green
        glBegin(GL_POLYGON);
                glVertex2f(x+0.3, y+0.3);
                glVertex2f(x+0.3, y-0.3);
                glVertex2f(x-0.3, y-0.3);
                glVertex2f(x-0.3, y+0.3);
        glEnd();

        glFlush();
	glutSwapBuffers();
}

void stop() {
        glutPostRedisplay();
}

void rotate() {
        x += 1;
        stop();
}


void reshape(int w, int h) {
	//glClearColor(0.0, 0.0, 0.2, 0.0);		// Space Blue
        glClearColor(0.0, 0.0, 0.0, 0.0);		// Black

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
                glOrtho(-6.0, 6.0, -6.0*(GLfloat) h / (GLfloat) w,
                        6.0*(GLfloat) h / (GLfloat) w, -9.0, 9.0);
        } else {
                glOrtho(-6.0*(GLfloat) w/(GLfloat) h, 6.0 * (GLfloat) w/ (GLfloat) h,
                        -6.0, 6.0, -9.0, 9.0);
        }
	glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
        if(key == 'q' || key == 27) exit(0);
        if(key == 'p') glutIdleFunc( NULL );
        switch (key) {
        case 'd':
                x += 1;
                //y -= 0.1;
                glutPostRedisplay();
                break;
        case 'a':
                x -= 1;
                //y -= 0.1;
                glutPostRedisplay();
                break;
        case 'w':
                glutIdleFunc( rotate );
                break;
        case 'q':
                exit(0);
                break;
        }
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);

        // Windowing:
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(0.0, 0.0);

        glutCreateWindow("TETRIS");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
	glutKeyboardFunc( myKeyboard );
        glutMainLoop();
}
