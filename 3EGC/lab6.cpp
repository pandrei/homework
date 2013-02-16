/*
 * Necula Roxana - Valentina 332CA
 * Tema 3 EGC - Labirint
 */
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "glut.h"
#include <math.h>
#include "ground.h"

float xpos = 1.5, zpos = 1.5, xrot = 0, yrot = 90, angle=0.0, xold = 1.5, zold = 1.5;
float xportal, zportal;

float cr = 3.0f;

float lastx, lasty;
bool tps = true, sus = false, rotire = false, move = true;
int **matrice;
int a, b;

//functie ce verifica coliziunile dintre erou si pereti
bool boundingSphereCollision(int i, int j)
{
	float relPosx, relPosz;
	float dist, minDist;
	relPosx = xpos - i*4;
	relPosz = zpos - j*4;
	dist = sqrt(relPosx * relPosx + relPosz * relPosz);
	//raza cubului(perete) + raza eroului
	minDist = 2 + 0.5;
	bool result;
	if (dist <= minDist)
		result = true;
	else result = false;
	if (matrice[i][j] != 1)
		result = false;
	return result;
}

//functie folosita pentru verificarea daca eroul atinge portalul
bool portalCollision()
{
	float relPosx, relPosz;
	float dist, minDist;
	relPosx = xpos - xportal*4;
	relPosz = zpos - zportal*4;
	dist = sqrt(relPosx * relPosx + relPosz * relPosz);
	minDist = 2 + 0.5;
	bool result;
	if (dist <= minDist)
		result = true;
	else result = false;
	return result;
}

void display (void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
	//setup view
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	//ground
	glColor3f(0.1f,0.1f,0.1f);
	if (sus == false)
		draw_ground(1000,1000,1000,1000,-0.5f);

	//vederea este FPS sau TPS
	if (sus == false)
		if (tps == true)
			glTranslatef(0.0f, 0.0f, -cr);
		else
			if (tps == false)
				glTranslatef(0.0f, 0.0f, 0.5f);

	//culoarea eroului
    glColor3f(0.13f,0.37f,0.31f);

	//rotirea camerei stanga sau dreapta
	if (sus == false)
		glRotatef(yrot,0.0,1.0,0.0);

	if (sus == true)
	{
		//vedere de sus
		glRotatef(0, 0, 1, 0);
		glTranslatef(-33, 25, 0);
		gluLookAt (0, 50, 2, 0, 0, 0, 0, 1, 0);
	}
	else
		{
			//eroul nostru
			glutWireSphere(0.5, 10, 10);
			glTranslatef(-xpos,-0.7f,-zpos);
		}
	
	//portalul
	for (int i = 0; i < b; i++)
		for (int j = 0;j < a; j++)
		{
			glPushMatrix();
			glColor3f(0, 0, 1);
			glTranslatef(i*4, 1.1f, j*4);
			if (matrice[i][j] == 2)
			{
				glutWireTorus(0.2f, 0.75f, 30, 50);
				xportal = i;
				zportal = j;
			}
			glPopMatrix();
		}

    glColor3f(1.0f, 1.0f, 1.0f);

	//peretii
	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < a; j++)
		{
			glPushMatrix();

			glColor3f(0.55f,0.13f,0.13f);

			glTranslatef(i*4, 0, j*4);
			if (matrice[i][j] == 1)
				glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(i*4, 0, j*4);
			if (matrice[i][j] == 1)
				glutWireCube(4);
			glPopMatrix();
		}
	}

    glutSwapBuffers();
}

void reshape(int width, int height){
	//set viewport
	glViewport(0,0,width,height);

	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,(float)width/(float)height,0.2,100);
}

void keyboard(unsigned char ch, int x, int y){
	switch(ch){
		case 27:	//esc
			exit(0);
			break;

		case 'w':
			xold = xpos;
			zold = zpos;
			if (sus == false && move == true)
			{
				xpos += float(sin(yrot / 180 * 3.141592654f));
				zpos -= float(cos(yrot / 180 * 3.141592654f));
			}
			move = true;
			break;
		case 's':
			xold = xpos;
			zold = zpos;
			if (sus == false && move == true)
			{
				xpos -= float(sin(yrot / 180 * 3.141592654f));
				zpos += float(cos(yrot / 180 * 3.141592654f));
			}
			move = true;
			break;
		case 'a':
			yrot -= (float) 4.0;
			break;
		case 'd':
			yrot += (float) 4.0;
			break;
		case 'p':
			tps = !tps;
			break;
		case 'o':
			sus = !sus;
			rotire = !rotire;
			break;
		default:
			break;
	}

}

void idle(){
	
	angle = angle+1;
	if(angle >360) angle = angle-360;
	glutPostRedisplay();

	for (int i = 0; i < b; i++)
		for (int j = 0; j < a; j++)
			if (boundingSphereCollision(i, j) == true)
			{
				move = false;
				xpos = xold;
				zpos = zold;
			}
	
	if (portalCollision() == true)
	{
		xpos = 0;
		zpos = 0;
	}
}

using namespace std;
int main (int argc, char **argv) {
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d %d", &b, &a);

	matrice = new int *[b];
	for(int i = 0; i < b; i++)
		matrice[i] = new int [a];
	for (int i = 0; i < b; i++)
		for (int j = 0; j < a; j++)
			fscanf(fp, "%d", &matrice[i][j]);
	//init glut
    glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//init window
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Tema 3 EGC - Labirint");
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutReshapeFunc (reshape);

    glutKeyboardFunc (keyboard);

	//set background
	glClearColor(0.19f,0.6f,0.8f,1.0);

    glutMainLoop ();
    return 0;
}
