#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive y
GLfloat size = 0.0;

// Specify The Location Of Light 0
GLfloat light0_pos[] = {1.0, 1.0, 1.0, 0.0};

// Cloud Variables
GLfloat cloudTheta = 0.0;
int cloudSwitch = 0;

// Car Variables
GLfloat carThetaX = 0.0, carThetaY = 0.0;
int carSwitchY = 0;

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
  10.0
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
	{0.6, 0.9, 1.0, 1},
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
        {0.9, 0.9, 0.9, 1},
        {0.01, 0.01, 0.01, 1},
        10.0
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

// Black
materialStruct black = {
        {0.0, 0.0, 0.0, 1},
        {0.3, 0.3, 0.3, 1},
        {0.7, 0.7, 0.7, 1},
        10.0
};

// Vanta Black
materialStruct vantaBlack = {
	{0.0, 0.0, 0.0, 1},
	{0.0, 0.0, 0.0, 1},
	{0.0, 0.0, 0.0, 1},
	10.0
};

// Grey
materialStruct grey = {
	{0.3, 0.3, 0.3, 1},
	{0.7, 0.7, 0.7, 1},
	{0.9, 0.9, 0.9, 1},
	10.0
};

// Brown
materialStruct brown = {
        {0.4, 0.2, 0.0, 1},
        {0.6, 0.4, 0.2, 1},
        {0.8, 0.8, 0.5, 1},
        10.0
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

	// Ground
	glPushMatrix();
		materials(&ground);
		glTranslatef(0.0, -4.0, 0.0);
		glScalef(15.0, 1.0, 15.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&grey);
		glTranslatef(0.0, -4.0, 9.5);
		glScalef(25.0, 1.0, 4.0);
		glutSolidCube(1.0);
	glPopMatrix();

	// Clouds
	glPushMatrix();
		materials(&white);
		glTranslatef(0.0+cloudTheta, 8.0, 0.0);
		for(int i=0; i<3; i++) {
			glutSolidSphere(1.0, 100, 100);
			glTranslatef(1.0, 0.0, 0.0);
		}
	glPopMatrix();
	glPushMatrix();
		materials(&white);
		glTranslatef(-6.0+cloudTheta*1.5, 8.0, -6.0);
		for(int i=0; i<3; i++) {
			glutSolidSphere(1.0, 100, 100);
			glTranslatef(1.0, 0.0, 0.0);
		}
	glPopMatrix();

	// Cars
	// CarBody1
	glPushMatrix();
		materials(&door);
		glTranslatef(-4.0+(carThetaX/2.0)*2.0, -2.5+carThetaY, 9.5);
		glScalef(2.0, 1.0, 1.0);
		glutSolidSphere(0.75, 100, 100);

		materials(&window);
		glTranslatef(0.0, 0.65, 0.0);
		glScalef(1.0, 1.5, 1.0);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
	// Wheels
	glPushMatrix();
		materials(&vantaBlack);
		glTranslatef(-4.5+carThetaX, -3.25+carThetaY, 10.0);
		glScalef(1.0, 1.0, 0.2);
		glutSolidSphere(0.35, 100, 100);
		glTranslatef(1.0, 0.0, 0.0);
		glutSolidSphere(0.35, 100, 100);
		glTranslatef(0.0, 0.0, -5.0);
		glutSolidSphere(0.35, 100, 100);
		glTranslatef(-1.0, 0.0, 0.0);
		glutSolidSphere(0.35, 100, 100);
	glPopMatrix();
	// Lights
	glPushMatrix();
		materials(&house);
		glTranslatef(-5.0+carThetaX, -2.5+carThetaY, 10.0);
		glScalef(2.0, 1.0, 1.0);
		glutSolidSphere(0.25, 100, 100);
		glTranslatef(0.0, 0.0, -1.0);
		glutSolidSphere(0.25, 100, 100);
	glPopMatrix();

	// House Walls
	// ######### MAIN BUILDING
	glPushMatrix();
		materials(&house);
		glScalef(1.6, 0.8, 1.2);
		glTranslatef(0.0, -2.0, 0.0);
		glutSolidCube(5.0);
	glPopMatrix();

	glPushMatrix();
		materials(&house);
		glRotatef(45, 1, 0, 0);
		glScalef(1.8, 1.0, 1.0);
		glutSolidCube(4.3);
	glPopMatrix();

        glPushMatrix();
                materials(&house2);
                glRotatef(45, 1, 0, 0);
		glScalef(1.75, 1.0, 1.0);
		glTranslatef(0.0, 0.2, -0.2);
                glutSolidCube(4.4);
        glPopMatrix();

	// ########### SIDE BUILDING
        glPushMatrix();
                materials(&house);
                glScalef(0.6, 0.8, 1.2);
                glTranslatef(8.0, -3.0, 0.0);
                glutSolidCube(3.0);
        glPopMatrix();

        glPushMatrix();
                materials(&house);
                glRotatef(45, 1, 0, 0);
                glScalef(0.6, 1.0, 1.0);
		glTranslatef(8.0, -1.0, 1.0);
                glutSolidCube(2.6);
        glPopMatrix();

       glPushMatrix();
                materials(&house2);
                glRotatef(45, 1, 0, 0);
                glScalef(0.57, 1.0, 1.0);
                glTranslatef(8.3, -0.8, 0.9);
                glutSolidCube(2.6);
        glPopMatrix();

	// ########## GARAGE
        glPushMatrix();
                materials(&house);
                glScalef(0.6, 0.8, 1.2);
                glTranslatef(-8.0, -3.0, 0.0);
                glutSolidCube(3.0);
        glPopMatrix();

        glPushMatrix();
                materials(&house);
                glRotatef(45, 1, 0, 0);
                glScalef(0.6, 1.0, 1.0);
                glTranslatef(-8.0, -1.0, 1.0);
                glutSolidCube(2.6);
        glPopMatrix();

        glPushMatrix();
                materials(&house2);
                glRotatef(45, 1, 0, 0);
                glScalef(0.57, 1.0, 1.0);
                glTranslatef(-8.3, -0.8, 0.9);
                glutSolidCube(2.6);
        glPopMatrix();

	// ########## ROOF
	glPushMatrix();
		materials(&house);
		glTranslatef(2.0, 1.5, 1.5);
		glutSolidCube(2.0);
		glTranslatef(-4.0, 0.0, 0.0);
		glutSolidCube(2.0);
	glPopMatrix();

        glPushMatrix();
                materials(&house);
		glRotatef(45, 0, 0, 1);
                glTranslatef(3.1, 0.3, 1.7);
                glutSolidCube(1.5);
                glTranslatef(-2.8, 2.8, 0.0);
                glutSolidCube(1.5);
        glPopMatrix();

        glPushMatrix();
                materials(&house2);
                glRotatef(45, 0, 0, 1);
                glTranslatef(3.2, 0.4, 1.68);
                glutSolidCube(1.5);
                glTranslatef(-2.8, 2.8, 0.0);
                glutSolidCube(1.5);
        glPopMatrix();

	// DOOR
	glPushMatrix();
		materials(&door);
		glScalef(1.0, 2.0, 1.0);
		glTranslatef(0.0, -1.3, 2.6);
		glutSolidCube(1.0);
		materials(&white);
		glTranslatef(0.0, 0.0, -0.1);
		glutSolidCube(1.15);
	glPopMatrix();
	glPushMatrix();
		materials(&white);
		glRotatef(45, 0, 0, 1);
		glTranslatef(-1.0, -1.0, 2.75);
		glutSolidCube(0.6);
		materials(&door);
		glTranslatef(0.0, 0.0, -0.1);
		glutSolidCube(0.75);
	glPopMatrix();
	glPushMatrix();
		materials(&white);
		glTranslatef(0.0, -3.75, 3.25);
		glutSolidCube(1.0);
	glPopMatrix();
	// DESIGN
	glPushMatrix();
		materials(&black);
		glScalef(1.0, 2.5, 1.0);
		glTranslatef(-0.2, -0.8, 3.0);
		glutWireCube(0.25);
		glTranslatef(0.4, 0.0, 0.0);
		glutWireCube(0.25);
		glTranslatef(0.0, -0.325, 0.0);
		glutWireCube(0.25);
		glTranslatef(-0.4, 0.0, 0.0);
		glutWireCube(0.25);
	glPopMatrix();
	// KNOB
	glPushMatrix();
		materials(&black);
		glTranslatef(0.29, -2.4, 3.1);
		glutSolidSphere(0.075, 100, 100);
	glPopMatrix();
	// SECOND FRONT DOOR & WINDOWS
	glPushMatrix();
		materials(&yellow);
		glTranslatef(4.8, -2.75, 1.55);
		glScalef(1.0, 2.3, 1.0);
		glutSolidCube(0.8);
		materials(&door2);
		glTranslatef(0.0, 0.0, -0.1);
		glutSolidCube(0.9);
		// WINDOWS
		materials(&window);
		glScalef(0.75, 1.0, 0.75);
		glTranslatef(0.4, 0.2, 0.1);
		glutSolidCube(0.8);
		glTranslatef(-0.9, 0.0, 0.0);
		glutSolidCube(0.8);
		glTranslatef(1.35, 0.0, -0.8);
		glutSolidCube(0.8);
		glTranslatef(0.0, 0.0, -1.2);
		glutSolidCube(0.8);
		glTranslatef(0.0, 0.0, -1.2);
		glutSolidCube(0.8);
		glTranslatef(-0.4, 0.0, -0.85);
		glutSolidCube(0.8);
		glTranslatef(-0.4, 0.0, 0.0);
		glutSolidCube(0.8);
		glTranslatef(-0.4, 0.0, 0.0);
		glutSolidCube(0.8);
	glPopMatrix();
	// STEPS
	glPushMatrix();
                materials(&white);
		glTranslatef(4.8, -3.8, 2.04);
                glutSolidCube(1.0);
	glPopMatrix();
	// KNOB
	glPushMatrix();
		materials(&black);
		glTranslatef(5.0, -2.6, 1.95);
		glutSolidSphere(0.075, 100, 100);
	glPopMatrix();

	// PATH & GARAGE
	glPushMatrix();
		materials(&white);
		glTranslatef(0.0, -3.95, 5.0);
		glScalef(1.0, 1.0, 4.0);
		glutSolidCube(1.0);
		glTranslatef(-4.75, 0.0, -0.1);
		glScalef(2.0, 1.0, 1.35);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&white);
		glTranslatef(-4.6, -2.5, 1.4);
		glScalef(1.0, 1.0, 0.5);
		glutSolidCube(1.95);
	glPopMatrix();

	// Front Bottom Windows
	glPushMatrix();
		materials(&window);
		glTranslatef(-2.0, -2.0, 2.4);
		glutSolidCube(1.35);
		glTranslatef(4.0, 0.0, 0.0);
		glutSolidCube(1.35);
	glPopMatrix();
	glPushMatrix();
		materials(&yellow);
		glTranslatef(-2.0, -2.0, 2.5);
		glScalef(0.1, 1.0, 1.0);
		glutSolidCube(1.35);
		glTranslatef(-7.5, 0.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(15.0, 0.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(40.0, 0.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(-15, 0.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(7.5, 0.0, 0.0);
		glutSolidCube(1.35);
	glPopMatrix();
        glPushMatrix();
                materials(&yellow);
                glTranslatef(-2.0, -2.0, 2.5);
                glScalef(1.0, 0.1, 1.0);
                glutSolidCube(1.35);
                glTranslatef(4.0, 0.0, 0.0);
                glutSolidCube(1.35);
		glTranslatef(0.0, 6.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(0.0, -12.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(-4.0, 0.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(0.0, 12.0, 0.0);
		glutSolidCube(1.35);
        glPopMatrix();
	glPushMatrix();
		materials(&yellow);
		glTranslatef(-3.075, -2.0, 2.9);
		glScalef(1.0, 2.7, 1.0);
		glutSolidCube(0.5);
		glTranslatef(2.15, 0.0, 0.0);
		glutSolidCube(0.5);
		glTranslatef(1.85, 0.0, 0.0);
		glutSolidCube(0.5);
		glTranslatef(2.15, 0.0, 0.0);
		glutSolidCube(0.5);
	glPopMatrix();

	// Front Top Windows
        glPushMatrix();
                materials(&window);
                glTranslatef(-2.0, 1.8, 1.9);
                glutSolidCube(1.35);
                glTranslatef(4.0, 0.0, 0.0);
                glutSolidCube(1.35);
        glPopMatrix();
        glPushMatrix();
                materials(&yellow);
                glTranslatef(-2.0, 1.8, 1.95);
                glScalef(0.1, 1.0, 1.0);
                glutSolidCube(1.35);
                glTranslatef(-7.5, 0.0, 0.0);
                glutSolidCube(1.35);
                glTranslatef(15.0, 0.0, 0.0);
                glutSolidCube(1.35);
                glTranslatef(40.0, 0.0, 0.0);
                glutSolidCube(1.35);
                glTranslatef(-15, 0.0, 0.0);
                glutSolidCube(1.35);
                glTranslatef(7.5, 0.0, 0.0);
                glutSolidCube(1.35);
        glPopMatrix();
        glPushMatrix();
                materials(&yellow);
                glTranslatef(-2.0, 1.8, 1.95);
                glScalef(1.0, 0.1, 1.0);
                glutSolidCube(1.35);
                glTranslatef(4.0, 0.0, 0.0);
                glutSolidCube(1.35);
		glTranslatef(0.0, 6.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(0.0, -12.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(-4.0, 12.0, 0.0);
		glutSolidCube(1.35);
		glTranslatef(0.0, -12.0, 0.0);
		glutSolidCube(1.35);
        glPopMatrix();

	// TREE
	glPushMatrix();
		materials(&brown);
		glTranslatef(6.5, 0.0, -6.5);
		glScalef(1.0, 7.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		materials(&greenery);
		glTranslatef(6.5, 5.0, -6.5);
		glScalef(1.75, 1.0, 2.0);
		glutSolidSphere(2.2, 100, 100);
	glPopMatrix();

	// CHIMNEY
	glPushMatrix();
		materials(&chimney);
		glTranslatef(2.5, 3.0, -0.35);
		glScalef(0.7, 2.0, 0.7);
		glutSolidCube(1.0);
		glTranslatef(0.0, 0.45, 0.0);
		glScalef(1.2, 0.25, 1.2);
		glutSolidCube(1.0);
	glPopMatrix();

	// BUSHES
	glPushMatrix();
		materials(&greenery);
		glTranslatef(-3.0, -3.35, 3.5);
		glScalef(1.5, 1.0, 1.0);
		glutSolidSphere(0.65, 100, 100);
		glTranslatef(1.0, 0.0, 0.0);
		glutSolidSphere(0.65, 100, 100);
		glTranslatef(2.0, 0.0, 0.0);
		glutSolidSphere(0.65, 100, 100);
		glTranslatef(1.0, 0.0, 0.0);
		glutSolidSphere(0.65, 100, 100);
        glPopMatrix();
	glPushMatrix();
		materials(&greenery);
		glTranslatef(4.25, -3.25, 2.65);
		glutSolidSphere(0.35, 100, 100);
		glTranslatef(1.25, 0.0, 0.0);
		glutSolidSphere(0.35, 100, 100);
	glPopMatrix();

	// ############## BACK OF HOUSE
	glPushMatrix();
		materials(&house);
		glTranslatef(0.0, 0.25, -0.9);
		glutSolidCube(4.0);
		glRotatef(-20, 1, 0, 0);
		glScalef(1.0, 1.0, 0.7);
		glTranslatef(0.0, 0.65, 0.45);
		glutSolidCube(4.0);
		// ROOF
		materials(&house2);
		glTranslatef(0.0, 0.1, 0.0);
		glutSolidCube(3.9);
	glPopMatrix();

	// BACK TOP WINDOWS
	glPushMatrix();
		materials(&window);
		glTranslatef(1.0, 1.35, -2.2);
		glutSolidCube(1.5);
		glTranslatef(-2.0, 0.0, 0.0);
		glutSolidCube(1.5);
	glPopMatrix();
	// BACK BOTTOM WINDOWS
	glPushMatrix();
		materials(&window);
		glTranslatef(3.0, -1.75, -2.3);
		glScalef(0.75, 1.0, 1.0);
		glutSolidCube(1.5);
		glTranslatef(-2.0, 0.0, 0.0);
		glutSolidCube(1.5);
		glTranslatef(-4.0, 0.0, 0.0);
		glutSolidCube(1.5);
		glTranslatef(-2.0, 0.0, 0.0);
		glutSolidCube(1.5);
	glPopMatrix();
	// BACK DOOR
	glPushMatrix();
		materials(&white);
		glTranslatef(0.0, -2.5, -2.4);
		glScalef(1.0, 1.75, 1.0);
		glutSolidCube(1.25);
		materials(&door);
		glTranslatef(0.0, 0.0, -0.1);
		glutSolidCube(1.1);
		// DESIGN
		materials(&black);
		glTranslatef(0.25, 0.25, -0.4);
		glutWireCube(0.35);
		glTranslatef(-0.5, 0.0, 0.0);
		glutWireCube(0.35);
		glTranslatef(0.0, -0.5, 0.0);
		glutWireCube(0.35);
		glTranslatef(0.5, 0.0, 0.0);
		glutWireCube(0.35);
	glPopMatrix();
	// BACK KNOB
	glPushMatrix();
		materials(&black);
		glTranslatef(-0.4, -2.5, -3.0);
		glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
	// BACK STEPS
	glPushMatrix();
		materials(&white);
		glTranslatef(0.0, -3.6, -3.0);
		glScalef(1.0, 0.5, 1.0);
		glutSolidCube(1.25);
	glPopMatrix();

	// ############## PERSON
	// BODY
	glPushMatrix();
		glTranslatef(2.0, -0.45, 2.0);
		materials(&white);
		glTranslatef(0.0, -2.0, 4.0);
		glScalef(0.5, 0.8, 0.5);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();
	// Arms
	glPushMatrix();
                glTranslatef(2.0, 0.0, 2.0);
		materials(&skincolor);
		glRotatef(35, 0, 0, 1);
		glTranslatef(-1.0, -2.0, 4.0);
		glScalef(0.2, 0.6, 0.2);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();
	glPushMatrix();
                glTranslatef(2.0, 0.0, 2.0);
		materials(&skincolor);
		glRotatef(-35, 0, 0, 1);
		glTranslatef(1.0, -2.0, 4.0);
		glScalef(0.2, 0.6, 0.2);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();
	// Legs
	glPushMatrix();
		glTranslatef(2.0, 0.0, 2.0);
		materials(&greenpants);
		glTranslatef(0.25, -3.0, 4.0);
		glScalef(0.2, 0.6, 0.2);
		glutSolidSphere(1.0, 100, 100);
		glTranslatef(-2.35, 0.0, 0.0);
		glutSolidSphere(1.0, 100, 100);
	glPopMatrix();
	// Head
	glPushMatrix();
		glTranslatef(2.0, -1.4, 6.0);
		materials(&skincolor2);
		glutSolidSphere(0.3, 100, 100);
		materials(&brown);
		glTranslatef(0.0, 0.1, 0.0);
		glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
	// Eyes & Mouth
	glPushMatrix();
		glTranslatef(1.9, -1.3, 6.3);
		materials(&white);
		glutSolidSphere(0.05, 100, 100);
		glTranslatef(0.2, 0.0, 0.0);
		glutSolidSphere(0.05, 100, 100);
		materials(&black);
		glTranslatef(-0.1, -0.15, -0.05);
		glRotatef(10, 0, 0, 1);
		glScalef(2.0, 1.0, 1.0);
		glutSolidSphere(0.075, 100, 100);
	glPopMatrix();

}

// Added For Lighting Effects
void init() {
	glClearColor(0.4, 0.8, 1.0, 0.0);	// Blue Background

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

void autoIdle() {
	// Cloud Theta Position Updates
	if(cloudSwitch == 0) cloudTheta += 0.05;
	if(cloudSwitch == 1) cloudTheta -= 0.05;
	if(cloudTheta > 20) cloudSwitch = 1;
	if(cloudTheta < -20) cloudSwitch = 0;

	// Car Theta Position Updates
//	if(carSwitchY == 0) {
//	}
//	if(carSwitchY == 1) {
//	}
	carThetaX -= 0.05;
	if(carThetaX < -9.25 || carThetaX > 9.25) {
		carThetaY -= 0.1;
	}
	if(carThetaY < -15.0) {
		carThetaY = 20.0;
		carThetaX = 19.25;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h) {
		glOrtho(-12.0, 12.0, -12.0*(GLfloat) h / (GLfloat) w,
			12.0*(GLfloat) h / (GLfloat) w, -20.0, 20.0);
	} else {
		glOrtho(-12.0*(GLfloat) w/(GLfloat) h, 12.0 * (GLfloat) w/ (GLfloat) h,
			-12.0, 12.0, -20.0, 20.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
	if(key == 'r') glutIdleFunc( idle );
	if(key == 's') glutIdleFunc( autoIdle );
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

        glutCreateWindow("My Moving Objects");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
	glutIdleFunc( autoIdle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
	init();
        glutMainLoop();
}
