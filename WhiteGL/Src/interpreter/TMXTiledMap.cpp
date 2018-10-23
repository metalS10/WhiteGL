#include "TMXTiledMap.h"

TMXTiledMap::TMXTiledMap()
{

}
TMXTiledMap::~TMXTiledMap()
{
	for (rendInfo::CTexRendInfo* tex : m_tileTextures)
	{
		SAFE_DELETE(tex);
	}
}
void TMXTiledMap::load(const std::string& tmxFile)
{

	xml = new LoadXml(tmxFile.c_str());

	loadTMXMap(xml->m_layerData, xml->m_width, xml->m_height);
	TMXMapSetPos(0.0f, 0.0f);

	_tileSize = CSize(xml->m_layerData[0].m_tileWidth, xml->m_layerData[0].m_tileHeight);
	_mapSize = CSize(xml->m_width, xml->m_height);
}

// public
CLayerData TMXTiledMap::getLayer(const int layerName)
{
	return xml->m_layerData[layerName];
}

uint32_t TMXTiledMap::getTileGIDAt(const CVec2& pos, const int layerData)
{

	int idx = static_cast<int>(((int)pos.x + (int)pos.y * xml->m_width));
	// Bits on the far end of the 32-bit global tile ID are used for tile flags
	uint32_t tile = xml->m_layerData[layerData].m_gid[idx];



	return (tile & kTMXFlippedMask);
}

void TMXTiledMap::loadTMXMap(CLayerData layerData[MAX_LAYER_NUMBER], int width, int height)
{
	//ステージを変えるタイミングなので初期化しておく
	m_tileTextures.clear();
	int countW = 0;
	int countH = height - 1;
	int tileID = 0;

	for (int j = 0; j < MAX_LAYER_NUMBER; j++)
	{
		for (int i = 0; i < layerData[j].m_gid.size(); i++)
		{
			if (j == 2)
			{
				int t = 1;
			}
			if (layerData[j].m_gid[i] != 0)
			{
				int gidten = (int)((layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns < 0.0 ? (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns - 0.9 : (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns);
				int gidone = (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) % (layerData[j].m_columns);
				float rectL = layerData[j].m_tileWidth * gidone - layerData[j].m_tileWidth;
				float rectB = layerData[j].m_tileHeight * gidten;
				m_tileTextures.push_back(new rendInfo::CTexRendInfo());
				m_tileTextures.back()->setImage(layerData[j].m_imageSource.c_str(), rendInfo::TEX_TYPE::PNG, START_MAP_TEXTURE_NUMBER + tileID + countMap, CVec2(layerData[j].m_tileWidth * 0.5 + (layerData[j].m_tileWidth * countW), layerData[j].m_tileHeight * 0.5 + (layerData[j].m_tileHeight * countH)), CVec4(rectL, rectB, layerData[j].m_tileWidth, layerData[j].m_tileHeight), rendInfo::LAYER::MAIN);
				tileID++;
			}
			if (countW >= width - 1)
			{
				countW = 0;
				countH--;
			}
			else
			{
				countW++;
			}
			
		}
		countMap += layerData[j].m_gid.size();
	}
	//レイヤーまで終わったら初期化
	countMap = 0;

}

void TMXTiledMap::TMXMapSetPos(float x, float y)
{
	for (int i = 0; i < countMap; i++)
	{
		m_tileTextures[i]->setMapPosition(CVec2(x, y), START_MAP_TEXTURE_NUMBER + i);
	}
}


