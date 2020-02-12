/// CG HW 2 ///
/// Student ID: U15106191   Student name: Masa Hilal ///

#include <iostream>
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>

using namespace std;

int screenWidth = 800;
int screenHeight = 600;

double zoomFactorX = 0.0;
double zoomFactorY = 0.0;

double zoomVPX = 0.0;
double zoomVPY = 0.0;

bool n=false;

double moveX = 0;
double moveY = 0;

double moveHX=0, moveHY=0;

double Wl = -10.0, Wr = 30.0, Wb = -10.0, Wt = 20.0;
int Vl = 0, Vr = 400, Vb = 0, Vt = 300;

int viewportWidth = Vr-Vl;
int viewportHeight = Vt-Vb;


int invertTemp=0;

void setupWindow(double left, double right, double bottom, double top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void drawHouse(int moveHX, int moveH)
{
	glColor3f(0.0, 1.0, 1.0);
	glRecti(-5+moveHX, -5+moveHY, 5+moveHX, 10+moveHY);

	glColor3f(0.0, 0.0, 1.0);
	glRecti(-2+moveHX, -5+moveHY, 2+moveHX, 5+moveHY);

	glColor3f(0.0, 1.0, 0.0);
	glRecti(5+moveHX, -5+moveHY, 20+moveHX, 10+moveHY);

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(-5+moveHX, 10+moveHY);
	glVertex2i(5+moveHX, 10+moveHY);
	glVertex2i(0+moveHX, 15+moveHY);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(0+moveHX, 15+moveHY);
	glVertex2i(5+moveHX, 10+moveHY);
	glVertex2i(20+moveHX, 10+moveHY);
	glVertex2i(15+moveHX, 15+moveHY);
	glEnd();
}


//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // set white background color
	glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color
	glPointSize(4.0);		       // a ‘dot’ is 4 by 4 pixels
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    if(n==false)
        setupWindow(Wl- zoomFactorX, Wr + zoomFactorX , Wb  - zoomFactorY, Wt+ zoomFactorY);

    if(n==true)
        setupWindow(Wl- zoomFactorX, Wr + zoomFactorX , Wb  + zoomFactorY, Wt- zoomFactorY);

    glViewport(Vl+moveX, Vb+moveY, (screenWidth/2)-(zoomVPX*4), (screenHeight/2)+(3*zoomVPY));


	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
									  // Write your drawing code here
    drawHouse(moveHX, moveHY);

    setupWindow(Wl, Wr, Wb,Wt);

	glLineWidth(3.0);

    glColor3d(1.0, 0.0, 1.0);

    glBegin(GL_LINE_STRIP);
        glVertex2i(Wl, Wb);
        glVertex2i(Wl, Wt);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(Wl, Wt);
        glVertex2i(Wr, Wt);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(Wr, Wt);
        glVertex2i(Wr, Wb);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(Wr, Wb);
        glVertex2i(Wl, Wb);
    glEnd();

    glutSwapBuffers();

	glFlush();		                 // send all output to display
}

void myMouse(int button, int state, int x, int y)
{

	glutPostRedisplay();
}

void myMovedMouse(int x, int y)
{
	glutPostRedisplay(); //Repaint the screen
}

void myKeyboard(unsigned char key, int x, int y)
{
	double aspect = 4.0 / 3.0;

	// pan the viewport
	if (key == 'a')
	{
		moveX = moveX - 10;
	}

	if (key == 'd')
	{
		moveX = moveX + 10;
	}

	if (key == 'w')
	{
		moveY = moveY + 10;
	}

	if (key == 's')
	{
		moveY = moveY - 10;
	}

	// pan the house
	if (key == 'i')
	{
		moveHY = moveHY + 1;
	}

	if (key == 'k')
	{
		moveHY = moveHY - 1;
	}

	if (key == 'j')
	{
		moveHX = moveHX - 1;
	}

	if (key == 'l')
	{
		moveHX = moveHX + 1;
	}

	// invert the house

	if(key =='n'){
        if(n==false)
            n=true;
        else if(n==true)
            n=false;
        invertTemp=Wt;
        Wt=Wb;
        Wb=invertTemp;
	}

	//zooming the viewport

	if(key=='e'){
	    zoomVPX = zoomVPX + 1;
	    zoomVPY = zoomVPY - 1;
	}
	if(key=='q'){
	    zoomVPX = zoomVPX - 1;
	    zoomVPY = zoomVPY + 1;

	}

	//zooming the worldwindow
	if (key == 'u')
	{
		zoomFactorX = zoomFactorX - 0.4;
		zoomFactorY = zoomFactorY - 0.3;
	}

	if (key == 'o')
	{
		zoomFactorX = zoomFactorX + 0.4;
		zoomFactorY = zoomFactorY + 0.3;
	}



	glutPostRedisplay();
}

void myReshape(int _w, int _h)
{
	screenWidth = _w;
	screenHeight = _h;

	double aspect = 4.0 / 3.0;

	if (screenWidth <= screenHeight)
	{
		viewportWidth = screenWidth;
		viewportHeight = screenWidth / aspect;
	}
	else
	{
		viewportHeight = screenHeight;
		viewportWidth = screenHeight * aspect;
	}

	cout << "New Width: " << viewportWidth << endl;
	cout << "New height: " << viewportHeight << endl;

	glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE); // set display mode
	glutInitWindowSize(screenWidth, screenHeight);     // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("My Graphics App"); // open the screen window
	glutDisplayFunc(myDisplay);     // register redraw function
	glutMouseFunc(myMouse);
	glutMotionFunc(myMovedMouse);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);

	myInit();
	glutMainLoop(); 		     // go into a perpetual loop

	return 0;
}
