#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define DTR PI/180

float radiusCalc(float x, float y);
void orbit(float x1, float y1);
void stars();

GLfloat x=0, z=0, x0=0, z0=0;

GLfloat theta[] = {0.0, 0.0, 0.0};
GLfloat orbitTheta = 0.0;
GLint axis = 2; 	// When we start the program, object will rotate with respect to positive z

void objects() {

	// The Sun
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere(2.0, 100.0, 100.0);
	glPopMatrix();

	// Planets Orbits
	orbit(2.5, 2.5);
	orbit(3.5, 3.5);
	orbit(4.5, 4.5);
	orbit(5.5, 5.5);
	orbit(6.5, 6.5);
	orbit(8.0, 8.0);
	orbit(10.0, 10.0);
	orbit(12.0, 12.0);
	orbit(14.5, 14.5);

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Pluto
        glPushMatrix();
                glRotatef(orbitTheta+359, 0.0, 1.0, 0.0);
                glTranslatef(-14.5, 0.0, -14.5);
                glColor3f(0.5, 0.5, 0.6);
                glutSolidSphere(0.15, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Neptune
        glPushMatrix();
                glRotatef(orbitTheta+45, 0.0, 1.0, 0.0);
                glTranslatef(-12.0, 0.0, -12.0);
                glColor3f(0.0, 0.8, 1.0);
                glutSolidSphere(0.65, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Uranus
        glPushMatrix();
                glRotatef(orbitTheta+209, 0.0, 1.0, 0.0);
                glTranslatef(-10.0, 0.0, -10.0);
                glColor3f(0.0, 0.8, 1.0);
                glutSolidSphere(0.60, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Saturn
        glPushMatrix();
                glRotatef(orbitTheta+54, 0.0, 1.0, 0.0);
                glTranslatef(-8.0, 0.0, -8.0);
                glColor3f(1.0, 0.9, 0.0);
                glutSolidSphere(0.70, 100.0, 100.0);
		// Rings
		GLUquadricObj *object1;
		object1 = gluNewQuadric();
		gluQuadricDrawStyle(object1, GLU_LINE);
		glColor3f(0.85, 0.7, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		gluDisk(object1, 0, 1.25, 40, 50);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Jupiter
        glPushMatrix();
                glRotatef(orbitTheta+12, 0.0, 1.0, 0.0);
                glTranslatef(-6.5, 0.0, -6.5);
                glColor3f(1.0, 0.8, 0.0);
                glutSolidSphere(0.75, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Mars
        glPushMatrix();
                glRotatef(orbitTheta+253, 0.0, 1.0, 0.0);
                glTranslatef(-5.5, 0.0, -5.5);
                glColor3f(1.0, 0.2, 0.0);
                glutSolidSphere(0.35, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Earth
        glPushMatrix();
                glRotatef(orbitTheta+43, 0.0, 1.0, 0.0);
                glTranslatef(-4.5, 0.0, -4.5);
                glColor3f(0.0, 0.8, 0.7);
                glutSolidSphere(0.45, 100.0, 100.0);
		// The Moon
		glTranslatef(-0.8, 0.0, 0.0);
		glColor3f(0.8, 0.8, 0.8);
		glutSolidSphere(0.15, 100.0, 100.0);
        glPopMatrix();

        glRotatef(orbitTheta, 0.0, 1.0, 0.0);
        // Venus
        glPushMatrix();
                glRotatef(orbitTheta+180, 0.0, 1.0, 0.0);
                glTranslatef(-3.5, 0.0, -3.5);
                glColor3f(0.8, 0.6, 0.0);
                glutSolidSphere(0.45, 100.0, 100.0);
        glPopMatrix();

	// Mercury
        glPushMatrix();
                glRotatef(orbitTheta+300, 0.0, 1.0, 0.0);
                glTranslatef(-2.5, 0.0, -2.5);
                glColor3f(0.5, 0.5, 0.0);
                glutSolidSphere(0.25, 100.0, 100.0);
        glPopMatrix();

}

void orbit(float x1, float y1) {
	glLineWidth(2.0);
	glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
                for(int i=0; i<360; i++) {
                        x = x0 + radiusCalc(x1, y1) * cos(DTR*i);        // x coordinate of 1 point o>
                        z = z0 + radiusCalc(x1, y1) * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x, 0, z);                       // x and y verteces
                        x = x0 + radiusCalc(x1, y1) * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        z = z0 + radiusCalc(x1, y1) * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x, 0, z);                       // x and y verteces
                }
        glEnd();

}

void stars() {
	srand(time(NULL));
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 1.0);
	for(int i=0; i<50; i++) {
		float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
		float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
		glBegin(GL_POINTS);
			glVertex3f(x2, y2, -10);
		glEnd();
	}
        for(int i=0; i<50; i++) {
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, (-1)*y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, (-1)*y2, -10);
                glEnd();
        }

}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

	        // Calls Stars Function
	        stars();

		glPushMatrix();
			// Rotations
			glRotatef(15.0, 1.0, 0.0, 0.0);

			glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
			glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
			glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis
			objects();
		glPopMatrix();

        glFlush();
	glutSwapBuffers();
}

void idle() {
	// Increments theta when called
	theta[axis] += 1;
	orbitTheta += 0.05;
	if(theta[axis] > 360.0) {
		theta[axis] -= 360;
	}
	if(orbitTheta > 360.0) {
		orbitTheta -= 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Black Background
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-10.0, 10.0, -10.0*(GLfloat) h / (GLfloat) w,
			10.0*(GLfloat) h / (GLfloat) w, -20.0, 20.0);
	} else {
		glOrtho(-10.0*(GLfloat) w/(GLfloat) h, 10.0 * (GLfloat) w/ (GLfloat) h,
			-10.0, 10.0, -20.0, 20.0);
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

float radiusCalc(float x, float y) {
	GLfloat radius = sqrt(pow(x, 2) + pow(y, 2));
	return radius;
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);

        // Windowing:
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0.0, 0.0);

        glutCreateWindow("My Planets");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        glutMainLoop();
}
