#ifndef MODEL_H
#define MODEL_H

//include定義
#include "Common.h"
#include "OBJLoader.h"
#include "ShaderManager.h"
#include "Texture.h"

//#define定義
#define MODEL_FILE_DIR	"../Resource/Model/"	//モデルファイルの保存ディレクトリ

//モデルデータのフォーマット
//ここの定義を変更する場合は、「Model.frag」の上部「#define」定義も同じように変更してください
typedef enum
{
	FILE_FORMAT_OBJ = 1,				//OBJ形式のモデルファイル（OBJファイルに指定があればMTLファイルも読み込まれる）
	
	//以下、自作モデルデータ（特殊パターン）
	ORIGINAL_FORMAT_PIERCED_CUBE,		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
	ORIGINAL_FORMAT_PIERCED_CUBE2,		//オリジナルフォーマットで穴あきのキューブデータ（エッジ無し）
}FileFotmat;

class Model
{

public:
	//コンストラクタ
	Model();

	//デストラクタ
	~Model();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルファイルからモデルデータの読み込みを行います。
	*	　既にモデルデータが読み込まれている場合は、データを破棄（メモリ解放）してから新しく読み込みします。
	*	　読み込んだモデルデータの描画は「ModelDataDraw」関数で行います。
	*	引数
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
	*							 [Resource/Model/]フォルダ以降のファイルパスを入力してください。
	*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.obj」）
	*					　　　※「p_FileFotmat」で自作モデルデータ（特殊パターン）を指定するときは、
	*							「p_FileName」は「NULL」を指定してください。
	*	　p_FileFotmat	：[I/ ]　モデルファイルのフォーマット（詳細は定義部分のコメント参照）
	*
	*					　　　※「p_FileFotmat」で自作モデルデータ（特殊パターン）を指定するときは、
	*							「p_FileName」は「NULL」を指定してください。
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void FileDataLoad(const char* p_FileName, FileFotmat p_FileFotmat);

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
	*	　p_ProjModelMat	：[I/ ]　「プロジェクション × モデルビュー」を乗算済みの行列
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void DataDraw(mat4 &p_ProjModelMat);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　モデルデータを描画するための準備をします
	*	引数
	*	　p_Global		：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void Prepare(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　破棄(終了)処理（変数などを破棄します）
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void Destroy(void);

private:

	///////////////////////////////
	// 描画情報データ構造体

	//[glVertexAttribPointer]用パラメータ情報
	typedef struct
	{
		GLuint index;
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
		GLvoid *indices;
		unsigned int MaterialIndex;		//特殊パラメータ（glDrawElementsには直接使用しない）
										//どのマテリアル情報を使用すればよいのかを示すパラメータ
	}DrawElementsInfo;

	//マテリアル情報
	typedef struct
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
	}MaterialInfo;

	///////////////////////////////
	// 通常構造体

	// 頂点データ構造体
	typedef struct
	{
		vec2 Position;
		bColor3 Color;
	}Vec2_bColor3;

	// 頂点データ構造体
	typedef struct
	{
		vec2 Position;
		bColor4 Color;
	}Vec2_bColor4;

	// 頂点データ構造体
	typedef struct
	{
		vec3 Position;
		bColor3 Color;
	}Vec3_bColor3;

	// 頂点データ構造体
	typedef struct
	{
		vec3 Position;
		bColor4 Color;
	}Vec3_bColor4;

	typedef struct
	{
		char *Name;
		GLuint *TexObj;
	}MaterialTex;

	///////////////////////////////
	//【モデルデータ情報】
	// ※モデルデータのフォーマットによって設定されるメンバと設定されないメンバがある

	typedef struct
	{
		VertexAttribPointerInfo Position;			//頂点座標情報
		VertexAttribPointerInfo Normal;				//法線情報
		VertexAttribPointerInfo Color;				//カラー情報
		VertexAttribPointerInfo TexCoord;			//テクスチャ座標情報
		std::vector<DrawElementsInfo> DrawElements;	//描画情報（DrawElements版）
		std::vector<MaterialInfo> Material;			//マテリアル情報
		GLuint BufferObj_v;							//VBO、バッファーオブジェクト（頂点データ用）
		GLuint BufferObj_i;							//VBO、バッファーオブジェクト（インデックスデータ用）
		FileFotmat FileFotmat;						//モデルデータのフォーマット
		void *ClassObj;								//モデルデータの読み込み処理をしたクラスのオブジェクト
	}ModelInfo;

	///////////////////////////////
	// メンバ変数定義

	ModelInfo m_ModelInfo;
	
	//ロケーション
	static ShaderManager m_ModelShader;		//モデル描画用のシェーダーオブジェクト
	static GLint m_attr_Position;			//頂点座標のロケーション
	static GLint m_attr_Normal;				//法線ロケーション
	static GLint m_attr_Color;				//カラーロケーション
	static GLint m_attr_TexCoord;			//テクスチャ座標のロケーション
	static GLint m_unif_FileFotmat;			//モデルデータのフォーマットのロケーション
	static GLint m_unif_ProjModelMat;		//「プロジェクション × モデルビュー」を乗算済みの行列のロケーション
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
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
	*					　		（ディレクトリ構造を含まないファイル名を設定、デバッグ情報表示として使用）
	*	　p_DirFileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
	*					　		（ディレクトリ構造も含んだフルパスを設定）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void FileLoad_OBJ(const char* p_FileName, const char* p_DirFileName);

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