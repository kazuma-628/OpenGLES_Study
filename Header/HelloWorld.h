#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

//include定義
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"

class HelloWorld
{

public:
	//コンストラクタ
	HelloWorld();

	//デストラクタ
	~HelloWorld();

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

	// 頂点データ構造体
	typedef struct
	{
		vec3 Vector;
		bColor3 Color;
	}Vec3_bColor3;

	ShaderManager *m_MainShader;		//メインシェーダーオブジェクト
	GLint m_attr_pos;					//頂点データ
	GLint m_attr_color;					//カラーデータ
	GLint m_ProjModel_matrix;			//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
};
#endif