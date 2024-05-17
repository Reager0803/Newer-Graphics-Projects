// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define PI 3.14159
#define DTR PI/180

// x and y values of the single block:
double x1 = 0, y2 = 0;

// x and y values of the other blocks
double x3[7], y3[7];

// Array containing block values for each column
int yHeights[10];
int yHindex = 0;

// Array containing the real graphical y values of each colomn
double yHeightsReal[10];

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

// White Material
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

// Dark Grey Material
materialStruct Dark_Grey = {
        {0.0, 0.0, 0.0},
        {0.1, 0.1, 0.1},
        {0.3, 0.3, 0.3},
        100.0
};

materialStruct *currentMaterial;
void materials(materialStruct *materials) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials -> ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials -> diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials -> specular);
}

// Resets game
void resetGame() {
        for(int i=0; i<20; i++) {
                yHeights[i] = 0;
        }
}

void Single_Block() {
        // Draws the falling block
        materials(&White);
        glPushMatrix();
                glTranslatef(1, 19.825, 0);
                glTranslatef((GLfloat)x1, (GLfloat)y2, 0);
                glutSolidCube(2.0);
        glPopMatrix();

        // Check for rows to clear
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

        // If the height in any of the indexes exceeds 20,
        // then the game is lost and the game resets
        for(int i=0; i<10; i++) {
                if(yHeights[i] > 21) {
                        resetGame();
                }
        }

        // Draws Permanent Blocks
        int xVal = 0, yVal = 0;
        for(int i=0; i<10; i++) {
                for(int j=0; j<yHeights[i]; j++) {
                        glPushMatrix();
                                xVal -= 5;
                                xVal = i * 2.1;
                                xVal -= 9;
                                yVal = j * 2.1; 
                                yVal -= 20;
                                glTranslatef(xVal, yVal, 0);
                                glutSolidCube(2.0);
                        glPopMatrix();
                }
        }
}

// x4 y4
void I_Block() {
       // Draws the falling block
        materials(&White);
        glPushMatrix();
                glTranslatef(1, 19.825, 0);
                //glTranslatef((GLfloat)x4[0], (GLfloat)y4[0], 0);
                glutSolidCube(2.0);
        glPopMatrix();

        // Check for rows to clear
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

        // If the height in any of the indexes exceeds 20,
        // then the game is lost and the game resets
        for(int i=0; i<10; i++) {
                if(yHeights[i] > 21) {
                        resetGame();
                }
        }

        // Draws Permanent Blocks
        int xVal = 0, yVal = 0;
        for(int i=0; i<10; i++) {
                for(int j=0; j<yHeights[i]; j++) {
                        glPushMatrix();
                                xVal -= 5;
                                xVal = i * 2.1;
                                xVal -= 9;
                                yVal = j * 2.1; 
                                yVal -= 20;
                                glTranslatef(xVal, yVal, 0);
                                glutSolidCube(2.0);
                        glPopMatrix();
                }
        }
}
void J_Block() {

}
void L_Block() {

}
void O_Block() {

}
void S_Block() {

}
void T_Block() {

}
void Z_Block() {
        
}

// Draws the initial game
void drawGame() {
        // Initializes the 7 blocks
        for(int i=0; i<7; i++) {
                x3[i] = 0;
                y3[i] = 0;
        }

        // Box for the game
        glLineWidth(3.0);
        materials(&White);
        glBegin(GL_LINE_LOOP);
                glVertex2f(10.75, 21.2);
                glVertex2f(10.75, -21.2);
                glVertex2f(-10.75, -21.2);
                glVertex2f(-10.75, 21.2);
        glEnd();
        materials(&Dark_Grey);
        glBegin(GL_POLYGON);
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

        Single_Block();
//        I_Block();
//        J_Block();
//        L_Block();
//        O_Block();
//        S_Block();
//        T_Block();
//        Z_Block();
}

// Added For Lighting Effects
void init() {
	glClearColor(0.3, 0.3, 0.3, 0.0);	// Grey Background

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
                //Draws the initial game
		drawGame();
        glFlush();
	glutSwapBuffers();
}

// Autostarts without user input
void myIdle() {
        // Guesses random number, when correct, it ticks the game (I know it sucks)
        float num = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num2 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num3 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num4 = (float)rand()/(float)(RAND_MAX) * 2.0;
        if(((num > 0.0 && num < 0.1) || (num2 > 0.0 && num2 < 0.1) || (num3 > 0.0 && num3 < 0.1) || (num3 > 0.0 && num3 < 0.1)) && y2 > -39.0) {
                y2 -= 1.05;
        }
        int temp = x1 + 12.6;
        temp /= 2.1;
        if(x1 == 8.4) {
                temp = 9;
        }
        if(y2 <= (-39 + (yHeights[temp] * 2.1))) {
                yHindex = x1 + 12.6;
                yHindex /= 2.1;
                if(x1 == 8.4) {
                        yHindex = 9;
                }
                yHeights[yHindex] += 1;
                yHeightsReal[yHindex] += 2.1;                
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
        int temp = x1 + 12.6;
        temp /= 2.1;
        if(x1 == 8.4) {
                temp = 9;
        }

        if(y2 > -39) {
                switch (key) {
                case 'd':
                        //printf("y2 %lf\n", y2);
                        //printf("temp %d\n", temp);
                        //printf("yHeights %lf\n", yHeightsReal[temp]-39);
                        if(x1 < 8 && y2 >= (yHeightsReal[temp+1]-39))
                                x1 += 2.1;
                        glutPostRedisplay();
                        break;
                case 'a':
                        if(x1 > -10 && y2 >= (yHeightsReal[temp-1]-39))
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
	glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
	init();
        glutMainLoop();
}
