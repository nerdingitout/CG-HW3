/// CG_Assignment 3 ///
/// Done by student Masa Hilal, ID# U15106191 ///

#include <iostream>
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>
#include "vector.h"
#define PI 3.14159265359

using namespace std;

const int screenWidth = 640;
const int screenHeight = 480;
Point points[4];
int num_clicks = 0;
float stepSize= 0.1;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
glClearColor(1.0,1.0,1.0,0.0);       // set white background color
glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color
glPointSize(4.0);       // a ‘dot’ is 4 by 4 pixels
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{

glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

	// Write your drawing code here

	//Set the color to red
	for(int i=0; i<3; i++){
		glColor3d(1, 0, 0);
		glBegin(GL_POINTS);
		glVertex2d(points[i].x, points[i].y); //C
		glEnd();
    }
    /// Vectors
    Vector AB=points[1]-points[0]; //vector between two point
    Vector BC=points[2]-points[1];
    Vector AC=points[2]-points[0];

    if(num_clicks>1){
        ///first circle ABC
        Point center= points[0]+AB/2;
        Vector R=center-points[0];
        int rad=sqrt(pow(R.x,2)+pow(R.y,2));
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            for(float i=0; i<=2*PI; i+=stepSize){
                float x=rad*cos(i)+center.x, y=rad*sin(i)+center.y;
                glVertex2d(x,y);
            }
        glEnd();
        }
    if(num_clicks==3){

        //draw point D
        glBegin(GL_POINTS);
            glColor3d(1,0,0);
            glVertex2d(points[3].x, points[3].y);
        glEnd();

        /// Vectors
        Vector DA=points[0]-points[3];
        Vector BD=points[3]-points[1];
        Vector CD=points[3]-points[2];
        Vector DB=points[1]-points[3];

        /// Perp
        Vector perpAB = perp(AB);
        Vector perpAC = perp(AC);
        Vector perpBC = perp(BC);

        ///second circle ABD
        Point center1 = points[0]+ 0.5*(AB + perpAB*((DA.x*BD.x+DA.y*BD.y+DA.z*BD.z)/(perpAB.x*DA.x+perpAB.y*DA.y+perpAB.z*DA.z))); //AB BD DA

        Vector R1 = center1 - points[0];
        int radABD=sqrt(pow(R1.x,2)+ pow(R1.y,2));

        glBegin(GL_LINE_LOOP);
            glColor3f(0,0,1);
            for(float i=0; i<=2*PI; i+=stepSize){
                float x1=radABD*cos(i)+center1.x, y1=radABD*sin(i)+center1.y;
                glVertex2d(x1,y1);
            }
        glEnd();

        ///third circle ACD
        Point center2= points[0]+ 0.5*(AC + perpAC*((DA.x*CD.x+DA.y*CD.y+DA.z*CD.z)/(perpAC.x*DA.x+perpAC.y*DA.y+perpAC.z*DA.z))); //AC CD DA
        Vector R2=center2-points[0];
        int radACD=sqrt(pow(R2.x,2)+pow(R2.y,2));

        glBegin(GL_LINE_LOOP);
            for(float i=0; i<=2*PI; i+=stepSize){
                glColor3f(1,0,1);
                float x=radACD*cos(i)+center2.x, y=radACD*sin(i)+center2.y;
                glVertex2d(x,y);
            }
        glEnd();

        ///fourth circle BCD
        Point center3= points[1]+ 0.5*(BC + perpBC*((DB.x*CD.x+DB.y*CD.y+DB.z*CD.z)/(perpBC.x*DB.x+perpBC.y*DB.y+perpBC.z*DB.z))); //BC CD DB
        Vector R3=center3-points[1];
        int radBCD=sqrt(pow(R3.x,2)+pow(R3.y,2));

        glBegin(GL_LINE_LOOP);
            for(float i=0; i<=2*PI; i+=stepSize){
                glColor3f(0,1,0);
                float x=radBCD*cos(i)+center3.x, y=radBCD*sin(i)+center3.y;
                glVertex2d(x,y);
            }
        glEnd();
	}

	glFlush();                 // send all output to display
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "Left button pressed" << endl;
		cout << "Location: " << x << " " << y << endl;

		y = screenHeight - y;

		if (num_clicks==0)
		{
			points[num_clicks] = Point(x,y);
			num_clicks++;
		}
		else if (num_clicks == 1)
		{
			points[num_clicks] = Point(x,y);
			points[2]=Point(points[1].x, points[0].y);
			num_clicks++;
		}
		else if(num_clicks==2){
            points[3] = Point(x,y);
			num_clicks++;
		}
		if(num_clicks>3){
            num_clicks=0;
		}

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		cout << "Right button pressed" << endl;
		cout << "Location: " << x << " " << y << endl;
	}

	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int  main(int argc, char** argv)
{
glutInit(&argc, argv);          // initialize the toolkit
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
glutInitWindowSize(screenWidth,screenHeight);     // set window size
glutInitWindowPosition(100, 100); // set window position on screen
glutCreateWindow("HW3"); // open the screen window
glutDisplayFunc(myDisplay);     // register redraw function
glutMouseFunc(myMouse);		//register the mouse click
myInit();
glutMainLoop();      // go into a perpetual loop

return 0;
}




