// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

/* header files for lab machine */
//#include "GL\glut.h"

using namespace std;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

/**get the cordination of a dot on the curve by 4 dots*/
double bezier(double A,  // Start value
              double B,  // First control value
              double C,  // Second control value
              double D,  // Ending value
              double t)  // Parameter 0 <= t <= 1
{
    double s = 1 - t;
    double AB = A*s + B*t;
    double BC = B*s + C*t;
    double CD = C*s + D*t;
    double ABC = AB*s + CD*t;
    double BCD = BC*s + CD*t;
    return ABC*s + BCD*t;
}

/** draw a bezier curve with 4 points*/
void curve(double points[4][3],float r, float g, float b, int nPoints=100){
    glBegin(GL_POLYGON);

    for(int i=0; i < nPoints; i++)
    {
        double t= ((double)i)/(nPoints-1);
        glColor3f(t*r, t*g, t*b);
        glVertex3f(bezier(points[0][0], points[1][0],points[2][0], points[3][0], t),bezier(points[0][1], points[1][1],points[2][1], points[3][1], t),0);
    }
    
    glEnd();
}

/**draw the left wing*/
void drawWing(float r, float g, float b){
    double ctrlpoints[4][3] = {
        {0.0, 0.0, 0.0},{-2.0, 4.0, 0.0},{ -5.0, 5.0, 0.0},
         { -5.0, 3.0, 0.0}};
    double ctrlpoints2[4][3] = {
        {0.0, 0.0, 0.0},{-3.5, -0.5, 0.0},
       { -5.5, -1.0, 0.0}, { -5.0, 3.0, 0.0}
        };
    double ctrlpoints3[4][3] = {
        {0.0, 0.0, 0.0},{-2, 0.5, 0.0},
        { -4.5, -0.5, 0.0}, { -3.5, -2, 0.0}
    };
    double ctrlpoints4[4][3] = {
        {0.0, 0.0, 0.0},{-0.1, -5.0, 0.0},
        { -3, -5.5, 0.0}, { -3.5, -2, 0.0}
    };
    
    curve(ctrlpoints,r,g,b);
    curve(ctrlpoints2,r,g,b);
    curve(ctrlpoints3,r,g,b);
    curve(ctrlpoints4,r,g,b);
}

/**right antenna*/
void antenna(){
    double antennaPoints[4][3] = {
        { 0.35, 1.7, 0.0}, { 0, 2.0, 0.0},
        {0.5, 3, 0.0}, {1, 3.5, 0.0}};
    glBegin(GL_LINE_STRIP);
    for (double t = 0; t<=1; t+=0.1){
        glVertex3f(bezier(antennaPoints[0][0], antennaPoints[1][0],antennaPoints[2][0], antennaPoints[3][0], t),bezier(antennaPoints[0][1], antennaPoints[1][1],antennaPoints[2][1], antennaPoints[3][1], t),0);
    }
    glEnd();
}

void butterfly(float red, float green, float blue){
    
    drawWing(red,green, blue);
    glScalef(-1, 1, 1);
    drawWing(red,green,blue);
    
    //draw the butterfly's body
   
    double bodypoints[4][3] = {
        { -0.35, 1.0, 0.0}, { -0.6, -5.0, 0.0},
        {0.6, -5, 0.0}, {0.35, 1.0, 0.0}};
    curve(bodypoints,red, green, blue);

    
    //head
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++) {
        glColor3f(red*i/20, green*i/20, blue*i/20);
        glVertex2f(0.495*sin(2*M_PI*i/20), 1.35+0.495*cos(2*M_PI*i/20));
    }
    glEnd();
    
    //antanne
    antenna();
    glScalef(-1, 1, 1);
    antenna();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    //modify the background color
    glBegin(GL_POLYGON);
    glColor3f(0.529,0.808,1.0);
    
    glVertex2f(-10.0,-10.0);
    
    glVertex2f(-10.0,10.0);
    
    glColor3f(0.678, 1, 0.184);
    glVertex2f(10.0,10.0);
    
    glVertex2f(10.0, -10.0);
    
    glEnd();
      
	
	glPushMatrix();
    
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
	
	//draw your stuff here
   
    
    glScalef(0.3, 0.3, 0.3);
    glRotated(-10, 0, 0, 1);
    butterfly(1,0,1);
    
    glTranslatef(10, 10, 0);
    glScalef(0.7, 0.6, 0.8);
    glRotated(-60, 0, 0, 1);
    butterfly(0, 1, 0);
    glPopMatrix();
    
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(-10, -5, 0);
    glRotated(60, 0, 0, 1);
    butterfly(0, 0, 1);
	glPopMatrix();
    
    glFlush ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {
            
		case 'a':
			alpha+=10;
			glutPostRedisplay();
            break;
            
		case 'd':
			alpha-=10;
			glutPostRedisplay();
            break;
            
		case 'q':
			k+=0.1;
			glutPostRedisplay();
            break;
            
		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
            break;
            
		case 'z':
			tx-=0.1;
			glutPostRedisplay();
            break;
            
		case 'c':
			tx+=0.1;
			glutPostRedisplay();
            break;
            
		case 's':
			ty-=0.1;
			glutPostRedisplay();
            break;
            
		case 'w':
			ty+=0.1;
			glutPostRedisplay();
            break;
            
		default:
            break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
	return 0;
}
