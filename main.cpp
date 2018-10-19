#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>


#ifdef APPLE
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float _angle = 0.0f,_angle2=0.0f;
const float DEG2RAD = 3.14159 / 180;
float radius = 0.25;
float b1_color = 0.0,b2_color=0.0;
int drc = 0, flage = 1,val;
int numOfBall = 1;
int speed = 100;
void moveBall1();
void moveBall2();
void update(int val);


void moveBall2() {

	if (_angle2 == 0 && drc == 1) {
		b2_color = 0.0;
		drc = 0;
		val = 0;
		flage = 1;

	}
	else
	{
		b2_color = 1.0;
		if (_angle2 < 45 && drc == 0)  _angle2 += 5;
		else if (_angle2 <= 45 && _angle2 > 0) { _angle2 -= 5; drc = 1; }

	}

}

void moveBall1() {


	if (_angle == 0 && drc == 1) {
		b1_color = 0.0;
		drc = 0;
		val = 1;
		flage = 2;
	}
	else
	{
		b1_color = 1.0;
		if (_angle > -45 && drc == 0)  _angle -= 5;
		else if (_angle <= -45 || _angle < 0) { _angle += 5; drc = 1; }

	}
}

void changeNumBall(int num) {
	numOfBall = num;

}


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
		break;
	case 32:
		update(1);
		break;
	//press number from 2-6 to change number of ball
	case 50:   //number 2
		changeNumBall(2);
		break; //3
	case 51:
		changeNumBall(3);
		break;
	case 52:
		changeNumBall(4);
		break;
	case 53:
		changeNumBall(5);
		break;

	case 54:
		changeNumBall(6);
		break;
	case 45: //click - to decrease the motion speed
		speed += 20;
		break;
	case 43:  //click + to increase the motion speed
		speed -=20;
		if (speed < 20) speed = 40;
		break;
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(0.0f, 0.0f, -5.0f); //Move forward 5 units

	glPushMatrix();

	glScalef(.9f, .8f, 0.8f);

	glColor3f(0.5f, 0.3f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(-3.8f, 1.5f, 0.0f);
	glVertex3f(1.0f, 1.5f, 0.0f);
	glVertex3f(1.0f, 1.8f, 0.0f);
	glVertex3f(-3.8f, 1.8f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(5.0);

	glTranslatef(-3.5, 1.5, 0.0f);

	//draw first pendulums
	glPushMatrix();

	glTranslatef(0.0f, -2.5f, 0.0f);

	for (int x = 0; x < numOfBall; x++) {
		if (numOfBall > 3 && flage == 2 && x >= 7 - numOfBall) {
			break;
		}
		glPushMatrix();

		glTranslatef(0.53*(x+1), 2.5f, 0.0f);
		glRotatef(_angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -2.5f, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		//line
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glVertex3f(0.0f, 2.5f, 0.0f);
		glEnd();
		//circle
		glColor3f(b1_color, 0.0f, 1.0 - b1_color);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
		}
		glEnd();

		glPopMatrix();
	}

	glPopMatrix();


	//draw inbetween pendulums
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(numOfBall*0.53, -2.5f, 0.0f);
	for (int x = numOfBall; x < 7-numOfBall; x++) {

		glTranslatef(0.53f, 0.0f, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		//line
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glVertex3f(0.0f, 2.5f, 0.0f);
		glEnd();
		//circle
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
		}

		glEnd();

	}
	glPopMatrix();


	//draw last pendulums
	glPushMatrix();

	glTranslatef( 8 *0.53, -2.5f, 0.0f);
	int count = 1;
	for (int x = 7; x > 7-numOfBall; x--) {
		if (numOfBall > 3 && flage == 1 && x <= numOfBall) {
			break;
		}

		glPushMatrix();

		glTranslatef(-0.53*count, 2.5f, 0.0f);
		glRotatef(_angle2, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -2.5f, 0.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		//line
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glVertex3f(0.0f, 2.5f, 0.0f);
		glEnd();
		//circle
		glColor3f(b2_color, 0.0f, 1.0 - b2_color);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
		}

		glEnd();
		glPopMatrix();
		count++;
	}
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}


void update(int value) {

	if (flage==1) {
		moveBall1();
	}
	else if (flage == 2 )
	{
		moveBall2();
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 50 milliseconds
	glutTimerFunc(speed, update, 0);
}



int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 400);

	//Create the window
	glutCreateWindow("Newton cradle");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

//	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
