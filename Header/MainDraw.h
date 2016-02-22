#ifndef MAINDRAW_H
#define MAINDRAW_H

//include定義
#include "Common.h"
#include "ShaderManager.h"

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
};
#endif