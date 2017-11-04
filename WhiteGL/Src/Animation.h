#pragma once

//===================================================================
//追加のインクルードはここから
//===================================================================
#include "Constants.h"
#include "Vec4.h"
#include <vector>

//===================================================================
//チップデータクラス
//	画像の1部分の位置とサイズのデータ
//===================================================================
typedef CVec4 CChip;


//===================================================================
//アニメーションクラス
//	このクラスにはチップの情報は存在しない
//	アニメーション間隔と枚数をもとに
//	現在のフレーム数を計算するだけのクラス
//===================================================================
class CAnimation
{
protected:
	//カウンター
	int m_counter = 0;

	//切り替え間隔(パラパラ漫画の速度になる)
	int m_interval = 0;

	//アニメーション枚数
	int m_number = 0;

	//現在のフレーム数
	int m_currentFrame = 0;

	//ループするかどうかのフラグ
	//true...ループする
	bool m_isLoop = false;

	//アニメーションが終了したかどうかのフラグ
	//true...終了した
	bool m_isEnd = false;

	//アニメーションのスタートを設定するためのフラグ
	//isLoopがfalseだと1から始まらなくなるのでinputでstartを呼び出す
	bool m_isStart = true;

public:
	CAnimation(int interval, int number, bool isLoop = false) :
		m_interval(interval), m_number(number), m_isLoop(isLoop) {}
	virtual ~CAnimation() {}

	//現在フレームの取得
	int getCurrentFrame() { return this->m_currentFrame; }
	//アニメーションが終了したかどうか
	bool isEnd() { return this->m_isEnd; }

	/**
	*	@descカウンターや現在のフレーム数のクリア
	*/
	void clear()
	{
		this->m_counter = 0;
		this->m_currentFrame = 0;
	}

	virtual void start()
	{
		if (this->m_isStart == false)
		{
			this->m_counter = 0;
			this->m_isStart = true;
			this->m_isEnd = false;
		}
	}


	/**
	*	@descアニメーションの更新処理
	*	@return 表示するフレーム数(-1初期化がまだ行われていない)
	*/
	virtual int update()
	{

		//アニメーションが終了していなければカウンターの更新を行う
		if (this->m_isEnd == false && this->m_isStart == true)
		{
			this->m_counter++;

			//カウンターの数がアニメーションさせる枚数以上になったらカウンターをリセットする
			if (this->m_counter >= this->m_interval * this->m_number)
			{
				if (this->m_isLoop == true)
				{
					//ループするアニメーションはカウンターをリセットする
					this->m_counter = 0;
				}
				else
				{
					//アニメーションが終了したかどうかのフラグに対してtrueを入れる
					//this->m_isEnd = true;

					//ループしないアニメーションに対しては飛び出たカウンターをデクリメントする
					this->m_counter--;
					m_isEnd = true;
					m_isStart = false;
				}
			}
		}

		//表示するフレーム数
		m_currentFrame = this->m_counter / this->m_interval;

		return m_currentFrame;
	}
	/**
	*	@descチップデータの追加
	*	@oaram チップデータ
	*/
	virtual void addChipData(CChip*) = 0;

	/**
	*	@desc現在フレームのチップを取得する
	*	@return 現在フレームのチップ
	*/
	virtual CChip getCurrentChip() = 0;
};

//======================================================================
//チップアニメーションクラス
//	アニメーションする画像が横に並んでいる場合のみに限る
//	アニメーションクラスをもとに現在のフレームから切り取るべき画像を取得
//======================================================================
class CChipAnimation : public CAnimation
{
protected:
	//参照するチップデータ
	CChip* m_pChip = NULL;

public:
	CChipAnimation(int interval, int number, bool isLoop = false) :
		CAnimation(interval, number, isLoop) {}
	~CChipAnimation() {}

	/**
	*	@descチップデータの追加
	*	@param	チップデータ
	*/
	void addChipData(CChip* pChip)override
	{
		this->m_pChip = pChip;
	}

	/**
	*	@desc現在のフレームのチップを取得
	*/
	virtual CChip getCurrentChip() override
	{
		CChip chip
		(
			m_pChip->z * m_currentFrame,
			m_pChip->y,
			m_pChip->z,
			m_pChip->w
		);

		return chip;
	}
};

//======================================================================
//チップノットアニメーションクラス
//	チップクラスをアニメーションクラスに統合したので
//	アニメーションなしの1枚絵の画像の表示を行うためのキャラクターを
//	生成することが困難になる。
//	もちろんCChipAnimation内部でif文を使ったり
//	一枚絵を使用するクラスのみチップデータクラスを持たせたりでもよいのだが
//	今回は状態によって画像を複数扱ったりとしているので
//	CAnimationの派生クラスとして存在していた方が扱いやすい
//	なのでアニメーションしないアニメーションクラスを1つ用意しておく方が
//	スマートで開発しやすくなる
//======================================================================
class CChipNotAnimation : public CChipAnimation
{
public:
	CChipNotAnimation() :CChipAnimation(0, 0, false) {}
	~CChipNotAnimation() {}

	/**
	*	@desc更新処理は行わず返す値は必ず1になる
	*/
	int update() override { return 1; }

	/**
	*	@desc現在フレームのチップを取得する
	*	@return 現在フレームのチップ
	*/
	CChip getCurrentChip() override
	{
		return (*this->m_pChip);
	}
};

//=======================================================================
//チップリストアニメーション
//	画像がある程度パラパラに並んでいても対応可能だが
//	チップデータのサイズが統一されていなければならない
//	チップデータのサイズが統一されていない場合はそれに応じた中心位置を
//	計算しなければならないということを考慮すること
//	アニメーションクラスをもとに現在のフレームのチップデータをリストから取得
//=======================================================================
class CChipListAnimation : public CAnimation
{
protected:
	//アニメーションさせるチップデータのリスト
	std::vector<CChip*> m_chipList;

public:
	CChipListAnimation(int interval, bool isLoop = false) :CAnimation(interval, 0, isLoop) {}

	~CChipListAnimation()
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
	void addChipData(CChip* pChip) override
	{
		//チップデータを追加する
		this->m_chipList.push_back(pChip);

		//チップデータを追加したらアニメーションの最大数も更新する
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