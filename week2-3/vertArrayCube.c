#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2; 	// When we start the program, object will rotate with respect to positive z

// 2DArray of the cubes 8 verteces
GLfloat vertices[][3] = {
	{-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, 
	{-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}
	};

// 2DArray of the cubes 6 colors
GLfloat colors[][3] = {
	{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 
	{1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}
	};

void cubeObject(int a, int b, int c, int d) {	// Defines a side using the parameters a,b,c,d for vertices[]

	glBegin(GL_POLYGON);
		glVertex3fv( vertices[a] );
		glVertex3fv( vertices[b] );
		glVertex3fv( vertices[c] );
		glVertex3fv( vertices[d] );
	glEnd();

	// Line Borders
	/*
	glLineWidth(10.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3fv( vertices[a] );
		glVertex3fv( vertices[b] );
		glVertex3fv( vertices[c] );
		glVertex3fv( vertices[d] );
	glEnd();
	*/

}

void cube() {

        glColor3fv(colors[0]);          // Red
        cubeObject(0, 1, 5, 4);         // Front

        glColor3fv(colors[1]);          // Green
        cubeObject(1, 2, 6, 5);         // Right

        glColor3fv(colors[2]);          // Blue
        cubeObject(0, 3, 2, 1);         // Bottom

        glColor3fv(colors[3]);          // Orange
        cubeObject(3, 0, 4, 7);         // Left

        glColor3fv(colors[4]);          // Teal
        cubeObject(3, 2, 6, 7);         // Back

        glColor3fv(colors[5]);          // Purple
        cubeObject(4, 5, 6, 7);         // Top

}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

		// Rotations
		glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
		glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
		glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis
	cube();
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
