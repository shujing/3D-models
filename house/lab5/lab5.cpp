#include "drawHouses.h"

void A0118626mapSquare(double vertices[4][3] ){
    
    // glBindTexture(GL_TEXTURE_2D, texSet[texIndex]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
    glTexCoord2d(1,0);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
    glTexCoord2d(1,1);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
    glTexCoord2d(0,1);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glEnd();
    
    
}

void A0118626drawBox(double x, double y, double z){
    double v[4][3]={
        {0,0,0},{0,y,0},{x,y,0},{x,0,0}
    };
    double v1[4][3]={
        {0,0,0},{0,y,0},{0,y,z},{0,0,z}
    };
    double v2[4][3]={
        {0,0,0},{x,0,0},{x,0,z},{0,0,z}
    };
 //glBegin(GL_QUADS);
    A0118626mapSquare(v);
    A0118626mapSquare(v1);
    A0118626mapSquare(v2);
    glPushMatrix();
    glTranslated(0, 0, z);
    A0118626mapSquare(v);
    glPopMatrix();
    glPushMatrix();
    glTranslated(x, 0, 0);
    A0118626mapSquare(v1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, y, 0);
    A0118626mapSquare(v2);
    glPopMatrix();
}

void A0118626drawStairs(GLuint texSet[],double vertices[4][3]){
    glPushMatrix();
    
 //   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texSet[3]);
    
    for (int i = 0; i < 3; i++) {
        A0118626mapSquare(vertices);
        glTranslated(0.2, 0.2, 0);
    };
    
    glPopMatrix();
}

void A0118626House(GLuint texSet[])
{
    
    double houseX = 3.0;
    double houseY = 6.5;
    double houseZ = 2.24;
    double roofHeight = 3.5;
    double poolHeight = 7.5;
	//plot dimension
	//x: -4:4
	//y: 0:12
	//z: -4:4
    
    
    double wallVertexes[4][3] = {
        {-houseX,roofHeight,-houseZ},
        {houseX, roofHeight, -houseZ},
        {houseX,houseY,-houseZ},
        {-houseX,houseY,-houseZ}
    };
    double wallVertexes1[4][3] = {
        {houseX,roofHeight,-houseZ},
        {houseX, roofHeight, houseZ},
        {houseX,houseY,houseZ},
        {houseX,houseY,-houseZ}
    };
    double grassVertexes[4][3] = {
        {-4,0,4},
        {4, 0, 4},
        {4,0,-4},
        {-4,0,-4}
    };
    double roofVertexes[4][3] = {
        {houseX+0.2,0.0,0.0},
        {-houseX-0.2,0.0,0.0},
        {-houseX-0.2, roofHeight*1.2, -houseZ*1.2},
        {houseX+0.2, roofHeight*1.2, -houseZ*1.2 }
    };
    
    double windowVertexes[4][3] = {
        {houseX+0.01,0.4*(houseY-roofHeight)+roofHeight,-houseZ*0.75},
        {houseX+0.01,0.4*(houseY-roofHeight)+roofHeight,-houseZ*0.25},
        {houseX+0.01, 0.8*(houseY-roofHeight)+roofHeight,-houseZ*0.25},
        {houseX+0.01, 0.8*(houseY-roofHeight)+roofHeight,-houseZ*0.75 }
    };
    double d = 0.4, l = 1.0;
    double windowVertexes1[4][3] = {
        {houseX/2-d,0.5*(houseY+roofHeight)-l/2,-houseZ-0.05},
        {houseX/2-d,0.5*(houseY+roofHeight)+l/2,-houseZ-0.05},
        {houseX/2+d, 0.5*(houseY+roofHeight)+l/2,-houseZ-0.05},
        {houseX/2+d, 0.5*(houseY+roofHeight)-l/2,-houseZ-0.05 }
    };
    double doorVertexes[4][3] = {
        {-houseX*0.2,houseY, houseZ+0.01},
        {houseX*0.2,houseY, houseZ+0.01},
        {houseX*0.2,0.4*(houseY-roofHeight)+roofHeight,houseZ+0.01},
        {-houseX*0.2,0.4*(houseY-roofHeight)+roofHeight,houseZ+0.01}
    };
    double doorVertexes1[4][3]={
        {-houseX-0.01, 0.3*roofHeight,-houseZ*0.25},
        {-houseX-0.01, 0.3*roofHeight,houseZ*0.25},
        {-houseX-0.01, 0.8*roofHeight,houseZ*0.25},
        {-houseX-0.01, 0.8*roofHeight,-houseZ*0.25}
    };
    double ceilingVertexes[4][3]={
        {-houseX*1.1, houseY-0.01, houseZ*1.1},
        {houseX*1.1, houseY-0.01, houseZ*1.1},
        {houseX*1.1, houseY-0.01, -houseZ*1.1},
        {-houseX*1.1, houseY-0.01, -houseZ*1.1}
    };
    double poolVerterexes[4][3]={
        {-houseX,houseY,houseZ},
        {-houseX,houseY,-houseZ},
        {houseX,houseY,-houseZ},
        {houseX,houseY,houseZ}
    };
	double platform[4][3]={
        {-0.4*houseX+0.4,0.95*houseY,-houseZ},
        {-0.4*houseX+0.4,0.95*houseY,-1.6*houseZ},
        {-houseX,0.95*houseY,-1.6*houseZ},
        {-houseX,0.95*houseY,-houseZ}
    };
	//bounding volume
	glPushMatrix();
	glTranslatef(0, 6, 0);
	glScalef(8, 12, 8);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);
	glPopMatrix();
    
    
    //start building the house
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    
    //grass
    glBindTexture(GL_TEXTURE_2D, texSet[9]);
    A0118626mapSquare(grassVertexes);
    
    //stairs
    glBindTexture(GL_TEXTURE_2D, texSet[39]);
  /*  glPushMatrix();
    for (int i =0; i< 3; i++) {
        
        A0118626mapSquare(stairVertexes1);
        A0118626mapSquare(stairVertexes2);
        glTranslated(houseX*0.1, 0.08*roofHeight, 0);
    }
    glPopMatrix();*/
    
    double x = 0.3, y = 0.3, z = 1.2;
    glPushMatrix();
    glTranslated(-1.3*houseX, 0, -z/2);
    A0118626drawBox(x, y, z);
    
    for (int i = 0; i < 4; i++) {
        glTranslated(x, y, 0);
        A0118626drawBox(x, y, z);
    }
    glPopMatrix();
    
    //stairs to the pool
    glPushMatrix();
    glTranslated(0.85, 4.15, -houseZ-z);
    A0118626drawBox(x, y, z);
    for (int i = 0; i < 6; i++) {
        glTranslated(-x, y, 0);
        A0118626drawBox(x, y, z);
    }
    glPopMatrix();
    
    //platform
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texSet[39]);
    A0118626mapSquare(platform);
    glPopMatrix();
    
//the window on the back wall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texSet[27]);
    A0118626mapSquare(windowVertexes1);
    glPopMatrix();
    
    //draw the chimney
     glBindTexture(GL_TEXTURE_2D, texSet[3]);
    glPushMatrix();
    glTranslated(2, 0, 0.6);
    A0118626drawBox(0.5, 2, 0.5);
    glPopMatrix();
    
   
    
    //start building the house
  /*  glRotated(-15, 0, 0, 1);
    glTranslated(-0.9, 0, 0);
    glScalef(0.9, 1, 1);*/
    //front wall
    glBindTexture(GL_TEXTURE_2D, texSet[37]);
    A0118626mapSquare(wallVertexes);
    //back wall
    glPushMatrix();
    glTranslated(0, 0, 2*houseZ);
    A0118626mapSquare( wallVertexes);
    glPopMatrix();
    //right wall
    //right rectangle part
    A0118626mapSquare(wallVertexes1);
    //right triangle part
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);
	glVertex3f(houseX,roofHeight ,-houseZ );
    glTexCoord2d(0,1);
	glVertex3f(houseX,roofHeight ,houseZ );
    glTexCoord2d(1,0.5);
	glVertex3f(houseX,0 ,0 );
    glEnd();
    //left wall
    //left rectangle part
    glPushMatrix();
    glTranslated(-2*houseX, 0, 0);
    A0118626mapSquare(wallVertexes1);
    glPopMatrix();
    //left triangle part
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);
	glVertex3f(-houseX,roofHeight ,-houseZ );
    glTexCoord2d(0,1);
	glVertex3f(-houseX,roofHeight ,houseZ );
    glTexCoord2d(1,0.5);
	glVertex3f(-houseX,0 ,0 );
    glEnd();
    
    //roof
    glBindTexture(GL_TEXTURE_2D, texSet[17]);
    A0118626mapSquare(roofVertexes);
    glPushMatrix();
    glScalef(1.0, 1.0, -1.0);
    A0118626mapSquare(roofVertexes);
    glPopMatrix();
    
  //  glPopMatrix();
    
    //windows
    glBindTexture(GL_TEXTURE_2D, texSet[31]);
    A0118626mapSquare(windowVertexes);
    glPushMatrix();
    glScalef(1, 1, -1);
    A0118626mapSquare(windowVertexes);
    glScalef(-1, 1, 1);
     A0118626mapSquare(windowVertexes);
    glScalef(1, 1, -1);
    A0118626mapSquare(windowVertexes);
    glPopMatrix();
  //  glBindTexture(GL_TEXTURE_2D, texSet[28]);
    

       
    //door
    glBindTexture(GL_TEXTURE_2D, texSet[4]);
    A0118626mapSquare(doorVertexes);
    A0118626mapSquare(doorVertexes1);
    
    //ceiling
    glBindTexture(GL_TEXTURE_2D, texSet[38]);
    A0118626mapSquare(ceilingVertexes);
    
    //pool tile
    glBindTexture(GL_TEXTURE_2D, texSet[22]);
    A0118626mapSquare(poolVerterexes);
    
    
    glDisable(GL_TEXTURE_2D);
    
    
    //////////////////////////
    
    //the window beside the door
    glPushMatrix();
    glColor4f(0.0, 0.8, 1.0,0.7);
    glBegin(GL_POLYGON);
    int n = 20;
    double r=0.5;
    for (int i = 0 ; i <= n; i++) {
        glVertex3d(-houseX*0.5+r*cos(2.0*M_PI*i/(double)n), r*sin(i*2.0/(double)n*M_PI)+roofHeight+0.5*(houseY-roofHeight), houseZ+0.01);
    }
    glEnd();
    
    glColor4d(1, 1, 1, 0.5);
    glPointSize(20.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0 ; i <= n; i++) {
        glVertex3d(-houseX*0.5+r*cos(2.0*M_PI*i/(double)n), r*sin(i*2.0/(double)n*M_PI)+roofHeight+0.5*(houseY-roofHeight), houseZ);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(-houseX*0.5, roofHeight+0.5*(houseY-roofHeight)+r, houseZ+0.01);
    glVertex3d(-houseX*0.5, roofHeight+0.5*(houseY-roofHeight)-r, houseZ+0.01);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(-houseX*0.5-r, roofHeight+0.5*(houseY-roofHeight), houseZ+0.01);
    glVertex3d(-houseX*0.5+r, roofHeight+0.5*(houseY-roofHeight), houseZ+0.01);
    glEnd();
    glPopMatrix();

    ///////////////////
    
    
    
    
  
    
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    
    //pool
    glColor4f(0.25, 0.5, 1.0,0.7);
    glBegin(GL_POLYGON);
    glVertex3d(-houseX,houseY,houseZ);
    glVertex3d(-houseX,houseY,-houseZ);
    glVertex3d(houseX,houseY,-houseZ);
    glVertex3d(houseX,houseY,houseZ);
    glEnd();
    
    //glasses of pool
    glPushMatrix();
    
    glBegin(GL_QUADS);
     glColor3f(0.25, 0.5, 1.0);
    glVertex3d(-houseX, houseY, -houseZ);
     glVertex3d(houseX, houseY, -houseZ);
    glColor4f(1.0, 1.0, 1.0, 0.2);
     glVertex3d(houseX, poolHeight, -houseZ);
    glVertex3d(-houseX, poolHeight, -houseZ);
   

     glColor3f(0.25, 0.5, 1.0);
    glVertex3d(-houseX, houseY, houseZ);
    glVertex3d(houseX, houseY, houseZ);
     glColor4f(1.0, 1.0, 1.0, 0.2);
     glVertex3d(houseX, poolHeight, houseZ);
    glVertex3d(-houseX, poolHeight, houseZ);
   
    
    glColor3f(0.25, 0.5, 1.0);
    glVertex3d(houseX, houseY, -houseZ);
    glVertex3d(houseX, houseY, houseZ);
    glColor4f(1.0, 1.0, 1.0, 0.2);
    glVertex3d(houseX, poolHeight, houseZ);
    glVertex3d(houseX, poolHeight, -houseZ);
    
    glColor3f(0.25, 0.5, 1.0);
    glVertex3d(-houseX, houseY, -houseZ);
    glVertex3d(-houseX, houseY, houseZ);
    glColor4f(1.0, 1.0, 1.0, 0.2);
    glVertex3d(-houseX, poolHeight, houseZ);
     glVertex3d(-houseX, poolHeight, -houseZ);
    
    glEnd();
    glPopMatrix();
    
    glDisable(GL_BLEND);
    
    glPopMatrix();
    
   
    
    glPopMatrix();
    
    
}

