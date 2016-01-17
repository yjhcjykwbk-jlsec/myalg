#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#define pi 3.1415926
#define GLfloat float
#define GLdouble double
#define GLint int
double c=pi/180.0;
double radius=150.0;
int w=500,h=500;
double angle=10.0;
double a=10.0;
void drawSphere(void)
{
	glViewport (0.0, 0.0, (GLsizei) w, (GLsizei) h);
	float theta,phir,phi,thetar,phir20;
	float x,y,z;
	for(phi=-90.0;phi<=90.0;phi+=a)
	{
		phir=c*phi;
		phir20=c*(phi+a);
		glPolygonMode(GL_FRONT,GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);  
		glFrontFace(GL_CCW); //éæ¶éä¸ºæ­£é¢
		//glBegin(GL_TRIANGLES);
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_TRIANGLE_STRIP);
		//glBegin(GL_TRIANGLE_FAN);
		//glBegin(GL_QUADS);
		//glBegin(GL_QUAD_STRIP);
		for(theta=-180.0;theta<=180.0;theta+=a)
		{
			thetar=c*theta;
			x=radius*sin(thetar)*cos(phir);
			y=radius*cos(thetar)*cos(phir);
			z=radius*sin(phir);
			glVertex3d(x,y,z);
			//glVertex3f(x,y,z);
			x=radius*sin(thetar)*cos(phir20);
			y=radius*cos(thetar)*cos(phir20);
			z=radius*sin(phir20);
			glVertex3d(x,y,z);
			//glVertex3f(x,y,z);
		}

		glEnd();
	}
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);  
	glFrontFace(GL_CCW); 
	//glBegin(GL_QUADS);
	//glBegin(GL_QUAD_STRIP);
	glBegin(GL_TRIANGLE_STRIP);
	//glBegin(GL_TRIANGLES);
	//glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_LINE_LOOP);
	//glBegin(GL_LINES);
	//glVertex3f(0.0,0.0,radius);
	glVertex3d(0.0,0.0,radius);
	double c80=c*90.0;
	z=radius*sin(c80);
	for(theta=-180.0;theta<=180.0;theta+=a)
	{
		thetar=c*theta;
		x=radius*sin(thetar)*cos(c80);
		y=radius*cos(thetar)*cos(c80);
		glVertex3d(x,y,z);
		//glVertex3f(x,y,z);
	}
	glEnd();
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);  
	glFrontFace(GL_CCW); 
	//glBegin(GL_QUADS);
	//glBegin(GL_QUAD_STRIP);
	glBegin(GL_TRIANGLE_STRIP);
	//glBegin(GL_TRIANGLES);
	//glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_LINE_LOOP);
	//glBegin(GL_LINES);
	glVertex3d(0.0,0.0,-radius);
	//Vertex3f(0.0,0.0,-radius);
	z=-radius*sin(c80);
	for(theta=-180.0;theta<=180.0;theta+=a)
	{
		thetar=c*theta;
		x=radius*sin(thetar)*cos(c80);
		y=radius*cos(thetar)*cos(c80);
		glVertex3d(x,y,z);
		//lVertex3f(x,y,z);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();

}

void reshape(GLsizei ww, GLsizei hh)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w,  0.0,(GLdouble)h, -w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	w=ww;
	h=hh;

}
void init(void)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, (GLdouble)w,  0.0,(GLdouble)h, -500, 500);
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	//glFlush();
}
void mouse(int btn,int state, int x,int y)
{
	//if(btn==GLUT_RIGHT_BUTTON &&state==GLUT_DOWN) exit(0);
	if(btn==GLUT_LEFT_BUTTON &&state==GLUT_DOWN) 
	{
		radius=radius+15.0;
		drawSphere();
		printf("time is :%d\n",glutGet(GLUT_ELAPSED_TIME));
	}
}

static void idle(void)
{
	glutPostRedisplay(); 
}
void display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glTranslated(250,250,0);
	glRotated(30,1,0,0);
	glRotated(60,0,1,0);
	glRotated(90,0,0,1);
	angle = 12500.0/glutGet(GLUT_ELAPSED_TIME);
	glRotated(angle,1,0,0);
	glutPostRedisplay();
	drawSphere();
	printf("time is :%d\n",glutGet(GLUT_ELAPSED_TIME));
}
void submenu(int id)
{


	switch(id)
	{
		case 1:
			exit(0);
			break;
		case 2:
			radius=radius+10.0;
			break;
		case 3:
			if(radius>1.0) radius=radius/2;
			break;
	}

}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Swkkkk");
	glutCreateMenu(submenu);
	glutAddMenuEntry("quit",1);
	glutAddMenuEntry("Increase radius",2);
	glutAddMenuEntry("Decrease radius",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();

	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	//glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}


