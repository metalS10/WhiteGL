//ただのポリゴン表示の勉強

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <GL/glut.h>
#include "Src\Constants.h"
#define scanf scanf_s



int angle = 0;
GLenum mode = GL_POLYGON;
float x_in = 1, y_in = 1, z_in = 1, px_in = 0, py_in = 0, pz_in = 0;

//OpenGLの初期設定
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);//正面から見た表示サイズの設定
	glEnable(GL_DEPTH_TEST);
}

//送られてきたサイズとポジションの点を描写するための関数とつくる
void print(float x, float y, float z, float px, float py, float pz)
{
	glVertex3f(x + px, y + py, z + pz);
}

//それらの点に関する操作は、glBegin関数に送るモードによって決定。
//点を連結するポリゴンを表示したい場合は、glBegin(GL_POLYGON)とglEnd()の間で、繋がる点同士を描写。
//例えばポリゴンの代わりに線で結びたい場合は、GL_LINE_LOOPとかするとできる。
//今回は、ポリゴンの描写の繰り返しでドラゴンを描きたいため、以下の関数を作成。
//引数は、ドラゴンの大きさ変数のx, y, zと、場所を指定するpx, py, px
//glColor3f(R, B, G)でカラーの指定もできる。
//R, B, Gはそれぞれ0から1の間の値で指定
void dragon(float x, float y, float z, float px, float py, float pz)
{
	
	glBegin(mode);
	glColor3f(0.8, 0.7, 0.1);
	print(-0.5*x, 5.2*y, 3.0*z, px, py, pz);
	print(0.5*x, 5.2*y, 3.0*z, px, py, pz);
	print(0.5*x, 4.7*y, 3.0*z, px, py, pz);
	print(-0.5*x, 4.7*y, 3.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 0.8, 0.1);
	print(-0.8*x, 6.5*y, 1.0*z, px, py, pz);
	print(0.8*x, 6.5*y, 1.0*z, px, py, pz);
	print(0.5*x, 5.2*y, 3.0*z, px, py, pz);
	print(-0.5*x, 5.2*y, 3.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.8, 0.0, 0.1);
	print(-0.5*x, 2.5*y, 4.0*z, px, py, pz);
	print(0.5*x, 2.5*y, 4.0*z, px, py, pz);
	print(0.5*x, 4.2*y,4.0*z, px, py, pz);
	print(-0.5*x, 4.2*y, 4.0*z, px, py, pz);
	glEnd();
	
	
	//以下略
	//..
	//..
}

void rokuyon(float x, float y, float z, float px, float py, float pz)
{
	glBegin(mode);
	glColor3f(0.2, 0.2, 0.2);
	print(5.0*x, -5.0*y, -5.0*z, px, py, pz);
	print(-5.0*x, -5.0*y, -5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, -5.0*z, px, py, pz);
	print(5.0*x, 5.0*y, -5.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.4, 0.4, 0.4);
	print(5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, -5.0*y, -5.0*z, px, py, pz);
	print(5.0*x, -5.0*y, -5.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.6, 0.6, 0.6);
	print(5.0*x, 5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, -5.0*z, px, py, pz);
	print(5.0*x, 5.0*y, -5.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.8, 0.8, 0.8);
	print(5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, 5.0*z, px, py, pz);
	print(5.0*x, 5.0*y, 5.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(0.1, 0.1, 0.1);
	print(-5.0*x, -5.0*y, -5.0*z, px, py, pz);
	print(-5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, 5.0*z, px, py, pz);
	print(-5.0*x, 5.0*y, -5.0*z, px, py, pz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 1.0, 1.0);
	print(5.0*x, -5.0*y, -5.0*z, px, py, pz);
	print(5.0*x, -5.0*y, 5.0*z, px, py, pz);
	print(5.0*x, 5.0*y, 5.0*z, px, py, pz);
	print(5.0*x, 5.0*y, -5.0*z, px, py, pz);
	glEnd();

}

//display関数をつくってそこから描写
//ウィンドウサイズを変更したり、再描写される度にドラゴンが5度ずつ回転するようにしてみた笑゛
void display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(M_PI + angle / 180.0, 0.5, 1.0, 0.0);
	angle = (angle + 5) % 360;

	// Draw a dragon
	rokuyon(x_in, y_in, z_in, px_in, py_in, pz_in);

	glFlush();
}



float input()
{
	float input;
	char str[10], *trm;
	int flag = 1;
	while (flag) {
		flag = 0;
		scanf("%s", str);
		input = strtod(str, &trm); //convert str -> double
		if ((trm != NULL) && (*trm != '\0'))
		{
			printf("error: type any numbers\n");
			flag = 1;
		}
		rewind(stdin);
	}
	return input;
}

float a = 0.01;
void timer(int value) {
	 //正方形のサイズを増加 
	if (x_in >= 1.5)
	{
		a = -0.01f;
	}
	else if (x_in <= 0.0)
	{
		a = 0.01f;
	}

	x_in += a;
	y_in += a;
	z_in += a;

	printf("%d\n", x_in);
	/* 画面を再描写 */
	glutPostRedisplay();
	/* 100ミリ秒後に再実行 */
	glutTimerFunc(30, timer, 0);
}

int main2(int argc, char *argv[])
{
	printf("* coordinates for polygon of dragon *\n");
	printf("height of the dragon?\n");
	y_in = 1;
	printf("width of the dragon?\n");
	x_in =1;
	printf("depth of the dragon?\n");
	z_in = 1;
	printf("x position\n");
	px_in = 0;
	printf("y position?\n");
	py_in = 0;
	printf("z position?\n");
	pz_in = 0;
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("64");
	glutDisplayFunc(display2);
	init();
	glutTimerFunc(30, timer, 0);

	glutMainLoop();
	

		
	return 0;
}