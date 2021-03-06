﻿#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

//include定義
#include "Common.h"

class ShaderManager;

//モデルデータのフォーマット
//ここの定義を変更する場合は、「Model.frag」の上部「#define」定義も同じように変更してください
enum class ModelFormat : uint16_t
{
	UNDEFINED = 0,				//未定義（初期化された状態）
	OBJ,						//OBJ形式のモデルファイル（OBJファイルに指定があればMTLファイルも読み込まれる）
	
	//以下、自作モデルデータ（特殊パターン）
	ORIGINAL_PIERCED_CUBE,		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
	ORIGINAL_PIERCED_CUBE2,		//オリジナルフォーマットで穴あきのキューブデータ（エッジ無し）
};
	
class ModelManager
{

public:
	//コンストラクタ
	ModelManager();

	//デストラクタ
	~ModelManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルファイルからモデルデータの読み込みを行います。
	*	　既にモデルデータが読み込まれている場合は、データを破棄（メモリ解放）してから新しく読み込みします。
	*	　読み込んだモデルデータの描画は「ModelDataDraw」関数で行います。
	*	引数
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
	*							 [Resource/Model/]フォルダ以降のファイルパスを入力してください。
	*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.obj」）
	*					　　　※「p_ModelFormat」で自作モデルデータ（特殊パターン）を指定するときは、
	*							「p_FileName」は「空("")」を指定してください。
	*	　p_ModelFormat	：[I/ ]　モデルファイルのフォーマット（詳細は定義部分のコメント参照）
	*
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void FileDataLoad(const string &p_FileName, ModelFormat p_ModelFormat);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルデータを破棄（メモリ解放）します。
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void FileDataFree(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルデータを描画します。
	*	　予めモデルデータを「FileDataLoad」関数で読み込んでおく必要があります。
	*
	*	　※本関数では描画のみしか実行しません
	*　　　「glClearColor, glClear, glViewport」などの設定は関数コール前に必要に応じて行ってください。
	*	引数
	*	　p_ModelViewMat	：[I/ ]　描画に使用するモデルビューマトリクス
	*	　p_ProjectionMat	：[I/ ]　描画に使用するプロジェクションマトリクス
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void DataDraw(const mat4 &p_ModelViewMat, const mat4 &p_ProjectionMat);

private:

	static const string MODEL_FILE_DIR;		//モデルファイルの保存ディレクトリ

	///////////////////////////////
	// 描画情報データ構造体

	//[glVertexAttribPointer]用パラメータ情報
	struct VertexAttribPointerInfo
	{
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		GLvoid *pointer;
	};

	//[glDrawArrays]用パラメータ情報
	struct DrawArraysInfo
	{
		GLenum mode;
		GLint first;
		GLsizei count;
	};

	//[glDrawElements]用パラメータ情報
	struct DrawElementsInfo
	{
		GLenum mode;
		GLsizei count;
		GLenum type;
		GLvoid *indices;
		uint16_t MaterialIndex;		//特殊パラメータ（glDrawElementsには直接使用しない）
									//どのマテリアル情報を使用すればよいのかを示すパラメータ
	};

	//マテリアル情報
	struct MaterialInfo
	{
		vec3 ambient;				//アンビエント値
		vec3 diffuse;				//ディフューズ値
		vec3 specular;				//スペキュラ値
		GLfloat shininess;			//シャイネス値
		GLfloat alpha;				//アルファ値
		GLuint ambientTexObj;		//テクスチャオブジェクト（アンビエント） 
		GLuint diffuseTexObj;		//テクスチャオブジェクト（ディフューズ） 
		GLuint specularTexObj;		//テクスチャオブジェクト（スペキュラ）
		GLuint bumpMapTexObj;		//テクスチャオブジェクト（バンプマップ）
	};

	///////////////////////////////
	// 通常構造体

	// 頂点データ構造体
	struct Vec3_Color3
	{
		vec3 Position;
		ucvec3 Color;
	};

	struct MaterialTex
	{
		string Name;
		GLuint *TexObj;
	};

	///////////////////////////////
	//【モデルデータ情報】
	// ※モデルデータのフォーマットによって設定されるメンバと設定されないメンバがある

	struct ModelInfo
	{
		VertexAttribPointerInfo Position;			//頂点座標情報
		VertexAttribPointerInfo Normal;				//法線情報
		VertexAttribPointerInfo Color;				//カラー情報
		VertexAttribPointerInfo TexCoord;			//テクスチャ座標情報
		vector<DrawElementsInfo> DrawElements;		//描画情報（DrawElements版）
		vector<MaterialInfo> Material;				//マテリアル情報
		GLuint BufferObj_v;							//VBO、バッファーオブジェクト（頂点データ用）
		GLuint BufferObj_i;							//VBO、バッファーオブジェクト（インデックスデータ用）
		ModelFormat ModelFormat;					//モデルデータのフォーマット
	};

	///////////////////////////////
	// メンバ変数定義

	ModelInfo m_ModelInfo = { 0 };
	
	//ロケーション
	static shared_ptr<ShaderManager> m_ModelShader;		//モデル描画用のシェーダーオブジェクト
	static GLint m_attr_Position;			//頂点座標のロケーション
	static GLint m_attr_Normal;				//法線ロケーション
	static GLint m_attr_Color;				//カラーロケーション
	static GLint m_attr_TexCoord;			//テクスチャ座標のロケーション
	static GLint m_unif_ModelFormat;		//モデルデータのフォーマットのロケーション
	static GLint m_unif_ModelViewMat;		//モデルビューマトリクスのロケーション
	static GLint m_unif_ProjectionMat;		//プロジェクションマトリクスのロケーション
	static GLint m_unif_RotateMat;			//回転行列のロケーション
	static GLint m_unif_Ambient;			//アンビエント値のロケーション
	static GLint m_unif_Diffuse;			//ディフューズ値のロケーション
	static GLint m_unif_Specular;			//スペキュラ値のロケーション
	static GLint m_unif_Shininess;			//シャイネス値のロケーション
	static GLint m_unif_Alpha;				//アルファ値のロケーション
	static GLint m_unif_AmbientTexFlag;		//テクスチャ（アンビエント） 有り・無しフラグのロケーション
	static GLint m_unif_DiffuseTexFlag;		//テクスチャ（ディフューズ） 有り・無しフラグのロケーション
	static GLint m_unif_SpecularTexFlag;	//テクスチャ（スペキュラ）有り・無しフラグのロケーション
	static GLint m_unif_BumpMapTexFlag;		//テクスチャ（バンプマップ）有り・無しフラグのロケーション
	static GLint m_unif_AmbientTex;			//テクスチャ（アンビエント） のロケーション
	static GLint m_unif_DiffuseTex;			//テクスチャ（ディフューズ）のロケーション
	static GLint m_unif_SpecularTex;		//テクスチャ（スペキュラ）のロケーション
	static GLint m_unif_BumpMapTex;			//テクスチャ（バンプマップ）のロケーション


	///////////////////////////////
	// 関数定義

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　OBJ形式のモデルファイルからモデルデータの読み込みを行います
	*	引数
	*	　p_DirFileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
	*					　		（ディレクトリ構造も含んだフルパスを設定）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void FileLoad_OBJ(const string &p_DirFileName);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する（エッジ有り）
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void DataLoad_PiercedCube(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　穴あきキューブを取得する（エッジ無し）
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void DataLoad_PiercedCube2(void);
};

#endif