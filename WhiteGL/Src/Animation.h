#pragma once
/**
*animation.h
*
*	2017/10/11	Mat
*		テクスチャのアニメーション
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Constants.h"

class CAnimation
{
	float m_Interval = 0;
	std::vector<CVec4> m_Rect;
	int i = 0;
	int m_Nowrect = 0;

	CAnimation(std::vector<CVec4> rect, float interval)
	{
		m_Rect = rect;
		m_Interval = interval;
	}

	CVec4 animUpdate()
	{
		i++;
		if (i >= m_Interval)
		{
			i = 0;
			m_Nowrect++;
			if (m_Nowrect >= m_Rect.size())
			{
				return m_Rect[m_Nowrect];
			}
		}
	}
};