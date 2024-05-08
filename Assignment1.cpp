#include<GL/glut.h>
#include<cstdlib>
#include<iostream>
using namespace std;

int x1, y1, x2, y2;
bool first = true;
bool lineDrawn = false;
int lineType = 0; 
int lineAlgo = 0;

void draw_pixel(float x, float y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void myInit() {
    glClearColor(0,0,0,0);
    glPointSize(3);
    glViewport(0,0,800,800);
    gluOrtho2D(0,800,0,800);
}

void DDA(int x1, int y1, int x2, int y2, int lineType) {
    int dx, dy, step, i;
    float incx, incy, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        step = abs(dx);
    }
    else {
        step = abs(dy);
    }

    incx = (float)dx / step;
    incy = (float)dy / step;

    x = x1;
    y = y1;

    draw_pixel(x, y);

    switch (lineType) {
        case 0: // Simple Line
            for (i = 1; i < step; i++) {
                x += incx;
                y += incy;
                draw_pixel(x, y);
            }
            break;
        case 1: // Dotted Line
            for (i = 1; i < step; i++) {
                x += incx;
                y += incy;
                if (i % 5 == 0)
                    draw_pixel(x, y);
            }
            break;
        case 2: // Dashed Line
            for (i = 1; i < step; i++) {
                x += incx;
                y += incy;
                if (i % 10 < 5)
                    draw_pixel(x, y);
            }
            break;
        case 3: // Solid Line
            glLineWidth(10);
            glBegin(GL_LINE_LOOP);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glEnd();
            glFlush();
            break;
        default:
            break;
    }
}

void bres_line(int x1, int y1, int x2, int y2, int lineType) {
    int dx, dy, x, y, e, i, incx, incy, inc1, inc2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if (x2 >= x1) {
        incx = 1;
    } else {
        incx = -1;
    }
    if (y2 >= y1) {
        incy = 1;
    } else {
        incy = -1;
    }

    x = x1;
    y = y1;

    switch (lineType) {
        case 0: // Simple Line
            for (i = 0; i <= dx; i++) {
                draw_pixel(x, y);
                x += incx;
                e += 2 * dy;
                if (e >= 0) {
                    y += incy;
                    e -= 2 * dx;
                }
            }
            break;
        case 1: // Dotted Line
            for (i = 1; i <= dx; i++) {
                if (i % 5 == 0)
                    draw_pixel(x, y);
                x += incx;
                e += 2 * dy;
                if (e >= 0) {
                    y += incy;
                    e -= 2 * dx;
                }
            }
            break;
        case 2: // Dashed Line
            for (i = 1; i <= dx; i++) {
                if (i % 10 < 5)
                    draw_pixel(x, y);
                x += incx;
                e += 2 * dy;
                if (e >= 0) {
                    y += incy;
                    e -= 2 * dx;
                }
            }
            break;
        case 3: // Solid Line
            glLineWidth(10);
            glBegin(GL_LINE_LOOP);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glEnd();
            glFlush();
            break;
        default:
            break;
    }
}

void line(int x1, int y1, int x2, int y2) {
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void axis() {
    glColor3f(0,1.0,1.0);

    line(0,400,800,400);
    line(400,0,400,800);

    for (int x = 0; x <= 800; x += 10) {
    	glColor3f(1.0,1.0,1.4);
        line(x,397,x,403);
    }

    for (int y = 0; y <= 800; y += 10) {
    	glColor3f(1.0,1.0,1.4);
        line(397,y,403,y);
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
       axis();
    glFlush();
}

void menu(int value) {
    lineType = value;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (first) {
                axis();
                glFlush();
                first = false;
            }
            else {
                axis();
                glColor3f(1.0f, 0.5f, 0.0f);
                switch(lineAlgo) {
                    case 0:
                        // Draw the pentagon using DDA algorithm
                        DDA(x1 + 400, y1 + 400, x2 + 400, y2 + 400, lineType); 
                        DDA(x1 + 400, y2 + 400, x2 + 400, y1 + 400, lineType); 
//                        DDA(x2 + 550, y2 + 600, x1 + 400, y1 + 700, lineType); // Top right
//                        DDA(x1 + 400, y1 + 700, x1 + 250, y1 + 600, lineType); // Top left
//                        DDA(x1 + 250, y1 + 600, x1 + 400, y1 + 400, lineType); // Left side
                        break;
                    case 1:
                        // Draw the pentagon using Bresenham algorithm
                        bres_line(x1 + 400, y1 + 400, x2 + 400, y2 + 400, lineType); // Base
                        bres_line(x1 + 400, y2 + 400, x2 + 400, y1 + 400, lineType); // Right side
//                        bres_line(x2 + 550, y2 + 600, x1 + 400, y1 + 700, lineType); // Top right
//                        bres_line(x1 + 400, y1 + 700, x1 + 250, y1 + 600, lineType); // Top left
//                        bres_line(x1 + 250, y1 + 600, x1 + 400, y1 + 400, lineType); // Left side
                        break;
                    default:
                        break;              
                }
                glFlush();
                lineDrawn = true;
            }
        }
    }
}

  

int main(int argc, char **argv) {
	
	cout << "Which algorithm to use (0 for DDA, 1 for Bresenham): ";
	cin >> lineAlgo;
	
    cout << "Enter starting point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter ending point (x2 y2): ";
    cin >> x2 >> y2;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(800,150);
    glutCreateWindow("DDA Line");
    myInit();
    glutDisplayFunc(myDisplay);

    // menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 0);
    glutAddMenuEntry("Dotted Line", 1);
    glutAddMenuEntry("Dashed Line", 2);
    glutAddMenuEntry("Solid Line", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

