// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

/* header files for xcode */
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

/* header files for lab machine */
//#include "GL\glut.h"

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8
#define PI 3.1415926

using namespace std;

// Global variables that you can use
struct Point {
	int x,y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];
Point copyPtList[MAXPTNO];
Point interPoints[MAXPTNO*2];
double tangent[MAXPTNO*2];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;

void drawRightArrow()
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
    glVertex2f(0,0);
    glVertex2f(100,0);
    glVertex2f(95,5);
    glVertex2f(100,0);
    glVertex2f(95,-5);
	glEnd();
}


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
	glPushMatrix();
    
    if (C1Continuity) {
        for (int i = 1; i <(nPt-1)/3; i++) {
            ptList[i*3+1].x=2* copyPtList[i*3].x-copyPtList[i*3-1].x;
            ptList[i*3+1].y=2*copyPtList[i*3].y-copyPtList[i*3-1].y;
        }
        
    }
    else{
        for (int i = 1; i <(nPt-1)/3; i++) {
            ptList[i*3+1].x=copyPtList[i*3+1].x;
            ptList[i*3+1].y=copyPtList[i*3+1].y;
        }
    }

    
    //compute all the tangent value
    for (int i = 0 ; i < nPt-3; i+=3) {
        
        double d  = 1.0/(double)NOBJECTONCURVE;
        
        for (int j = 0; j < NOBJECTONCURVE; j++) {
            double t = d*(double)j;
            interPoints[j+i/3*8].x = pow(1.0-t, 3)*ptList[i].x+3*t*pow(1.0-t, 2)*ptList[i+1].x+3*pow(t, 2)*(1.0-t)*ptList[i+2].x+pow(t, 3)*ptList[i+3].x;
            interPoints[j+i/3*8].y = pow(1.0-t, 3)*ptList[i].y+3*t*pow(1.0-t, 2)*ptList[i+1].y+3*pow(t, 2)*(1.0-t)*ptList[i+2].y+pow(t, 3)*ptList[i+3].y;
            double dx = -3*(1.0-t)*(1.0-t)*ptList[i].x+3*(t-1.0)*(3*t-1.0)*ptList[i+1].x+3*t*(2.0-3*t)*ptList[i+2].x+3*t*t*ptList[i+3].x;
            double dy = -3*(1.0-t)*(1.0-t)*ptList[i].y+3*(t-1.0)*(3*t-1.0)*ptList[i+1].y+3*t*(2.0-3*t)*ptList[i+2].y+3*t*t*ptList[i+3].y;
            tangent[j+i/3*8] = dy/dx;
            
        }
    }
    
 	if (displayTangentVectors) {
        for (int i = 0; i < (nPt-1)/3*NOBJECTONCURVE; i++) {
            
            glPushMatrix();
            glTranslated(interPoints[i].x, interPoints[i].y, 0);
            glRotated(atan(tangent[i])*180.0/PI, 0, 0, 1);
            glScaled(0.6, 0.6, 1);
            drawRightArrow();
            glPopMatrix();
            
        }
    }
    
        
    // display the control points
    if(displayControlPoints)
	{
        
		glPointSize(5);
		glBegin(GL_POINTS);
        
        
		for(int i=0;i<nPt; i++)
		{
            glColor3f(0,0,0);
            glVertex2d(ptList[i].x,ptList[i].y);
		}
        
        //make the line continue
        if (C1Continuity) {
            for (int i = 1; i <(nPt-1)/3; i++) {
                glColor3f(0.8, 0.8, 0.8);
                glVertex2d(copyPtList[i*3+1].x, copyPtList[i*3+1].y);
                glColor3f(1, 0, 0);
                glVertex2d(ptList[i*3+1].x, ptList[i*3+1].y);
            }
        }
		glEnd();
		glPointSize(1);
        
	}
    
    
    
    //control line
	if(displayControlLines)
	{
		glColor3f(0,1,0);
        glBegin(GL_LINE_STRIP);
        for (int i  = 0 ; i < nPt; i++) {
            glVertex2d(ptList[i].x, ptList[i].y);
        }
        glEnd();
        
    }
    
    //curve
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for(int i = 3 ; i < nPt; i +=3)
    {
        for (float k = 0 ; k<NLINESEGMENT; k++) {
            float x = pow(1.0-k/NLINESEGMENT, 3)*ptList[i-3].x+
            3*(k/NLINESEGMENT)*pow(1.0-k/NLINESEGMENT, 2)*ptList[i-2].x+
            3*(1.0-k/NLINESEGMENT)*pow(k/NLINESEGMENT, 2)*ptList[i-1].x+
            pow(k/NLINESEGMENT, 3)*ptList[i].x;
            float y = pow(1.0-k/NLINESEGMENT, 3)*ptList[i-3].y+
            3*(k/NLINESEGMENT)*pow(1.0-k/NLINESEGMENT, 2)*ptList[i-2].y+
            3*(1.0-k/NLINESEGMENT)*pow(k/NLINESEGMENT, 2)*ptList[i-1].y+
            pow(k/NLINESEGMENT, 3)*ptList[i].y;
            glVertex2d(x, y);
        }
    }
    glEnd();
    
    //butterflies along the curve
    if (displayObjects) {
        for (int i = 0; i < (nPt-1)/3*NOBJECTONCURVE; i++) {
            //  glTranslated(interPoints[i].x, interPoints[i].y, 0);
            glPushMatrix();
            glTranslated(interPoints[i].x, interPoints[i].y, 0);
            glRotated(atan(tangent[i])*180.0/PI - 90, 0, 0, 1);
            glScaled(3, 3, 1);
            butterfly(1, 0, 1);
            glPopMatrix();
        }
        
    }
    
	glPopMatrix();
	glutSwapBuffers ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void init(void)
{
	glClearColor (1.0,1.0,1.0, 1.0);
}

void readFile()
{
    
	std::ifstream file;
    file.open("savefile.txt");
	file >> nPt;
    
	if(nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}
    
	for(int i=0;i<nPt;i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
copyPtList[i].x = ptList[i].x;
        copyPtList[i].y= ptList[i].y;
      //  cout >> (ptList[i].x+" "+ptList[i].y);
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
    file.open("savefile.txt");
    file << nPt << endl;
    
	for(int i=0;i<nPt;i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
            break;
            
		case 'w':
		case 'W':
			writeFile();
            break;
            
		case 'T':
		case 't':
			displayTangentVectors = !displayTangentVectors;
            break;
            
		case 'o':
		case 'O':
			displayObjects = !displayObjects;
            break;
            
		case 'p':
		case 'P':
			displayControlPoints = !displayControlPoints;
            break;
            
		case 'L':
		case 'l':
			displayControlLines = !displayControlLines;
            break;
            
		case 'C':
		case 'c':
			C1Continuity = !C1Continuity;
            break;
            
		case 'e':
		case 'E':
			// Do something to erase all the control points added
            nPt = 0;
            break;
            
		case 'Q':
		case 'q':
			exit(0);
            break;
            
		default:
            break;
	}
    
	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
	{
		if(nPt==MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x=x;
        copyPtList[nPt].x =x;
        copyPtList[nPt].y =y;
		ptList[nPt].y=y;
		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 4"<< endl<< endl;
	cout << "Left mouse click: Add a control point"<<endl;
	cout << "Q: Quit" <<endl;
	cout << "P: Toggle displaying control points" <<endl;
	cout << "L: Toggle displaying control lines" <<endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" <<endl;
	cout << "T: Toggle displaying tangent vectors" <<endl;
	cout << "O: Toggle displaying objects" <<endl;
	cout << "R: Read in control points from \"savefile.txt\"" <<endl;
	cout << "W: Write control points to \"savefile.txt\"" <<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 4");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    
	return 0;
}
