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

typedef CVec4 CChip;

class CAnimation
{
protected:
	float m_Interval = 0;
	std::vector<CChip*> m_Rect;
	int i = 0;
	int m_Nowrect = 0;
	//アニメーション枚数
	int m_number = 0;
	bool m_isLoop = true;
	//現在のフレーム数
	int m_currentFrame = 0;

public:
	CAnimation(float interval,int number ,bool isLoop):
		m_Interval(interval),m_number(number),m_isLoop(isLoop){}

	virtual CChip* animUpdate()
	{
		i++;
		if (i >= m_Interval)
		{
			i = 0;
			m_Nowrect++;
			if (m_Nowrect <= m_number)
			{
				return m_Rect[m_Nowrect];
			}
			//最後のアニメーション&ループがtrueなら
			else if (m_isLoop)
			{
				m_Nowrect = 0;
				return m_Rect[m_Nowrect];
			}
			//ループがfalseなら
			else
			{
				m_Nowrect = m_number;
				return m_Rect[m_Nowrect];
			}
		}
	}

	virtual void addChipData(CChip* pChip){}

	/**
	*	@desc現在フレームのチップを取得する
	*	@return 現在フレームのチップ
	*/
	virtual CChip getCurrentChip() = 0;
};

class CListAnimation : public CAnimation
{
protected:
	std::vector<CChip*> m_chipList;

public:
	CListAnimation(int interval, bool isLoop = false) :
		CAnimation(interval,0, isLoop) {}
	~CListAnimation()
	{
		//チップの解放
		std::vector<CChip*>::iterator itr = this->m_chipList.begin();
		while (itr != this->m_chipList.end())
		{
			SAFE_DELETE((*itr));
			itr++;
		}
	}
	/**
	*	@descチップデータの追加
	*	@param	チップデータ
	*/
	void addChipData(CChip* pChip)override
	{
		//切り取る範囲を追加する
		this->m_chipList.push_back(pChip);

		//切り取る範囲を追加したらアニメーションの最大数も更新する
		this->m_number = this->m_chipList.size();
	}

	/**
	*	@desc現在のフレームのチップを取得
	*	@return 現在のフレームのチップ
	*/
	virtual CChip getCurrentChip() override
	{
		//添え字演算子で取得したデータ自体がCChip*　なのでその中身を返す
		return *(this->m_chipList[this->m_currentFrame]);
	}
};

class CNotAnimation : public CListAnimation
{
private:
	//参照するチップデータ
	CChip* m_pChip = NULL;
public:
	CNotAnimation() :CListAnimation(0, false) {}
	~CNotAnimation() {}

	/**
	*	@desc更新処理は行わず返す値は必ず1になる
	*/
	CChip* animUpdate() override { return 0; }
	
	void addChipData(CChip* pChip)override
	{
		this->m_pChip = pChip;
	}
	/**
	*	@desc現在フレームのチップを取得する
	*	@return 現在フレームのチップ
	*/
	CChip getCurrentChip() override
	{
		return (*this->m_pChip);
	}
};
