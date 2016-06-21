#ifndef MAIN_DRAW_H
#define MAIN_DRAW_H

//include定義
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
#include "ResourceManager.h"

//グラフィック空間の座標系
typedef struct
{
	GLfloat x;		//X座標
	GLfloat y;		//Y座標
	GLfloat z;		//Z座標
}Vector;


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
	*	　p_WindowManager		：[I/ ]　ウィンドウ管理オブジェクト
	*	　p_DeviceManager		：[I/ ]　Key管理オブジェクト
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Drawing(WindowManager* p_WindowManager, DeviceManager* p_DeviceManager);

private:

	ShaderManager *m_MainShader;		//メインシェーダーオブジェクト
	GLint m_attr_pos;					//頂点データ
	GLint m_attr_color;					//カラーデータ
	GLint m_ModelView_matrix;			//モデルビューマトリックス（オブジェクト移動用のマトリックス）
	GLint m_Proj_matrix;				//モデルビューマトリックス（3D空間にするためのマトリクス）

	Vector m_Rotate;				//回転量を管理する変数
	Vector m_Translate;				//移動量を管理する変数
};
#endif