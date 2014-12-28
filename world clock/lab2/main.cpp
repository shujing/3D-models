// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

/* header files for lab machine */
//#include "GL/glut.h"

using namespace std;

#define numStars 100
#define numPlanets 9

class planet
{
public:
	float distFromRef;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;
    
	planet()
	{
		distFromRef = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
	}
};

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
planet planetList[numPlanets];
pair<double,double> stars[numStars];
bool mode = false;

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
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //stars[i] stores the position of stars
    double range = 200;
    for (int i=0; i<numStars; i++) {
        stars[i]=pair<double, double> ((rand()%1000)/1000.0*range-range/2.0-10,(rand()%1000)/1000.0*range-range/2.0+5);
    }
    
}

void drawSomething(){
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++) {
      //  glColor3f(0,0,0);
        glVertex2f(2*sin(2*M_PI*i/40), 2*cos(2*M_PI*i/40));
    }
    glEnd();
}

void display(void)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    double timeinfo = ((double)clock())/((double)CLOCKS_PER_SEC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glPushMatrix();
    
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
    
	//draw stuff here!
   
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    
    //draw the stars
    glPushMatrix();
    
    double s = .05;
    glScalef(s, s, s);    
    for (int i = 0; i <numStars; i++) {
        //    double randomPositionX = rand();
        glColor4f(1, 1, 1, sin(timeinfo+stars[i].first));
        glTranslatef(stars[i].first , stars[i].second, 0);
        drawSomething();
    }
    glPopMatrix();

    //draw the planets
    
    glColor3f(1, 1, 0);
    
    double angle = 360-timeinfo/30*3600;
    drawSomething();
    
    //clock mode
    if (mode) {
        
        // current date/time based on current system
        
        int hours = (ltm->tm_hour) % 12;
        glPushMatrix();
        glRotatef(90-((double)hours)/12.0*360, 0, 0, 1);
        glTranslatef(5, 0, 0);
        glColor4f(0, 0, 1, 0.5);
        glScalef(0.5, 0.5, 1);
        drawSomething();
        glPopMatrix();
        
        int minutes = (ltm->tm_min) % 60;
        glPushMatrix();
        glRotatef(90-((double)minutes)/60*360, 0, 0, 1);
        glTranslatef(7, 0, 0);
        glColor4f(0, 1, 1, 1);
        glScalef(0.25, 0.25, 1);
        drawSomething();
        glPopMatrix();
        
        int seconds = (ltm->tm_sec) % 60;
        glPushMatrix();
        glRotatef(90-((double)seconds)/60*360, 0, 0, 1);
        glTranslatef(8, 0, 0);
        glColor4f(0.6, 0.5, 1, 1);
        glScalef(0.2, 0.2, 1);
        drawSomething();
        glPopMatrix();
        
    }
    else //solar system mode
    {
        glRotatef(angle,0,0,1);
        
        glPushMatrix();
        glTranslatef(5, 0, 0);
        glColor4f(0, 0, 1, 1);
        glScalef(0.5, 0.5, 1);
        drawSomething();
        
        glPushMatrix();
        double ang = 360-timeinfo/5*3600;
        ang = ang/180.0*3.14159265;
        double r1 = 3, r2 = 6;
        glTranslatef(cos(ang)*r1, sin(ang)*r2, 0);
        glColor4f(0, 1, 1, 0.5);
        glScalef(0.3, 0.3, 1);
        drawSomething();
        glPopMatrix();
        
        glTranslatef(-15, -6, 0);
        glColor4f(1, 0.8, 0.1, 1);
        glScalef(0.5, 0.5, 1);
        drawSomething();
        glPopMatrix();
        
    }
    
    
    glPopMatrix();
 	glPopMatrix();
	glFlush ();
}


void idle()
{
	//update animation here
	
	glutPostRedisplay();	//after updating, draw the screen again
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
            
        case 't':
            mode = !mode;
            
		default:
            break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
	return 0;
}
