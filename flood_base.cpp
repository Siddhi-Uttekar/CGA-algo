#include<iostream>
#include<GL/glut.h>
#include<cstdlib>

using namespace std;

int x1,y1,x2,y2;

void myinit(){
	glClearColor(1,1,1,1);
//	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,800,0,800);
}

void line(int x1,int y1,int x2,int y2){
	
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
	glFlush();
}

void axis(){
	glColor3f(1,1,1);
	
	line(0,400,800,400);
	line(400,0,400,800);
}

void flood_fill(int x, int y, float* o, float* n)
{
	float current[3];
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);
	
	if(current[0]==o[0] && current[1]==o[1] && current[2]==o[2])
	{
		glColor3f(n[0],n[1],n[2]);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		glFlush();

		flood_fill(x+2,y,o,n);
		flood_fill(x-2,y,o,n);
		flood_fill(x,y+2,o,n);
		flood_fill(x,y-2,o,n);
	}
}

void display(){
	glLineWidth(3);
	glPointSize(2);
	glClear(GL_COLOR_BUFFER_BIT);
////	axis();
    glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(400,600);
		glVertex2i(600,200);
		glVertex2i(200,200);
	glEnd();
	glFlush();
//	glLineWidth(3);
//	glPointSize(2);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_LINE_LOOP);
//		glColor3f(1,0,0);
//		glVertex2i(400,600);
//		glColor3f(0,1,0);
//		glVertex2i(600,200);
//		glColor3f(0,0,1);
//		glVertex2i(200,200);
//	glEnd();
//	glFlush();
}

void mouse(int btn,int state,int x,int y){
	y=800-y;
	if(btn == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			float o[] = {1.0,1.0,1.0};
			float n[] = {0.0,1.0,0.0};

			flood_fill(x,y,o,n);
		}
	}
}

int main(int c,char **v){
	//initilize
	glutInit(&c,v);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	
	//window creation
	glutInitWindowSize(800,800);
	glutInitWindowPosition(800,150);
	glutCreateWindow("Window");
	
	myinit();
	
	//callback function
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;				
}
