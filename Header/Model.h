#ifndef MODEL_H
#define MODEL_H

//include定義
#include "Common.h"

////////////////////////////////////
// モデルデータ情報構造体

//頂点パラメータ情報（[VertexAttribPointer]用）
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

//バッファーデータ用（glBufferData等）パラメータ情報
typedef struct
{
	GLsizei size;		//全頂点のサイズ（byte）
	GLvoid *data;		//全頂点が格納された先頭アドレス
}BufferDataInfo;

//モデルデータ情報（オリジナル用）
typedef struct
{
	VertexAttribPointerInfo Vertex;		//頂点情報
	VertexAttribPointerInfo Color;		//カラー情報
	DrawArraysInfo DrawArrays;			//描画情報
	BufferDataInfo BufferData;			//バッファー情報（VBOを）
}ModelInfo_Original;

//モデルデータ（インデックス使用版）情報（オリジナル用）
typedef struct
{
	VertexAttribPointerInfo Vertex;		//頂点情報
	VertexAttribPointerInfo Color;		//カラー情報
	DrawElementsInfo DrawElements;		//描画情報
	BufferDataInfo BufferData;			//バッファー情報
}ModelInfo_index_Original;


class Model
{

public:
	//コンストラクタ
	Model();

	//デストラクタ
	~Model();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する
	*	　（[glDrawArrays]として登録するモデルデータ）
	*	引数
	*	　p_vbo			：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
	*					　		 VBOとして使用する場合、「glBufferData」でデータを登録してから「glDrawArrays」する。
	*							 登録するデータは「BufferData」メンバに格納されている情報を使用すれば良い。
	*							 ※「false」を指定した場合は「BufferData」メンバには情報が格納されないので扱いに注意
	*	　p_ModelData	：[ /O]　モデルデータ情報
	*							 ※注意※
	*							 モデルデータが不要になった時点で、必ず[PiercedCube_free]をコールしてください。
	*							 （モデルデータのメモリを解放します）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void GetPiercedCube(bool p_vbo, ModelInfo_Original *p_ModelData);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルデータのメモリを解放します
	*	引数
	*	　p_ModelData	：[ /O]　モデルデータ（メモリを解放後「NULL」が格納されるという意味で[ /O]指定）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void PiercedCube_free(ModelInfo_Original *p_ModelData);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する（インデックス版）
	*	　（[glDrawElements]用パラメータ情報）
	*	引数
	*	　p_vbo			：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
	*						　	 VBOとして使用する場合、「glBufferData」でデータを登録してから「glDrawElements」する。
	*							 登録するデータは「BufferData」メンバに格納されている情報を使用すれば良い。
	*							 ※「false」を指定した場合は「BufferData」メンバには情報が格納されないので扱いに注意
	*	　p_ModelData	：[ /O]　モデルデータ情報
	*							 ※注意※
	*							 モデルデータが不要になった時点で、必ず[PiercedCube_index_free]をコールしてください。
	*							 （モデルデータのメモリを解放します）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void GetPiercedCube_index(bool p_vbo, ModelInfo_index_Original *p_ModelData);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルデータのメモリを解放します
	*	引数
	*	　p_ModelData	：[ /O]　モデルデータ（メモリを解放後「NULL」が格納されるという意味で[ /O]指定）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void PiercedCube_index_free(ModelInfo_index_Original *p_ModelData);

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

};

#endif