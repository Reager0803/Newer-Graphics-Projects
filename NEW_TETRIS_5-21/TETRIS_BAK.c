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
    {0.1, 0.1, 0.1},
    {0.3, 0.3, 0.3},
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

int board[ROWS][COLS] = {0};
int score = 0;
char GameOn = TRUE;
suseconds_t timer = 400000; // decrease this to make it faster
int decrease = 1000;

typedef struct {
    int **array;
    int width, row, col;
} Shape;
Shape current;

const Shape ShapesArray[7]= {
    {(int *[]){(int []){0,1,1},(int []){1,1,0}, (int []){0,0,0}}, 3},                           //S shape
    {(int *[]){(int []){1,1,0},(int []){0,1,1}, (int []){0,0,0}}, 3},                           //Z shape
    {(int *[]){(int []){0,1,0},(int []){1,1,1}, (int []){0,0,0}}, 3},                           //T shape
    {(int *[]){(int []){0,0,1},(int []){1,1,1}, (int []){0,0,0}}, 3},                           //L shape
    {(int *[]){(int []){1,0,0},(int []){1,1,1}, (int []){0,0,0}}, 3},                           //flipped L shape
    {(int *[]){(int []){1,1},(int []){1,1}}, 2},                                                 //square shape
    {(int *[]){(int []){0,0,0,0}, (int []){1,1,1,1}, (int []){0,0,0,0}, (int []){0,0,0,0}}, 4} //long bar shape
};

Shape CopyShape(Shape shape) {
    Shape new_shape = shape;
    int **copyshape = shape.array;
    new_shape.array = (int**)malloc(new_shape.width*sizeof(int));
    for(int i=0; i<new_shape.width; i++) {
        new_shape.array[i] = (int*)malloc(new_shape.width*sizeof(int));
        for(int j=0; j<new_shape.width; j++) {
            new_shape.array[i][j] = copyshape[i][j];
        }
    }
}

void DeleteShape(Shape shape) {
    for(int i=0; i<shape.width; i++) {
        free(shape.array[i]);
    }
    free(shape.array);
}

int CheckPosition(Shape shape) {    // Checks the position of the copied shape
    int **array = shape.array;
    for(int i=0; i<shape.width; i++) {
        for(int j=0; j<shape.width; j++) {
            if((shape.col+j < 0 || shape.col+j >= COLS || shape.row+1 >= ROWS)) {   // Outside of boarders
                if(array[i][j])
                    return FALSE;

            }
            else if(board[shape.row+1][shape.col+j] && array[i][j])
                return FALSE;
        }
    }
    return TRUE;
}

void SetNewRandomShape() {  // Updates [current] with new shape
    Shape new_shape = CopyShape(ShapesArray[rand()%7]);
    new_shape.col = rand()%(COLS-new_shape.width+1);
    new_shape.row = 0;
    DeleteShape(current);
    current = new_shape;
    if(!CheckPosition(current)) {
        GameOn = FALSE;
    }
}

void RotateShape(Shape shape) {
    Shape temp = CopyShape(shape);
    int i, j, k, width;
    width = shape.width;
    for(i = 0; i<width; i++) {
        for(j = 0, k = width-1; j<width; j++, k--) {
            shape.array[i][j] = temp.array[k][i];
        }
    }
    DeleteShape(temp);
}

void WriteToBoard() {
    for(int i=0; i<current.width; i++) {
        for(int j=0; j<current.width; i++) {
            if(current.array[i][j]) {
                board[current.row+i][current.col+j] = current.array[i][j];
            }
        }
    }
}

void RemoveFullRowsAndUpdateScore(){
    int i, j, sum, count=0;
    for(i=0;i<ROWS;i++){
        sum = 0;
        for(j=0;j< COLS;j++) {
            sum+=board[i][j];
        }
        if(sum==COLS){
            count++;
            int l, k;
            for(k = i;k >=1;k--)
                for(l=0;l<COLS;l++)
                    board[k][l]=board[k-1][l];
            for(l=0;l<COLS;l++)
                board[k][l]=0;
            timer -= decrease--;
        }
    }
    score += 100*count;
}

// Draws the board
void PrintBoard() {
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

    board[0][0] = ShapesArray[0].array[1][1];
    WriteToBoard();

    // Draws out the dynamic board
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            if(board[i][j] > 0) {
                glPushMatrix();
                switch (0) {
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
}

// struct timeval before_now, now;
// int hasToUpdate() {
//     return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
// }

// Draws the initial game
void Game() {
    PrintBoard();
}

// Autostarts without user input
void myIdle() {

    glutPostRedisplay();
}

// Gets user's keyboard input
void myKeyboard(unsigned char key, int x, int y) {
    /*Shape temp = CopyShape(current);
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
            temp.row++; // Move Down
            if(CheckPosition(temp))
                current.row++;
            else {
                WriteToBoard();
                RemoveFullRowsAndUpdateScore();
                SetNewRandomShape();
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
    }
    DeleteShape(temp);
    PrintBoard(); */
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
    Game();
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
