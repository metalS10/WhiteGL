#pragma once
#include "../Constants.h"
#include "../Vec2.h"
#include "../Vec3.h"
#include "../Vec4.h"
#include <stdio.h>


#define scanf scanf_s

class CPolygon
{
private:

	//GLenum mode = GL_POLYGON;

	int _maxNumber = MAX_BACKGROUND_NUMBER;
	int _number = 0;

	CVec2 _position[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _rectPosition[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _colorRGBA[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _scale[MAX_BACKGROUND_NUMBER] = {};

	//CGameEngine& m_game;

public :
	CPolygon();
	~CPolygon();


	void init();
	void update();
	void print(float x, float y, float z, float px, float py, float pz);

	void first();
};


