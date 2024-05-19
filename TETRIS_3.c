// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define ROWS 20
#define COLUMNS 10

GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 1; 	// When we start the program, object will rotate with respect to positive y
double zoom;

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
int permBoard[ROWS][COLUMNS] = {0};

// Stores the color values of the board based on the type of tetromino
int colors[ROWS][COLUMNS];
int permColors[ROWS][COLUMNS] = {0};

// Rotational value for the tetrominoes 0 = 0deg. 1 = 90deg. 2 = 180deg. 3 = 270
int rotation = 0;

// Switch used to determine wether or not the tetromino can be rotated
int rotationSwitch = 0;

// Tetromino variables
int boardRow = 19, boardCol = 5;

// Tetrominoes (O,Yellow // I,LightBlue // Z,Green, // S,Red // T,Purple // L,Orange // J,DarkBlue)
char tetromino = 'O';
int tet;

char getTetro() {
        rotation = 0;
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

// Initializes the board by filling it with the given value, 0 for dynamic, 1 for fixed, 2 for colors, other for fixed colors
void boardInit(int value, int choice) {
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(choice == 0)
                    board[i][j] = value;
            else if(choice == 1)
                    permBoard[i][j] = value;
            else if(choice == 2)
                    colors[i][j] = value;
            else
                    permColors[i][j] = value;
        }
    }
}

// Prints Board 0 for dynamic, 1 for permanant, 2 for colors, other for permanent colors
void boardPrint(int choice) {
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(choice == 0)
                    printf("%d, ", board[i][j]);
            else if(choice == 1)
                    printf("%d, ", permBoard[i][j]);
            else if(choice == 2)
                    printf("%d, ", colors[i][j]);
            else
                    printf("%d, ", permColors[i][j]);
        }
        printf("\n");
    }
}

// Draws blocks to screen
void Block() {
    boardInit(0, 0);
    boardInit(0, 2);
    materials(&White);

        // Starting point (already initialized): boardRow = 19, boardCol = 5
        // Sets the dynamic board with each possible tetromino
        switch (tetromino) {
        case 'O':
                board[boardRow][boardCol-1] = 1;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-1][boardCol] = 1;
                colors[boardRow][boardCol-1] = 0;
                colors[boardRow][boardCol] = 0;
                colors[boardRow-1][boardCol-1] = 0;
                colors[boardRow-1][boardCol] = 0;
                break;
        case 'I':
                if(rotation == 0 || rotation == 2) {
                        board[boardRow][boardCol] = 1;
                        board[boardRow-1][boardCol] = 1;
                        board[boardRow-2][boardCol] = 1;
                        board[boardRow-3][boardCol] = 1;
                        colors[boardRow][boardCol] = 1;
                        colors[boardRow-1][boardCol] = 1;
                        colors[boardRow-2][boardCol] = 1;
                        colors[boardRow-3][boardCol] = 1;
                } else if (rotation == 1 || rotation == 3) {
                        board[boardRow-1][boardCol] = 1;
                        board[boardRow-1][boardCol-1] = 1;
                        board[boardRow-1][boardCol-2] = 1;
                        board[boardRow-1][boardCol-3] = 1;
                        colors[boardRow-1][boardCol] = 1;
                        colors[boardRow-1][boardCol-1] = 1;
                        colors[boardRow-1][boardCol-2] = 1;
                        colors[boardRow-1][boardCol-3] = 1;
                }
                break;
        case 'T':
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-1][boardCol+1] = 1;
                colors[boardRow][boardCol] = 2;
                colors[boardRow-1][boardCol-1] = 2;
                colors[boardRow-1][boardCol] = 2;
                colors[boardRow-1][boardCol+1] = 2;
                break;
        case 'S':
                if(rotation == 0 || rotation == 2) {
                        board[boardRow][boardCol+1] = 1;
                        board[boardRow][boardCol] = 1;
                        board[boardRow-1][boardCol] = 1;
                        board[boardRow-1][boardCol-1] = 1;
                        colors[boardRow][boardCol+1] = 3;
                        colors[boardRow][boardCol] = 3;
                        colors[boardRow-1][boardCol] = 3;
                        colors[boardRow-1][boardCol-1] = 3;
                } else if (rotation == 1 || rotation == 3) {
                        board[boardRow+1][boardCol-1] = 1;
                        board[boardRow][boardCol-1] = 1;
                        board[boardRow][boardCol] = 1;
                        board[boardRow-1][boardCol] = 1;
                        colors[boardRow+1][boardCol-1] = 3;
                        colors[boardRow][boardCol-1] = 3;
                        colors[boardRow][boardCol] = 3;
                        colors[boardRow-1][boardCol] = 3;
                }
                break;
        case 'Z':
                board[boardRow][boardCol-1] = 1;
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-1][boardCol+1] = 1;
                colors[boardRow][boardCol-1] = 4;
                colors[boardRow][boardCol] = 4;
                colors[boardRow-1][boardCol] = 4;
                colors[boardRow-1][boardCol+1] = 4;
                break;
        case 'L':
                board[boardRow][boardCol-1] = 1;
                board[boardRow-1][boardCol-1] = 1;
                board[boardRow-2][boardCol-1] = 1;
                board[boardRow-2][boardCol] = 1;
                colors[boardRow][boardCol-1] = 5;
                colors[boardRow-1][boardCol-1] = 5;
                colors[boardRow-2][boardCol-1] = 5;
                colors[boardRow-2][boardCol] = 5;
                break;
        case 'J':
                board[boardRow][boardCol] = 1;
                board[boardRow-1][boardCol] = 1;
                board[boardRow-2][boardCol] = 1;
                board[boardRow-2][boardCol-1] = 1;
                colors[boardRow][boardCol] = 6;
                colors[boardRow-1][boardCol] = 6;
                colors[boardRow-2][boardCol] = 6;
                colors[boardRow-2][boardCol-1] = 6;
                break;
        }

    // Draws out the dynamic board
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                        switch (colors[i][j]) {
                        case 0:
                                materials(&Yellow);
                                break;
                        case 1:
                                materials(&LightBlue);
                                break;
                        case 2:
                                materials(&Purple);
                                break;
                        case 3:
                                materials(&Red);
                                break;
                        case 4:
                                materials(&Green);
                                break;
                        case 5:
                                materials(&DarkBlue);
                                break;
                        case 6:
                                materials(&Orange);
                                break;
                        }
                        glTranslatef(inToC_X(j), inToC_Y(i), 0);
                        glutSolidCube(2.0);
                glPopMatrix();
            }
        }
    }

   // Draws out the fixed/permanent board
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(permBoard[i][j] > 0) {
                glPushMatrix();
                        switch (permColors[i][j]) {
                        case 0:
                                materials(&Yellow);
                                break;
                        case 1:
                                materials(&LightBlue);
                                break;
                        case 2:
                                materials(&Purple);
                                break;
                        case 3:
                                materials(&Red);
                                break;
                        case 4:
                                materials(&Green);
                                break;
                        case 5:
                                materials(&DarkBlue);
                                break;
                        case 6:
                                materials(&Orange);
                                break;
                        }
                        glTranslatef(inToC_X(j), inToC_Y(i), 0);
                        glutSolidCube(2.0);
                glPopMatrix();
            }
        }
    }

    // Both for lines of the blocks hence the wirecube
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                        materials(&Black);
                        glTranslatef(inToC_X(j), inToC_Y(i), 0);
                        glutWireCube(2.1);
                glPopMatrix();
            }
        }
    }
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
            if(permBoard[i][j] > 0) {
                glPushMatrix();
                        materials(&Black);
                        glTranslatef(inToC_X(j), inToC_Y(i), 0);
                        glutWireCube(2.1);
                glPopMatrix();
            }
        }
    }

    // Checks if a row has been cleared
    int sumOfCols = 0; 
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLUMNS; j++) {
                if(permBoard[i][j] == 1)
                        sumOfCols++;
        }
        if(sumOfCols == 10) {
                for(int k=0; k<COLUMNS; k++) {
                        permBoard[i][k] = 0;
                }
        }
        sumOfCols = 0;
    }
}

// Draws the initial game
void drawGame() {
        glScalef(1.0+zoom, 1.0+zoom, 1.0+zoom);

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
                glScalef(1.0, 1.0, 0.1);
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
        if(((num > 0.0 && num < 0.1) || (num2 > 0.0 && num2 < 0.1) || (num3 > 0.0 && num3 < 0.1) || (num3 > 0.0 && num3 < 0.1) || (num4 > 0.0 && num4 < 0.1))) {
                rotationSwitch = 1;
                boardRow--;
        }
        /*        for(int i=0; i<COLUMNS; i++) {
                if(boardRow <= 0 || (permBoard[boardRow-1][i] == 1)) {
                        
                        permBoard[boardRow][boardCol] = 1;
                        boardRow = 19;
                        boardCol = 5;
                        tetromino = getTetro();
                }
        }*/
        for(int i=0; i<COLUMNS; i++) {
                switch (tetromino) {
                case 'O':
                        if(boardRow-1 <= 0 || (permBoard[boardRow-2][boardCol] == 1)) {
                                rotationSwitch = 0;

                                permBoard[boardRow][boardCol-1] = 1;
                                permBoard[boardRow][boardCol] = 1;
                                permBoard[boardRow-1][boardCol-1] = 1;
                                permBoard[boardRow-1][boardCol] = 1;
                                permColors[boardRow][boardCol-1] = 0;
                                permColors[boardRow][boardCol] = 0;
                                permColors[boardRow-1][boardCol-1] = 0;
                                permColors[boardRow-1][boardCol] = 0;
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'I':
                        int offset = 0;
                        if(rotation == 0 || rotation == 2)
                                offset = 0;
                        else if(rotation == 1 || rotation == 3)
                                offset = 2;
                        if(boardRow-3+offset <= 0 || (permBoard[boardRow-4+offset][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                if(rotation == 0 || rotation == 2) {
                                        permBoard[boardRow][boardCol] = 1;
                                        permBoard[boardRow-1][boardCol] = 1;
                                        permBoard[boardRow-2][boardCol] = 1;
                                        permBoard[boardRow-3][boardCol] = 1;
                                        permColors[boardRow][boardCol] = 1;
                                        permColors[boardRow-1][boardCol] = 1;
                                        permColors[boardRow-2][boardCol] = 1;
                                        permColors[boardRow-3][boardCol] = 1;
                                } else if (rotation == 1 || rotation == 3) {
                                        permBoard[boardRow-1][boardCol] = 1;
                                        permBoard[boardRow-1][boardCol-1] = 1;
                                        permBoard[boardRow-1][boardCol-2] = 1;
                                        permBoard[boardRow-1][boardCol-3] = 1;
                                        permColors[boardRow-1][boardCol] = 1;
                                        permColors[boardRow-1][boardCol-1] = 1;
                                        permColors[boardRow-1][boardCol-2] = 1;
                                        permColors[boardRow-1][boardCol-3] = 1;
                                }
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'T':
                        if(boardRow-1 <= 0 || (permBoard[boardRow-2][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                permBoard[boardRow][boardCol] = 1;
                                permBoard[boardRow-1][boardCol-1] = 1;
                                permBoard[boardRow-1][boardCol] = 1;
                                permBoard[boardRow-1][boardCol+1] = 1;
                                permColors[boardRow][boardCol] = 2;
                                permColors[boardRow-1][boardCol-1] = 2;
                                permColors[boardRow-1][boardCol] = 2;
                                permColors[boardRow-1][boardCol+1] = 2;
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'S':
                        if(boardRow-1 <= 0 || (permBoard[boardRow-2][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                if(rotation == 0 || rotation == 2) {
                                        permBoard[boardRow][boardCol+1] = 1;
                                        permBoard[boardRow][boardCol] = 1;
                                        permBoard[boardRow-1][boardCol] = 1;
                                        permBoard[boardRow-1][boardCol-1] = 1;
                                        permColors[boardRow][boardCol+1] = 3;
                                        permColors[boardRow][boardCol] = 3;
                                        permColors[boardRow-1][boardCol] = 3;
                                        permColors[boardRow-1][boardCol-1] = 3;
                                } else if (rotation == 1 || rotation == 3) {
                                        permBoard[boardRow+1][boardCol-1] = 1;
                                        permBoard[boardRow][boardCol-1] = 1;
                                        permBoard[boardRow][boardCol] = 1;
                                        permBoard[boardRow-1][boardCol] = 1;
                                        permColors[boardRow+1][boardCol-1] = 3;
                                        permColors[boardRow][boardCol-1] = 3;
                                        permColors[boardRow][boardCol] = 3;
                                        permColors[boardRow-1][boardCol] = 3;
                                }
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'Z':
                        if(boardRow-1 <= 0 || (permBoard[boardRow-2][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                permBoard[boardRow][boardCol-1] = 1;
                                permBoard[boardRow][boardCol] = 1;
                                permBoard[boardRow-1][boardCol] = 1;
                                permBoard[boardRow-1][boardCol+1] = 1;
                                permColors[boardRow][boardCol-1] = 4;
                                permColors[boardRow][boardCol] = 4;
                                permColors[boardRow-1][boardCol] = 4;
                                permColors[boardRow-1][boardCol+1] = 4;
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'L':
                        if(boardRow-2 <= 0 || (permBoard[boardRow-3][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                permBoard[boardRow][boardCol-1] = 1;
                                permBoard[boardRow-1][boardCol-1] = 1;
                                permBoard[boardRow-2][boardCol-1] = 1;
                                permBoard[boardRow-2][boardCol] = 1;
                                permColors[boardRow][boardCol-1] = 5;
                                permColors[boardRow-1][boardCol-1] = 5;
                                permColors[boardRow-2][boardCol-1] = 5;
                                permColors[boardRow-2][boardCol] = 5;
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                case 'J':
                        if(boardRow-2 <= 0 || (permBoard[boardRow-3][boardCol] == 1)) {
                                rotationSwitch = 0;
                                
                                permBoard[boardRow][boardCol] = 1;
                                permBoard[boardRow-1][boardCol] = 1;
                                permBoard[boardRow-2][boardCol] = 1;
                                permBoard[boardRow-2][boardCol-1] = 1;
                                permColors[boardRow][boardCol] = 6;
                                permColors[boardRow-1][boardCol] = 6;
                                permColors[boardRow-2][boardCol] = 6;
                                permColors[boardRow-2][boardCol-1] = 6;
                                boardRow = 19;
                                boardCol = 5;
                                tetromino = getTetro();
                        }
                        break;
                }
        }

        // Check if game has been lost
        for(int i=0; i<COLUMNS; i++) {
                if(permBoard[19][i] == 1) {
                        boardInit(0, 1);
                        boardInit(0, 3);
                }
        }
        glutPostRedisplay();
}

// Rotates the tetromino by 90 degrees
void Rotate() {
        if(rotationSwitch == 1) {
                rotation++;
                if(rotation == 4)
                        rotation = 0;
        }
}

// Gets user's keyboard input
void myKeyboard(unsigned char key, int x, int y) {
        if(key == 'q' || key == 27) exit(0);
        if(key == 'p') glutIdleFunc( NULL );
        switch (key) {
        // Moves the tetromino to the right by 1
        case 'd':
                if(boardCol < 9)
                        boardCol++;
                glutPostRedisplay();
                break;
        // Moves the tetromino to the left by 1
        case 'a':
                if(boardCol > 0)
                        boardCol--;
                glutPostRedisplay();
                break;
        // Rotates the tetromino by 90 degrees
        case 'w':
                Rotate();
                glutPostRedisplay();
                break;
        // Moves the tetromino down
        case 's':
                boardRow--;
                glutPostRedisplay();
                break;
        // Rotates the entire game
        case 'r':
                theta[axis] += 4;
                if(theta[axis] > 360.0) {
                        theta[axis] -= 360;
                }
	        glutPostRedisplay();
                break;
        case 'R':
                theta[axis] -= 4;
                if(theta[axis] < 0) {
                        theta[axis] += 360;
                }
	        glutPostRedisplay();
                break;
        // Zooms the game in
        case 'z':
                zoom -= 0.05;
	        glutPostRedisplay();
                break;
        // Zooms the game out
        case 'Z':
                zoom += 0.05;
	        glutPostRedisplay();
                break;
        }
}

// ######## BOILER PLATE CODE ########

// Gets user input from the mouse (mainly used for game rotations at this point)
void myMouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
        // Rotations
        glRotatef(theta[0], 1.0, 0.0, 0.0);		// Rotate object with respect to x axis
        glRotatef(theta[1], 0.0, 1.0, 0.0);		// Rotate object with respect to y axis
        glRotatef(theta[2], 0.0, 0.0, 1.0);		// Rotate object with respect to z axis
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
        glutMouseFunc( myMouse );
        glEnable(GL_DEPTH_TEST);	// Enables 3D in OPENGL
        init();
        glutMainLoop();
}
