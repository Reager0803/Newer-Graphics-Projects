#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2; 	// When we start the program, object will rotate with respect to positivez

double dimension = 3.0;

void houseObject( ) {

		double x = 0, y = 0;
        double x0 = 0.0, y0 = 0.0;      // Origin of circle
		double radius = 1.0;
        int n = 100;                   // Number of points
        int j, l;

		// ################## SUN ##################
		// The Sun
        glColor3f(1.0,1.0,0.0);         // Yellow
        x0 = 3.0;
        y0 = 1.5;
        glBegin(GL_POLYGON);
                for(int i=0; i<360; i++) {
                        x = x0 + radius * cos(DTR*i);        // x coordinate of 1 point o>
                        y = y0 + radius * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x, y, -4);                       // x and y verteces
                        x = x0 + radius * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        y = y0 + radius * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x, y, -4);                       // x and y verteces

                }
        glEnd();

	// ##################### HOUSE ROOF #######################
	glColor3f(0.5, 0.5, 0.5);	// Grey
	// Bottom
	glBegin(GL_POLYGON);
		glVertex3f(1.2, 1, 1.2);
		glVertex3f(1.2, 1, -1.2);
		glVertex3f(-1.2, 1, -1.2);
		glVertex3f(-1.2, 1, 1.2);
	glEnd();

	glColor3f(0.75, 0.75, 0.75);	// Light Grey
	// Left
	glBegin(GL_POLYGON);
		glVertex3f(-1, 1.2, -1.2);
		glVertex3f(-1.2, 1.0, -1.2);
		glVertex3f(-1.2, 1.0, 1.2);
		glVertex3f(-1, 1.2, 1.2);
	glEnd();

	// Right
	glBegin(GL_POLYGON);
		glVertex3f(1, 1.2, -1.2);
		glVertex3f(1.2, 1.0, -1.2);
		glVertex3f(1.2, 1.0, 1.2);
		glVertex3f(1, 1.2, 1.2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5); // Black
	// Front
	glBegin(GL_POLYGON);
		glVertex3f(-1.2, 1, 1.2);
		glVertex3f(-1, 1.2, 1.2);
		glVertex3f(0, 1.7, 1.2);
		glVertex3f(1, 1.2, 1.2);
		glVertex3f(1.2, 1, 1.2);
	glEnd();

	// Back
	glBegin(GL_POLYGON);
		glVertex3f(-1.2, 1, -1.2);
		glVertex3f(-1, 1.2, -1.2);
		glVertex3f(0, 1.7, -1.2);
		glVertex3f(1, 1.2, -1.2);
		glVertex3f(1.2, 1, -1.2);
	glEnd();

	glColor3f(0.8, 0.8, 0.8);	// Light Grey
	// Top
	glBegin(GL_POLYGON);
		glVertex3f(1, 1.2, 1.2);
		glVertex3f(1, 1.2, -1.2);
		glVertex3f(0, 1.7, -1.2);
		glVertex3f(0, 1.7, 1.2);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(0, 1.7, 1.2);
		glVertex3f(0, 1.7, -1.2);
		glVertex3f(-1, 1.2, -1.2);
		glVertex3f(-1, 1.2, 1.2);
	glEnd();

	// ##################### HOUSE WALLS #######################

	// Bottom
	glBegin(GL_POLYGON);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(-1, -1, -1);
		glVertex3f(-1, -1, 1);
	glEnd();

	glColor3f(0.2, 0.5, 0.5);	// Dark Teal
	// Right
	glBegin(GL_POLYGON);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, 1, -1);
		glVertex3f(1, 1, 1);
	glEnd();

		glColor3f(0.0, 0.3, 0.3);	// Darker Teal
	// Left
        glBegin(GL_POLYGON);

			glVertex3f(-1, -1, 1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, 1, 1);
        glEnd();

		glColor3f(0.3, 0.6, 0.6);	// Lighter Teal
		// Back
		glBegin(GL_POLYGON);
			glVertex3f(1, -1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(1, 1, -1);
        glEnd();

		glColor3f(0.0, 0.4, 0.4);	// Darker Teal
        // Front
        glBegin(GL_POLYGON);
			glVertex3f(1, -1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(-1, 1, 1);
			glVertex3f(1, 1, 1);
        glEnd();

		// ################## HOUSE WINDOWS ##################

		// Front
		glColor3f(1, 1, 0); // Yellow
		glBegin(GL_POLYGON);
			glVertex3f(0.8, 0.2, 1.02);
			glVertex3f(0.8, -0.2, 1.02);
			glVertex3f(0.4, -0.2, 1.02);
			glVertex3f(0.4, 0.2, 1.02);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(-0.8, 0.2, 1.02);
			glVertex3f(-0.8, -0.2, 1.02);
			glVertex3f(-0.4, -0.2, 1.02);
			glVertex3f(-0.4, 0.2, 1.02);
		glEnd();

		// Back
		glBegin(GL_POLYGON);
			glVertex3f(0.3, 0.3, -1.02);
			glVertex3f(0.3, -0.3, -1.02);
			glVertex3f(-0.3, -0.3, -1.02);
			glVertex3f(-0.3, 0.3, -1.02);
		glEnd();

		// Left
		glBegin(GL_POLYGON);
			glVertex3f(-1.02, 0.3, 0.3);
			glVertex3f(-1.02, 0.3, -0.3);
			glVertex3f(-1.02, -0.3, -0.3);
			glVertex3f(-1.02, -0.3, 0.3);
		glEnd();

		// Right
		glBegin(GL_POLYGON);
			glVertex3f(1.02, 0.3, 0.3);
			glVertex3f(1.02, 0.3, -0.3);
			glVertex3f(1.02, -0.3, -0.3);
			glVertex3f(1.02, -0.3, 0.3);
		glEnd();

		// Front Panes
		glLineWidth(5);
		glColor3f(0, 0, 0); // Black
		glBegin(GL_LINES);
			glVertex3f(0.6, 0.2, 1.03);
			glVertex3f(0.6, -0.2, 1.03);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0.4, 0.0, 1.03);
			glVertex3f(0.8, 0.0, 1.03);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(-0.6, 0.2, 1.03);
			glVertex3f(-0.6, -0.2, 1.03);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-0.4, 0.0, 1.03);
			glVertex3f(-0.8, 0.0, 1.03);
		glEnd();

		glLineWidth(8);
		// Left Panes
		glBegin(GL_LINES);
			glVertex3f(-1.02, 0.3, 0);
			glVertex3f(-1.02, -0.3, 0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-1.02, 0, -0.3);
			glVertex3f(-1.02, 0, 0.3);
		glEnd();

		// Right Panes
		glBegin(GL_LINES);
			glVertex3f(1.02, 0.3, 0);
			glVertex3f(1.02, -0.3, 0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(1.02, 0, -0.3);
			glVertex3f(1.02, 0, 0.3);
		glEnd();

		// Back Panes
		glBegin(GL_LINES);
			glVertex3f(-0.3, 0, -1.02);
			glVertex3f(0.3, 0, -1.02);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0, -0.3, -1.02);
			glVertex3f(0, 0.3, -1.02);
		glEnd();

		// ########## DOOR ############

		glColor3f(0.6, 0.3, 0.0);	// Brownish

		glBegin(GL_POLYGON);
			glVertex3f(0.2, 0.2, 1.02);
			glVertex3f(0.2, -0.6, 1.02);
			glVertex3f(-0.2, -0.6, 1.02);
			glVertex3f(-0.2, 0.2, 1.02);

		glEnd();

		glPointSize(6.5);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3f(0.1, -0.2, 1.05);
		glEnd();

		// ############ YARD ################

		// Top
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_POLYGON);
			glVertex3f(-4.0, -1.0, -4.0);
			glVertex3f(-4.0, -1.0, 4.0);
			glVertex3f(4.0, -1.0, 4.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(4.0, -1.0, -4.0);
		glEnd();

		// Front
		glColor3f(0.5, 0.3, 0.0);		// Brownish
		glBegin(GL_POLYGON);
			glVertex3f(-4.0, -1.0, 4.0);
			glVertex3f(-4.0, -2.0, 4.0);
			glVertex3f(4.0, -2.0, 4.0);
			glVertex3f(4.0, -1.0, 4.0);
		glEnd();

		// Back
		glBegin(GL_POLYGON);
			glVertex3f(-4.0, -1.0, -4.0);
			glVertex3f(-4.0, -2.0, -4.0);
			glVertex3f(4.0, -2.0, -4.0);
			glVertex3f(4.0, -1.0, -4.0);
		glEnd();

		// Left
		glBegin(GL_POLYGON);
			glVertex3f(-4.0, -1.0, -4.0);
			glVertex3f(-4.0, -2.0, -4.0);
			glVertex3f(-4.0, -2.0, 4.0);
			glVertex3f(-4.0, -1.0, 4.0);
		glEnd();

		// Right
		glBegin(GL_POLYGON);
			glVertex3f(4.0, -1.0, -4.0);
			glVertex3f(4.0, -2.0, -4.0);
			glVertex3f(4.0, -2.0, 4.0);
			glVertex3f(4.0, -1.0, 4.0);
		glEnd();

		// ########### STEPS #################

		glColor3f(0.5, 0.5, 0.5);	// Grey
		// Step1
		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -0.6, 1.0);
			glVertex3f(-0.4, -0.6, 1.5);
			glVertex3f(0.4, -0.6, 1.5);
			glVertex3f(0.4, -0.6, 1.0);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -0.6, 1.5);
			glVertex3f(-0.4, -0.8, 1.5);
			glVertex3f(0.4, -0.8, 1.5);
			glVertex3f(0.4, -0.6, 1.5);
		glEnd();

		// Step2
		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -0.8, 1.5);
			glVertex3f(-0.4, -0.8, 2.0);
			glVertex3f(0.4, -0.8, 2.0);
			glVertex3f(0.4, -0.8, 1.5);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -0.8, 2.0);
			glVertex3f(-0.4, -1.0, 2.0);
			glVertex3f(0.4, -1.0, 2.0);
			glVertex3f(0.4, -0.8, 2.0);
		glEnd();

		glColor3f(0.3, 0.3, 0.3);	// Dark Grey
		// Left Side
		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -0.6, 1.0);
			glVertex3f(-0.4, -0.6, 1.5);
			glVertex3f(-0.4, -0.8, 1.5);
			glVertex3f(-0.4, -0.8, 1.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-0.4, -1.0, 2.0);
			glVertex3f(-0.4, -1.0, 1.0);
			glVertex3f(-0.4, -0.8, 1.0);
			glVertex3f(-0.4, -0.8, 2.0);
		glEnd();

		// Right Side
		glBegin(GL_POLYGON);
			glVertex3f(0.4, -0.6, 1.0);
			glVertex3f(0.4, -0.6, 1.5);
			glVertex3f(0.4, -0.8, 1.5);
			glVertex3f(0.4, -0.8, 1.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(0.4, -1.0, 2.0);
			glVertex3f(0.4, -1.0, 1.0);
			glVertex3f(0.4, -0.8, 1.0);
			glVertex3f(0.4, -0.8, 2.0);
		glEnd();

		// ######################## PATH ###########################

		glBegin(GL_POLYGON);
			glVertex3f(0.4, -0.98, 2.0);
			glVertex3f(0.4, -0.98, 4.0);
			glVertex3f(-0.4, -0.98, 4.0);
			glVertex3f(-0.4, -0.98, 2.0);
		glEnd();

		// ######################### FENCE ###########################

		// Left
		glColor3f(0.8, 0.8, 0.8);		// Light Grey
		glBegin(GL_POLYGON);
			glVertex3f(-1.0, -1.0, 0.0);
			glVertex3f(-3.0, -1.0, 0.0);
			glVertex3f(-3.0, -0.6, 0.0);
			glVertex3f(-1.0, -0.6, 0.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-3.0, -1.0, 0.0);
			glVertex3f(-3.0, -1.0, 3.0);
			glVertex3f(-3.0, -0.6, 3.0);
			glVertex3f(-3.0, -0.6, 0.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-3.0, -1.0, 3.0);
			glVertex3f(-0.5, -1.0, 3.0);
			glVertex3f(-0.5, -0.6, 3.0);
			glVertex3f(-3.0, -0.6, 3.0);
		glEnd();

		// Right
		glColor3f(1.0, 1.0, 1.0);		// White
		glBegin(GL_POLYGON);
			glVertex3f(1.0, -1.0, 0.0);
			glVertex3f(3.0, -1.0, 0.0);
			glVertex3f(3.0, -0.6, 0.0);
			glVertex3f(1.0, -0.6, 0.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(3.0, -1.0, 0.0);
			glVertex3f(3.0, -1.0, 3.0);
			glVertex3f(3.0, -0.6, 3.0);
			glVertex3f(3.0, -0.6, 0.0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(3.0, -1.0, 3.0);
			glVertex3f(0.5, -1.0, 3.0);
			glVertex3f(0.5, -0.6, 3.0);
			glVertex3f(3.0, -0.6, 3.0);
		glEnd();

		// ######################## TREE ######################

		// WOOD FRONT
		glColor3f(0.3, 0.2, 0.1);		// Brown
		glBegin(GL_POLYGON);
			glVertex3f(-2.5, -1.0, -2.5);
			glVertex3f(-2.1, -1.0, -2.5);
			glVertex3f(-2.1, 1.0, -2.5);
			glVertex3f(-2.5, 1.0, -2.5);
		glEnd();

		// WOOD BACK
		glColor3f(0.3, 0.2, 0.1);		// Brown
		glBegin(GL_POLYGON);
			glVertex3f(-2.5, -1.0, -2.9);
			glVertex3f(-2.1, -1.0, -2.9);
			glVertex3f(-2.1, 1.0, -2.9);
			glVertex3f(-2.5, 1.0, -2.9);
		glEnd();

		//WOOD LEFT
		glBegin(GL_POLYGON);
			glVertex3f(-2.5, -1.0, -2.9);
			glVertex3f(-2.5, -1.0, -2.5);
			glVertex3f(-2.5, 1.0, -2.5);
			glVertex3f(-2.5, 1.0, -2.9);
		glEnd();

		//WOOD RIGHT
		glBegin(GL_POLYGON);
			glVertex3f(-2.1, -1.0, -2.9);
			glVertex3f(-2.1, -1.0, -2.5);
			glVertex3f(-2.1, 1.0, -2.5);
			glVertex3f(-2.1, 1.0, -2.9);
		glEnd();

		//LEAVES BOTTOM
		glColor3f(0.0, 0.2, 0.0);		// Green
		glBegin(GL_POLYGON);
			glVertex3f(-3.3, 1.0, -3.7);
			glVertex3f(-1.3, 1.0, -3.7);
			glVertex3f(-1.3, 1.0, -1.7);
			glVertex3f(-3.3, 1.0, -1.7);
		glEnd();

		//LEAVES TOP
		glColor3f(0.0, 0.6, 0.0);		// Green
		glBegin(GL_POLYGON);
			glVertex3f(-3.3, 2.2, -3.7);
			glVertex3f(-1.3, 2.2, -3.7);
			glVertex3f(-1.3, 2.2, -1.7);
			glColor3f(0.0, 0.28, 0.0);
			glVertex3f(-3.3, 2.2, -1.7);
		glEnd();

		glColor3f(0.0, 0.3, 0.0);		// Green
		//LEAVES LEFT
		glBegin(GL_POLYGON);
			glVertex3f(-3.3, 1.0, -3.7);
			glVertex3f(-3.3, 2.2, -3.7);
			glVertex3f(-3.3, 2.2, -1.7);
			glVertex3f(-3.3, 1.0, -1.7);
		glEnd();

		glColor3f(0.0, 0.6, 0.0);		// Green
		//LEAVES RIGHT
		glBegin(GL_POLYGON);
			glVertex3f(-1.3, 1.0, -3.7);
			glVertex3f(-1.3, 2.2, -3.7);
			glVertex3f(-1.3, 2.2, -1.7);
			glVertex3f(-1.3, 1.0, -1.7);
		glEnd();

		glColor3f(0.0, 0.3, 0.0);		// Green
		//LEAVES FRONT
		glBegin(GL_POLYGON);
			glVertex3f(-3.3, 1.0, -1.7);
			glVertex3f(-3.3, 2.2, -1.7);
			glVertex3f(-1.3, 2.2, -1.7);
			glVertex3f(-1.3, 1.0, -1.7);
		glEnd();

		glColor3f(0.0, 0.6, 0.0);		// Green
		//LEAVES BACK
		glBegin(GL_POLYGON);
			glVertex3f(-3.3, 1.0, -3.7);
			glVertex3f(-3.3, 2.2, -3.7);
			glVertex3f(-1.3, 2.2, -3.7);
			glVertex3f(-1.3, 1.0, -3.7);
		glEnd();
}


void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		// Rotations
		glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
		glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
		glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis

		houseObject();	// Will call the cube object which contains the verteces

        glFlush();
		glutSwapBuffers();
}

void idle() {
	theta[1] += 1;
	if(theta[1] > 360.0) {
		theta[1] = theta[1] - 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glClearColor(0.0, 0.0, 1.0, 0.0);		// Sky Color
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-4.0, 4.0, -4.0*(GLfloat) h / (GLfloat) w,
			4.0*(GLfloat) h / (GLfloat) w, -20.0, 20.0);
	} else {
		glOrtho(-4.0*(GLfloat) w/(GLfloat) h, 4.0 * (GLfloat) w/ (GLfloat) h,
			-4.0, 4.0, -20.0, 20.0);
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

		theta[0] = 30.0;
		theta[1] = 30.0;
        glutInit(&argc, argv);

        // Windowing:
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0.0, 0.0);

        glutCreateWindow("My House");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        glutMainLoop();
}
