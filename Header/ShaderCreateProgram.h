#ifndef SHADERCREATEPROGRAM_H
#define SHAdERCREATEPROGRAM_H

//include定義
#include "Common.h"

//Define定義
#define SHADER_STRING_LINE_MAX		256			//シェーダーの1行の最大文字数
#define SHADER_STRING_ALL_MAX		10240		//シェーダーの全文の最大文字数
#define SHADER_FILE_NAME_MAX		64			//シェーダーのファイル名最大文字数（ディレクトリ名含む）

class ShaderManager
{

public:

	//コンストラクタ
	ShaderManager::ShaderManager();

	//デストラクタ
	ShaderManager::~ShaderManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　頂点・フラグメントシェーダーをリンクし、ShaderProgramを作成する
	*	引数
	*	　p_vertex_shader_file		：[I/ ]　バーテックスシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
	*	　p_fragment_shader_file	：[I/ ]　フラグメントシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void CreateShaderProgram(const char* p_vertex_shader_file, const char* p_fragment_shader_file);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Attribute変数のロケーションIDを生成（ほぼ glGetAttribLocation と同じです）
	*	　分かりやすいように引数を少なくしたのと、エラー管理を一元化した点が違うのみです。
	*	引数
	*	　p_attribute_name			：[I/ ]　シェーダーで使用するAttribute変数の名前
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	GLint GetAttribLocation(const GLchar* p_attribute_name);

	//シェーダープログラム返却
	inline GLint GetShaderProgram()	{ return m_ShaderProgram; }

private:

	//変数定義
	GLint m_ShaderProgram;		//プログラムオブジェクト
	char m_vertex_shader_file[SHADER_FILE_NAME_MAX];	//バーテックスシェーダーファイル名
	char m_fragment_shader_file[SHADER_FILE_NAME_MAX];	//フラグメントシェーダーファイル名

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　シェーダーファイルの読み込みを行う
	*	引数
	*	　p_shader_file_name	：[I/ ]　各シェーダーのファイル名（Shaderフォルダに格納されている必要があります）
	*	　p_shader_source		：[ /O]　各シェーダーのソースデータ
	*	　p_source_size			：[I/ ]　シェーダーの全文の最大文字数
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Shader_FileLoad(const char* p_shader_file_name, char* p_shader_source, const int p_source_size);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　シェーダーソースの読み込みを行う
	*	引数
	*	　p_shader_source		：[I/ ]　各シェーダーのソースデータ
	*	　p_gl_xxxx_shader		：[I/ ]　作成するシェーダーオブジェクト（バーテックス or フラグメント）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	GLint Shader_SourceLoad(const char* p_shader_source, const GLuint p_gl_xxxx_shader);
};
#endif