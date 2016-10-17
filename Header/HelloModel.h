#ifndef HELLO_MODEL_H
#define HELLO_MODEL_H

//include定義
#include "Common.h"
#include "BaseDraw.h"
#include "ModelManager.h"

class HelloModel : public BaseDraw
{

public:
	//コンストラクタ
	HelloModel();

	//デストラクタ
	~HelloModel();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ハローモデル描画（モデルデータのお試し描画）の準備をする
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Prepare(const GlobalData &p_Global);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ハローモデル描画（モデルデータのお試し描画）を開始する
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Drawing(const GlobalData &p_Global);

private:

	ModelManager *m_Model;		//モデル管理オブジェクト
};
#endif