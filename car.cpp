#include <GL/glut.h>	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <random>
#include <windows.h>

int cx,cy,cz;
int sz;
int rcz;
double minspeed = 10, maxspeed = 1.2;
double speed = minspeed;
int score = -1;
char sco[10] = {0};
int view = 0;

void keyy(unsigned char key, int x, int y)
{
	if(key == '4' && cx > 100)
		cx-=100;
	if(key == '6' && cx < 400)
		cx+=100;
	if(key == 'v')
	{
		if(view == 0)
			view=1;
		else
			view=0;
	}
}

void object_name(float x, float y,char* name)
{
	glRasterPos2f(x,y);
	//glColor3f(1.0, 0.0, 0.0);
	int len_of_name,i;
	len_of_name=(int)strlen(name);
	for(i = 0; i < len_of_name;)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
		i++;
	}
}

void setOrthographicProjection() 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if(view == 0)
	{
		gluPerspective(90.0, 1.5, 0, 200);
	}
	else
	{
		gluPerspective(100.0, 1.5, -400, 0);
	}
	
	if(view == 1)
	{
		//glScalef(1,1,.5);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0, -1, 4.79);
		glScalef(1,1,2.4);
	}
	glOrtho(0.0, (double)600, 0.0,(double)400, 0, 200);
	//glViewport(0, 0, 600, 400);
	//glTranslatef(0, 0, sz);
	glMatrixMode(GL_MODELVIEW);
	//gluPerspective(10.0, 1.5, 0, 200);
}

void resetPerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

GLUquadricObj *quadratic;
int ll=-50;
int kk;
float a,b,c,d,e,f;
int state = 0;
int cw = 100;
int ch = 30;
int cl = 50;
int cm = 20;
void drawcar(int cx,int cy,int cz,float r, float g, float b,float m, float n, float o)
{
	//floor
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy,cz+cl);
		glVertex3i(cx+cw,cy,cz+cl);
		glVertex3i(cx+cw,cy,cz);
		glVertex3i(cx,cy,cz);
	glEnd();
	
	//front side
	glColor3f(m,n,o);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz);
		glVertex3i(cx,cy+cm,cz+cl);
		glVertex3i(cx,cy,cz+cl);
		glVertex3i(cx,cy,cz);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3i(cx+cw,cy+cm,cz);
		glVertex3i(cx+cw,cy+cm,cz+cl);
		glVertex3i(cx+cw,cy,cz+cl);
		glVertex3i(cx+cw,cy,cz);
	glEnd();

	//front number plate
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy,cz+cl);
		glVertex3i(cx+cw,cy,cz+cl);
		glVertex3i(cx+cw,cy+cm,cz+cl);
		glVertex3i(cx,cy+cm,cz+cl);
	glEnd();

	//front dikki
	glColor3f(m,n,o);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz+cl-10);
		glVertex3i(cx+cw,cy+cm,cz+cl-10);
		glVertex3i(cx+cw,cy+cm,cz+cl);
		glVertex3i(cx,cy+cm,cz+cl);
	glEnd();

	//front shisha
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz+cl-10);
		glVertex3i(cx+cw,cy+cm,cz+cl-10);
		glVertex3i(cx+cw,cy+cm+20,cz+cl-20);
		glVertex3i(cx,cy+cm+20,cz+cl-20);
	glEnd();

	//back side
	glColor3f(m,n,o);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz+10);
		glVertex3i(cx,cy+cm,cz);
		glVertex3i(cx,cy,cz);
		glVertex3i(cx,cy,cz+10);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3i(cx+cw,cy+cm,cz+10);
		glVertex3i(cx+cw,cy+cm,cz);
		glVertex3i(cx+cw,cy,cz);
		glVertex3i(cx+cw,cy,cz+10);
	glEnd();

	//back number plate
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy,cz);
		glVertex3i(cx+cw,cy,cz);
		glVertex3i(cx+cw,cy+cm,cz);
		glVertex3i(cx,cy+cm,cz);
	glEnd();

	//back dikki
	glColor3f(m,n,o);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz+10);
		glVertex3i(cx+cw,cy+cm,cz+10);
		glVertex3i(cx+cw,cy+cm,cz);
		glVertex3i(cx,cy+cm,cz);
	glEnd();

	//back shisha
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm,cz+10);
		glVertex3i(cx+cw,cy+cm,cz+10);
		glVertex3i(cx+cw,cy+cm+20,cz+20);
		glVertex3i(cx,cy+cm+20,cz+20);
	glEnd();
	
	//chatt
	glColor3f(m,n,o);
	glBegin(GL_POLYGON);
		glVertex3i(cx,cy+cm+20,cz+20);
		glVertex3i(cx+cw,cy+cm+20,cz+20);
		glVertex3i(cx+cw,cy+cm+20,cz+30);
		glVertex3i(cx,cy+cm+20,cz+30);
	glEnd();
	
}

int rotate = 0;
void drawtrack()
{
	//grass
	glColor3f(0.2,0.8,0.2);
	glBegin(GL_POLYGON);
		glVertex3i(-6000,   0, 200);
		glVertex3i(6000,    0, 200);
		glVertex3i(6000,    0, 0);
		glVertex3i(-6000,   0, 0);
	glEnd();

	if(rotate == 0)
	{
		//track
		glColor3f(0.6,0.6,0.6);
		glBegin(GL_POLYGON);
			glVertex3i(100, 0, 200);
			glVertex3i(500, 0, 200);
			glVertex3i(500, 0, 0);
			glVertex3i(100, 0, 0);
		glEnd();

		glColor3f(1.0,1.0,1.0);
		// road markers
		//int hh = (sz%50);
		int hh = sz;
		glBegin(GL_POLYGON);
			glVertex3i(290, 0, 100+hh);
			glVertex3i(290, 0, 150+hh);
			glVertex3i(310, 0, 150+hh);
			glVertex3i(310, 0, 100+hh);
		glEnd();
		// road markers
		glBegin(GL_POLYGON);
			glVertex3i(290, 0, hh);
			glVertex3i(290, 0, 50+hh);
			glVertex3i(310, 0, 50+hh);
			glVertex3i(310, 0, hh);
		glEnd();
		// road markers
		glBegin(GL_POLYGON);
			glVertex3i(290, 0, 200+hh);
			glVertex3i(290, 0, 250+hh);
			glVertex3i(310, 0, 250+hh);
			glVertex3i(310, 0, 200+hh);
		glEnd();

		if(ll == -50)
		{
			score += 1;
			ll = 250;
			kk = rand()%3;
			a = 0; b=0; c=0; d=0; e=0; f=0;
			if(kk == 0)
			{
				a=1.0;
				d=0.8;
			}
			else if(kk == 1)
			{
				a=1.0;
				b=1.0;
				d=0.8;
				e=0.8;
			}
			else
			{
				c=1.0;
				f=0.8;
			}
		
			kk = rand()%2;
			if(kk == 1)
			{
				kk = 140;
			}
			else
			{
				kk = 360;
			}
		}
		//random cars
		drawcar(kk,cy,ll,a,b,c,d,e,f);
		ll--;

		//check if they collide
		if(state == 0)
		{
			if(!(ll+cl<=cz || ll>=cz+cl || kk>=cw+cx || kk+cw<=cx))
			{
				state = 1;
				score -= 5;
				speed = minspeed;
			}
		}
		if(state == 1)
		{
			if(ll+cl<=cz || ll>=cz+cl || kk>=cw+cx || kk+cw<=cx)
			{
				state = 0;
			}
		}

		//sky
		glColor3f(0.3,0.3,1.0);
		glBegin(GL_POLYGON);
			glVertex3i(-6000,    0, 200);
			glVertex3i(6000,    0, 200);
			glVertex3i(6000, 4000, 200);
			glVertex3i(-6000, 4000, 200);
		glEnd();

		//trees
		quadratic=gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);
		gluQuadricDrawStyle(quadratic, GLU_LINE);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(-150, 0, hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(+150, 0, -hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(750, 0, hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-750, 0, -hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(750, 0, 100+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-750, 0, -100-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(750, 0, 200+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-750, 0, -200-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(750, 0, 300+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-750, 0, -300-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(750, 0, 400+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-750, 0, -400-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(-150, 0, 100+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(150, 0, -100-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(-150, 0, 200+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(150, 0, -200-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(-150, 0, 300+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(150, 0, -300-hh);

		glColor3f(0.7,0.6,0.0);
		glTranslatef(-150, 0, 400+hh);
		glRotatef(+90, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,10,10,150,32,32);
		glColor3f(0.2,1.0,0.2);
		gluSphere(quadratic,30,32,32);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(150, 0, -400-hh);
	}
}

int aa = 0;
void display()
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();

	drawtrack();
	drawcar(cx,cy,cz,1.0,0.0,0.0,0.8,0.0,0.0);
	/*if(view == 1)
	{
		//glTranslatef(100, 0, -400-hh);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
	}*/

	glColor3f(0.0,0.0,0.0);
	object_name(-140,375,"SCORE: ");
	itoa(score,sco,10);
	glColor3f(0.0,0.0,0.0);
	object_name(0,375,sco);

	if(aa <= 3)
	{
		if(aa == 3)
		{
			object_name(280,200,"GO !!");
			glFlush();
			Sleep(1000);
			aa++;
		}
		else
		{
			if(aa==0)
				object_name(290,200,"3");
			else if(aa==1)
				object_name(290,200,"2");
			else if(aa==2)
				object_name(290,200,"1");
			aa = aa + 1;
			glFlush();
			Sleep(1000);
			display();
		}
		return;
	}
	if(score <= -50)
	{
		object_name(190,200,"GAME OVER !!");
		glFlush();
		Sleep(2000);
		exit(0);
	}


	if(sz == -50)
		sz = 50;

	glPopMatrix();
	resetPerspectiveProjection();
	glutSwapBuffers();
	glFlush();
	
	sz--;
	Sleep(speed);
	if(speed > maxspeed)
		speed -= 0.05;
	
	glutPostRedisplay();
}

void myinit(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3d(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (double)600, 0.0,(double)400, 0, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 600, 400);	
	glFlush();
}

void main(int argc, char *argv[], char *envp[])
{
	cx = 100; cy = 5; cz = 5; sz = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowSize(600, 400);	
	glutInitWindowPosition(100, 100);	

	glutCreateWindow("Welcome to Caar");	

	myinit(); 			
	//glEnable(GL_MAP1_VERTEX_3);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyy);
	glutMainLoop();
}