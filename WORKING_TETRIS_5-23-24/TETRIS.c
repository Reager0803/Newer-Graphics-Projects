// Tetris Game

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ROWS 20
#define COLS 10
#define TRUE 1
#define FALSE 0

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

materialStruct *currentMaterial;
void materials(materialStruct *materials) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials -> ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials -> diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials -> specular);
}

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
    {0.1, 0.1, 0.2},
    {0.2, 0.25, 0.35},
    100.0
};

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



// ######## Boiler Plate Code above ########

// Other important global variables:

char board[ROWS][COLS] = {0};
char permBoard[ROWS][COLS] = {0};
char colors[ROWS][COLS] = {0};
int decrease = 1000;
int color;
int game_on = 1;
int warp_speed = 0;
int lines_cleared = 0;  // Total lines cleared in the game

// Switches
int start_switch = 0;   // Starts the game when set to 1
int theta_switch = 0;   // Starts rotating automatically when set to 1

// When next_block_switch is set to 1, the next block is loaded.
// When next_block_display is set to 1, the next block is shown in the
// next block box.
int next_block_switch = 0, next_block_display = 0;

typedef struct {
    char **array;
    int width, row, col;
} Shape;

// The current tetromino which has a 2d array which contains the shape
// as well as the width of the tetromino, the row, and the column
Shape current;

const Shape ShapesArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},                           //Z block     
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},                           //S block     
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},                           //T block     
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},                           //J block     
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},                           //L block    
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},                                                 //O block
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4} //I block
};

Shape CopyShape(Shape shape){
	Shape new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void DeleteShape(Shape shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

int CheckPosition(Shape shape){ //Check the position of the copied shape
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= COLS || shape.row+1-i <= 0)){ //Out of borders
				if(array[i][j]) //but is it just a phantom?
					return FALSE;
			}
            else if(permBoard[shape.row-i][shape.col+j] && array[i][j] == 1)
                return FALSE;
		}
	}
	return TRUE;
}

// The color of the next block
int next_color = 0;

void SetNewRandomShape(){ //updates [current] with new shape
    Shape new_shape;
    srand(time(NULL));
    if(next_block_switch == 0) {
        color = rand()%7;
        new_shape = CopyShape(ShapesArray[color]);
        next_color = rand()%7;
    } else {
        color = next_color;
        new_shape = CopyShape(ShapesArray[color]);
        next_color = rand()%7;
    }

    if(color == 5)
        new_shape.col = 4;
    else
        new_shape.col = 3;
    new_shape.row = 19;
    DeleteShape(current);
	current = new_shape;
}

void RotateShape(Shape shape){ //rotates clockwise
	Shape temp = CopyShape(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	DeleteShape(temp);
}

void WriteToBoard(){
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j]) {
				board[current.row-i][current.col+j] = current.array[i][j];
                colors[current.row-i][current.col+j] = color;
            }                
		}
	}
}

int total_lines = 0;
// Draws the cleared lines (not the board though)
void DrawLinesCleared() {
    total_lines += lines_cleared;
}

void RemoveFullRowsAndUpdateScore(){
	int sum, count=0;
	for(int i = 0; i < ROWS; i++){
		sum = 0;
		for(int j = 0; j < COLS; j++) {
			sum+=permBoard[i][j];
		}
		if(sum == COLS) {
            int k, l;
            count++;
            lines_cleared++;
            DrawLinesCleared();
			for(k = i; k < ROWS; k++) {
				for(l = 0; l < COLS; l++) {
					permBoard[k][l] = permBoard[k+1][l];
                    colors[k][l] = colors[k+1][l];
                }
            }
            for(int l=0; l<COLS; l++) {
				    permBoard[k][l] = 0;
                    colors[k][l] = 0;
            }
		}
	}
}

// Sets the dynamic board to the permanent board
void UpdateBoard() {
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            int catch = 0;
            if(permBoard[i][j] == 1)
                catch = 1;
            permBoard[i][j] = board[i][j];
            if(catch == 1)
                permBoard[i][j] = 1;
        }
    }
}

// Erases the board, 0 for the dynamic one, other for the permanent board
void ClearBoard(int choice) {
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            if(choice == 0)
                board[i][j] = 0;
            else
                permBoard[i][j] = 0;
        }
    }
}

// Prints the total scores and lines
void PrintScores(int multiplier, double yOff, int max) {
    glPushMatrix();
        materials(&White);
        glTranslatef(1.5,-5.25+yOff,0);
        glRasterPos3f(12, 12, 0);
        int lines_temp = total_lines*multiplier, temp_digit;
        char digits[max];
        char rDigits[max];
        for(int i=0; i<max; i++) {
            temp_digit = lines_temp % 10;
            lines_temp /= 10;
            digits[i] = temp_digit + 48;
        }
        for(int j=0; j<max; j++) {
            rDigits[j] = digits[max-1-j];
        }
        for(int i=0; i<max; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rDigits[i]);
        }
    glPopMatrix();
}

// Draws a box
void DrawClearedBoard(double x1, double x2, double y1, double y2) {
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
        materials(&White);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
        glVertex2f(x1, y1);
    glEnd();
    glBegin(GL_POLYGON);
        materials(&Dark_Grey);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
        glVertex2f(x1, y1);
    glEnd();
    glPopMatrix();
}

// Draws the next block to be spawned to the side of the board
void DrawNextBlock() {
    glPushMatrix();
        glBegin(GL_LINE_LOOP);
            materials(&White);
            glVertex2f(12, 5);
            glVertex2f(22, 5);
            glVertex2f(22, -3);
            glVertex2f(12, -3);
        glEnd();
        glBegin(GL_POLYGON);
            materials(&Dark_Grey);
            glVertex2f(12, 5);
            glVertex2f(22, 5);
            glVertex2f(22, -3);
            glVertex2f(12, -3);
        glEnd();
    glPopMatrix();

    if(next_block_display == 1) {
        glPushMatrix();
            glTranslatef(15.0, 0.0, 0.0);
            switch (next_color) {
                case 0:
                    materials(&Green);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(0, 2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    break;
                case 1:
                    materials(&Red);
                    glTranslatef(0, 2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(0, -2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    break;
                case 2:
                    materials(&Purple);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(0, 2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, -2.1, 0);
                    glutSolidCube(2.0);
                    break;
                case 3:
                    materials(&Orange);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(0, 2.1, 0);
                    glutSolidCube(2.0);
                    break;
                case 4:
                    materials(&DarkBlue);
                    glutSolidCube(2.0);
                    glTranslatef(0, 2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, -2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    break;
                case 5:
                    materials(&Yellow);
                    glTranslatef(1.05, 2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(0, -2.1, 0);
                    glutSolidCube(2.0);
                    glTranslatef(-2.1, 0, 0);
                    glutSolidCube(2.0);
                    break;
                case 6:
                    materials(&LightBlue);
                    glTranslatef(-1.05, 1.05, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    glTranslatef(2.1, 0, 0);
                    glutSolidCube(2.0);
                    break;
            }
        glPopMatrix();
    }
}

// Draws the board
void PrintBoard() {
    ClearBoard(0);

    DrawNextBlock();

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

    WriteToBoard();

    // Draws out the board
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                switch (colors[i][j]) {
                    case 0:
                        materials(&Green);
                        break;
                    case 1:
                        materials(&Red);
                        break;
                    case 2:
                        materials(&Purple);
                        break;
                    case 3:
                        materials(&Orange);
                        break;
                    case 4:
                        materials(&DarkBlue);
                        break;
                    case 5:
                        materials(&Yellow);
                        break;
                    case 6:
                        materials(&LightBlue);
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
        for(int j=0; j<COLS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                materials(&Black);
                glTranslatef(inToC_X(j), inToC_Y(i), 0);
                glutWireCube(2.1);
                glPopMatrix();
            }
        }
    }
    
    // Draws out the permanent board
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            if(permBoard[i][j] > 0) {
                glPushMatrix();
                switch (colors[i][j]) {
                    case 0:
                        materials(&Green);
                        break;
                    case 1:
                        materials(&Red);
                        break;
                    case 2:
                        materials(&Purple);
                        break;
                    case 3:
                        materials(&Orange);
                        break;
                    case 4:
                        materials(&DarkBlue);
                        break;
                    case 5:
                        materials(&Yellow);
                        break;
                    case 6:
                        materials(&LightBlue);
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
        for(int j=0; j<COLS; j++) {
            if(permBoard[i][j] > 0) {
                glPushMatrix();
                materials(&Black);
                glTranslatef(inToC_X(j), inToC_Y(i), 0);
                glutWireCube(2.1);
                glPopMatrix();
            }
        }
    }

    glPushMatrix();
        materials(&White);
        glRasterPos3f(13.5, 8.5, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
    glPopMatrix();
        materials(&White);
        glRasterPos3f(13.5, -5.5, 0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
    glPushMatrix();

    glPopMatrix();

    PrintScores(1500, 0, 10);
    PrintScores(1, -14, 7);

    DrawClearedBoard(12, 22, 6, 10);
    DrawClearedBoard(12, 22, -8, -4);
    DrawClearedBoard(-23, -12, -18, 18);
}

// Autostarts without user input
void myIdle() {
    Shape temp = CopyShape(current);
    temp.row--;

    // Checks wether or not warp speed is enabled (warp speed is determined by the cpu speed)
    if(warp_speed == 0) {
        // Guesses random number, when correct, it ticks the game (I know it sucks)
        float num = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num2 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num3 = (float)rand()/(float)(RAND_MAX) * 2.0;
        float num4 = (float)rand()/(float)(RAND_MAX) * 2.0;
        if(((num > 0.0 && num < 0.1) || (num2 > 0.0 && num2 < 0.1) && (num3 > 0.0 && num3 < 0.1) && (num3 > 0.0 && num3 < 0.1) && (num4 > 0.0 && num4 < 0.1))) {
            current.row--;
        }
    } else {
        current.row--;
        if(!CheckPosition(temp))
            warp_speed = 0;
    }

    if(!CheckPosition(temp)) {
        next_block_switch = 1;
        UpdateBoard();
        RemoveFullRowsAndUpdateScore();
        RemoveFullRowsAndUpdateScore();
        RemoveFullRowsAndUpdateScore();
        SetNewRandomShape();
    }
    DeleteShape(temp);

    for(int i=0; i<COLS; i++) {
        if(permBoard[ROWS-1][i] > 0) {
            ClearBoard(1);
            exit(0);
        }
    }

    // Check if the board is spinning:
    if(theta_switch == 1) {
        theta[0] -= 1;
        theta[1] -= 1;
        theta[2] -= 1;
    }
    glutPostRedisplay();
}

// Gets user's keyboard input
void myKeyboard(unsigned char key, int x, int y) {
    Shape temp = CopyShape(current);
    if(key == 'q' || key == 27) exit(0);
    if(key == 'p') glutIdleFunc( NULL );
    switch (key) {
        // Moves the tetromino to the right by 1
        case 'd':
            temp.col++;
            if(CheckPosition(temp))
                current.col++;  // Move Right
            glutPostRedisplay();
            break;
        // Moves the tetromino to the left by 1
        case 'a':
            temp.col--; // Move Left
            if(CheckPosition(temp))
                current.col--;
            glutPostRedisplay();
            break;
        // Rotates the tetromino by 90 degrees
        case 'w':
            RotateShape(temp);  // Rotate Clockwise
            if(CheckPosition(temp))
                RotateShape(current);
            glutPostRedisplay();
            break;
            // Moves the tetromino down
        case 's':
            temp.row--; // Move Down
            if(CheckPosition(temp))
                current.row--;
            else {
                WriteToBoard();
                RemoveFullRowsAndUpdateScore();
            }
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
        case 't':
            game_on = 1;
            next_block_display = 1;
            if(start_switch == 0) {
                SetNewRandomShape();
                start_switch = 1;
            }
            break;
        case 'k':   // Start spinnings the board
            theta_switch = 1;
            break;
        case 'K':   // Stop spinning the board
            theta_switch = 0;
            theta[0] = 0;
            theta[1] = 0;
            theta[2] = 0;
            break;
        case 32:
            warp_speed = 1;
    }
    DeleteShape(temp);
    PrintBoard();
}

// ######## BOILER PLATE CODE BELOW ########

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
    PrintBoard();
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
    glClearColor(0.0, 0.15, 0.2, 0.0);	// Space Background
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
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
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(800.0, 200.0);
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
