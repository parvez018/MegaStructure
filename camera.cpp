//# include <windows.h> // uncomment it if running from Code Blocks or command line
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include <GL/glut.h>

#define pi 2*acos(0.0)

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

struct point
{
	double x, y, z;
};

// draws the axes
void drawAxes()
{
	if (drawaxes == 1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES); {
			glVertex3f(100, 0, 0);
			glVertex3f(-100, 0, 0);
			glVertex3f(0, -100, 0);
			glVertex3f(0, 100, 0);
			glVertex3f(0, 0, 100);
			glVertex3f(0, 0, -100);
		}
		glEnd();
	}
}

// draws grid along X-Y plane
void drawGrid()
{
	int i;
	if (drawgrid == 1)
	{
		glColor3f(0.6, 0.6, 0.6); // grey
		glBegin(GL_LINES); {
			for (i = -8; i <= 8; i++) {
				if (i == 0)
					continue; // SKIP the MAIN axes

				// lines parallel to Y-axis
				glVertex3f(i * 10, -90, 0);
				glVertex3f(i * 10, 90, 0);

				// lines parallel to X-axis
				glVertex3f(-90, i * 10, 0);
				glVertex3f(90, i * 10, 0);
			}
		}
		glEnd();
	}
}

// draws a square on the X-Y plane
void drawSquare(float a)
{
	glBegin(GL_QUADS); {
		glVertex3f(a, a, 0);
		glVertex3f(a, -a, 0);
		glVertex3f(-a, -a, 0);
		glVertex3f(-a, a, 0);
	}
	glEnd();
}

// draws a half sphere over the X-Y plane
void drawsphere(float radius, int slices, int stacks)
{
	struct point points[100][100];
	int i, j;
	double h, r;
	for (i = 0; i <= stacks; i++)
	{
		h = radius*sin(((double)i / (double)stacks)*(pi / 2));
		r = sqrt(radius*radius - h*h);
		for (j = 0; j <= slices; j++)
		{
			points[i][j].x = r*cos(((double)j / (double)slices) * 2 * pi);
			points[i][j].y = r*sin(((double)j / (double)slices) * 2 * pi);
			points[i][j].z = h;
		}
	}
	for (i = 0; i < stacks; i++)
	{
		for (j = 0; j < slices; j++)
		{
			glColor3f((double)i / (double)stacks, (double)i / (double)stacks, (double)i / (double)stacks);
			glBegin(GL_QUADS); {
				glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
				glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
				glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
				glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
			}
			glEnd();
		}
	}
}

// keyboard key listener
void keyboardListener(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		drawgrid = 1 - drawgrid;
		break;

	default:
		break;
	}
}

// special key listener
void specialKeyListener(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:		// down arrow key
		cameraHeight -= 3.0;
		break;
	case GLUT_KEY_UP:		// up arrow key
		cameraHeight += 3.0;
		break;

	case GLUT_KEY_RIGHT:
		cameraAngle += 0.03;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle -= 0.03;
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}

// mouse listener
void mouseListener(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			drawaxes = 1 - drawaxes;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}

// the main display function
void display()
{
	// clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set-up camera here
	// load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	// initialize the matrix
	glLoadIdentity();

	// now give three info
	// 1. where is the camera (viewer)?
	// 2. where is the camera looking?
	// 3. Which direction is the camera's UP direction?

	// gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(100 * cos(cameraAngle), 100 * sin(cameraAngle), cameraHeight, 0, 0, 0, 0, 0, 1);
	// gluLookAt(0,-1,150,	0,0,0,	0,0,1);


	// again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	// add objects from here

	drawAxes();
	drawGrid();

	// ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

// animate function: is called after display
void animate()
{
	//codes for any changes in Models, Camera
	angle += 0.05;

	// Do NOT remove this line
	glutPostRedisplay();
}

// initialize OpenGL
void init()
{
	// codes for initialization
	drawgrid = 0;
	drawaxes = 1;
	cameraHeight = 100.0;
	cameraAngle = 1.0;
	angle = 0;

	// clear the screen
	glClearColor(0, 0, 0, 0);

	// set-up projection here
	// load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	// initialize the matrix
	glLoadIdentity();

	// give PERSPECTIVE parameters
	gluPerspective(80, 1, 1, 10000.0);
	// field of view in the Y (vertically)
	// aspect ratio that determines the field of view in the X direction (horizontally)
	// near distance
	// far distance
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	// Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program"); // enter window title here

	init();

	glEnable(GL_DEPTH_TEST);	// enable Depth Testing

	glutDisplayFunc(display);	// display callback function
	glutIdleFunc(animate);		// what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		// The main loop of OpenGL

	return 0;
}
