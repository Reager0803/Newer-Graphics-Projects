// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive y
GLfloat size = 0.0;

// x and y values of the current block:
double x1 = 0, y2 = 0;

// Array containing block values for each column
int yHeights[10];

// Specify The Location Of Light 0
GLfloat light0_pos[] = {1.0, 1.0, 1.0, 0.0};

// Specify The Other Properties Of Light 0 Using The Struct
typedef struct lightStruct {
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat ambient[4];
} lightStruct;

lightStruct redLight = {
	{0.9, 0.2, 0.2, 1.0},
	{0.7, 0.7, 0.7, 1.0},
	{0.1, 0.1, 0.1, 1.0}
};

lightStruct blueLight = {
        {1.0, 1.0, 1.0, 1.0},
        {0.5, 0.5, 0.5, 1.0},
        {0.2, 0.2, 0.2, 1.0}
};

lightStruct *currentLight;

// Defines Material Structure
typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

// Moon Material
materialStruct White = {
        {0.65, 0.65, 0.65},
        {0.80, 0.80, 0.80},
        {0.9746, 0.9746, 0.9746},
        10.8
};

// Black Material
materialStruct Black = {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        100.0
};

materialStruct *currentMaterial;
void materials(materialStruct *materials) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials -> ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials -> specular);
}

void objects() {
/*
    glPushMatrix();
        glTranslatef(1.75, 0.0, 0.0);
        //glRotatef((GLfloat)rightLeg2, 0.0, 1.0, 0.0);
        glTranslatef(1.75, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.9, 0.9);
                glutSolidSphere(1.75, 100, 100);
        glPopMatrix();

    glPopMatrix();
*/
        // Box for the game
        glLineWidth(10.0);
        materials(&White);
        glBegin(GL_LINE_LOOP);
                glVertex2f(10.75, 21.2);
                glVertex2f(10.75, -21.2);
                glVertex2f(-10.75, -21.2);
                glVertex2f(-10.75, 21.2);
        glEnd();

        // Test For Filling the box
        materials(&Black);
        glPushMatrix();
                glTranslatef(-11.5, -20.0, 0.0);
                for(int j=0; j<20; j++) {
                        for(int i=0; i<10; i++) {
                                glTranslatef(2.10, 0.0, 0.0);
                                glutWireCube(2.0);
                        }
                        glTranslatef(-21, 2.10, 0.0);
                }
        glPopMatrix();

        materials(&White);
        glPushMatrix();
                glTranslatef(1, 19.825, 0);
                glTranslatef((GLfloat)x1, (GLfloat)y2, 0);
                glutSolidCube(2.0);
        glPopMatrix();

        // Check if for rows to clear
        int min = yHeights[0];
        for(int i=0; i<10; i++) {
                if(yHeights[i] < min) {
                        min = yHeights[i];
                }
        }

        // Clear minimum number of rows to be cleared
        for(int i=0; i<10; i++) {
                yHeights[i] -= min;
        }

        // Draws Permanent Blocks
        int xVal = 0, yVal = 0;
        for(int i=0; i<10; i++) {
                for(int j=0; j<yHeights[i]; j++) {
                        glPushMatrix();
                                xVal = i * 2.1;
                                xVal -= 6.5;
                                yVal = j * 2.1; 
                                yVal -= 20;
                                glTranslatef(xVal, yVal, 0);
                                glutSolidCube(2.0);
                        glPopMatrix();
                }
        }

}

// Added For Lighting Effects
void init() {
	glClearColor(0.0, 0.1, 0.3, 0.0);	// Space Background

	// Eyes at 1, 1, 1, object at 0, 0, 0, and up is in y direction
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_LIGHTING);			// Enable The Lighting
	glEnable(GL_LIGHT0);			// Light Source Number 0

	currentLight = &blueLight;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLight -> specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLight -> diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLight -> ambient);

	currentMaterial = &White;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentMaterial -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentMaterial -> specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentMaterial -> ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentMaterial -> shininess);
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

// Requires user input (keyboard or mouse)
void idle() {
	// Increments theta when called
	theta[axis] += 1.25;
	if(theta[axis] > 360.0) {
		theta[axis] -= 360;
	}
	glutPostRedisplay();
}

// Autostarts without user input
void myIdle() {
        // Guesses random number, when correct, it ticks the game (I knopw it sucks)
        float num = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num2 = (float)rand()/(float)(RAND_MAX) * 2.0;
        if(((num > 0.0 && num < 0.2) || (num2 > 0.0 && num2 < 0.2)) && y2 > -39.0) {
                y2 -= 1.05;
        }
        if(y2 <= -39) {
                int yHindex = x1 + 12.6;
                yHindex /= 2.1;
                yHindex -= 1;
                yHeights[yHindex] += 1;
                x1 = 0, y2 = 0;
        }
        glutPostRedisplay();
}

// Rotates the block
void Rotate() {
        glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
                glOrtho(-24.0, 24.0, -24.0*(GLfloat) h / (GLfloat) w,
                        24.0*(GLfloat) h / (GLfloat) w, -36.0, 36.0);
        } else {
                glOrtho(-24.0*(GLfloat) w/(GLfloat) h, 24.0 * (GLfloat) w/ (GLfloat) h,
                        -24.0, 24.0, -36.0, 36.0);
        }
	glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
        if(key == 'q' || key == 27) exit(0);
        if(key == 'p') glutIdleFunc( NULL );
        if(y2 > -39) {
                switch (key) {
                case 'd':
                        x1 += 2.1;
                        glutPostRedisplay();
                        break;
                case 'a':
                        x1 -= 2.1;
                        glutPostRedisplay();
                        break;
                case 'w':
                        glutIdleFunc(Rotate);
                        break;
                case 's':
                        y2 -= 1.05;
                        glutPostRedisplay();
                        break;
                }
        }
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

        glutCreateWindow("Tetris Game");
        glutDisplayFunc(display);

	glutIdleFunc(myIdle);

	glutReshapeFunc( reshape );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
	init();
        glutMainLoop();
}
