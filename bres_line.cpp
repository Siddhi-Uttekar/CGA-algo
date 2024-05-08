#include<GL/glut.h>
#include<cstdlib>
#include<iostream>
using namespace std;

int x1,y1,x2,y2;
bool first=true;

void draw_pixel(float x, float y){
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}

void myInit() {
	glClearColor(1.0,1.0,1.0,1.0);
	glPointSize(3);
	glViewport(0,0,800,800);
	gluOrtho2D(0,800,0,800);
}

void bres_line(int x1,int y1,int x2,int y2) {
	int dx,dy,x,y,e,i,incx,incy,inc1,inc2;

	dx=abs(x2-x1);
	dy=abs(y2-y1);

	if(x2>=x1){
		incx=1;
	}else{
		incx=-1;
	}
	if(y2>=y1){
		incy=1;
	}else{
		incy=-1;
	}

	x=x1;
	y=y1;

	if(dx>dy){
		draw_pixel(x,y);
		e=2*dy-dx;
		inc1=2*(dy-dx);
		inc2=2*dy;
		for(i=0;i<dx;i++){
			if(e>=0){
				y+=incy;
				e+=inc1;
			}else{
				e+=inc2;
			}
			x+=incx;
			draw_pixel(x,y);
		}
	}else{
		draw_pixel(x,y);
		e=2*dx-dy;
		inc1=2*(dx-dy);
		inc2=2*dx;
		for(i=0;i<dy;i++){
			if(e>=0){
				x+=incx;
				e+=inc1;
			}else{
				e+=inc2;
			}
			y+=incy;
			draw_pixel(x,y);
		}
	}
}

void line(int x1,int y1,int x2,int y2) {
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
	glFlush();
}

void axis(){
	glColor3f(0.0,0.0,0.0);

	line(0,400,800,400);
	line(400,0,400,800);

	for(int x=0;x<=800;x+=20) {
		line(x,390,x,410);
	}

	for(int y=0;y<=800;y+=20) {
		line(390,y,410,y);
	}
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			if(first){
				axis();
				glFlush();
				first=false;
			}
			else{
				axis();
				glColor3f(1.0,0.0,0.0);
				bres_line(x1+400,y1+400,x2+400,y2+400);
				glFlush();
			}
		}
	}
}

int main(int argc, char **argv)
{
	cout<<"Enter starting and ending points"<<endl;
	cin>>x1>>y1>>x2>>y2;	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(500,500);
	glutCreateWindow("DDA Line");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}