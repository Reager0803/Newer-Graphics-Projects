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

	glRotatef(20.0, 1.0, 0.0, 0.0);
	glRotatef(15.0, 0.0, 1.0, 0.0);

	//glScalef(2.0, 1.0, 1.0);

	// Castle Floor
	glPushMatrix();
		glTranslatef(0.0, -1.7, 0.0);
		glScalef(1.0, 0.05, 1.0);
		glColor3f(0.3, 0.3, 0.3);
		glutSolidCube(15.0);
	glPopMatrix();

	// Floor2
        glPushMatrix();
                glTranslatef(0.0, -2.5, 0.0);
                glScalef(1.0, 0.05, 1.0);
                glColor3f(0.0, 0.8, 0.0);
                glutSolidCube(22.0);
        glPopMatrix();

	// Bridge
        glPushMatrix();
                glTranslatef(0.0, -1.6, 8.0);
                glScalef(0.5, 0.05, 0.5);
                glColor3f(0.7, 0.7, 0.3);
                glutSolidCube(10.0);
        glPopMatrix();

	// Moat
        glPushMatrix();
                glTranslatef(0.0, -2.4, 0.0);
                glScalef(1.0, 0.05, 1.0);
                glColor3f(0.0, 0.0, 0.9);
                glutSolidCube(19.0);
        glPopMatrix();

	// Back Wall
        glPushMatrix();
		glTranslatef(0.0, 0.0, -3.0);
		glScalef(6.0, 3.0, 1.0);
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCube(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1.0);
        glPopMatrix();

	// Left Wall
        glPushMatrix();
                glTranslatef(-3.0, 0.0, 0.0);
                glScalef(1.0, 3.0, 6.0);
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();

        // Right Wall
        glPushMatrix();
                glTranslatef(3.0, 0.0, 0.0);
                glScalef(1.0, 3.0, 6.0);
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();

	// Left Front Door
        glPushMatrix();
		glRotatef(65.0, 0.0, 1.0, 0.0);
                glTranslatef(-4.0, 0.0, 0.0);
                glScalef(0.5, 3.0, 3.0);
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();

        // Left Front Door
        glPushMatrix();
                glRotatef(-65.0, 0.0, 1.0, 0.0);
                glTranslatef(4.0, 0.0, 0.0);
                glScalef(0.5, 3.0, 3.0);
                glColor3f(0.5, 0.5, 0.5);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();

	// Piller1
	glPushMatrix();
		glTranslatef(3.0, 0.0, -3.0);
		glScalef(1.5, 6.0, 1.5);
		glColor3f(0.6, 0.6, 0.6);
		glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
		// Top of Pillar
		glColor3f(0.7, 0.0, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, 0.5);
	        glutSolidCone(0.8, 0.5, 100, 100);
	glPopMatrix();

        // Piller2
        glPushMatrix();
                glTranslatef(3.0, 0.0, 3.0);
                glScalef(1.5, 6.0, 1.5);
                glColor3f(0.6, 0.6, 0.6);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
                // Top of Pillar
                glColor3f(0.7, 0.0, 0.0);
                glRotatef(-90.0, 1.0, 0.0, 0.0);
                glTranslatef(0.0, 0.0, 0.5);
                glutSolidCone(0.8, 0.5, 100, 100);
        glPopMatrix();

        // Piller3
        glPushMatrix();
                glTranslatef(-3.0, 0.0, 3.0);
                glScalef(1.5, 6.0, 1.5);
                glColor3f(0.6, 0.6, 0.6);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
                // Top of Pillar
                glColor3f(0.7, 0.0, 0.0);
                glRotatef(-90.0, 1.0, 0.0, 0.0);
                glTranslatef(0.0, 0.0, 0.5);
                glutSolidCone(0.8, 0.5, 100, 100);
        glPopMatrix();

        // Piller4
        glPushMatrix();
                glTranslatef(-3.0, 0.0, -3.0);
                glScalef(1.5, 6.0, 1.5);
                glColor3f(0.6, 0.6, 0.6);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
                // Top of Pillar
                glColor3f(0.7, 0.0, 0.0);
                glRotatef(-90.0, 1.0, 0.0, 0.0);
                glTranslatef(0.0, 0.0, 0.5);
                glutSolidCone(0.8, 0.5, 100, 100);
        glPopMatrix();

	// Wall Tops 1
	glPushMatrix();
                glTranslatef(-3.0, 1.75, 4.0);
		for(int i=0; i<7; i++) {
                glTranslatef(0.0, 0.0, -1);
                glColor3f(0.4, 0.4, 0.4);
                glutSolidCube(0.5);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(0.5);
		}
        glPopMatrix();

        // Wall Tops 2
        glPushMatrix();
                glTranslatef(3.0, 1.75, 4.0);
                for(int i=0; i<7; i++) {
                glTranslatef(0.0, 0.0, -1);
                glColor3f(0.4, 0.4, 0.4);
                glutSolidCube(0.5);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(0.5);
                }
        glPopMatrix();

        // Wall Tops 3
        glPushMatrix();
                glTranslatef(-3.0, 1.75, -3.0);
                for(int i=0; i<6; i++) {
                glTranslatef(1.0, 0.0, 0.0);
                glColor3f(0.4, 0.4, 0.4);
                glutSolidCube(0.5);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(0.5);
                }
        glPopMatrix();

	//############################################
	// Person

        // Body
        glPushMatrix();
                glScalef(0.2, 0.4, 0.2);
                glColor3f(1.0, 0.0, 0.0);
                glutSolidSphere(2.5, 100, 100);
                glColor3f(0.0, 0.0, 0.0);
        glPopMatrix();

        // Arms
        glPushMatrix();
                glRotatef(45, 0.0, 0.0, 1.0);
                glTranslatef(0.5, -0.2, 0.0);
                glScalef(0.1, 0.3, 0.1);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(2.5, 100, 100);
        glPopMatrix();

        glPushMatrix(); 
                glRotatef(-45, 0.0, 0.0, 1.0);
                glTranslatef(-0.5, -0.2, 0.0);
                glScalef(0.1, 0.3, 0.1);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(2.5, 100, 100);
        glPopMatrix();

        // Legs
        glPushMatrix();
                glScalef(0.1, 0.3, 0.1);
                glTranslatef(-2.5, -3.0, 0.0);  
                glutSolidSphere(2.5, 100, 100);
        glPopMatrix();

        glPushMatrix();
                glScalef(0.1, 0.3, 0.1);
                glTranslatef(2.5, -3.0, 0.0);  
                glutSolidSphere(2.5, 100, 100);
        glPopMatrix();

        // Eyes
        glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);
                glTranslatef(0.25, 1.5, 0.4);
                glutSolidSphere(0.1, 100, 100);
        glPopMatrix();

        glPushMatrix(); 
                glColor3f(0.0, 0.0, 0.0);
                glTranslatef(-0.25, 1.5, 0.4);
                glutSolidSphere(0.1, 100, 100);
        glPopMatrix();

        // Head
        glPushMatrix();
                glTranslatef(0.0, 1.5, 0.0);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(0.5, 100.0, 100.0);
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
	glClearColor(0.5, 0.5, 1.0, 0.0);	// Blue Background
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-10.0, 10.0, -10.0*(GLfloat) h / (GLfloat) w,
			10.0*(GLfloat) h / (GLfloat) w, -14.0, 14.0);
	} else {
		glOrtho(-10.0*(GLfloat) w/(GLfloat) h, 10.0 * (GLfloat) w/ (GLfloat) h,
			-10.0, 10.0, -14.0, 14.0);
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

        glutCreateWindow("My Castle");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        glutMainLoop();
}
