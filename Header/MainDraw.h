#ifndef MAIN_DRAW_H
#define MAIN_DRAW_H

//include定義
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
#include "Texture.h"

class MainDraw
{

public:
	//コンストラクタ
	MainDraw();

	//デストラクタ
	~MainDraw();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　メイン描画の準備をする
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Prepare();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　メイン描画を開始する
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Drawing(const GlobalData &p_Global);

private:

	ShaderManager *m_MainShader;		//メインシェーダーオブジェクト
	GLint m_attr_pos;					//頂点データ
	GLint m_attr_color;					//カラーデータ
	GLint m_ProjModel_matrix;			//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
};
#endif