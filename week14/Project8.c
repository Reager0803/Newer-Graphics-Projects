// Human Robot

#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive y
GLfloat size = 0.0;

// Specify The Location Of Light 0
GLfloat light0_pos[] = {1.0, 1.0, 1.0, 0.0};

GLfloat sclX = 1.0;

// Arm and Leg Rotational Values
int leftArm1 = 0, leftArm2 = 0;
int rightArm1 = -75, rightArm2 = 0;
int leftLeg1 = 0, leftLeg2 = 0;
int rightLeg1 = 0, rightLeg2 = 0;
int leftArmY = 0;

// Switches
int s = 0, sLeftLeg1 = 0, sLeftLeg2 = 0, sRightLeg1 = 0, sRightLeg2 = 0;
int sLeftArm1 = 0, sLeftArm2 = 0, sRightArm1 = 0, sRightArm2 = 0, sLeftArmY = 0;
int sHead = 0, sBody = 0;
int sfX = 0, sfY = 0, sfZ = 0;	// Flying Switches
int sMalfunc = 0;	// Malfunction Switch

// Flying Thetas
GLfloat fX = 0.0, fY = 0.0, fZ = 0.0;

// Thetas
GLfloat r = 0.0, head = 0.0, body = 0.0;

// Malfunction Translation Value
GLfloat malfunc = 0.0;

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
materialStruct Moon = {
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
    materials(&Moon);

	glTranslatef((fX/16.0), 0.0, 0.0);
	glTranslatef(0.0, (fY/16.0), 0.0);
	glTranslatef(0.0, 0.0, (fZ/16.0));

	glRotatef(fZ+fY, 1, 0, 0);
	glRotatef(fY+fX, 0, 0, 1);
	glRotatef(fX+fZ, 0, 1, 0);

	glRotatef(r, 0, 1, 0);

    // HEAD
	glPushMatrix();
		glTranslatef(0.0, 0.0, head+malfunc);
		glTranslatef(0.0, 9.0+malfunc, 0.0);
		glutSolidSphere(4.0, 100, 100);
	glPopMatrix();
    // EYES
	glPushMatrix();
		materials(&Black);
		glTranslatef(0.0, 0.0, head+malfunc);
		glTranslatef(1.5, 9.5, 3.5);
		glutSolidSphere(0.75, 100, 100);
		glTranslatef(-3.0, 0.0, 0.0+malfunc);
		glutSolidSphere(0.75, 100, 100);
	glPopMatrix();

    materials(&Moon);

    // BODY
	glPushMatrix();
		glRotatef(body, 0, 1, 0);
		glTranslatef(0.0, -2.0, 0.0+(malfunc*2.0));

		glScalef(2.0, 3.0, 2.0);
		glutSolidSphere(3.05, 100, 100);
	glPopMatrix();

	// LEFT ARM
	glPushMatrix();
        glRotatef(-90, 0, 0, 1);
	glTranslatef(3.0, -6.0+malfunc, 0.0);

        glTranslatef(-4.0, 0.0, 0.0);
        glRotatef( (GLfloat)leftArm1, 0.0, 1.0, 0.0);

	// TESTING
	glRotatef( (GLfloat)leftArmY, 0.0, 0.0, 1.0);
        glRotatef( (GLfloat)leftArmY, 1.0, 0.0, 0.0);

        glTranslatef(-4.0, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.8, 0.8);
                glutSolidSphere(2.0, 100, 100);
        glPopMatrix();

        glTranslatef(-1.75, 0.0, 0.0);
        glRotatef((GLfloat)leftArm2, 0.0, 1.0, 0.0);
        glTranslatef(-1.75, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.9, 0.9);
                glutSolidSphere(1.75, 100, 100);
        glPopMatrix();

    glPopMatrix();

    // RIGHT ARM
	glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef(-3.0, -6.0-malfunc, 0.0);

        glTranslatef(4.0, 0.0, 0.0);
        glRotatef( (GLfloat)rightArm1, 0.0, 1.0, 0.0);
        glTranslatef(4.0, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.8, 0.8);
                glutSolidSphere(2.0, 100, 100);
        glPopMatrix();

        glTranslatef(1.75, 0.0, 0.0);
        glRotatef((GLfloat)rightArm2, 0.0, 1.0, 0.0);
        glTranslatef(1.75, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.9, 0.9);
                glutSolidSphere(1.75, 100, 100);
        glPopMatrix();

    glPopMatrix();

    	// LEFT LEG
	glPushMatrix();
        glTranslatef(2.5, -4.0-malfunc, 0.0);
        glRotatef(-270, 0, 0, 1);

        glTranslatef(-4.0, 0.0, 0.0);
        glRotatef( (GLfloat)leftLeg1, 0.0, 1.0, 0.0);
        glTranslatef(-4.0, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.8, 0.8);
                glutSolidSphere(2.0, 100, 100);
        glPopMatrix();

        glTranslatef(-1.75, 0.0, 0.0);
        glRotatef((GLfloat)leftLeg2, 0.0, 1.0, 0.0);
        glTranslatef(-1.75, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.9, 0.9);
                glutSolidSphere(1.75, 100, 100);
        glPopMatrix();

    glPopMatrix();

    // RIGHT LEG
	glPushMatrix();
        glTranslatef(-2.5, -4.0-malfunc, 0.0);
        glRotatef(270, 0, 0, 1);

        glTranslatef(4.0, 0.0, 0.0);
        glRotatef( (GLfloat)rightLeg1, 0.0, 1.0, 0.0);
        glTranslatef(4.0, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.8, 0.8);
                glutSolidSphere(2.0, 100, 100);
        glPopMatrix();

        glTranslatef(1.75, 0.0, 0.0);
        glRotatef((GLfloat)rightLeg2, 0.0, 1.0, 0.0);
        glTranslatef(1.75, 0.0, 0.0);
        glPushMatrix();
                glScalef(2.0, 0.9, 0.9);
                glutSolidSphere(1.75, 100, 100);
        glPopMatrix();

    glPopMatrix();

}

void stars() {
        srand(time(NULL));
        glPointSize(3.0);
//        glColor3f(1.0, 1.0, 1.0);
	materials(&Moon);
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 5.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 5.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, (-1)*y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 5.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 5.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 40.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, (-1)*y2, -10);
                glEnd();
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

	currentMaterial = &Moon;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentMaterial -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentMaterial -> specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentMaterial -> ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, currentMaterial -> shininess);
}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

        // Calls Stars Function
        stars();

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
        glutPostRedisplay();
}

// Makes Him Do Some Dance Moves
void dance() {
	// Whole Body
	if(s == 0) {
		r += 0.75;
		if(r > 55) s = 1;
	} else {
		r -= 0.75;
		if(r < -55) s = 0;
	}

	// Head
	if(sHead == 0) {
		head -= 0.1;
		if(head < -1) sHead = 1;
	} else {
		head += 0.1;
		if(head > 1.5) sHead = 0;
	}

	// Left Leg
	if(sLeftLeg1 == 0) {
		leftLeg1++;
		if(leftLeg1 > 30) sLeftLeg1 = 1;
	} else {
		leftLeg1--;
		if(leftLeg1 < -30) sLeftLeg1 = 0;
	}

	// Right Leg
        if(sRightLeg1 == 0) {
                rightLeg1++;
                if(rightLeg1 > 30) sRightLeg1 = 1;
        } else {
                rightLeg1--;
                if(rightLeg1 < -30) sRightLeg1 = 0;
        }

        // Left Arm X-AXIS
        if(sLeftArm1 == 0) {
                leftArm1++;
                if(leftArm1 > 30) sLeftArm1 = 1;
        } else {
                leftArm1--;
                if(leftArm1 < -30) sLeftArm1 = 0;
        }

	// Left Arm Y-AXIS
        if(sLeftArmY == 0) {
                leftArmY++;
                if(leftArmY > 20) sLeftArmY = 1;
        } else {
                leftArmY--;
                if(leftArmY < -20) sLeftArmY = 0;
        }

        // Right Arm
        if(sRightArm1 == 0) {
                rightArm1 += 2;
                if(rightArm1 > -55) sRightArm1 = 1;
        } else {
                rightArm1 -= 2;
                if(rightArm1 < -95) sRightArm1 = 0;
        }

	glutPostRedisplay();
}

// I believe I can fly!!!
void fly() {
	dance();
        // Flying
        if(sfX == 0) {
                fX += 0.5;
                if(fX > 50) sfX = 1;
        } else {
                fX -= 0.5;
                if(fX < -50) sfX = 0;
        }
        if(sfY == 0) {
                fY += 1.0;
                if(fY > 50) sfY = 1;
        } else {
                fY -= 1.0;
                if(fY < -50) sfY = 0;
        }
        if(sfZ == 0) {
                fZ += 1.5;
                if(fZ > 50) sfZ = 1;
        } else {
                fZ -= 1.5;
                if(fZ < -50) sfZ = 0;
        }

	glutPostRedisplay();
}

// Small Malfunction
void malfunction() {
	fly();
	glutPostRedisplay();
}

// Major Malfunction!!!!!!!!!!
void majorMalfunction() {
        fly();
	fly();
        glutPostRedisplay();
}

// SELF DESTRUCTION!!!!!!!!!!
void selfDestruct() {
	if(sMalfunc == 0) {
		malfunc += 0.25;
		if(malfunc > 10000) sMalfunc = 1;
	} else {
		malfunc -= 0.25;
		if(malfunc < -10000) sMalfunc = 0;
	}
	glutPostRedisplay();
}

// Restoration
void restore() {
	malfunc = 0;
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
//	if(key == 'r') glutIdleFunc( idle );
//	if(key == 'q') exit(0);
	if(key == 's') glutIdleFunc( NULL );
	switch (key) {
                case 'w':
                        leftArm1 = (leftArm1 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'W':
                        leftArm1 = (leftArm1 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'e':
                        leftArm2 = (leftArm2 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'E':
                        leftArm2 = (leftArm2 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'r':
                        rightArm1 = (rightArm1 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'R':
                        rightArm1 = (rightArm1 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 't':
                        rightArm2 = (rightArm2 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'T':
                        rightArm2 = (rightArm2 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'y':
                        leftLeg1 = (leftLeg1 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'Y':
                        leftLeg1 = (leftLeg1 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'u':
                        leftLeg2 = (leftLeg2 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'U':
                        leftLeg2 = (leftLeg2 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'i':
                        rightLeg1 = (rightLeg1 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'I':
                        rightLeg1 = (rightLeg1 - 5)%360;
                        glutPostRedisplay();
                        break;
                case 'o':
                        rightLeg2 = (rightLeg2 + 5)%360;
                        glutPostRedisplay();
                        break;
                case 'O':
                        rightLeg2 = (rightLeg2 - 5)%360;
                        glutPostRedisplay();
                        break;
		case 'D':
			glutIdleFunc( dance );
			break;
		case 'F':
			glutIdleFunc( fly );
			break;
                case 'm':
                        glutIdleFunc( malfunction );
                        break;
		case 'M':
			glutIdleFunc( majorMalfunction );
			break;
		case 'd':
			glutIdleFunc( selfDestruct );
			break;
		case 'v':
			glutIdleFunc( restore );
			break;
		case 'q':
			exit(0);
			break;
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

        glutCreateWindow("My Robot");
        glutDisplayFunc(display);

	glutIdleFunc(myIdle);	// Makes the other objects rotate

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
	init();
        glutMainLoop();
}
