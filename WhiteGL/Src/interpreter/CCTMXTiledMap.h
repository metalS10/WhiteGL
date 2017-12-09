#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "../Constants.h"
#include <string>
#include "../Vec2.h"
#include "../Rect.h"
#include "../MSlib.h"

/**
 * @addtogroup _2d
 * @{
 */

/** Possible orientations of the TMX map. */
enum
{
    /** Orthogonal orientation. */
    TMXOrientationOrtho,

    /** Hexagonal orientation. */
    TMXOrientationHex,

    /** Isometric orientation. */
    TMXOrientationIso,
    
    /** Isometric staggered orientation. */
    TMXOrientationStaggered,
};

class /*CC_DLL*/ TMXTiledMap
{
public:

	TMXTiledMap() {}
	
	~TMXTiledMap() {}

    /** The map's size property measured in tiles. 
     *
     * @return The map's size property measured in tiles.
     */
    inline CSize& getMapSize() const { return _mapSize; };
    
    /** Set the map's size property measured in tiles. 
     *
     * @param mapSize The map's size property measured in tiles.
     */
    inline void setMapSize(CSize& mapSize) { _mapSize = mapSize; };

    /** The tiles's size property measured in pixels. 
     *
     * @return The tiles's size property measured in pixels.
     */
    inline CSize& getTileSize() const { return _tileSize; };

	inline const CVec2 getPosition() const { return CVec2(0.0f, 0.0f); };
    
    /** Set the tiles's size property measured in pixels. 
     *
     * @param tileSize The tiles's size property measured in pixels.
     */
    inline void setTileSize(CSize& tileSize) { _tileSize = tileSize; };

    /** Map orientation. 
     *
     * @return Map orientation.
     */
    inline int getMapOrientation() const { return _mapOrientation; };
    
    /** Set map orientation. 
     *
     * @param mapOrientation The map orientation.
     */
    inline void setMapOrientation(int mapOrientation) { _mapOrientation = mapOrientation; };

	
	//XML‚Ìƒf[ƒ^(tmx)
	LoadXml* xml;
    /** the map's size property measured in tiles */
    CSize& _mapSize = CSize(0.0f,0.0f);
    /** the tiles's size property measured in pixels */
    CSize& _tileSize = CSize(0.0f, 0.0f);
    /** map orientation */
    int _mapOrientation = 0;
  
	void load(const std::string& tmxFile)
	{
		CGameEngine& game = MS::CMS::getInstance()->getGame();

		xml = new LoadXml(tmxFile.c_str());

		game.loadTMXMap(xml->m_layerData[0], xml->m_width, xml->m_height);
		//game.loadTMXMap(xml->m_layerData[1], xml->m_width, xml->m_height);
		//game.loadTMXMap(xml->m_layerData[2], xml->m_width, xml->m_height);
		game.TMXMapSetPos(0.0f, 0.0f);

		_tileSize = CSize(xml->m_layerData[0].m_tileWidth, xml->m_layerData[0].m_tileHeight);
		_mapSize = CSize(xml->m_width, xml->m_height);
	}
	int i = 0;
	// public
	CLayerData getLayer(const int layerName)
	{
		return xml->m_layerData[layerName];
	}

	uint32_t getTileGIDAt(const CVec2& pos, const int layerData)
	{

		int idx = static_cast<int>(((int)pos.x + (int)pos.y * xml->m_width));
		// Bits on the far end of the 32-bit global tile ID are used for tile flags
		uint32_t tile = xml->m_layerData[layerData].m_gid[idx];



		return (tile & kTMXFlippedMask);
	}

};



#endif //__CCTMX_TILE_MAP_H__


