#include<GL/glut.h>
#include <cstdlib>
#include<iostream>
using namespace std;

int r,x,y,x1,y1;
bool first=true;
int colorChoice = 1; // Default color choice

void myInit(){
    glClearColor(0,0,0,0);
    glPointSize(3);
    glViewport(0,0,700,700); 
    gluOrtho2D(0,700,0,700); 
}

void setpixel(GLint x, GLint y)
{
    if(colorChoice==1)
    {
        glColor3f(1.0,0.0,0.0);//red
        //Center of color red
        glBegin(GL_POINTS);
                   glVertex2i(x1+350, y1+350); 
        glEnd();
    }
    else if(colorChoice==2)
    {
        glColor3f(0.0,1.0,0.0);//green
        //center plot
        glBegin(GL_POINTS);
            glVertex2i(x1+350, y1+350); 
        glEnd();
    }
    else if(colorChoice==3)
    {
        glColor3f(1.0,0.5,0.0);//orange
//        center
        glBegin(GL_POINTS);
            glVertex2i(x1+350, y1+350); 
        glEnd();
    }
    else if(colorChoice==4)
    {
        glColor3f(0.5,1.0,1.0);//cyan
        //center plot
        glBegin(GL_POINTS);
            glVertex2i(x1+350, y1+350); 
        glEnd();
    }
    else if(colorChoice==5)
    {
        glColor3f(1.0,0.0,1.0);//purple
        //center plot
        glBegin(GL_POINTS);
            glVertex2i(x1+350, y1+350); 
        glEnd();
    }

    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void draw_circ(int x, int y, int x1, int y1)
{
    setpixel(x1 + x, y1 + y);
    setpixel(x1 - x, y1 + y);
    setpixel(x1 + x, y1 - y);
    setpixel(x1 - x, y1 - y);
    setpixel(x1 - y, y1 + x);
    setpixel(x1 - y, y1 - x);
    setpixel(x1 + y, y1 + x);
    setpixel(x1 + y, y1 - x);

}

void bres_circ(int r,int x1,int y1){
    int d;
    d=3-2*r;

    x=0;
    y=r;

    do {
        draw_circ(x,y,x1,y1);

        if(d<0) {
            x++;
            d=d+4*x+6;
        } else {
            d=d+4*(x-y)+10;
            x++;
            y--;
        }
    } while (x<=y);
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
    glColor3f(0.0,1.0,1.0);

    line(0,350,700,350);
    line(350,0,350,700); 

    for(x=0;x<=700;x+=15) { 
        line(x,345,x,355); 
    }

    for(y=0;y<=700;y+=15) { 
        line(345,y,355,y); 
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
                glPointSize(3.0);
                glColor3f(1.0, 0.0, 0.0);
				for(int i=350 ; i<450 ; i=i+10){
                    bres_circ(r,x1+i,y1+i);	
				}  
                glFlush();
            }
        }
    }
}

void colorMenu(int value) {
    colorChoice = value;
}

void createMenu() {
    glutCreateMenu(colorMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("orange", 3);
    glutAddMenuEntry("Cyan",4);
    glutAddMenuEntry("Purple",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    cout<<"Enter the radius and centre coordinates of the circle"<<endl;
    cout<<"r = ";
    cin>>r;
    cout<<"x1 = ";
    cin>>x1;
    cout<<"Y1 = ";
    cin>>y1;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100,200);
    glutCreateWindow("Bresenham Circle");
    myInit();
    createMenu(); // menu
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 1;
}

