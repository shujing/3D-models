// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>
//gl headers for xcode
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

// global variable
// pi value can be accessed using the built-in M_PI
bool m_Smooth = false;
bool m_Highlight = false;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
    
	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
    float d = 100.0;
	//GLfloat lightPosition[] = {-d,-d/2,-d/2,1.0f};
	GLfloat lightPosition[] = {-d,d,d,1.0f};
	
    glClearDepth( 1.0 );
    
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
    //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
    //glLightModelf(GL_LIGHT_MODEL_AMBIENT    , 0.0);
    glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
    
	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
    
    
    
}

void drawSphere(double r)
{
    glPushMatrix();
    
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    // float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {1.0f, 0.1f, 0.0f, 1.0f};
    float no_shininess = 0.0f;
    //   float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    GLfloat	ambientProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat	diffuseProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    
	if(m_Highlight)
	{
        float no_mat[] = {0.0f, 1.0f, 0.1f, 1.0f};
		
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 12);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
            if(m_Smooth)
            {
                glBegin(GL_POLYGON);
                
			    // the normal of each vertex is actaully its own coordinates normalized for a sphere
                glNormal3d(sin((i)*M_PI/n)*cos((j)*M_PI/n),cos((i)*M_PI/n)*cos((j)*M_PI/n),sin((j)*M_PI/n));
                
			    // your normal here
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                
                glNormal3d(sin((i+1)*M_PI/n)*cos((j)*M_PI/n),cos((i+1)*M_PI/n)*cos((j)*M_PI/n),sin((j)*M_PI/n));
                
			    // your normal here
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
                
                glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
                
			    // your normal here
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                
                glNormal3d(sin((i)*M_PI/n)*cos((j+1)*M_PI/n),cos((i)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
                
			    // your normal here
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            } else	{
                glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
                glEnd();
            }
    glPopMatrix();
}

void drawTorus(double R, double r){
    glPushMatrix();
    
    
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    // float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.376f, 0.157f, 0.117f, 1.0f};
    float no_shininess = 0.0f;
    //   float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    GLfloat	ambientProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat	diffuseProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    
    
	if(m_Highlight)
	{
        //float no_mat[] = {0.0f, 1.0f, 0.1f, 1.0f};
		float mat_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 6);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    // glColor3f(1, 1, 0);
  //  glPushMatrix();
    int i, j;
    int n = 20;
    for (i=0; i<2*n; i++) {
        for (j=0; j<2*n; j++) {
            if(m_Smooth)
            {
                glBegin(GL_POLYGON);
                
                glNormal3d(r*cos(j*M_PI/n)*cos(i*M_PI/n),r*sin(j*M_PI/n),-r*cos(j*M_PI/n)*sin(i*M_PI/n));
                glVertex3f((R+ r*cos(j*M_PI/n))*cos(i*M_PI/n), r*sin(j*M_PI/n), -(R+ r*cos(j*M_PI/n))*sin(i*M_PI/n));
                
                glNormal3d(r*cos((j+1)*M_PI/n)*cos(i*M_PI/n), r*sin((j+1)*M_PI/n), -r*cos((j+1)*M_PI/n)*sin(i*M_PI/n));
                glVertex3f((R+ r*cos((j+1)*M_PI/n))*cos(i*M_PI/n), r*sin((j+1)*M_PI/n), -(R+ r*cos((j+1)*M_PI/n))*sin(i*M_PI/n));
                
                glNormal3d(r*cos((j+1)*M_PI/n)*cos((i+1)*M_PI/n), r*sin((j+1)*M_PI/n), -r*cos((j+1)*M_PI/n)*sin((i+1)*M_PI/n));
                glVertex3f((R+ r*cos((j+1)*M_PI/n))*cos((i+1)*M_PI/n), r*sin((j+1)*M_PI/n), -(R+ r*cos((j+1)*M_PI/n))*sin((i+1)*M_PI/n));
                
                glNormal3d(r*cos(j*M_PI/n)*cos((i+1)*M_PI/n), r*sin(j*M_PI/n), -r*cos(j*M_PI/n)*sin((i+1)*M_PI/n));
                glVertex3f((R+ r*cos(j*M_PI/n))*cos((i+1)*M_PI/n), r*sin(j*M_PI/n), -(R+ r*cos(j*M_PI/n))*sin((i+1)*M_PI/n));
                glEnd();
                
            }
            else{
                glBegin(GL_POLYGON);
                glNormal3d(r*cos((j+0.5)*M_PI/n)*cos((i+0.5)*M_PI/n),r*sin((j+0.5)*M_PI/n),-r*cos((j+0.5)*M_PI/n)*sin((i+0.5)*M_PI/n));
                glVertex3f((R+ r*cos(j*M_PI/n))*cos(i*M_PI/n), r*sin(j*M_PI/n), -(R+ r*cos(j*M_PI/n))*sin(i*M_PI/n));
                glVertex3f((R+ r*cos((j+1)*M_PI/n))*cos(i*M_PI/n), r*sin((j+1)*M_PI/n), -(R+ r*cos((j+1)*M_PI/n))*sin(i*M_PI/n));
                glVertex3f((R+ r*cos((j+1)*M_PI/n))*cos((i+1)*M_PI/n), r*sin((j+1)*M_PI/n), -(R+ r*cos((j+1)*M_PI/n))*sin((i+1)*M_PI/n));
                glVertex3f((R+ r*cos(j*M_PI/n))*cos((i+1)*M_PI/n), r*sin(j*M_PI/n), -(R+ r*cos(j*M_PI/n))*sin((i+1)*M_PI/n));
                glEnd();
            }}
    }
    glPopMatrix();
}

void drawCylindar(double r, double h){
   // glPushMatrix();
    glPushMatrix();
    
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    // float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.745f, 0.745f, 0.745f, 1.0f};
    float no_shininess = 0.0f;
    //   float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    GLfloat	ambientProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat	diffuseProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    
	if(m_Highlight)
	{
      //  float no_mat[] = {0.0f, 1.0f, 0.1f, 1.0f};
		float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 12);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    int i;
    double j;
    int n = 40;
    //    int m = h/n;
    for(i = 0 ; i < 2*n ; i++){
        for (j=0.0; j<h; j+=0.1) {
            if (m_Smooth) {
                glBegin(GL_POLYGON);
                glNormal3d(r*cos(i*M_PI/n), j-h/2, r*sin(i*M_PI/n));
                glVertex3f(r*cos(i*M_PI/n), j-h/2, r*sin(i*M_PI/n));
                glNormal3d(r*cos((i+1)*M_PI/n), j-h/2, r*sin((i+1)*M_PI/n));
                glVertex3f(r*cos((i+1)*M_PI/n), j-h/2, r*sin((i+1)*M_PI/n));
                glNormal3d(r*cos((i+1)*M_PI/n), j+0.1-h/2, r*sin((i+1)*M_PI/n));
                glVertex3f(r*cos((i+1)*M_PI/n), j+0.1-h/2, r*sin((i+1)*M_PI/n));
                glNormal3d(r*cos(i*M_PI/n), j+0.1-h/2, r*sin(i*M_PI/n));
                glVertex3f(r*cos(i*M_PI/n), j+0.1-h/2, r*sin(i*M_PI/n));
                glEnd();
            }else{
                glBegin(GL_POLYGON);
                glNormal3d(r*cos((i+0.5)*M_PI/n), j+0.05-h/2, r*sin((i+0.5)*M_PI/n));
                glVertex3f(r*cos(i*M_PI/n), j-h/2, r*sin(i*M_PI/n));
                glVertex3f(r*cos((i+1)*M_PI/n), j-h/2, r*sin((i+1)*M_PI/n));
                glVertex3f(r*cos((i+1)*M_PI/n), j+0.1-h/2, r*sin((i+1)*M_PI/n));
                glVertex3f(r*cos(i*M_PI/n), j+0.1-h/2, r*sin(i*M_PI/n));
                glEnd();
            }
        }
    }
    
    
 //bottoms of the cylindar
    double z = -h/2;
    glBegin(GL_POLYGON);
    
    glNormal3d(0, z, 0);
    
    for(i = 0 ; i < n ; i++){
        glVertex3f(r*cos(2*i*M_PI/n),z, r*sin(2*i*M_PI/n));
    }
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3d(0, -z, 0);
    
    for(i = 0 ; i < n ; i++){
        glVertex3f(r*cos(2*i*M_PI/n),-z, r*sin(2*i*M_PI/n));
    }
    glEnd();
    glPopMatrix();
}

void drawCuboid(double a, double b, double c){
    glPushMatrix();
    
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    // float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.80f, 0.427f, 0.38f, 1.0f};
    float no_shininess = 0.0f;
    //   float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    GLfloat	ambientProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat	diffuseProperties[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    
	if(m_Highlight)
	{
        float no_mat[] = {0.3f, 0.4f, 0.4f, 1.0f};
		
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 12);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glNormal3d(0, 0, c/2);
    glBegin(GL_POLYGON);
    glVertex3d(a/2, b/2, c/2);
    glVertex3d(-a/2, b/2, c/2);
    glVertex3d(-a/2, -b/2, c/2);
    glVertex3d(a/2, -b/2, c/2);
    glEnd();
    
    glNormal3d(0, 0, -c/2);
    glBegin(GL_POLYGON);
    glVertex3d(-a/2, -b/2, -c/2);
    glVertex3d(-a/2, b/2, -c/2);
    glVertex3d(a/2, b/2, -c/2);
    glVertex3d(a/2, -b/2, -c/2);
    glEnd();
    
    glNormal3d(0, b/2, 0);
    glBegin(GL_POLYGON);
    glVertex3d(a/2, b/2, c/2);
    glVertex3d(-a/2, b/2, c/2);
    glVertex3d(-a/2, b/2, -c/2);
    glVertex3d(a/2, b/2, -c/2);
    glEnd();
    
    glNormal3d(0, -b/2, 0);
    glBegin(GL_POLYGON);
    glVertex3d(a/2, -b/2, c/2);
    glVertex3d(a/2, -b/2, -c/2);
    glVertex3d(-a/2, -b/2, -c/2);
    glVertex3d(-a/2, -b/2, c/2);
    glEnd();
    
    glNormal3d(a/2, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3d(a/2, b/2, c/2);
    glVertex3d(a/2, b/2, -c/2);
    glVertex3d(a/2, -b/2, -c/2);
    glVertex3d(a/2, -b/2, c/2);
    glEnd();
    
    glNormal3d(-a/2, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3d(-a/2, b/2, c/2);
    glVertex3d(-a/2, -b/2, c/2);
    glVertex3d(-a/2, -b/2, -c/2);
    glVertex3d(-a/2, b/2, -c/2);
    glEnd();
    glPopMatrix();
}



void abacus(){
    // draw the frame
    glPushMatrix();
    glTranslatef(-2, 0, 0);
    drawCuboid(0.2, 2, 0.2);
    glTranslatef(4, 0, 0);
    drawCuboid(0.2, 2, 0.2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.9, 0);
    drawCuboid(3.8, 0.2, 0.2);
    glTranslatef(0, -0.8, 0);
    drawCuboid(3.8, 0.2, 0.2);
    glTranslatef(0, -1.0, 0);
    drawCuboid(3.8, 0.2, 0.2);
    glPopMatrix();
    
    
    int i,j,column,row ;
    column = 11;
    row = 5;
    //draw the bars inside
    for (i = 0; i<column; i++) {
        glPushMatrix();
        glTranslatef(-1.5+i*0.3, 0, 0);
        drawCylindar(0.05, 1.8);
        glPopMatrix();
    }
    
    //draw the beans
    for (j = 0; j <2; j++) {
    for(i = 0; i < column ;i++){
        glPushMatrix();
        glTranslatef(-1.5+i*0.3, 0.6-j*0.2, 0);
        drawTorus(0.08, 0.06);
        glPopMatrix();
    }}

    for (j = 0; j <row; j++) {
        for(i = 0; i < column ;i++){
            glPushMatrix();
            glTranslatef(-1.5+i*0.3, -0.15-j*0.15, 0);
            drawTorus(0.08, 0.06);
            glPopMatrix();
        }}
}

void orientalPearlTower(){
    
    glTranslatef(0, -0.8, 0);
    drawSphere(0.5);
    
    
    glPushMatrix();
    //  glRotated(60, -1, -1, -1);]
    glRotatef(30, 1, 0, 0);
    glTranslatef(0, -0.75, 0);
   //q  glRotatef(-30, 0, 0,1 );
   
    drawCylindar(0.15, 1.5);
    glPopMatrix();
    
    
    glPushMatrix();
    //  glRotated(60, -1, -1, -1);]
    glRotatef(120, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    glTranslatef(0, -0.75, 0);
    drawCylindar(0.15, 1.5);
    glPopMatrix();
    
    
    
    glPushMatrix();
    //  glRotated(60, -1, -1, -1);]
    glRotatef(-120, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    glTranslatef(0, -0.75, 0);
    drawCylindar(0.15, 1.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.15, 1, 0);
    drawCylindar(0.09, 1.8);
    glTranslatef(0.3, 0, 0);
    drawCylindar(0.09, 1.8);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 1.8, 0);
    drawSphere(0.35);
    glTranslatef(0, 0.35, 0);
    drawCylindar(0.05, 0.7);
    glTranslatef(0, 0.35, 0);
    drawSphere(0.1);
    glTranslatef(0, 0.4, 0);
    drawCylindar(0.02,0.8);
    glPopMatrix();
    
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
    glTranslatef(0, 0, -6);
    
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    
    glScalef(zoom,zoom,zoom);
    
    switch (current_object) {
		case 0:
			drawSphere(1);
			break;
		case 1:
			// draw your second primitive object here
            drawTorus(2, 0.5);
			break;
		case 2:
			// draw your first composite object here
            orientalPearlTower();
			break;
		case 3:
			// draw your second composite object here
            abacus();
			break;
		default:
			break;
    };
	glPopMatrix();
	glutSwapBuffers ();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
        case 'p':
        case 'P':
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        case 'w':
        case 'W':
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
        case 'v':
        case 'V':
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            break;
        case 's':
        case 'S':
            m_Smooth = !m_Smooth;
            break;
        case 'h':
        case 'H':
            m_Highlight = !m_Highlight;
            break;
            
        case '1':
        case '2':
        case '3':
        case '4':
            current_object = key - '1';
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
    if (state == GLUT_DOWN) {
        mouseButton = button;
        moving = 1;
        startx = x;
        starty = y;
    }
    if (state == GLUT_UP) {
        mouseButton = button;
        moving = 0;
    }
}

void motion(int x, int y)
{
    if (moving) {
        if(mouseButton==GLUT_LEFT_BUTTON)
        {
            angle = angle + (x - startx);
            angle2 = angle2 + (y - starty);
        }
        else zoom += ((y-starty)*0.001);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
    
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;
    
	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "Q: Quit" <<endl<< endl;
    
	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;
    
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
                   /* aspect ratio */ 1.0,
                   /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();
    
	return 0;
}