#pragma once
#include "../Vec2.h"
#include "../Vec4.h"

//テクスチャのタイプ
enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
//レイヤーのタイプ
enum class LAYER : int
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	BB = 3,
	MAX = BB,
};

class CRendInfo
{
protected:
	CVec4	_texRectPos = {};	//テクスチャの切り取り矩形
	CVec2	_texPosition = {};	//テクスチャのポジション
	int _texTag = {};	//テクスチャのタグ
	CVec4	_texRect = {};	//テクスチャの矩形
	CVec2	_texWH = {};	//テクスチャの縦横
	CVec2	_texScale = {};	//テクスチャのスケール
	float	_texDefaultScale = {};	//テクスチャの初期スケール
	TEX_TYPE _texType = {};	//テクスチャのタイプ
	CVec4	_texColorRGBA = {};	//テクスチャの色情報
};