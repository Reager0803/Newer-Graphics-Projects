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
        {0.6, 0.6, 1.0, 1.0},
        {0.5, 0.3, 0.4, 1.0},
        {0.1, 0.1, 0.1, 1.0}
};

lightStruct yellowLight = {
        {0.9, 0.9, 0.0, 1.0},
        {0.7, 0.7, 0.7, 1.0},
        {0.1, 0.1, 0.1, 1.0}
};

lightStruct *currentLight;

// Defines Material Structure
typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

// Ground Material
materialStruct ground = {
	{0.25, 0.85, 0.25},
	{0.40, 0.80, 0.40},
	{0.7746, 0.9746, 0.7746},
	10.8
};

// House Material
materialStruct house = {
  {0.929412, 0.923529, 0.027451, 1.0},
  {0.980392, 0.968627, 0.113725, 1.0},
  {0.000992157, 0.000991176, 0.000507843, 1.0},
  90.0
} ;

// House2 Material
materialStruct house2 = {
  {0.029412, 0.423529, 0.427451, 1.0},
  {0.180392, 0.668627, 0.513725, 1.0},
  {0.192157, 0.991176, 0.707843, 1.0},
  10.0
} ;

// Window Material
materialStruct window = {
	{0.1, 0.4, 0.6, 1},
	{0.2, 0.6, 0.8, 1},
	{0.0, 0.0, 0.0, 1},
	90.0
};

// Door Material
materialStruct door = {
        {0.7, 0.3, 0.1, 1},
        {0.8, 0.4, 0.2, 1},
        {1.0, 0.5, 0.3, 1},
        10.0
};

// Door Material2
materialStruct door2 = {
        {0.5, 0.1, 0.1, 1},
        {0.6, 0.2, 0.1, 1},
        {0.8, 0.3, 0.2, 1},
        10.0
};

// White Material
materialStruct white = {
        {0.6, 0.6, 0.6, 1},
        {1.0, 1.0, 1.0, 1},
        {0.0, 0.0, 0.0, 1},
        10.0
};

// White2 Material
materialStruct white2 = {
        {1.0, 1.0, 0.8, 1},
        {1.0, 1.0, 0.8, 1},
        {1.0, 1.0, 0.8, 1},
        0.0
};

// Yellow Material
materialStruct yellow = {
        {0.4, 0.4, 0.0, 1},
        {0.6, 0.6, 0.1, 1},
        {0.6, 0.6, 0.3, 1},
        10.0
};

// Chimney Material
materialStruct chimney = {
        {0.7, 0.5, 0.3, 1},
        {0.8, 0.6, 0.4, 1},
        {0.0, 0.0, 0.0, 1},
        5.0
};

// Greenery Material
materialStruct greenery = {
        {0.0, 0.2, 0.0, 1},
        {0.0, 0.4, 0.0, 1},
        {0.0, 0.6, 0.0, 1},
        10.0
};

// Green Pants Material
materialStruct greenpants = {
        {0.0, 0.2, 0.0, 1},
        {0.1, 0.2, 0.1, 1},
        {0.00000001746, 0.0000000746, 0.00000001746, 1},
        10.0
};

// Bright Green For Spheres
materialStruct greensphere = {
        {0.0, 0.9, 0.0, 1},
        {0.1, 1.0, 0.1, 1},
        {0.1746, 0.746, 0.1746, 1},
        10.0
};

// Skin Color
materialStruct skincolor = {
        {0.4, 0.4, 0.1, 1},
        {0.95, 0.69, 0.12, 1},
        {0.0000005, 0.0000001, 0.0000001, 1},
        10.0
};

// Skin Color2
materialStruct skincolor2 = {
        {0.8, 0.8, 0.3, 1},
        {0.85, 0.79, 0.22, 1},
        {0.9, 0.8, 0.5, 1},
        10.0
};

// Skin Color2
/*
materialStruct skincolor2 = {
        {0.8, 0.8, 0.3, 1},
        {0.85, 0.79, 0.22, 1},
        {0.9, 0.8, 0.5, 1},
        10.0
};
*/
// Black
materialStruct black = {
        {0.0, 0.0, 0.0, 1},
        {0.0, 0.0, 0.0, 1},
        {0.0, 0.0, 0.0, 1},
        10.0
};

// Brown
materialStruct brown = {
        {0.4, 0.2, 0.0, 1},
        {0.6, 0.4, 0.2, 1},
        {0.8, 0.8, 0.5, 1},
        10.0
};

// Silver
materialStruct silver = {
        {0.1, 0.1, 0.1, 1},
        {0.65, 0.65, 0.65, 1},
        {0.0, 0.0, 0.0, 1},
        100.0
};

// Silver2
materialStruct silver2 = {
        {0.1, 0.1, 0.1, 1},
        {0.075, 0.075, 0.075, 1},
        {0.0, 0.0, 0.0, 1},
        10.0
};

// Navy Blue
materialStruct navyblue = {
        {0.0, 0.0, 0.1, 1},
        {0.05, 0.05, 0.45, 1},
        {0.0, 0.0, 0.0, 1},
        100.0
};

materialStruct *currentMaterial;

void materials(materialStruct *materials) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials -> ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials -> specular);
}


void objects() {

	glRotatef(10, 1, 0, 0);
	glRotatef(345, 0, 1, 0);
//	glRotatef(160, 0, 1, 0);
//	glRotatef(-10, 1, 0, 0);

	// ######## WALLS ########
	// TOP BOTTOM
	glPushMatrix();
		materials(&white2);
		glTranslatef(0.0, -4.0, 0.0);
		glScalef(11.5, 1.0, 11.5);
		glutSolidCube(1.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();
	// OUTSIDE
        glPushMatrix();
                materials(&navyblue);
                glTranslatef(0.0, -5.0, 0.0);
                glScalef(12.0, 1.0, 12.0);
                glutSolidCube(1.0);
                glTranslatef(0.0, 12.0, 0.0);
                glutSolidCube(1.0);
		glScalef(0.75, 1.0, 0.75);
		glTranslatef(0.0, 0.5, 0.0);
		glutSolidCube(1.0);
        glPopMatrix();
	// LEFT RIGHT
	glPushMatrix();
		materials(&white2);
		glTranslatef(-5.0, 1.0, 0.0);
		glScalef(1.0, 10.0, 10.0);
		glutSolidCube(1.0);
		glTranslatef(10.0, 0.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&white2);
		glTranslatef(-5.0, 5.0, 5.0);
		glScalef(0.75, 1.0, 1.0);
		for(int k=0; k<2; k++) {
		for(int j=0; j<6; j++) {
		for(int i=0; i<6; i++) {
			glTranslatef(0.0, 0.0, -1.5);
			glutSolidSphere(1.0, 100.0, 100.0);
		}
		glTranslatef(0.0, -1.5, 9.0);
		}
		glTranslatef(13.35, 9.0, 0.0);
		}
	glPopMatrix();
	// OUTSIDE
	glPushMatrix();
		materials(&navyblue);
		glTranslatef(-5.75, 1.0, 0.0);
		glScalef(1.0, 11.75, 11.75);
		glutSolidCube(1.0);
		glTranslatef(11.5, 0.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();
	// BACK
	glPushMatrix();
                materials(&white2);
                glTranslatef(0.0, 1.0, -5.0);
                glScalef(10.0, 10.0, 1.0);
                glutSolidCube(1.0);
	glPopMatrix();
        glPushMatrix();
                materials(&white2);
                glTranslatef(5.0, 5.0, -5.0);
                glScalef(1.0, 1.0, 0.75);
                for(int j=0; j<6; j++) {
                for(int i=0; i<6; i++) {
                        glTranslatef(-1.5, 0.0, 0.0);
                        glutSolidSphere(1.0, 100.0, 100.0);
                }
                glTranslatef(9.0, -1.5, 0.0);
                }
        glPopMatrix();
	// OUTSIDE
	glPushMatrix();
		materials(&navyblue);
		glTranslatef(0.0, 1.0, -6.0);
		glScalef(11.75, 11.75, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
	// PILLARS
	glPushMatrix();
		materials(&navyblue);
		glTranslatef(-6.0, 1.0, 6.0);
		glScalef(1.0, 11.0, 1.0);
		glutSolidCube(1.25);
		glTranslatef(12.0, 0.0, 0.0);
		glutSolidCube(1.25);
		glTranslatef(0.0, 0.0, -12.0);
		glutSolidCube(1.25);
                glTranslatef(-12.0, 0.0, 0.0);
                glutSolidCube(1.25);
	glPopMatrix();
	// BASE
	glPushMatrix();
		materials(&navyblue);
		glTranslatef(0.0, -6.0, 0.0);
		glScalef(14.0, 1.0, 14.0);
		glutSolidCube(1.0);
	glPopMatrix();
	// WINDOWS
	glPushMatrix();
		materials(&window);
		glTranslatef(-6.15, 4.5, -5.6);
		glScalef(0.25, 2.0, 1.0);
		for(int j=0; j<2; j++) {
		for(int i=0; i<3; i++) {
			glTranslatef(0.0, 0.0, 1.35);
			glutSolidCube(1.0);
		}
		glTranslatef(0.0, -1.15, -4.05);
		}
	glPopMatrix();
        glPushMatrix();
                materials(&window);
                glTranslatef(-6.15, 4.5, 0.2);
                glScalef(0.25, 2.0, 1.0);
                for(int j=0; j<2; j++) {
                for(int i=0; i<3; i++) {
                        glTranslatef(0.0, 0.0, 1.35);
                        glutSolidCube(1.0);
                }
                glTranslatef(0.0, -1.15, -4.05);
                }
        glPopMatrix();
        glPushMatrix();
                materials(&window);
                glTranslatef(6.15, 4.5, 0.2);
                glScalef(0.25, 2.0, 1.0);
                for(int j=0; j<2; j++) {
                for(int i=0; i<3; i++) {
                        glTranslatef(0.0, 0.0, 1.35);
                        glutSolidCube(1.0);
                }
                glTranslatef(0.0, -1.15, -4.05);
                }
        glPopMatrix();
        glPushMatrix();
                materials(&window);
                glTranslatef(6.15, 4.5, -5.6);
                glScalef(0.25, 2.0, 1.0);
                for(int j=0; j<2; j++) {
                for(int i=0; i<3; i++) {
                        glTranslatef(0.0, 0.0, 1.35);
                        glutSolidCube(1.0);
                }
                glTranslatef(0.0, -1.15, -4.05);
                }
        glPopMatrix();
	// LIGHT
	glPushMatrix();
		materials(&house);
		glTranslatef(0.0, 8.0, 0.0);
		glScalef(0.25, 1.0, 0.25);
		glutSolidCube(2.0);
		materials(&black);
		glutWireCube(2.0);
	glPopMatrix();

	// ######## 2nd FLOOR ########
	glPushMatrix();
		materials(&white2);
		glTranslatef(0.0, 1.0, -3.0);
		glScalef(10.0, 0.5, 4.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glTranslatef(2.5, -1.75, -2.5);
		glScalef(1.0, 1.25, 0.75);
		glutSolidCube(4.0);
	glPopMatrix();

	// ######## SECOND DOOR ########
	glPushMatrix();
		materials(&silver2);
		glTranslatef(-2.0, 3.25, -4.5);
		glScalef(1.0, 2.0, 0.25);
		glutSolidCube(2.0);
		glTranslatef(4.0, 0.0, 0.0);
		glutSolidCube(2.0);
	glPopMatrix();
	glPushMatrix();
		materials(&black);
		glTranslatef(-1.5, 3.0, -4.2);
		glutSolidSphere(0.2, 100, 100);
		glTranslatef(4.0, 0.0, 0.0);
		glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	// ######## STAIRS ########
	glPushMatrix();
		materials(&silver);
		glTranslatef(3.25, 1.0, -1.55);
		glScalef(2.5, 0.25, 1.0);
		glutSolidCube(1.0);
		for(int i=0; i<7; i++) {
			glTranslatef(0.0, -2.5, 0.65);
			glutSolidCube(1.0);
		}
	glPopMatrix();
	glPushMatrix();
		materials(&black);
		glRotatef(45.0, 1, 0, 0);
		glTranslatef(2.0, -0.25, 2.5);
		glScalef(0.25, 0.5, 7.0);
		glutSolidCube(1.0);
		glTranslatef(9.5, 0.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();

	// ######## RAILINGS ########
	glPushMatrix();
		materials(&silver);
		glTranslatef(-1.5, 3.0, -1.2);
		glScalef(14.5, 0.5, 0.5);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glTranslatef(2.0, 2.0, -1.2);
		glScalef(0.5, 3.5, 0.5);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glRotatef(45, 1, 0, 0);
		glTranslatef(2.0, 1.35, 0.4);
		glScalef(0.5, 0.5, 13.25);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glTranslatef(2.0, -2.85, 3.55);
		glScalef(0.5, 5.0, 0.5);
		glutSolidCube(0.5);
	glPopMatrix();

	// ######## TABLE1 ########
	glPushMatrix();
		materials(&white2);
		glTranslatef(-2.0, -2.0, -3.0);
		glScalef(2.5, 0.25, 1.65);
		glutSolidCube(2.0);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glTranslatef(-2.0, -3.0, -3.0);
		glScalef(0.1, 1.0, 0.1);
		glutSolidCube(2.0);
	glPopMatrix();
	// ######## CHAIRS ########
	glPushMatrix();
                materials(&silver);
                glTranslatef(-3.0, -2.5, -1.0);
                glScalef(1.0, 0.25, 1.0);
                glutSolidCube(1.0);
                glTranslatef(2.0, 0.0, 0.0);
                glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&silver);
		glTranslatef(-3.0, -3.0, -1.0);
		glScalef(0.2, 1.0, 0.2);
		glutSolidCube(1.0);
		glTranslatef(10.0, 0.0, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();

	// ######## DUDE SITTING AT THE BAR ########
	glPushMatrix();
		// Body
		materials(&white);
		glTranslatef(-1.0, -1.5, -1.0);
		glScalef(1.0, 1.75, 1.0);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
        glPushMatrix();
                // Legs
                materials(&white);
                glTranslatef(-1.25, -2.05, -0.5);
                glScalef(1.0, 1.0, 2.0);
                glutSolidSphere(0.25, 100, 100);
		glTranslatef(0.5, 0.0, 0.0);
		glutSolidSphere(0.25, 100, 100);
        glPopMatrix();
        glPushMatrix();
                // Arms
                materials(&white);
                glTranslatef(-1.65, -1.15, -1.0);
                glScalef(2.0, 1.0, 1.0);
                glutSolidSphere(0.25, 100, 100);
                glTranslatef(0.65, 0.0, 0.0);
                glutSolidSphere(0.25, 100, 100);
        glPopMatrix();
	glPushMatrix();
		// Head
		materials(&skincolor);
		glTranslatef(-1.0, -0.35, -1.0);
		glutSolidSphere(0.35, 100, 100);
	glPopMatrix();
	glPushMatrix();
		// Eyes
		materials(&black);
		glTranslatef(-1.15, -0.25, -0.70);
		glutSolidSphere(0.075, 100, 100);
		glTranslatef(0.25, 0.0, 0.0);
		glutSolidSphere(0.075, 100, 100);
	glPopMatrix();

	// ######## 1UP ########
	glPushMatrix();
		// Bottom Shroom
		materials(&skincolor2);
		glTranslatef(-2.0, -1.25, -2.5);
		glScalef(1.15, 1.0, 1.15);
		glutSolidSphere(0.35, 100, 100);
	glPopMatrix();
	glPushMatrix();
		// Top Shroom
		materials(&greensphere);
		glTranslatef(-2.0, -0.85, -2.65);
		glScalef(1.5, 1.0, 1.25);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
	glPushMatrix();
		// Eyes
		materials(&black);
		glTranslatef(-1.85, -1.25, -2.15);
		glScalef(1.0, 2.0, 1.0);
		glutSolidSphere(0.075, 100, 100);
		glTranslatef(-0.35, 0.0, 0.0);
		glutSolidSphere(0.075, 100, 100);
	glPopMatrix();
	glPushMatrix();
		// Spots
		materials(&white);
		glTranslatef(-2.0, -0.75, -2.5);
		glScalef(1.0, 0.8, 1.0);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

/*
	// ######## COMPANION CUBE ########
	// Core
	glPushMatrix();
		materials(&white);
		glTranslatef(-3.0, 2.0, -2.75);
		glutSolidCube(1.0);
	glPopMatrix();
	// Corners
	glPushMatrix();
		materials(&white2);
		glTranslatef(-3.0, 
	glPopMatrix();
*/
}

void stars() {
        srand(time(NULL));
        glPointSize(3.0);
//        glColor3f(1.0, 1.0, 1.0);
	double val = 0;
	val = (float)rand()/(float)(RAND_MAX) * 10.0;
	if(val < 1)
		materials(&white);
	else if(val < 2)
		materials(&silver);
	else if(val < 3)
		materials(&window);
	else if(val < 4)
		materials(&chimney);
	else if(val < 5)
		materials(&skincolor);
        else if(val < 6)
                materials(&house);
        else if(val < 7)
                materials(&door);
        else if(val < 8)
                materials(&greenery);
        else if(val < 9)
                materials(&ground);
	else
		materials(&white2);
//	materials(&white);
        for(int i=0; i<50; i++) {
		glPointSize((float)rand()/(float)(RAND_MAX) * 15.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 15.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, (-1)*y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 15.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<50; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 15.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 20.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, (-1)*y2, -10);
                glEnd();
        }

}

// Added For Lighting Effects
void init() {
	glClearColor(0.15, 0.1, 0.2, 0.0);	// Navy Blue Background

	// Eyes at 1, 1, 1, object at 0, 0, 0, and up is in y direction
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_LIGHTING);			// Enable The Lighting
	glEnable(GL_LIGHT0);			// Light Source Number 0

	currentLight = &blueLight;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLight -> specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLight -> diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLight -> ambient);

	currentMaterial = &house;

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

void idle() {
	// Increments theta when called
	theta[axis] += 1.25;
	if(theta[axis] > 360.0) {
		theta[axis] -= 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-8.0, 8.0, -8.0*(GLfloat) h / (GLfloat) w,
			8.0*(GLfloat) h / (GLfloat) w, -12.0, 12.0);
	} else {
		glOrtho(-8.0*(GLfloat) w/(GLfloat) h, 8.0 * (GLfloat) w/ (GLfloat) h,
			-8.0, 8.0, -12.0, 12.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
	if(key == 'r') glutIdleFunc( idle );
	if(key == 's') glutIdleFunc( NULL );
	if(key == 'q') exit(0);
}

void myMouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 1;
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);

        // Windowing:
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0.0, 0.0);

        glutCreateWindow("My Room");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
	init();
        glutMainLoop();
}
