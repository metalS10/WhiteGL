#pragma once
#include <string>
class CElement
{
public:
	std::string m_elementName;
	int m_elementValue;

	CElement(std::string elementName, int elementValue)
		:m_elementName(elementName), m_elementValue(elementValue) {}
};

class CLayerData
{
public:
	int m_firstgid;
	std::string m_mapChip;
	float m_tileWidth;
	float m_tileHeight;
	int m_tilecount;
	int m_columns;
	std::string m_imageSource;
	int m_imagewidth;
	int m_imageheight;
	bool m_datacomp = false;
	bool m_gidcomp = false;
	std::vector<int> m_gid;

	void addgid(float width, float height, int gid)
	{
		m_gid.push_back(gid);
		if ((width * height) <= m_gid.size())
		{
			m_gidcomp = true;
		}
	}
};