
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define GL_SILENCE_DEPRECATION
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int sh = 600, sw = 1000;

typedef struct {
	float x;
	float y;
}Point2D;

Point2D rc = { 100,100 };

int rw = 20, rang = 0, rzoom = 1;

Point2D translate(Point2D p, float tx, float ty) {
	Point2D ptemp;
	//.....write the equations for translation

	ptemp.x = p.x + tx;//Calculate the point here
	ptemp.y = p.y + ty;//Calculate the point here

	return ptemp;
}

Point2D rotate_arb(Point2D p, Point2D piv, double ang) { // Rotating about a pivot
	Point2D ptemp;
	ang = ang * 3.14159265359 / (double)180.0;   //angle in radians

	double ac = cos(ang);
	double as = sin(ang);

	ptemp.x = (p.x * ac) - (p.y * as) - (piv.x * ac) + (piv.y * as) + piv.x;//Calculate the point here
	ptemp.y = (p.x * as) + (p.y * ac) - (piv.x * as) - (piv.y * ac) + piv.y;//Calculate the point here

	return ptemp;
}

Point2D scale_arb(Point2D p, Point2D piv, int sf) {
	Point2D ptemp;
	ptemp.x = (p.x * sf) + piv.x - (sf * piv.x);//Calculate the point here
	ptemp.y = (p.y * sf) + piv.y - (sf * piv.y);//Calculate the point here
	return ptemp;
}


void init(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, sw, 0, sh);
	glViewport(0, 0, sw, sh);

}

void drawBlock(Point2D center, int width, int ang, int zoom) {
	
	Point2D p1, p2, p3, p4;
	
		p1.x = center.x - width / 2; 	p1.y = center.y - width / 2;
		p2.x = center.x - width / 2; 	p2.y = center.y + width / 2;
		p3.x = center.x + width / 2; 	p3.y = center.y + width / 2;
		p4.x = center.x + width / 2; 	p4.y = center.y - width / 2;

		//Scale the points p1, p2, p3, and p4;
		p1 = scale_arb(p1, center, zoom);
		p2 = scale_arb(p2, center, zoom);
		p3 = scale_arb(p3, center, zoom);
		p4 = scale_arb(p4, center, zoom);

		//Rotate the points p1, p2, p3, and p4;
		p1 = rotate_arb(p1, center, rang);
		p2 = rotate_arb(p2, center, rang);
		p3 = rotate_arb(p3, center, rang);
		p4 = rotate_arb(p4, center, rang);
	
		glBegin(GL_POLYGON);
		glVertex2i(p1.x, p1.y);
		glVertex2i(p2.x, p2.y);
		glVertex2i(p3.x, p3.y);
		glVertex2i(p4.x, p4.y);
		glEnd();
	
}

/* Callback functions for GLUT */

/* Draw the window - this is where all the GL actions are */
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 0.0);
	drawBlock(rc, rw, rang, rzoom);

	glFlush();

  return;
}

/* Called when window is resized,
   also when window is first created,
   before the first call to display(). */


void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:
		rc = translate(rc, -rw, 0);
		break;
	case GLUT_KEY_RIGHT:
		rc = translate(rc, rw, 0);
		break;
	case GLUT_KEY_UP:
		rc = translate(rc, 0, rw);
		break;
	case GLUT_KEY_DOWN:
		rc = translate(rc, 0, -rw);
		break;
	default: return;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		rzoom += 1;
		break;
	case '-':
		rzoom -= 1;
		break;
	case 'R':
		rang += 10;
		break;
	case 'r':
		rang -= 10;
		break;
	case 'q':
		exit(EXIT_SUCCESS);
	case 'Q':
		exit(EXIT_SUCCESS);
	default: return;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
}

int
main(int argc, char *argv[])
{
  glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(sw, sh);
	glutCreateWindow("Rotating Square");

	init();

	glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);

	glutMainLoop();
	return(0);
}