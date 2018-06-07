#include "Polygon.h"
#include "../GameEngine/GameEngine.h"

CPolygon::CPolygon(CGameEngine& game)
{
	m_game = game;
	init();
}


CPolygon::~CPolygon()
{

}

void CPolygon::init()
{

	first();
}

void CPolygon::update()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(M_PI + angle / 180.0, 0.5, 1.0, 0.0);
	//angle = (angle + 5) % 360;

	// Draw a dragon

	//glFlush(); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0.0, WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.5, 0.0, -1.0, 1.0);

	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.0, 0.0, 1.0f);
	glVertex3f(WINDOW_RIGHT * 0.3, WINDOW_HEIGHT*0.5, 0);
	glColor4f(0.0, 1.0, 0.0, 0.5f);
	glVertex3f(WINDOW_RIGHT*0.7, WINDOW_HEIGHT*0.5, 0);
	glColor4f(0.0, 0.0, 1.0, 1.0f);
	glVertex3f(WINDOW_RIGHT*0.5, WINDOW_HEIGHT*0.7, 0);
	glEnd();



}

void CPolygon::print(float x, float y, float z, float px, float py, float pz)
{
	glVertex3f(x + px, y + py, z + pz);
}

void CPolygon::first()
{
	
}
	
