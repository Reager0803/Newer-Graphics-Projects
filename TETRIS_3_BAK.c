// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define ROWS 20
#define COLUMNS 10

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

// Orange Material
materialStruct Orange = {
        {0.65, 0.15, 0.0},
        {0.80, 0.30, 0.0},
        {0.9746, 0.4, 0.0},
        10.8
};

// LightBlue Material
materialStruct LightBlue = {
        {0.0, 0.55, 0.65},
        {0.0, 0.60, 0.80},
        {0.0, 0.7746, 0.9746},
        10.8
};

// Yellow Material
materialStruct Yellow = {
        {0.65, 0.65, 0.0},
        {0.80, 0.80, 0.0},
        {0.9746, 0.9746, 0.0},
        10.8
};

// Red Material
materialStruct Red = {
        {0.65, 0.0, 0.0},
        {0.80, 0.0, 0.0},
        {0.9746, 0.0, 0.0},
        10.8
};

// Purple Material
materialStruct Purple = {
        {0.3, 0.0, 0.3},
        {0.3, 0.0, 0.3},
        {0.5, 0.0, 0.5},
        10.8
};

// DarkBlue Material
materialStruct DarkBlue = {
        {0.0, 0.0, 0.4},
        {0.0, 0.0, 0.5},
        {0.0, 0.0, 0.6},
        10.8
};

// Green Material
materialStruct Green = {
        {0.0, 0.65, 0.25},
        {0.0, 0.80, 0.30},
        {0.0, 0.9746, 0.4746},
        10.8
};

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

// Convert index to coordinate (X)
double inToC_X(int index) {
    index *= 2.1;
    index -= 9;
    return index;
}

// Convert index to coordinate (Y)
double inToC_Y(int index) {
    index -= 5;
    index *= 2.0;
    index -= 9;
    return index;
}

// Board Values 0 = free, other = taken
int board[ROWS][COLUMNS];

/*
figures = [
        [[1, 5, 9, 13], [4, 5, 6, 7]],
        [[4, 5, 9, 10], [2, 6, 5, 9]],
        [[6, 7, 9, 10], [1, 5, 6, 10]],
        [[1, 2, 5, 9], [0, 4, 5, 6], [1, 5, 9, 8], [4, 5, 6, 10]],
        [[1, 2, 6, 10], [5, 6, 7, 9], [2, 6, 10, 11], [3, 5, 6, 7]],
        [[1, 4, 5, 6], [1, 4, 5, 9], [4, 5, 6, 9], [1, 5, 6, 9]],
        [[1, 2, 5, 6]],
]
*/

char getTetro() {
        int randNum = rand() % 7 + 0;
        if(randNum == 0) return 'O';
        if(randNum == 1) return 'I';
        if(randNum == 2) return 'Z';
        if(randNum == 3) return 'S';
        if(randNum == 4) return 'T';
        if(randNum == 5) return 'L';
        if(randNum == 6) return 'J';
        else return ' ';
}

// Tetromino variables
int boardRow = 19, boardCol = 5;

// Tetrominoes (O,Yellow // I,LightBlue // Z,Green, // S,Red // T,Purple // L,Orange // J,DarkBlue)
char tetromino = 'O';
int tet;
int blockHeight = 0;    // This should be only used for testing until I create arrays for the block values and can calculate this automatically, in order to implement collision

// Initializes the board by filling it with the given value (0 or 1 in most cases)
void boardInit(int value) {
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            board[i][j] = value;
        }
    }
}

// Draws block to screen
void Block() {
    boardInit(0);

        // boardRow = 19, boardCol = 5
        switch (tetromino) {
        case 'O':
                materials(&Yellow);
                blockHeight = 2;
                board[boardRow][boardCol-1] = 1;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-1][boardCol] = 1;
                break;
        case 'I':
                materials(&LightBlue);
                blockHeight = 4;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-2][boardCol] = 1;
                board[boardRow-3][boardCol] = 1;
                break;
        case 'T':
                materials(&Purple);
                blockHeight = 2;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-1][boardCol+1] = 1;
                break;
        case 'S':
                materials(&Red);
                blockHeight = 2;
                board[boardRow][boardCol+1] = 1;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-1][boardCol-1] = 1;
                break;
        case 'Z':
                materials(&Green);
                blockHeight = 2;
                board[boardRow][boardCol-1] = 1;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-1][boardCol+1] = 1;
                break;
        case 'L':
                materials(&Orange);
                blockHeight = 3;
                board[boardRow][boardCol-1] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-2][boardCol-1] = 1;
                board[boardRow-2][boardCol] = 1;
                break;
        case 'J':
                materials(&DarkBlue);
                blockHeight = 3;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-2][boardCol] = 1;
                board[boardRow-2][boardCol-1] = 1;
                break;
        }

    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                        glTranslatef(inToC_X(j), inToC_Y(i), 0);
                        glutSolidCube(2.0);
                glPopMatrix();
            }
        }
    }
}

// Draws the initial game
void drawGame() {
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
                glTranslatef(-11.5, -19.5, 0.0);
                for(int j=0; j<20; j++) {
                        for(int i=0; i<10; i++) {
                                glTranslatef(2.10, 0.0, 0.0);
                                glutWireCube(2.0);
                        }
                        glTranslatef(-21, 2.05, 0.0);
                }
        glPopMatrix();

        Block();
}

// Autostarts without user input
void myIdle() {
        // Guesses random number, when correct, it ticks the game (I know it sucks)
        float num = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num2 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num3 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num4 = (float)rand()/(float)(RAND_MAX) * 2.0;
        if(((num > 0.0 && num < 0.1) || (num2 > 0.0 && num2 < 0.1) || (num3 > 0.0 && num3 < 0.1) || (num3 > 0.0 && num3 < 0.1))) {
                boardRow--;
        }
        for(int i=0; i<COLUMNS; i++) {
                if(board[boardRow-(blockHeight+1)][i] < 0) {
                        boardRow = 19;
                        tetromino = getTetro();
                }
        }
        glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
        if(key == 'q' || key == 27) exit(0);
        if(key == 'p') glutIdleFunc( NULL );
}

// ######## BOILER PLATE CODE ########

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		drawGame();
        glFlush();
	glutSwapBuffers();
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

void init() {
	glClearColor(0.3, 0.3, 0.3, 0.0);	// Grey Background
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

int main(int argc, char** argv) {
        glutInit(&argc, argv);
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
