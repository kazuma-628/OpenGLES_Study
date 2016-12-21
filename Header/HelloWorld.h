#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

//include定義
#include "Common.h"
#include "BaseDraw.h"

class ShaderManager;

class HelloWorld : public BaseDraw
{

public:
	//コンストラクタ
	HelloWorld();

	//デストラクタ
	~HelloWorld();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ハローワールド描画（OpenGLの基本的な描画）の準備をする
	*	引数
	*	　p_Global			：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Prepare(const GlobalData &p_Global);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ハローワールド描画（OpenGLの基本的な描画）を開始する
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
		ucvec3 Color;
	}Vec3_Color3;

	shared_ptr<ShaderManager> m_MainShader = nullptr;		//メインシェーダーオブジェクト
	GLint m_attr_pos = -1;					//頂点データ
	GLint m_attr_color = -1;				//カラーデータ
	GLint m_ProjModel_matrix = -1;			//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
};
#endif