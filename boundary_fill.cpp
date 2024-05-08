#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int choice;

void my_init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,800,0,800);
}

void my_display()
{
	glLineWidth(3);
	glPointSize(2);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(400,600);
		glVertex2i(600,200);
		glVertex2i(200,200);
	glEnd();
	glFlush();	
}

void boundary_fill(int x, int y, float* b, float* f)
{
	float current[3];
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);
	
	if((current[0]!=b[0] || current[1]!=b[1] || current[2]!=b[2]) 
		&& (current[0]!=f[0] || current[1]!=f[1] || current[2]!=f[2]))
	{
		glColor3f(f[0],f[1],f[2]);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		glFlush();

		boundary_fill(x+2,y,b,f);
		boundary_fill(x-2,y,b,f);
		boundary_fill(x,y+2,b,f);
		boundary_fill(x,y-2,b,f);
	}
}

void mouse(int btn,int state, int x, int y)
{
	y=800-y;
	if(btn==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			float b[] = {1.0,0.0,0.0};
			float f[] = {0.0,1.0,0.0};

			boundary_fill(x,y,b,f);			
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(500,500);
	glutCreateWindow("Boundary Fill");
	cout<<"Click inside the triangle to fill the color using Boundary Fill"<<endl;
	glutDisplayFunc(my_display);
	glutMouseFunc(mouse);
	my_init();
	glutMainLoop();
	return 0;
}
