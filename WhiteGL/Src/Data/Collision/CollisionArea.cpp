
//=============================================
//追加のインクルードはここから
//=============================================
#include "CollisionArea.h"
#include "Model/Character/Character.h"
#include "Model/Map/Map.h"

/**
*@desc	イベントコールバックの呼び出し
*@param	呼び出すインスタンス
*		マップチップの際はブロックのタイプをイベントとして渡すが
*		画面端などにイベントは存在しないので
*		デフォルト値として0を設定しておく
*/
void CCollisionTerritory::callEventCallback(CCharacter* pChara, int event)
{
	//イベントコールバックが設定されていなければ
	//つまりNULLなら呼び出しを行わない
	if (this->m_pEventCallback != NULL)
	{
		
		
		//イベントコールバックを呼び出すメンバ関数が実装される
		//キャラクターから呼び出しを行う
		(pChara->*m_pEventCallback)(event);

		
	}

}

//=============================================
//下にある画面領域との衝突判定
//=============================================
void CCollisionTerritoryEndOfScreenBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうかをチェック
	if (pChara->m_pMove -> m_vel.y < 0.0f)
	{
		
		//下に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.y + basePt.y) < WINDOW_BOTTOM)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);
			//めり込んだ分の計算
			float boundary = (pChara->m_pMove->m_pos.y +basePt.y) - WINDOW_BOTTOM;

			//最終的に戻す値
			pChara->m_pMove->m_pos.y -= boundary;

			//リセットする値
			pChara->m_pMove->m_vel.y = 0.0f;
			pChara->m_pMove->m_accele.y = 0.0f;

			//ジャンプの停止はいったん削除化コメントアウトしておく
			//この部分も考えなくてはならないが今考えるとまとまらないので
			//今は考えない
		}
	}
}

//=============================================
//左にある画面領域との衝突判定
//=============================================
void CCollisionTerritoryEndOfScreenLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうかをチェック
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//下に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.x + basePt.x) < WINDOW_LEFT)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);

			//めり込んだ分の計算
			float boundary = (pChara->m_pMove->m_pos.x + basePt.x) - WINDOW_LEFT;

			//最終的に戻す値
			pChara->m_pMove->m_pos.x -= boundary;

			//リセットする値
			pChara->m_pMove->m_vel.x = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;

			//敵なら殺す
			if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
			{
				pChara->m_isAlive = false;
				pChara->m_activeFlag = false;
			}
		}
	}
}

//=============================================
//下のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryMapChipBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうか
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//衝突しているかどうか
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//衝突していた

			//ブロックのタイプを取得
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//イベントコールバックの呼び出し
				this->callEventCallback(pChara, (int)mapChipID);
				//戻すべき位置の計算

				//タイルのサイズ(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//キャラクターがめり込んでいるブロックの下のブロックの位置 = ブロック数 * ブロック高さ
				float blockPos = floor((pt.y) / tileSize.height) * tileSize.height;

				//戻すべき位置
				//	修正位置(キャラクターがめり込んでいるブロックの上の位置) =
				//	キャラクターがめり込んでいるブロックの下のブロックの位置 + ブロック1個分 - 位置y
				//めり込んだ分の計算
				float boundary = pt.y - (blockPos + tileSize.height);

				//最終的に戻す値(めり込んだ分を戻す)
				pChara->m_pMove->m_pos.y -= boundary;

				//リセットする値
				pChara->m_pMove->m_vel.y = 0.0f;
				pChara->m_pMove->m_accele.y = 0.0f;

			}
		}
	}
}


//=============================================
//上のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryMapChipTop::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//上に移動しているかどうか
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//衝突しているかどうか
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//衝突していた

			//ブロックのタイプを取得
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//イベントコールバックの呼び出し
				this->callEventCallback(pChara, (int)mapChipID);

				//戻すべき位置の計算

				//タイルのサイズ(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//キャラクターがめり込んでいるブロックの上のブロックの位置 = ブロック数 * ブロック高さ
				float blockPos = floor((pt.y) / tileSize.height) * tileSize.height;

				//戻すべき位置
				//	修正位置(キャラクターがめり込んでいるブロックの上の位置) =
				//	キャラクターがめり込んでいるブロックの上のブロックの位置 + ブロック1個分 - 位置y
				//めり込んだ分の計算
				float boundary = pt.y - (blockPos);

				//最終的に戻す値(めり込んだ分を戻す)
				pChara->m_pMove->m_pos.y -= boundary;

				//リセットする値
				pChara->m_pMove->m_vel.y = 0.0f;
				pChara->m_pMove->m_accele.y = 0.0f;

			}
		}
	}
}

//=============================================
//右のマップチップ領域との衝突判定
//=============================================
/**
*@desc	衝突判定
*@param	衝突対象
*/

void CCollisionTerritoryMapChipRight::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//右に移動しているかどうか
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//衝突しているかどうか
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//衝突していた

			//ブロックのタイプを取得
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//イベントコールバックの呼び出し
				this->callEventCallback(pChara, (int)mapChipID);
				//戻すべき位置の計算

				//タイルのサイズ(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//キャラクターがめり込んでいるブロックの上のブロックの位置 = ブロック数 * ブロック高さ
				float blockPos = floor((pt.x) / tileSize.width) * -tileSize.width;

				//戻すべき位置
				//	修正位置(キャラクターがめり込んでいるブロックの上の位置) =
				//	キャラクターがめり込んでいるブロックの上のブロックの位置 + ブロック1個分 - 位置y
				//めり込んだ分の計算
				float boundary = pt.x + (blockPos);

				//最終的に戻す値(めり込んだ分を戻す)
				pChara->m_pMove->m_pos.x -= boundary;

				

				//キャラクターが敵なら
				if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
				{
					//向きを変える
					pChara->m_moveVector *= -1;

					pChara->m_pMove->m_vel.x *= -1;
				}
				else
				{
					//リセットする値
					pChara->m_pMove->m_vel.x = 0.0f;
					pChara->m_pMove->m_accele.x = 0.0f;
				}

			}
		}
	}
}


//=============================================
//左のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/

void CCollisionTerritoryMapChipLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//左に移動しているかどうか
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//衝突しているかどうか
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//衝突していた

			//ブロックのタイプを取得
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//イベントコールバックの呼び出し
				this->callEventCallback(pChara, (int)mapChipID);

				//戻すべき位置の計算

				//タイルのサイズ(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//キャラクターがめり込んでいるブロックの上のブロックの位置 = ブロック数 * ブロック高さ
				float blockPos = floor((pt.x) / tileSize.width) * tileSize.width;

				//戻すべき位置
				//	修正位置(キャラクターがめり込んでいるブロックの上の位置) =
				//	キャラクターがめり込んでいるブロックの上のブロックの位置 + ブロック1個分 - 位置y
				//めり込んだ分の計算
				float boundary = pt.x - (blockPos + tileSize.width);

				//最終的に戻す値(めり込んだ分を戻す)
				pChara->m_pMove->m_pos.x -= boundary;

				//キャラクターが敵なら
				if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
				{
					//向きを変える
					pChara->m_moveVector *= -1;

					pChara->m_pMove->m_vel.x *= -1;
				}
				else
				{
					//リセットする値
					pChara->m_pMove->m_vel.x = 0.0f;
					pChara->m_pMove->m_accele.x = 0.0f;
				}

			}
		}
	}
}


//=============================================
//キャラクターの左との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryCharacterLeft::collision(CCharacter* pChara,CCharacter* pSelf, cocos2d::Point basePt)
{
	//右に移動しているかどうか
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + pChara->m_pBody->m_right, pChara->m_pMove->m_pos.y + basePt.y);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//自分の衝突判定矩形
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//衝突対象の衝突判定矩形
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//衝突判定
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
				this->callEventCallback(pSelf);

			//めり込んだ分の計算
			float boundary = ((Charapt.x) - (Selfpt.x));
			//最終的に戻す値
			pChara->m_pMove->m_pos.x -= boundary;

			pChara->m_pMove->m_accele.x = 0.0f;
			pChara->m_pMove->m_vel.x = 0.0f;

		}
	}
}

//=============================================
//キャラクターの右との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryCharacterRight::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//左に移動しているかどうか
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + pChara->m_pBody->m_left, pChara->m_pMove->m_pos.y + basePt.y);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//自分の衝突判定矩形
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//衝突対象の衝突判定矩形
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//衝突判定
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
				this->callEventCallback(pSelf);

			//めり込んだ分の計算
			float boundary = ((Charapt.x) - (Selfpt.x));
			//最終的に戻す値
			pChara->m_pMove->m_pos.x -= boundary;


			pChara->m_pMove->m_vel.x = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;

		}
	}
}


//=============================================
//キャラクターの上との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryCharacterTop::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//下に移動しているかどうか
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + pChara->m_pBody->m_bottom);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//自分の衝突判定矩形
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//衝突対象の衝突判定矩形
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//衝突判定
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
			{
				pChara->collisionBottomCallback(0);
				this->callEventCallback(pSelf);
			}
			//めり込んだ分の計算
			float boundary = ((Charapt.y) - (Selfpt.y));
			//最終的に戻す値
			pChara->m_pMove->m_pos.y -= boundary;

			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_vel.y = 0.0f;

		}
	}
}


//=============================================
//キャラクターの下との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryCharacterBottom::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//上に移動しているかどうか
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{
		//衝突してきた点(キャラクターの点)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + pChara->m_pBody->m_top);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//自分の衝突判定矩形
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//衝突対象の衝突判定矩形
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//衝突判定
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
			{
				this->callEventCallback(pSelf);
			}
			//めり込んだ分の計算
			float boundary = ((Charapt.y) - (Selfpt.y));
			//最終的に戻す値
			pChara->m_pMove->m_pos.y -= boundary;

			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_vel.y = 0.0f;

		}
	}
}




//=============================================
//画面端との衝突判定空間
//=============================================
/**
*@desc	衝突判定
*@param	衝突対象のキャラクター
*/
void CCollisionAreaEndOfScreen::collision(CCharacter* pChara)
{
	//領域分繰り返す
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//基準点分繰り返す
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//基準点の中に登録されている衝突判定領域タイプが一致したらその基準点で衝突判定を行う
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}

//=============================================
//画面上にあるすべてのマップチップとの衝突判定空間
//つまりマップとの衝突判定空間
//=============================================
/**
*@desc	衝突判定
*@param 衝突対象のキャラクター
*/
void CCollisionAreaMap::collision(CCharacter* pChara)
{
	//領域分繰り返す
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//基準点分繰り返す
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//基準点の中に登録されている衝突判定領域タイプが一致したらその基準点で衝突判定を行う
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}

//=============================================
//下のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryOutOfScreenBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうかをチェック
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{

		//下に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.y + basePt.y) < WINDOW_BOTTOM)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);

		}
	}
}

//=============================================
//上のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/
void CCollisionTerritoryOutOfScreenTop::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうかをチェック
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{

		//下に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.y + basePt.y) > WINDOW_TOP)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);

		}
	}
}

//=============================================
//右のマップチップ領域との衝突判定
//=============================================
/**
*@desc	衝突判定
*@param	衝突対象
*/

void CCollisionTerritoryOutOfScreenRight::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//下に移動しているかどうかをチェック
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//右に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.x + basePt.x) > WINDOW_RIGHT*3)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);

		}
	}
}


//=============================================
//左のマップチップ領域との衝突判定
//=============================================
/***
*@desc	衝突判定
*@param	衝突対象
*/

void CCollisionTerritoryOutOfScreenLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//左に移動しているかどうか
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//下に画面端があるかどうかをチェック
		if ((pChara->m_pMove->m_pos.x + basePt.x) < WINDOW_LEFT)
		{
			//イベントコールバックの呼び出し
			this->callEventCallback(pChara);

		}
	}
}


//=============================================
//画面上にあるすべてのマップチップとの衝突判定空間
//つまりマップとの衝突判定空間
//=============================================
/**
*@desc	衝突判定
*@param 衝突対象のキャラクター
*/
void CCollisionAreaOutOfScreen::collision(CCharacter* pChara)
{
	//領域分繰り返す
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//基準点分繰り返す
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//基準点の中に登録されている衝突判定領域タイプが一致したらその基準点で衝突判定を行う
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}


//=============================================
//キャラクターとの衝突判定空間
//=============================================
/**
*@desc	衝突判定
*@param	衝突対象のキャラクター
*/
void CCollisionAreaCharacter::collision(CCharacter* pChara,CCharacter* pSelf)
{
	//領域分繰り返す
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//基準点分繰り返す
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//基準点の中に登録されている衝突判定領域タイプが一致したらその基準点で衝突判定を行う
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pSelf, pBasePt->m_pt);
			}
		}
	}
}