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
	int m_tileWidth;
	int m_tileHeight;
	std::string m_imageSource;
	int m_width;
	int m_height;
	bool m_datacomp = false;
	bool m_gidcomp = false;
	std::vector<int> m_gid;

	void addgid(int gid)
	{
		m_gid.push_back(gid);
		if ((100 * 15) <= m_gid.size())
		{
			m_gidcomp = true;
		}
	}
};