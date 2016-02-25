#ifndef MAINDRAW_H
#define MAINDRAW_H

//include定義
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"

//Define定義


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
	void Prep();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　メイン描画を開始する
	*	引数
	*	　window		：[I/ ]　描画先のウィンドウを指定する
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Draw(GLFWwindow *const p_window);

private:

	ShaderManager *m_MainShader;		//メインシェーダーオブジェクト
	GLint m_attr_pos;					//頂点データ
	GLint m_attr_color;					//カラーデータ
	GLint m_ModelView_matrix;			//モデルビューマトリックス（オブジェクト移動用のマトリックス）
	GLint m_Proj_matrix;				//モデルビューマトリックス（3D空間にするためのマトリクス）

	float move_x;						//移動量を管理する変数（X値）
	float move_y;						//移動量を管理する変数（Y値）
};
#endif