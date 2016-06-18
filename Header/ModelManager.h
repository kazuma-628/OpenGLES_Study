#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

//include定義
#include "Common.h"

////////////////////////////////////
// モデルデータ情報構造体

//頂点パラメータ情報
typedef struct
{
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid *pointer;
}VertexAttribPointerInfo;

//[glDrawArrays]用パラメータ情報
typedef struct
{
	GLenum mode;
	GLint first;
	GLsizei count;
}DrawArraysInfo;

//[glDrawElements]用パラメータ情報
typedef struct
{
	GLenum mode;
	GLsizei count;
	GLenum type;
	const void *indices;
}DrawElementsInfo;

//モデルデータ情報
typedef struct
{
	VertexAttribPointerInfo Vertex;
	VertexAttribPointerInfo Color;
	DrawArraysInfo DrawArrays;
}ModelDataInfo;

//モデルデータ（インデックス使用版）情報
typedef struct
{
	VertexAttribPointerInfo Vertex;
	VertexAttribPointerInfo Color;
	DrawElementsInfo DrawElement;
}ModelDataInfo_index;

class ModelManager
{

public:
	//コンストラクタ
	ModelManager();

	//デストラクタ
	~ModelManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する
	*	　（[glDrawArrays]として登録するモデルデータ）
	*	引数
	*	　p_ModelData		：[ /O]　モデルデータ情報
	*	　p_vbo				：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void GetPiercedCube(ModelDataInfo *p_ModelData, bool p_vbo);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する（インデックス版）
	*	　（[glDrawElements]用パラメータ情報）
	*	引数
	*	　p_ModelData		：[ /O]　モデルデータ情報
	*	　p_vbo				：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void GetPiercedCube_index(ModelDataInfo_index *p_ModelData, bool p_vbo);

private:

	///////////////////////////////
	// 構造体定義

	// 頂点データ構造体
	typedef struct
	{
		Vec2 Vector;
		bColor3 Color;
	}Vec2_bColor3;

	// 頂点データ構造体
	typedef struct
	{
		Vec2 Vector;
		bColor4 Color;
	}Vec2_bColor4;

	// 頂点データ構造体
	typedef struct
	{
		Vec3 Vector;
		bColor3 Color;
	}Vec3_bColor3;

	// 頂点データ構造体
	typedef struct
	{
		Vec3 Vector;
		bColor4 Color;
	}Vec3_bColor4;

	// 頂点ポインタ構造体
	typedef struct
	{
		GLvoid *vertex;
	}Vertex;

	// 頂点ポインタ構造体
	typedef struct
	{
		GLvoid *vertex;
		GLvoid *index;
	}Vertex_index;

	///////////////////////////////
	// 変数

	Vertex		 m_PiercedCube;				//穴あきキューブ用の頂点データ
	Vertex_index m_PiercedCube_index;		//穴あきキューブ用の頂点データ（インデックス版）
};

#endif