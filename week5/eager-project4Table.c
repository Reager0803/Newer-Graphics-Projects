#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define DTR PI/180

void stars();
void drawPlate(float xOff, float yOff, float zOff);

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive z

GLfloat x=0.0, z=0.0, x0=0.0, z0=0.0, radius = 1.5;

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

	// Floor
	glPushMatrix();
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(1.6, 0.05, 1.6);
		glColor3f(0.2, 0.2, 0.2);
		glutSolidCube(16.0);
	glPopMatrix();

	// Table Legs
	for(int i=0; i<3; i++) {
	glPushMatrix();
		glTranslatef(-4.0+(i*5), -2.75, -3.5);
		glScalef(1.0, 5.0, 1.0);
		glColor3f(0.3, 0.3, 0.0);
		glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
	glPopMatrix();
	}

        for(int i=0; i<3; i++) {
        glPushMatrix();
                glTranslatef(-4.0+(i*5), -2.75, 3.5);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.3, 0.0);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();
        }

	// Table Top
        glPushMatrix();
                glTranslatef(1.0, 0.0, 0.0);
                glScalef(1.5, 0.05, 1.0);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(12.0);
        glPopMatrix();

	// Plates
	glPushMatrix();
		// Middle Plate
		glTranslatef(0.0, -0.69, 0.0);
		radius = 3.0;
		glColor3f(0.7, 0.7, 0.7);
		drawPlate(1.5, 0.0, 0.0);
		radius = 2.5;
		glColor3f(1.0, 1.0, 1.0);
		drawPlate(1.5, 0.05, 0.0);

		// Start Plate
		radius = 1.75;
		glColor3f(0.7, 0.7, 0.7);
		drawPlate(-5.0, 0.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		radius = 1.5;
		drawPlate(-5.0, 0.05, 0.0);

                // Middle Plate 1
                radius = 1.5;
                glColor3f(0.7, 0.7, 0.7);
                drawPlate(-2.5, 0.0, 3.0);
                radius = 1.25;
                glColor3f(1.0, 1.0, 1.0);
                drawPlate(-2.5, 0.05, 3.0);

                // Middle Plate 2
                radius = 1.5;
                glColor3f(0.7, 0.7, 0.7);
                drawPlate(-2.5, 0.0, -3.0);
                radius = 1.25;
                glColor3f(1.0, 1.0, 1.0);
                drawPlate(-2.5, 0.05, -3.0);

		// End Plate 1
		radius = 1.5;
                glColor3f(0.7, 0.7, 0.7);
		drawPlate(5.75, 0.0, 3.0);
		radius = 1.25;
		glColor3f(1.0, 1.0, 1.0);
		drawPlate(5.75, 0.05, 3.0);

		// End Plate 2
		radius = 1.5;
                glColor3f(0.7, 0.7, 0.7);
                drawPlate(5.75, 0.0, -3.0);
                radius = 1.25;
                glColor3f(1.0, 1.0, 1.0);
                drawPlate(5.75, 0.05, -3.0);
	glPopMatrix();

	// Chair1 Legs
        for(int i=0; i<3; i++) {
        glPushMatrix();
                glTranslatef(-11.0, -2.75, (-3.5 + (i * 3.5)));
                glScalef(0.5, 4.0, 0.5);
                glColor3f(0.3, 0.3, 0.0);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();
        }
        for(int i=0; i<3; i++) {
        glPushMatrix();
                glTranslatef(12.0, -2.75, (-3.5 + (i * 3.5)));
                glScalef(0.5, 4.0, 0.5);
                glColor3f(0.3, 0.3, 0.0);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();
        }

        // Chair1 Seat
        glPushMatrix();
                glTranslatef(-11.0, -1.0, 0.0);
                glScalef(0.25, 0.05, 1.0);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();
        glPushMatrix();
                glTranslatef(12.0, -1.0, 0.0);
                glScalef(0.25, 0.05, 1.0);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();

	// Chair1 Back
        glPushMatrix();
                glTranslatef(-12.5, 0.8, 0.0);
                glScalef(0.05, 0.25, 1.0);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();
        glPushMatrix();
                glTranslatef(13.5, 0.8, 0.0);
                glScalef(0.05, 0.25, 1.0);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();

	// Chairs2 Legs
	for(int j=0; j<2; j++) {
        for(int i=0; i<3; i++) {
        glPushMatrix();
                glTranslatef((-5.0 + (i * 2) + (j * 8)), -2.75, -8.5);
                glScalef(0.5, 4.0, 0.5);
                glColor3f(0.3, 0.3, 0.0);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();
        }
	}
        for(int j=0; j<2; j++) {
        for(int i=0; i<3; i++) {
        glPushMatrix();
                glTranslatef((-5.0 + (i * 2) + (j * 8)), -2.75, 8.5);
                glScalef(0.5, 4.0, 0.5);
                glColor3f(0.3, 0.3, 0.0);
                glutSolidCube(1.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(1.0);
        glPopMatrix();
        }
        }

	// Chairs2 Seat
	for(int i=0; i<2; i++) {
        glPushMatrix();
                glTranslatef(-3.0 + (i * 8), -1.0, -8.5);
                glScalef(0.5, 0.05, 0.25);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();
	}
        for(int i=0; i<2; i++) {
        glPushMatrix();
                glTranslatef(-3.0 + (i * 8), -1.0, 8.5);
                glScalef(0.5, 0.05, 0.25);
                glColor3f(0.6, 0.6, 0.0);
                glutSolidCube(12.0);
                glColor3f(0.0, 0.0, 0.0);
                glutWireCube(12.0);
        glPopMatrix();
        }

	// Teapot
        glPushMatrix();
		glTranslatef(1.25, 1.5, 0.5);
		glColor3f(0.0, 1.0, 0.0);
                glutWireTeapot(1.5);
	glPopMatrix();

	// Donuts
	glPushMatrix();
		glTranslatef(-4.65, 0.5, 0.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glColor3f(0.8, 0.8, 0.0);
		glutSolidTorus(0.15, 0.5, 100.0, 100.0);
		glTranslatef(0.0, -1.0, 0.0);
                glutSolidTorus(0.15, 0.5, 100.0, 100.0);
                glTranslatef(-1.0, 0.5, 0.0);
                glutSolidTorus(0.15, 0.5, 100.0, 100.0);
        glPopMatrix();

	// Apples
	glPushMatrix();
		glTranslatef(-4.0, 0.8, 3.0);
		glColor3f(1.0, 0.0, 0.0);
		for(int i=0; i<3; i++) {
			glTranslatef(0.75, 0.0, 0.0);
			glutSolidSphere(0.40, 100, 100);
		}
		glTranslatef(-2.25, 0.25, 0.0);
		glScalef(1.0, 5.0, 1.0);
		glColor3f(0.3, 0.3, 0.0);
                for(int i=0; i<3; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
	glPopMatrix();
        glPushMatrix();
                glTranslatef(-3.625, 0.8, 2.25);
                glColor3f(1.0, 0.0, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidSphere(0.40, 100, 100);
                }
                glTranslatef(-1.5, 0.25, 0.0);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.3, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
        glPopMatrix();
        glPushMatrix();
                glTranslatef(-3.625, 0.8, 3.75);
                glColor3f(1.0, 0.0, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidSphere(0.40, 100, 100);
                }
                glTranslatef(-1.5, 0.25, 0.0);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.3, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
        glPopMatrix();

        // Oranges
        glPushMatrix();
                glTranslatef(-4.0, 0.8, -3.0);
                glColor3f(1.0, 0.5, 0.0);
                for(int i=0; i<3; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidSphere(0.40, 100, 100);
                }
                glTranslatef(-2.25, 0.25, 0.0);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.5, 0.0);
                for(int i=0; i<3; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
        glPopMatrix();
        glPushMatrix();
                glTranslatef(-3.625, 0.8, -2.25);
                glColor3f(1.0, 0.5, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidSphere(0.40, 100, 100);
                }
                glTranslatef(-1.5, 0.25, 0.0);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.5, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
        glPopMatrix();
        glPushMatrix();
                glTranslatef(-3.625, 0.8, -3.75);
                glColor3f(1.0, 0.5, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidSphere(0.40, 100, 100);
                }
                glTranslatef(-1.5, 0.25, 0.0);
                glScalef(1.0, 5.0, 1.0);
                glColor3f(0.3, 0.5, 0.0);
                for(int i=0; i<2; i++) {
                        glTranslatef(0.75, 0.0, 0.0);
                        glutSolidCube(0.1);
                }
        glPopMatrix();

	// Cups
	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(5.75, 3.0, -0.8);
		glColor3f(0.9, 0.9, 0.9);
	        glutSolidCone(1.0, 1.0, 100, 100);
                glRotatef(270.0, 1.0, 0.0, 0.0);
		glTranslatef(1.0, 0.0, 0.0);
		glutSolidTorus(0.1, 0.2, 100.0, 100.0);
	glPopMatrix();
        glPushMatrix();
                glRotatef(90.0, 1.0, 0.0, 0.0);
                glTranslatef(5.75, -3.0, -0.8);
                glColor3f(0.9, 0.9, 0.9);
                glutSolidCone(1.0, 1.0, 100, 100);
                glRotatef(270.0, 1.0, 0.0, 0.0);
                glTranslatef(1.0, 0.0, 0.0);
                glutSolidTorus(0.1, 0.2, 100.0, 100.0);
        glPopMatrix();
	// Full Cup
        glPushMatrix();
                glRotatef(90.0, 1.0, 0.0, 0.0);
                glTranslatef(-5.75, -3.0, -0.8);
                glColor3f(0.9, 0.9, 0.9);
                glutSolidCone(1.0, 1.0, 100, 100);
		// Tea
		glColor3f(0.3, 0.3, 0.0);
		glTranslatef(0.0, 0.0, 0.25);
		glutSolidTorus(0.375, 0.175, 100.0, 100.0);
		glTranslatef(0.0, 0.0, -0.25);
                glRotatef(270.0, 1.0, 0.0, 0.0);
		glColor3f(0.9, 0.9, 0.9);
                glTranslatef(-1.0, 0.0, 0.0);
                glutSolidTorus(0.1, 0.2, 100.0, 100.0);
        glPopMatrix();

	// Body
        glPushMatrix();
                glTranslatef(-10.5, 2.0, 0.0);
                glScalef(1.0, 2.0, 1.0);
                glColor3f(1.0, 0.0, 0.0);
                glutSolidSphere(1.5, 100, 100);
        glPopMatrix();

	// Head
        glPushMatrix();
                glTranslatef(-10.5, 6.0, 0.0);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(1.0, 100, 100);
        glPopMatrix();

	// Eyes
	for(int i=0; i<2; i++) {
        glPushMatrix();
                glTranslatef(-9.55, 6.35, 0.5 + (i * -1));
		glScalef(0.2, 0.2, 0.2);
                glColor3f(0.0, 0.0, 0.0);
                glutSolidSphere(1.0, 100, 100);
        glPopMatrix();
	}

	// Arms
	for(int i=0; i<2; i++) {
        glPushMatrix();
                glTranslatef(-10.5, 4.25, 1.75 + (i * -3.5));
                glScalef(1.0, 2.0, 1.0);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(0.75, 100, 100);
        glPopMatrix();
	}

	// Legs
        for(int i=0; i<2; i++) {
        glPushMatrix();
                glTranslatef(-9.5, 0.0, 0.5 + (i * -1.0));
                glScalef(2.0, 1.0, 1.0);
                glColor3f(1.0, 1.0, 0.0);
                glutSolidSphere(0.75, 100, 100);
        glPopMatrix();
	}

	// Tardis
	glPushMatrix();
		// Box
		glTranslatef(0.0, 1.0, -4.0);
		glScalef(1.0, 2.0, 1.0);
		glColor3f(0.0, 0.0, 0.4);
		glutSolidCube(1.0);

		// Windows
		glTranslatef(0.0, 0.3, 0.0);
		glScalef(0.85, 0.15, 1.15);
		glColor3f(0.0, 0.7, 1.0);
		glutSolidCube(1.0);
		glScalef(1.2, 1.0, 0.85);
		glutSolidCube(1.0);

		// Police Sign
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0, 0.75, 0.0);
		glScalef(1.0, 0.5, 1.0);
		glutSolidCube(1.0);

		// Light
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(0.0, 0.8, 0.0);
		glScalef(0.15, 2.5, 0.15);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
                // Sides
                glTranslatef(0.0, 0.65, -4.0);
                glScalef(1.05, 1.6, 0.75);
                glColor3f(0.0, 0.0, 0.3);
                glutSolidCube(1.0);
	glPopMatrix();
        glPushMatrix();
                // Sides
                glTranslatef(0.0, 0.65, -4.0);
                glScalef(0.75, 1.6, 1.05);
                glColor3f(0.0, 0.0, 0.3);
                glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
                // Borders
                glTranslatef(0.0, 1.0, -4.0);
                glScalef(1.1, 1.6, 0.1);
                glColor3f(0.0, 0.0, 0.2);
                glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
                // Borders
                glTranslatef(0.0, 1.0, -4.0);
                glScalef(0.1, 1.6, 1.2);
                glColor3f(0.0, 0.0, 0.2);
                glutSolidCube(1.0);
        glPopMatrix();
	glPushMatrix();
                // Base
                glTranslatef(0.0, 0.25, -4.0);
                glScalef(1.1, 0.2, 1.1);
                glColor3f(0.0, 0.0, 0.3);
                glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
                // Borders2
		glTranslatef(0.0, 1.0, -4.0);
                glColor3f(0.0, 0.0, 0.2);
                glScalef(1.075, 0.2, 1.075);
                glutSolidCube(1.0);
	glPopMatrix();
        glPushMatrix();
                // Police Sign2
                glTranslatef(0.0, 1.85, -4.0);
                glColor3f(0.0, 0.0, 0.0);
                glScalef(0.9, 0.1, 1.05);
                glutSolidCube(1.0);
        glPopMatrix();

	// Mario Mushroom
	glPushMatrix();
		// Bottom Shroom
		glTranslatef(8.0, 1.0, 0.0);
		glColor3f(0.9, 0.9, 0.2);
		glScalef(1.5, 1.0, 1.25);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
        glPushMatrix();
		// Top Shroom
                glTranslatef(8.0, 1.75, -0.15);
                glColor3f(1.0, 0.0, 0.0);
                glScalef(1.5, 1.0, 1.25);
                glutSolidSphere(0.85, 100, 100);
        glPopMatrix();
	glPushMatrix();
		// Eyes
                glTranslatef(8.25, 1.0, 0.65);
                glColor3f(0.0, 0.0, 0.0);
                glScalef(1.0, 2.5, 1.0);
                glutSolidSphere(0.075, 100, 100);
		glTranslatef(-0.5, 0.0, 0.0);
                glutSolidSphere(0.075, 100, 100);
	glPopMatrix();
	glPushMatrix();
		// Spots
		glTranslatef(8.0, 1.75, 0.65);
		glScalef(1.0, 0.75, 0.5);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidSphere(0.7, 100, 100);
		glTranslatef(0.0, 0.0, -3.15);
		glutSolidSphere(0.7, 100, 100);
		glScalef(0.35, 1.0, 1.75);
		glTranslatef(-2.99, 0.0, 1.0);
		glutSolidSphere(0.7, 100, 100);
		glTranslatef(5.99, 0.0, 0.0);
		glutSolidSphere(0.7, 100, 100);
		glScalef(3.0, 0.35, 1.0);
		glTranslatef(-1.0, 2.75, -0.1);
		glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	// Rubik's Cube
	glPushMatrix();
		glLineWidth(2.0);
		glTranslatef(2.5, 0.5, -4.0);
		for(int k=0; k<3; k++) {
		glTranslatef(0.0, 0.25, -0.75);
		for(int j=0; j<3; j++) {
		glTranslatef(-0.75, 0.0, 0.25);
		for(int i=0; i<3; i++) {
		glTranslatef(0.25, 0.0, 0.0);
		glColor3f((double)i/3.0, (double)j/3.0, (double)k/3.0);
		glutSolidCube(0.25);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(0.25);
		}
		}
		}
		glLineWidth(1.0);
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

void drawPlate(float xOff, float yOff, float zOff) {
        glBegin(GL_POLYGON);
                for(int i=0; i<360; i++) {
                        x = x0 + radius * cos(DTR*i);        // x coordinate of 1 point o>
                        z = z0 + radius * sin(DTR*i);        // y coordinate of 1 point o>
                        glVertex3f(x+xOff, 1.0+yOff, z+zOff);                       // x and y verteces
                        x = x0 + radius * cos(DTR*(i+1));    // x coordinate of 1 point o>
                        z = z0 + radius * sin(DTR*(i+1));    // y coordinate of 1 point o>
                        glVertex3f(x+xOff, 1.0+yOff, z+zOff);                       // x and y verteces
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
	if(theta[axis] > 360.0) {
		theta[axis] -= 360;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glClearColor(0.0, 0.0, 0.5, 0.0);	// Blue Background
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

        glutCreateWindow("My Table");
        glutDisplayFunc(display);

	glutReshapeFunc( reshape );
//	glutIdleFunc( idle );
	glutKeyboardFunc( myKeyboard );
	glutMouseFunc( myMouse );
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        glutMainLoop();
}
