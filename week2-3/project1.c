#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2; 	// When we start the program, object will rotate with respect to positive z

void objects() {
	//glLineWidth(3.0);
	// Wire & Solid Cube
	/*
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1.0);
	*/

	//glScalef(2.0, 1.0, 1.0);

	glRotatef(15, 0.0, 0.0, 0.3);

	// Rectangle Base
	glPushMatrix();
		glTranslatef(0.0, -4.0, 0.0);
		glScalef(2.0, 0.5, 2.0);
		glColor3f(0.7, 0.7, 0.0);
		glutSolidCube(6.0);
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0);
		glutWireCube(6.0);
	glPopMatrix();

	// Bottom Sphere
	glPushMatrix();
		glTranslatef(0.0, -1.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1.5, 100.0, 100.0);
	glPopMatrix();

	// Bottom Cube
        glPushMatrix();
		glRotatef(45.0, 0.0, 0.0, 1.0);
                glTranslatef(-0.65, 1.5, 0.0);
                glColor3f(1.0, 0.0, 1.0);
                glutSolidCube(1.5);
        glPopMatrix();

	// Second Sphere
        glPushMatrix();
                glTranslatef(-0.6, 1.45, 0.0);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(0.55, 100.0, 100.0);
        glPopMatrix();

	// Second Cube
        glPushMatrix();
                glRotatef(45.0, 0.0, 0.0, 1.0);
		glRotatef(10.0, 1.0, 0.0, 0.0);
		glRotatef(10.0, 0.0, 1.0, 0.0);
                glTranslatef(1.5, 1.5, 0.0);
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(0.75);
        glPopMatrix();

	// Third Sphere
        glPushMatrix();
                glTranslatef(-0.55, 2.6, 0.2);
                glColor3f(0.0, 1.0, 1.0);
                glutSolidSphere(0.35, 100.0, 100.0);
        glPopMatrix();

	//glutSolidSphere(2.0, 100, 100);

	//glTranslatef(0.5, -0.5, 0.5);
	//glScalef(1.0, -2.0, 0.5);

	//glScalef(2.0, 3.0, 1.0);
	//glColor3f(0.0, 0.0, 1.0);
	//glutWireCube(1.0);

	// Wire & Solid Cone
	/*
	glColor3f(1.0, 0.0, 0.0);
	glutWireCone(1.0, 0.5, 100, 100);
	glutSolidCone(1.0, 0.5, 100, 100);
	*/

	/*
	// Wire & Solid Torus (Donut)
	glColor3f(1.0, 0.0, 0.0);
//	glutWireTorus(0.5, 1.0, 10.0, 10.0);
	glutSolidTorus(0.5, 1.0, 100.0, 100.0);
	*/

	/*
	// Wire & Solid UTAH TEAPOT
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(1.0);
	glutSolidTeapot(1.0);
	*/

	// Wire & Solid Platonic Solids
	//glColor3f(1.0, 0.0, 0.0);
	//glutWireTetrahedron();
	//glutWireOctahedron();
	//glutWireDodecahedron();


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
