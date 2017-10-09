#pragma once

#include <iostream>
#include "Vec3.h"

//==============================================
//
//行列変換を管理するクラス
//
//==============================================
class CNode
{
private:
	//位置
	CVec3 m_position = { 0.0f,0.0f,0.0f };
	//回転
	CVec3 m_rotate = { 0.0f,0.0f,0.0f };
	//拡大率
	CVec3 m_scale = { 1.0f,1.0f,1.0f };

public:
	//コンストラクタ
	CNode(){}
	//デストラクタ
	virtual ~CNode(){}
	
	/**
	*@desc 位置の設定
	*/
	void setPosition(float x, float y, float z)
	{
		this->m_position.set(x, y, z);
	}

	/**
	*@desc	回転の設定
	*/
	void setRotate(float x, float y, float z)
	{
		this->m_rotate.set(x, y, z);
	}

	/**
	*@desc	拡大率の設定
	*/
	void setScale(float x, float y, float z)
	{
		this->m_scale.set(x, y, z);
	}

	/**
	*@desc 行列変換
	*/
	void transform();

	/**
	*@desc	描画
	*/
	virtual void draw() = 0;

	/**
	*@desc	テクスチャの切り取り
	*@param	切り取る部分
	*/
};