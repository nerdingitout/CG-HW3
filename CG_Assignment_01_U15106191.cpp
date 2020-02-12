/// CG HW 1 ///
/// Student ID: U15106191   Student name: Masa Hilal ///
#include <iostream>
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>

using namespace std;

const int screenWidth = 640;
const int screenHeight = 480;

int whichButton = -1;

int num_clicks = 0;
int mX1, mY1, mX2, mY2;

string point="GL_POINTS";
float stepSize1= 0.1, stepSize2=1.0, stepSize=stepSize1;

float R1=1,G1=0,B1=0,R2=0,G2=1,B2=0;

int viewportWidth=640, viewportHeight=480;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // set white background color


	glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color

	glPointSize(3.0);
	glLineWidth(2.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glViewport(0,0,viewportWidth,viewportHeight);

}

///draw sin/cos graphs function
void drawGraphs(){
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	if(point=="GL_LINE_STRIP"){
        //cosine segment
        glColor3d(R1, G1, B1); //Set the color to red
        glBegin(GL_POINTS);
        for (double x = -6.28; x <= 6.28; x = x + stepSize)
        {
            double y = cos(x);

            double dx = (6.28+x)*screenWidth/12.56;
            double dy = (1.2+y)*screenHeight/2.4;

            glVertex2d(dx, dy);
            }
        glEnd();

        //sine segment
        glColor3d(R2, G2, B2); //set the color to green
        glBegin(GL_POINTS);
        for (double x = -6.28; x <= 6.28; x = x + stepSize)
        {
            double y = sin(x);

            double dx = (6.28+x)*screenWidth/12.56;
            double dy = (1.2+y)*screenHeight/2.4;

            glVertex2d(dx, dy);
        }
        glEnd();
	}
	else if(point=="GL_POINTS"){
        //cosine segment
        glColor3d(R1, G1, B1); //Set the color to red
        glBegin(GL_LINE_STRIP);
        for (double x = -6.28; x <= 6.28; x = x + stepSize)
        {
            double y = cos(x);

            double dx = (6.28+x)*screenWidth/12.56;
            double dy = (1.2+y)*screenHeight/2.4;

            glVertex2d(dx, dy);
        }
        glEnd();
        //sine segment
        glColor3d(R2, G2, B2); //set the color to green
        glBegin(GL_LINE_STRIP);
        for (double x = -6.28; x <= 6.28; x = x + stepSize)
        {
            double y = sin(x);

            double dx = (6.28+x)*screenWidth/12.56;
            double dy = (1.2+y)*screenHeight/2.4;

            glVertex2d(dx, dy);
        }
        glEnd();
    }
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    drawGraphs();

	if (num_clicks == 1)
	{
		glBegin(GL_POINTS);
		glVertex2d(mX1, mY1);
		glEnd();
	}
	else if (num_clicks == 2)
	{
	    glColor3d(0, 0, 1); //set the color to green

		glBegin(GL_LINE_STRIP);
		glVertex2d(mX1, mY1);
		glVertex2i(mX2, mY1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2d(mX1, mY1);
		glVertex2d(mX1, mY2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2d(mX2, mY1);
		glVertex2d(mX2, mY2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2d(mX1, mY2);
		glVertex2d(mX2, mY2);
		glEnd();
		}

	glFlush(); // send all output to display
}


void myKeyboard(unsigned char key, int x, int y)
{
    if(key=='c'){
        cout<<"c is pressed"<<endl;
        if(R1==1 && G1==0 && R2==0&& G2==1){
            R1=0;
            G1=1;
            R2=1;
            G2=0;
        }
        else if(R1==0 && G1==1 && R2==1&& G2==0){
            R1=1;
            G1=0;
            R2=0;
            G2=1;
        }
    }
	if(key=='s'){
	    cout<<"s is pressed"<<endl;
    if(stepSize==stepSize1){
        stepSize=stepSize2;
        cout<<stepSize<<endl;
    }
    else if(stepSize==stepSize2){
        stepSize=stepSize1;
        cout<<stepSize<<endl;
    }

	}
	if(key=='p'){
        cout<<"p is pressed"<<endl;
        ///*if GLUT_LINE_STRIP change to GLUT_POINTS, and do the other way round
       if(point=="GL_POINTS")
        point="GL_LINE_STRIP";
       else if(point=="GL_LINE_STRIP")
        point="GL_POINTS";
       cout<<point<<endl;
	}
    glutPostRedisplay();

}

void myMouse(int button, int state, int x, int y)
{
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            cout << "Left button pressed" << endl;
            cout << "Location: " << x << " " << y << endl;

            y = screenHeight - y;

            if (num_clicks == 0)
            {
                mX1 = x;
                mY1 = y;
                num_clicks++;
            }
            else if (num_clicks == 1)
            {
                mX2 = x;
                mY2 = y;
                num_clicks++;
            }
        }
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
            num_clicks=0;
            mX1=0;
            mY1=0;
            mX2=screenWidth;
            mY2=screenHeight;
        }

	glutPostRedisplay();
}

void myResize(int newWidth, int newHeight)
{
	if(num_clicks==1){
	    cout<<mX1<<endl<<mX2<<endl<<mY1<<endl<<mY2<<endl;
	    viewportHeight=abs(mX2-mX1);
	    viewportWidth=abs(mY1-mY2);
    }
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE); // set display mode

	glutInitWindowSize(screenWidth, screenHeight);     // set window size

	glutInitWindowPosition(100, 100); // set window position on screen

	glutCreateWindow("HW1_U15196191"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw function

	glutMouseFunc(myMouse);		//register the mouse click

	glutKeyboardFunc(myKeyboard); //register the keyboard

	glutReshapeFunc(myResize);

	myInit();

	glutMainLoop();      // go into a perpetual loop

	return 0;
}

