#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2; 	// When we start the program, object will rotate with respect to positivez

double dimension = 3.0;

void cubeObject( ) {
	// Top
	glColor3f(1, 1, 1);	// White
	glBegin(GL_POLYGON);
		glVertex3f(1, 1, 1);
		glVertex3f(1, 1, -1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, 1, 1);
	glEnd();

	// Bottom
	glColor3f(1, 1, 0);	// Yellow
	glBegin(GL_POLYGON);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(-1, -1, -1);
		glVertex3f(-1, -1, 1);
	glEnd();

	glColor3f(0, 0, 0.8);	// Blue
	// Right
	glBegin(GL_POLYGON);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, 1, -1);
		glVertex3f(1, 1, 1);
	glEnd();


		glColor3f(0, 0.8, 0);	// Green
	// Left
        glBegin(GL_POLYGON);

			glVertex3f(-1, -1, 1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, 1, 1);
        glEnd();

		glColor3f(1, 0.5, 0);	// Orange
		// Back
		glBegin(GL_POLYGON);
			glVertex3f(1, -1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(1, 1, -1);
        glEnd();

		glColor3f(1, 0, 0);	// Red
        // Front
        glBegin(GL_POLYGON);
			glVertex3f(1, -1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(-1, 1, 1);
			glVertex3f(1, 1, 1);
        glEnd();

		// LINE BORDER FOR CUBE

		glLineWidth(10.0);
        glColor3f(0, 0, 0);     // Black

        // Right
        glBegin(GL_LINE_LOOP);
                glVertex3f(1, -1, 1);
                glVertex3f(1, -1, -1);
                glVertex3f(1, 1, -1);
                glVertex3f(1, 1, 1);
        glEnd();

        // Left
        glBegin(GL_LINE_LOOP);

                        glVertex3f(-1, -1, 1);
                        glVertex3f(-1, -1, -1);
                        glVertex3f(-1, 1, -1);
                        glVertex3f(-1, 1, 1);
        glEnd();

                // Back
                glBegin(GL_LINE_LOOP);
                        glVertex3f(1, -1, -1);
                        glVertex3f(-1, -1, -1);
                        glVertex3f(-1, 1, -1);
                        glVertex3f(1, 1, -1);
        glEnd();

        // Front
        glBegin(GL_LINE_LOOP);
                        glVertex3f(1, -1, 1);
                        glVertex3f(-1, -1, 1);
                        glVertex3f(-1, 1, 1);
                        glVertex3f(1, 1, 1);
        glEnd();

		// Middle Line Sections

		double val = 1.0/dimension;

		// Middle1
		glBegin(GL_LINE_LOOP);
                glVertex3f(-val, -1, 1);
                glVertex3f(-val, -1, -1);
                glVertex3f(-val, 1, -1);
                glVertex3f(-val, 1, 1);
        glEnd();

		// Middle2
		glBegin(GL_LINE_LOOP);
                glVertex3f(val, -1, 1);
                glVertex3f(val, -1, -1);
                glVertex3f(val, 1, -1);
                glVertex3f(val, 1, 1);
        glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(1, -val, 1);
			glVertex3f(1, -val, -1);
			glVertex3f(-1, -val, -1);
			glVertex3f(-1, -val, 1);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(1, val, 1);
			glVertex3f(1, val, -1);
			glVertex3f(-1, val, -1);
			glVertex3f(-1, val, 1);
		glEnd();

		glBegin(GL_LINE_LOOP);
                        glVertex3f(1, -1, -val);
                        glVertex3f(-1, -1, -val);
                        glVertex3f(-1, 1, -val);
                        glVertex3f(1, 1, -val);
        glEnd();

        glBegin(GL_LINE_LOOP);
                        glVertex3f(1, -1, val);
                        glVertex3f(-1, -1, val);
                        glVertex3f(-1, 1, val);
                        glVertex3f(1, 1, val);
        glEnd();
}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		// Rotations
		glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
		glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
		glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis

		cubeObject();	// Will call the cube object which contains the verteces
        glFlush();
		glutSwapBuffers();
}

void idle() {
	theta[axis] += 1;
	if(theta[axis] > 360.0) {
		theta[axis] = theta[axis] - 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glClearColor(0.7, 0.7, 0.7, 0.0);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-2.0, 2.0, -2.0*(GLfloat) h / (GLfloat) w, 
			2.0*(GLfloat) h / (GLfloat) w, -10.0, 10.0);
	} else {
		glOrtho(-2.0*(GLfloat) w/(GLfloat) h, 2.0 * (GLfloat) w/ (GLfloat) h,
			-2.0, 2.0, -10.0, 10.0);
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
