#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define DTR PI/180

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive y
GLfloat size = 0.0;

// Planet/Moon Theta Values:
GLfloat mercury = 0.0, venus = 0.0, earth = 0.0, mars = 0.0, jupiter = 0.0, saturn = 0.0, uranus = 0.0, neptune = 0.0, pluto = 0.0, moon = 0.0;

// Specify The Location Of Light 0
GLfloat light0_pos[] = {1.0, 1.0, 1.0, 0.2};
//GLfloat light0_pos[] = {1.0, 1.0, 1.0, 0.0};

GLfloat sclX = 1.0;

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
/*
lightStruct blueLight = {
        {0.6, 0.6, 1.0, 1.0},
        {0.5, 0.3, 0.4, 1.0},
        {0.1, 0.1, 0.1, 1.0}
};
*/

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

// Sun Material
materialStruct Sun = {
        {1.0, 1.0, 0.5},
        {1.0, 1.0, 0.5},
        {1.0, 1.0, 0.7746},
        200.8
};

// Sun2 Material
materialStruct Sun2 = {
        {1.75, 1.75, 1.0},
        {1.5, 1.5, 1.0},
        {1.0, 1.0, 0.7746},
        300.8
};

// Mercury Material
materialStruct Mercury = {
        {0.55, 0.55, 0.45},
        {0.90, 0.90, 0.80},
        {0.9746, 0.9746, 0.8746},
        10.8
};

// Mercury2 Material
materialStruct Mercury2 = {
        {0.45, 0.4, 0.3},
        {1.80, 1.80, 1.20},
        {2.3746, 2.3746, 2.0746},
        10.8
};

// Venus Material
materialStruct Venus = {
        {0.95, 0.95, 0.25},
        {0.99, 0.99, 0.40},
        {0.9746, 0.9746, 0.7746},
        10.8
};

// Venus2 Material
materialStruct Venus2 = {
        {0.3, 0.3, 0.15},
        {2.39, 2.29, 0.80},
        {3.9746, 3.9746, 1.7746},
        10.8
};

// Earth Material
materialStruct Earth = {
        {0.25, 0.95, 0.75},
        {0.40, 0.99, 0.70},
        {0.7746, 0.9746, 0.7746},
        10.8
};

// Earth2 Material
materialStruct Earth2 = {
        {0.1, 0.3, 0.3},
        {0.80, 1.99, 1.40},
        {1.7746, 2.9746, 2.7746},
        10.8
};

// Mars Material
materialStruct Mars = {
        {0.85, 0.15, 0.05},
        {0.80, 0.20, 0.20},
        {0.9746, 0.2746, 0.2746},
        10.8
};

// Mars2 Material
materialStruct Mars2 = {
        {0.3, 0.1, 0.1},
        {2.40, 0.50, 0.50},
        {3.0746, 0.5746, 0.5746},
        10.8
};

// Jupiter Material
materialStruct Jupiter = {
        {0.95, 0.85, 0.75},
        {0.90, 0.80, 0.70},
        {0.9746, 0.9746, 0.8746},
        10.8
};

// Jupiter2 Material
materialStruct Jupiter2 = {
        {1.95, 1.85, 1.75},
        {1.90, 1.80, 1.70},
        {2.9746, 2.9746, 2.8746},
        10.8
};

// Saturn Material
materialStruct Saturn = {
        {0.85, 0.75, 0.45},
        {0.90, 0.80, 0.40},
        {0.9746, 0.9746, 0.6746},
        10.8
};

// Uranus Material
materialStruct Uranus = {
        {0.25, 0.55, 0.55},
        {0.50, 0.70, 0.80},
        {0.7746, 0.9746, 0.9746},
        10.8
};

// Neptune Material
materialStruct Neptune = {
        {0.25, 0.55, 0.95},
        {0.30, 0.50, 0.90},
        {0.4746, 0.7746, 0.9746},
        10.8
};

// Moon Material
materialStruct Moon = {
        {0.65, 0.65, 0.65},
        {0.80, 0.80, 0.80},
        {0.9746, 0.9746, 0.9746},
        10.8
};

// Moon2 Material
materialStruct Moon2 = {
        {0.65, 0.65, 0.65},
        {0.80, 0.80, 0.80},
        {1.9746, 1.9746, 1.9746},
        10.8
};

materialStruct *currentMaterial;

void materials(materialStruct *materials) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials -> ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials -> specular);
}


void objects() {

	glScalef(sclX, sclX, sclX);

	// SUN
	glPushMatrix();
		if(sclX == 1.0)	materials(&Sun);
		else if(sclX > 1.0) materials(&Sun2);
		glutSolidSphere(1.0, 200, 200);
	glPopMatrix();

	// MERCURY
        glPushMatrix();
                if(sclX == 1.0) materials(&Mercury);
		else if(sclX > 1.0) materials(&Mercury2);
                glRotatef(mercury, 0, 0, 1);
                glTranslatef(1.17, 0.0, 0.0);
                glutSolidSphere(0.09758, 200, 200);
        glPopMatrix();

        // VENUS
        glPushMatrix();
	        if(sclX == 1.0) materials(&Venus);
                else if(sclX > 1.0) materials(&Venus2);
		glRotatef(venus, 0, 0, 1);
                glTranslatef(2.16, 0.0, 0.0);
                glutSolidSphere(0.24208, 200, 200);
        glPopMatrix();

        // EARTH
        glPushMatrix();
                if(sclX == 1.0) materials(&Earth);
                else if(sclX > 1.0) materials(&Earth2);
		glRotatef(earth, 0, 0, 1);
                glTranslatef(3.0, 0.0, 0.0);
                glutSolidSphere(0.25512, 200, 200);

                // MOON1
                glPushMatrix();
                        if(sclX == 1.0) materials(&Moon);
                        else if(sclX > 1.0) materials(&Moon2);
			glRotatef(moon, 0, 0, 1);
                        glTranslatef(0.35, 0.0, 0.0);
                        glutSolidSphere(0.05, 200, 200);
                glPopMatrix();

        glPopMatrix();

	// MARS
	glPushMatrix();
		if(sclX == 1.0) materials(&Mars);
		else if(sclX > 1.0) materials(&Mars);
		glRotatef(mars, 0, 0, 1);
		glTranslatef(4.56, 0.0, 0.0);
		glutSolidSphere(0.13584, 200, 200);

		// MOON1
		glPushMatrix();
			materials(&Moon);
			glRotatef(moon, 0, 0, 1);
			glTranslatef(0.25, 0.0, 0.0);
			glutSolidSphere(0.05, 200, 200);
		glPopMatrix();
		// MOON2
		glPushMatrix();
			materials(&Moon);
			glRotatef(moon, 0, 0, 1);
			glTranslatef(0.0, 0.5, 0.0);
			glutSolidSphere(0.05, 200, 200);
		glPopMatrix();
	glPopMatrix();

	// Asteroid Belt
	for(int j=0; j<8; j++) {
	for(int i=0; i<20; i++) {
                glPushMatrix();
			glPointSize(1.1);
                        if(sclX == 1.0) materials(&Moon);
			else if(sclX > 1.0) materials(&Moon2);
			glScalef(5.2+(0.1*j), 5.2+(0.1*j), 0.0);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(cos(((i*j)*PI)*DTR), sin(((i*j)*PI)*DTR), 0.0);
	                glBegin(GL_POINTS);
        	                glVertex3f(0, 0, 0);
	                glEnd();
                glPopMatrix();
	}
	}
        for(int j=0; j<8; j++) {
        for(int i=0; i<70; i++) {
                glPushMatrix();
                        glPointSize(1.6);
                        if(sclX == 1.0) materials(&Moon);
                        else if(sclX > 1.0) materials(&Moon2);
                        glScalef(5.7+(0.1*j), 5.7+(0.1*j), 0.0);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(cos(((i*j)*PI)*DTR), sin(((i*j)*PI)*DTR), 0.0);
                        glBegin(GL_POINTS);
                                glVertex3f(0, 0, 0);
                        glEnd();
                glPopMatrix();
        }
        }
        for(int j=0; j<8; j++) {
        for(int i=0; i<20; i++) {
                glPushMatrix();
                        glPointSize(1.1);
                        if(sclX == 1.0) materials(&Moon);
                        else if(sclX > 1.0) materials(&Moon2);
                        glScalef(6.2+(0.1*j), 6.2+(0.1*j), 0.0);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(cos(((i*j)*PI)*DTR), sin(((i*j)*PI)*DTR), 0.0);
                        glBegin(GL_POINTS);
                                glVertex3f(0, 0, 0);
                        glEnd();
                glPopMatrix();
        }
        }

       // JUPITER
        glPushMatrix();
                if(sclX == 1.0) materials(&Jupiter);
                else if(sclX > 1.0) materials(&Jupiter2);
		glRotatef(jupiter, 0, 0, 1);
                glTranslatef(10.4, 0.0, 0.0);
                glutSolidSphere(2.85968, 200, 200);

                // MOON1
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(mercury, 0, 0, 1);
                        glTranslatef(-2.25, -2.25, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
                // MOON2
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(venus, 0, 0, 1);
                        glTranslatef(2.5, 2.5, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
               // MOON3
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(earth, 0, 0, 1);
                        glTranslatef(-2.75, -2.75, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
                // MOON4
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(mars, 0, 0, 1);
                        glTranslatef(3.0, 3.0, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
               // MOON5
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(jupiter, 0, 0, 1);
                        glTranslatef(-3.25, -3.25, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
        glPopMatrix();

       // SATURN
        glPushMatrix();
                materials(&Saturn);
                glRotatef(saturn, 0, 0, 1);
                glTranslatef(19.08, 0.0, 0.0);
                glutSolidSphere(2.41072, 200, 200);

               // MOON1
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(mercury, 0, 0, 1);
                        glTranslatef(-2.25, -2.25, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
                // MOON2
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(venus, 0, 0, 1);
                        glTranslatef(2.5, 2.5, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
               // MOON3
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(earth, 0, 0, 1);
                        glTranslatef(-2.75, -2.75, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
                // MOON4
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(mars, 0, 0, 1);
                        glTranslatef(3.0, 3.0, 0.0);
                        glutSolidSphere(0.15, 200, 200);
                glPopMatrix();
               // MOON5
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(jupiter, 0, 0, 1);
                        glTranslatef(-3.25, -3.25, 0.0);
                        glutSolidSphere(0.15, 200, 200);
		glPopMatrix();

		// RINGS
        for(int j=0; j<8; j++) {
        for(int i=0; i<230; i++) {
                glPushMatrix();
                        glPointSize(1.1);
                        materials(&Mercury);
                        glScalef(2.5+(0.1*j), 2.5+(0.1*j), 0.0);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(cos(((i*j)*PI)*DTR), sin(((i*j)*PI)*DTR), 0.0);
                        glBegin(GL_POINTS);
                                glVertex3f(0, 0, 0);
                        glEnd();
                glPopMatrix();
        }
        }

        glPopMatrix();

        // URANUS
        glPushMatrix();
                materials(&Uranus);
                glRotatef(uranus, 0, 0, 1);
                glTranslatef(29.18, 0.0, 0.0);
                glutSolidSphere(1.02236, 200, 200);

                // MOON1
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(1.5, 0.0, 0.0);
                        glutSolidSphere(0.1, 200, 200);
                glPopMatrix();
                // MOON2
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(0.0, 1.5, 0.0);
                        glutSolidSphere(0.1, 200, 200);
                glPopMatrix();
        glPopMatrix();

	// NEPTUNE
        glPushMatrix();
                materials(&Neptune);
                glRotatef(neptune, 0, 0, 1);
                glTranslatef(40.06, 0.0, 0.0);
                glutSolidSphere(0.99056, 200, 200);

                // MOON1
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(1.5, 0.0, 0.0);
                        glutSolidSphere(0.1, 200, 200);
                glPopMatrix();
                // MOON2
                glPushMatrix();
                        materials(&Moon);
                        glRotatef(moon, 0, 0, 1);
                        glTranslatef(0.0, 1.5, 0.0);
                        glutSolidSphere(0.1, 200, 200);
                glPopMatrix();
        glPopMatrix();

        // PLUTO
        glPushMatrix();
                materials(&Moon);
                glRotatef(pluto, 0, 0, 1);
                glTranslatef(45.06, 0.0, 0.0);
                glutSolidSphere(0.1, 200, 200);
        glPopMatrix();

	// Kuiper Belt
        for(int j=0; j<50; j++) {
        for(int i=0; i<115; i++) {
                glPushMatrix();
                        glPointSize(1.1);
                        materials(&Moon);
                        glScalef(45+(0.1*j), 45+(0.1*j), 0.0);
                        glRotatef(pluto, 0, 0, 1);
                        glTranslatef(cos(((i*j)*PI)*DTR), sin(((i*j)*PI)*DTR), 0.0);
                        glBegin(GL_POINTS);
                                glVertex3f(0, 0, 0);
                        glEnd();
                glPopMatrix();
        }
        }

}

void stars() {
        srand(time(NULL));
        glPointSize(3.0);
//        glColor3f(1.0, 1.0, 1.0);
	double val = 0;
	val = (float)rand()/(float)(RAND_MAX) * 10.0;
	if(val < 1)
		materials(&Earth);
	else if(val < 2)
		materials(&Mars);
	else if(val < 3)
		materials(&Sun);
	else if(val < 4)
		materials(&Uranus);
	else if(val < 5)
		materials(&Neptune);
        else if(val < 6)
                materials(&Saturn);
        else if(val < 7)
                materials(&Venus);
        else if(val < 8)
                materials(&Uranus);
        else if(val < 9)
                materials(&Neptune);
	else
		materials(&Mercury);
//	materials(&white);
        for(int i=0; i<200; i++) {
		glPointSize((float)rand()/(float)(RAND_MAX) * 2.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<100; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 2.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, (-1)*y2, -10);
                glEnd();
        }
        for(int i=0; i<100; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 2.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                glBegin(GL_POINTS);
                        glVertex3f((-1)*x2, y2, -10);
                glEnd();
        }
        for(int i=0; i<100; i++) {
                glPointSize((float)rand()/(float)(RAND_MAX) * 2.0);
                float x2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                float y2 = (float)rand()/(float)(RAND_MAX) * 50.0;
                glBegin(GL_POINTS);
                        glVertex3f(x2, (-1)*y2, -10);
                glEnd();
        }

}

// Added For Lighting Effects
void init() {
	glClearColor(0.05, 0.075, 0.1, 0.0);	// Black Background

	// Eyes at 1, 1, 1, object at 0, 0, 0, and up is in y direction
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_LIGHTING);			// Enable The Lighting
	glEnable(GL_LIGHT0);			// Light Source Number 0

	currentLight = &blueLight;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLight -> specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLight -> diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLight -> ambient);

	currentMaterial = &Earth;

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
	mercury += 1.5;
	venus += 1.25;
	earth += 1.0;
	mars += 0.55;
	jupiter += 0.35;
	saturn += 0.25;
	uranus += 0.15;
	neptune += 0.1;
	pluto += 0.05;
	moon += 0.5;

        if(mercury > 360) mercury -= 360;
        if(venus > 360) venus -= 360;
        if(earth > 360) earth -= 360;
        if(mars > 360) mars -= 360;
        if(jupiter > 360) jupiter -= 360;
        if(saturn > 360) saturn -= 360;
        if(uranus > 360) uranus -= 360;
        if(neptune > 360) neptune -= 360;
	if(pluto > 360) pluto -= 360;
        if(moon > 360) moon -= 360;
        glutPostRedisplay();
}

// Zooms in:
void zoomIn() {
	sclX = 5.0;
}

// Zooms out:
void zoomOut() {
	sclX = 1.0;
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
	if(key == 'r') glutIdleFunc( myIdle );
	if(key == 's') glutIdleFunc( NULL );
	if(key == 'z') glutIdleFunc( zoomIn );
	if(key == 'x') glutIdleFunc( zoomOut );
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

        glutCreateWindow("My Solar System");
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
