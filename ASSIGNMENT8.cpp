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

int WinWidth = 1000, WinHeight = 1000;

typedef struct { float x; float y; }Point2D;
typedef struct { float x; float y; float z; }Point3D;
float sff = 1;
Point3D A, B, C, D, E, F, G, H;	// Vertices of the cube

void InitCube() {
	A.x = -20; A.y = -20; A.z = 20;
	B.x = 20; B.y = -20; B.z = 20;
	C.x = 20; C.y = 20; C.z = 20;
	D.x = -20; D.y = 20; D.z = 20;

	E.x = -20; E.y = -20; E.z = -20;
	F.x = 20; F.y = -20; F.z = -20;
	G.x = 20; G.y = 20; G.z = -20;
	H.x = -20; H.y = 20; H.z = -20;
}

Point2D Project_OrthoXY(Point3D p) {  // Orthographic parallel projection on 
	Point2D p2;
	p2.x = p.x;
	p2.y = p.y;
	return p2;
}


Point3D translate3D(Point3D p, float tx, float ty, float tz) {
	Point3D tp3;
	tp3.x = p.x + tx;
	tp3.y = p.y + ty;
	tp3.z = p.z + tz;


	return tp3;
}

Point3D rotate_z(Point3D p, Point3D piv, float ang) {
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	double ac = cos(ang);
	double as = sin(ang);
	pr.x = (p.x * ac) - (p.y * as) - (piv.x * ac) + (piv.y * as) + piv.x;
	pr.y = (p.x * as) + (p.y * ac) - (piv.x * as) - (piv.y * ac) + piv.y;
	pr.z = p.z;

	return pr;
}

Point3D rotate_y(Point3D p,Point3D piv, float ang ) {
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	double ac = cos(ang);
	double as = sin(ang);
	pr.x = (p.x * ac) + (p.z * as) - (piv.x * ac) - (piv.z * as) + piv.x;
	pr.z = (p.z * ac) + (piv.x * as) - (p.x * as) - (piv.z * ac) + piv.z;
	pr.y = p.y;

	return pr;
}

Point3D rotate_x(Point3D p,Point3D piv, float ang) {
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;
	double ac = cos(ang);
	double as = sin(ang);
	pr.y = (p.y * ac) + (piv.z * as) - (p.z * as) - (piv.y * ac) + piv.y;
	pr.z = (p.y * as) + (p.z * ac) - (piv.z * ac) - (piv.y * as) + piv.z;
	pr.x = p.x;

	return pr;
}

Point3D scale(Point3D p, Point3D piv, float sf){
	Point3D pr;
	pr.x = (sf * p.x) + (piv.x) - (piv.x * sf);
	pr.y = (piv.y) - (sf * piv.y) + (sf * p.y);
	pr.z = (piv.z) - (sf * piv.z) + (sf * p.z);

	return pr;
}

void scaleBox(float zoom) {
	Point3D cog;
	
	

	cog.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	cog.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	cog.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;
	A = scale(A, cog, zoom);
	B = scale(B, cog, zoom);
	C = scale(C, cog, zoom);
	D = scale(D, cog, zoom);
	E = scale(E, cog, zoom);
	F = scale(F, cog, zoom);
	G = scale(G, cog, zoom);
	H = scale(H, cog, zoom);

	
}

void rotatebox_y(float ang) {
	Point3D cog;

	cog.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	cog.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	cog.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;
	A = rotate_y(A,cog, ang);
	B = rotate_y(B,cog, ang);
	C = rotate_y(C,cog, ang);
	D = rotate_y(D,cog, ang);
	E = rotate_y(E,cog, ang);
	F = rotate_y(F,cog, ang);
	G = rotate_y(G,cog, ang);
	H = rotate_y(H,cog, ang);


	glutPostRedisplay();
}

void rotatebox_x(float ang) {
	Point3D cog;

	cog.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	cog.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	cog.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;
	A = rotate_x(A,cog, ang);
	B = rotate_x(B,cog, ang);
	C = rotate_x(C,cog, ang);
	D = rotate_x(D,cog, ang);
	E = rotate_x(E,cog, ang);
	F = rotate_x(F,cog, ang);
	G = rotate_x(G,cog, ang);
	H = rotate_x(H,cog, ang);


	glutPostRedisplay();
}
void rotatebox_z(float ang) {
	Point3D cog;
	
	cog.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x)/8;
	cog.y = (A.y + B.y+ C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	cog.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;
	A = rotate_z(A,cog, ang);
	B = rotate_z(B,cog, ang);
	C = rotate_z(C,cog, ang);
	D = rotate_z(D,cog, ang);
	E = rotate_z(E,cog, ang);
	F = rotate_z(F,cog, ang);
	G = rotate_z(G,cog, ang);
	H = rotate_z(H,cog, ang);


	glutPostRedisplay();
}

void translate_x(int tx) {
	A = translate3D(A, tx,0,0);
	B = translate3D(B, tx, 0, 0);
	C = translate3D(C, tx, 0, 0);
	D = translate3D(D, tx, 0, 0);
	E = translate3D(E, tx, 0, 0);
	F = translate3D(F, tx, 0, 0);
	G = translate3D(G, tx, 0, 0);
	H = translate3D(H, tx, 0, 0);
}
void translate_y(int ty) {
	A = translate3D(A, 0, ty, 0);
	B = translate3D(B, 0, ty, 0);
	C = translate3D(C, 0, ty, 0);
	D = translate3D(D, 0, ty, 0);
	E = translate3D(E, 0, ty, 0);
	F = translate3D(F, 0, ty, 0);
	G = translate3D(G, 0, ty, 0);
	H = translate3D(H, 0, ty, 0);
}
void DrawCube() {
	Point2D Ap, Bp, Cp, Dp, Ep, Fp, Gp, Hp;

	
	Ap = Project_OrthoXY(A);
	Bp = Project_OrthoXY(B);
	Cp = Project_OrthoXY(C);
	Dp = Project_OrthoXY(D);
	Ep = Project_OrthoXY(E);
	Fp = Project_OrthoXY(F);
	Gp = Project_OrthoXY(G);
	Hp = Project_OrthoXY(H);

	//DRAWING BACK FACE
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(Ep.x, Ep.y); glVertex2i(Fp.x, Fp.y);	glVertex2i(Gp.x, Gp.y); glVertex2i(Hp.x, Hp.y);
	glEnd();

	//DRAWING FRONT FACE
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(Ap.x, Ap.y); glVertex2i(Bp.x, Bp.y);	glVertex2i(Cp.x, Cp.y); glVertex2i(Dp.x, Dp.y);
	glEnd();

	//DRAWING OTHER LINES
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(Ap.x, Ap.y); glVertex2i(Ep.x, Ep.y);

	glVertex2i(Bp.x, Bp.y); glVertex2i(Fp.x, Fp.y);

	glVertex2i(Cp.x, Cp.y); glVertex2i(Gp.x, Gp.y);

	glVertex2i(Dp.x, Dp.y); glVertex2i(Hp.x, Hp.y);
	glEnd();

}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: translate_x(-5); break;
	case GLUT_KEY_RIGHT: translate_x(5); break;
	case GLUT_KEY_UP: translate_y(5); break;
	case GLUT_KEY_DOWN: translate_y(-5); break;
	default: return;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		sff=sff+0.1;
		if (sff < 1) {
			sff = sff + 1;
		}
		scaleBox(sff);
		break;
	case '-':
		sff=sff-0.1;
		if (sff > 1) {
			sff = (1 / sff);
		}
		scaleBox(sff);
		break;
	case 'R':
		rotatebox_z(-5);
		break;
	case 'r':
		rotatebox_z(5);
		break;
	case 'X':
		rotatebox_x(-5);
		break;
	case 'x':
		rotatebox_x(5);
		break;
	case 'Y':
		rotatebox_y(-5);
		break;
	case 'y':
		rotatebox_y(5);
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
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{

		}
		else if (button == GLUT_RIGHT_BUTTON)
		{

		}
	}
}

void myDisplay()
{
	glLineWidth(2.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawCube();
	
	glFlush();
}

void myInit() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow("Projection of a Cube");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WinWidth / 2, WinWidth / 2, -WinWidth / 2, WinWidth / 2);
	glViewport(0, 0, WinWidth, WinHeight);

	myInit();
	InitCube();

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return(0);
}
