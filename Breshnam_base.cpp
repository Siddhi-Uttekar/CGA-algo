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

// BRESENHAM CIRCLE

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenhamCircle(int r, int x1, int y1) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        setPixel(x1 + x, y1 + y);
        setPixel(x1 - x, y1 + y);
        setPixel(x1 + x, y1 - y);
        setPixel(x1 - x, y1 - y);
        setPixel(x1 + y, y1 + x);
        setPixel(x1 - y, y1 + x);
        setPixel(x1 + y, y1 - x);
        setPixel(x1 - y, y1 - x);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
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
			axis();
			glColor3f(0.5,1.0,1.0);
			bresenhamCircle(100, 550, 550);
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
	glutCreateWindow("Window");
	
	myinit();
	
	//callback function
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;				
}
