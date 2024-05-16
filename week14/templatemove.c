/* a template to move object */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

float positionar_x[10];
float positionar_y[10];
float velocityar_x[10];
float velocityar_y[10];

float position_x = 0.0, position_y = 0.0;
float present_time, last_time;
float velocity_x, velocity_y;
float mass = 5.0;
float speed = 2.0;
float coef = 1.0;
float pointSize = 10.0;

float position2_x = 0.0, position2_y = 0.0;
float velocity2_x, velocity2_y;
float mass2 = 5.0;

void display( ) {

  glClear(GL_COLOR_BUFFER_BIT);

  // Walls
  glColor3f(0.0, 0.0, 0.0);
  glLineWidth(5.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(1.5, 1.5);
    glVertex2f(1.5, -1.5);
    glVertex2f(-1.5, -1.5);
    glVertex2f(-1.5, 1.5);
  glEnd();


  // Object Point
  glColor3f(1.0, 0.0, 0.0);   // Red Object
  glPointSize(pointSize);
  glBegin(GL_POINTS);
    glVertex2f(position_x, position_y);
  glEnd();

  // Object Polygon
  glColor3f(0.0, 1.0, 0.0);   // Green Object
  glBegin(GL_POLYGON);
    glVertex2f(position_y+0.2, position_x);
    glVertex2f(position_y, position_x-0.2);
    glVertex2f(position_y-0.2, position_x);
    glVertex2f(position_y, position_x+0.2);
  glEnd();

  // Object Polygon
  glColor3f(0.0, 0.0, 1.0);   // Blue Object
  glBegin(GL_POLYGON);
    glVertex2f(position2_x-0.2, position2_y-0.2);
    glVertex2f(position2_x+0.2, position2_y-0.2);
    glVertex2f(position2_x+0.2, position2_y+0.2);
    glVertex2f(position2_x-0.2, position2_y+0.2);
  glEnd();

  // Object Polygon
  glColor3f(0.0, 1.0, 1.0);   // Cyan Object
  glBegin(GL_POLYGON);
    glVertex2f(position2_y-0.2, position2_x-0.2);
    glVertex2f(position2_y+0.2, position2_x-0.2);
    glVertex2f(position2_y+0.2, position2_x+0.2);
    glVertex2f(position2_y-0.2, position2_x+0.2);
  glEnd();

  // Object Polygon
  glColor3f(1.0, 1.0, 0.0);   // Yellow Object
  glBegin(GL_POLYGON);
    glVertex2f(positionar_x[0]-0.2, positionar_y[0]-0.2);
    glVertex2f(positionar_x[0]+0.2, positionar_y[0]-0.2);
    glVertex2f(positionar_x[0]+0.2, positionar_y[0]+0.2);
    glVertex2f(positionar_x[0]-0.2, positionar_y[0]+0.2);
  glEnd();

  // Object Polygon
  glColor3f(1.0, 0.5, 0.0);   // Orange Object
  glBegin(GL_POLYGON);
    glVertex2f(positionar_x[1]-0.2-0.4, positionar_y[1]-0.2);
    glVertex2f(positionar_x[1]+0.2, positionar_y[1]-0.2);
    glVertex2f(positionar_x[1]+0.2, positionar_y[1]+0.2);
    glVertex2f(positionar_x[1]-0.2, positionar_y[1]+0.2);
  glEnd();

  glutSwapBuffers();  // add this

}

void myinit() {
  srand(time(NULL));

  position_x = 2.0*( (float)rand()/RAND_MAX)-1.0;
  position_y = 2.0*( (float)rand()/RAND_MAX)-1.0;
  velocity_x = speed*2.0*( (float)rand()/RAND_MAX)-1.0;
  velocity_y = speed*2.0*( (float)rand()/RAND_MAX)-1.0;

  position2_x = 2.0*( (float)rand()/RAND_MAX)-1.0;
  position2_y = 2.0*( (float)rand()/RAND_MAX)-1.0;
  velocity2_x = speed*2.0*( (float)rand()/RAND_MAX)-1.0;
  velocity2_y = speed*2.0*( (float)rand()/RAND_MAX)-1.0;
}


void idle( ) {
  float dt;
  present_time = glutGet(GLUT_ELAPSED_TIME);
  dt = 0.001*(present_time - last_time);

  position_x += dt * velocity_x;
  position_y += dt * velocity_y;
  velocity_x += dt * (1.0)/mass;
  velocity_y += dt * (1.0)/mass;

  if(position_x >= 1.5) {
    velocity_x = -coef*velocity_x;
    position_x = 1.5-coef*(position_x - 1.5);
  }
  if(position_y >= 1.5) {
    velocity_y = -coef*velocity_y;
    position_y = 1.5-coef*(position_y - 1.5);
  }
  if(position_x <= -1.5) {
    velocity_x = -coef*velocity_x;
    position_x = -1.5-coef*(position_x + 1.5);
  }
  if(position_y <= -1.5) {
    velocity_y = -coef*velocity_y;
    position_y = -1.5-coef*(position_y + 1.5);
  }

  position2_x += dt * velocity2_x;
  position2_y += dt * velocity2_y;
  velocity2_x += dt * (1.0)/mass;
  velocity2_y += dt * (1.0)/mass;

  if(position2_x >= 1.5) {
    velocity2_x = -coef*velocity2_x;
    position2_x = 1.5-coef*(position2_x - 1.5);
  }
  if(position2_y >= 1.5) {
    velocity2_y = -coef*velocity2_y;
    position2_y = 1.5-coef*(position2_y - 1.5);
  }
  if(position2_x <= -1.5) {
    velocity2_x = -coef*velocity2_x;
    position2_x = -1.5-coef*(position2_x + 1.5);
  }
  if(position2_y <= -1.5) {
    velocity2_y = -coef*velocity2_y;
    position2_y = -1.5-coef*(position2_y + 1.5);
  }

  for(int i=0; i<10; i++) {
    positionar_x[i] += dt * velocityar_x[i];
    positionar_y[i] += dt * velocityar_y[i];
    velocityar_x[i] += dt * (1.0)/mass;
    velocityar_y[i] += dt * (1.0)/mass;

    if(positionar_x[i] >= 1.5) {
      velocityar_x[i] = -coef*velocityar_x[i];
      positionar_x[i] = 1.5-coef*(positionar_x[i] - 1.5);
    }
    if(positionar_y[i] >= 1.5) {
      velocityar_y[i] = -coef*velocityar_y[i];
      positionar_y[i] = 1.5-coef*(positionar_y[i] - 1.5);
    }
    if(positionar_x[i] <= -1.5) {
      velocityar_x[i] = -coef*velocityar_x[i];
      positionar_x[i] = -1.5-coef*(positionar_x[i] + 1.5);
    }
    if(positionar_y[i] <= -1.5) {
      velocityar_y[i] = -coef*velocityar_y[i];
      positionar_y[i] = -1.5-coef*(positionar_y[i] + 1.5);
    }
  }

  last_time = present_time;

  glutPostRedisplay();

}

void Reshape(int w, int h) {
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glViewport(0, 0, w, h);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  if (w <= h)
   glOrtho(-2.0, 2.0, -2.0*(GLfloat) h/ (GLfloat) w,
    2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
  else
   glOrtho(-2.0*(GLfloat) w/ (GLfloat) h, 2.0*(GLfloat) w/(GLfloat) h,
   -2.0, 2.0, -10.0, 10.0);

  glMatrixMode( GL_MODELVIEW );
}

void main_menu(int index) 
{
  switch(index)
  {
   case(1):
    {
      speed *= 1.5;
      myinit();
      break;
    }
   case(2):
    {
      speed /= 1.5;
      myinit();
      break;
    }
   case(3):
   {
     pointSize *= 2.0;
     myinit();
     break;

  }
   case(4):
   {
     pointSize /= 2.0;
     myinit();
     break;
  }
   case(5):
   {
      exit(0);
      break;
   }
}}
      
void mykeyboard(unsigned char key, int x, int y) {
  if (key == 'c') glutIdleFunc(idle);
  if (key == 's') glutIdleFunc(NULL);
  if (key == 'q' || key == 'Q') exit(0);
}

int main( int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // change to glut double
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("One particle moves in a plane");  
  glutReshapeFunc( Reshape );  // add this

  glutCreateMenu(main_menu);  // Creates a menu
  glutAddMenuEntry("Increase speed by 1.5", 1);
  glutAddMenuEntry("Decrease speed by 1.5", 2);
  glutAddMenuEntry("Increase size by 2.0", 3);
  glutAddMenuEntry("Decrease size by 2.0", 4);
  glutAddMenuEntry("Quit", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc( display );  // call the function display
  glutIdleFunc( idle );  // call the function idle
  myinit();
  glutMainLoop();

}
 
