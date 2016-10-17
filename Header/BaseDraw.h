#ifndef BASE_DRAW_H
#define BASE_DRAW_H

//include定義
#include "Common.h"

class BaseDraw
{

public:
	//コンストラクタ
	BaseDraw();

	//デストラクタ
	virtual ~BaseDraw();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　描画の準備をする（純粋仮想関数）
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	virtual void Prepare(const GlobalData &p_Global) = 0;
	
	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　描画を開始する（純粋仮想関数）
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	virtual void Drawing(const GlobalData &p_Global) = 0;

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　描画の再準備（資源の再作成）フラグを立てる
	*	引数
	*	　RePrepareFlag		：[I/ ]　再準備フラグ（trueで再準備必要）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	inline void SetRePrepareFlag(const bool p_RePrepareFlag)
	{
		RePrepareFlag = p_RePrepareFlag;
	}

protected:

	bool PrepareCompFlag;		//描画準備完了フラグ
	bool RePrepareFlag;			//描画再準備フラグ（trueで再準備必要）
};
#endif