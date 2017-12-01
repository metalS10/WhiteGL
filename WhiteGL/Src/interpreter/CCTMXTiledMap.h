#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "../Constants.h"
#include <string>
#include "../Vec2.h"
#include "../Rect.h"

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

	inline const CVec2& getPosition() const { return CVec2(0, 0); };
    
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


    /** the map's size property measured in tiles */
    CSize& _mapSize = CSize(0.0f,0.0f);
    /** the tiles's size property measured in pixels */
    CSize& _tileSize = CSize(0.0f, 0.0f);
    /** map orientation */
    int _mapOrientation = 0;
  

};

#endif //__CCTMX_TILE_MAP_H__


