#include<iostream>
#include<GL/glut.h>
#include<cstdlib>

using namespace std;

int x1,y1,x2,y2;

void myinit(){
	glClearColor(0,0,0,1);
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

// DDA ALGORITHM

void draw_pixel(float x, float y){
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}

void DDA(int x1,int y1,int x2,int y2) {
	int dx,dy,step,i;
	float incx,incy,x,y;

	dx=x2-x1;
	dy=y2-y1;

	if(abs(dx)>abs(dy)){
		step=abs(dx);
	}
	else {
		step=abs(dy);
	}

	incx = (float) dx/step;
	incy = (float) dy/step;

	x=x1;
	y=y1;

	draw_pixel(x,y);

	for(i=1;i<step;i++) {
		x += incx;
		y += incy;
		draw_pixel(x,y);
	}
}


void display(){
//	glLineWidth(3);
//	glPointSize(2);
	glClear(GL_COLOR_BUFFER_BIT);
////	axis();
//    glColor3f(1,0,0);
//	glBegin(GL_LINE_LOOP);
//		glVertex2i(400,600);
//		glVertex2i(600,200);
//		glVertex2i(200,200);
//	glEnd();
	glFlush();
}

void mouse(int btn,int state,int x1,int y1){
	if(btn == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			axis();
			glColor3f(0.5,1.0,1.0);
			DDA(x1+400,y1+400,x2+400,y2+400);
			glFlush();
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
	glutCreateWindow("DDA");
	
	myinit();
	
	//callback function
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;				
}
