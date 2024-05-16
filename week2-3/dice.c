#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2; 	// When we start the program, object will rotate with respect to positive z
GLfloat x0 = 0, y2 = 0, z0 = 0, radius = 0.5, x = 0, y = 0, z = 0;

void drawDot1(float xOff, float yOff, float zOff);
void drawDot2(float xOff, float yOff, float zOff);
void drawDot3(float xOff, float yOff, float zOff);

void objects() {

	glLineWidth(10.0);

        glPushMatrix();
                glColor3f(1.0, 1.0, 1.0);
                glutSolidCube(5.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(5.0);
        glPopMatrix();

	// One
	drawDot1(0.0, 2.55, 0.0);

	// Six
	drawDot1(1.2, -2.55, 1.2);
        drawDot1(0.0, -2.55, 1.2);
        drawDot1(-1.2, -2.55, 1.2);
        drawDot1(1.2, -2.55, -1.2);
        drawDot1(0.0, -2.55, -1.2);
        drawDot1(-1.2, -2.55, -1.2);

	// Two
	drawDot2(0.8, 0.8, -2.55);
        drawDot2(-0.8, -0.8, -2.55);

	// Five
	drawDot2(0.0, 0.0, 2.55);
	drawDot2(1.2, 1.2, 2.55);
        drawDot2(1.2, -1.2, 2.55);
        drawDot2(-1.2, 1.2, 2.55);
        drawDot2(-1.2, -1.2, 2.55);

	// Four
	drawDot3(2.55, 1.2, 1.2);
        drawDot3(2.55, -1.2, 1.2);
        drawDot3(2.55, 1.2, -1.2);
        drawDot3(2.55, -1.2, -1.2);

	// Three
	drawDot3(-2.55, 0.0, 0.0);
        drawDot3(-2.55, 1.2, 1.2);
        drawDot3(-2.55, -1.2, -1.2);

}

void drawDot1(float xOff, float yOff, float zOff) {
        x=0,y=0,z=0;
        glBegin(GL_POLYGON);
                for(int i=0; i<360; i++) {
                        x = x0 + radius * cos(DTR*i);        // x coordinate of 1 point o>
                        z = z0 + radius * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                        x = x0 + radius * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        z = z0 + radius * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                }
        glEnd();
}

void drawDot2(float xOff, float yOff, float zOff) {
        x=0,y=0,z=0;
        glBegin(GL_POLYGON);
                for(int i=0; i<360; i++) {
                        x = x0 + radius * cos(DTR*i);        // x coordinate of 1 point o>
                        y = y2 + radius * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                        x = x0 + radius * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        y = y2 + radius * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                }
        glEnd();
}

void drawDot3(float xOff, float yOff, float zOff) {
	x=0,y=0,z=0;
        glBegin(GL_POLYGON);
                for(int i=0; i<360; i++) {
                        z = z0 + radius * cos(DTR*i);        // x coordinate of 1 point o>
                        y = y2 + radius * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                        z = z0 + radius * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        y = y2 + radius * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x+xOff, y+yOff, z+zOff);                       // x and y verteces
                }
        glEnd();
}


void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// Rotations
		glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
		glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
		glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis
		objects();
        glFlush();
	glutSwapBuffers();
}

void idle() {
	// Increments theta when called
	theta[axis] += 1;
	if(theta[axis] > 360.0) {
		theta[axis] -= 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glClearColor(0.7, 0.7, 0.7, 0.0);	// Grey Background
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-6.0, 6.0, -6.0*(GLfloat) h / (GLfloat) w,
			6.0*(GLfloat) h / (GLfloat) w, -10.0, 10.0);
	} else {
		glOrtho(-6.0*(GLfloat) w/(GLfloat) h, 6.0 * (GLfloat) w/ (GLfloat) h,
			-6.0, 6.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
	if(key == 'r') glutIdleFunc( idle );
	if(key == 's') glutIdleFunc( NULL );
	if(key == 'q') exit(0);
}

void myMouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);

        // Windowing:
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0.0, 0.0);

        glutCreateWindow("My Cube");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        glutMainLoop();
}
