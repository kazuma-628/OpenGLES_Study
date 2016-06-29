#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

//include定義
#include "Common.h"

//Define定義
#define SHADER_FILE_NAME_MAX		64				//シェーダーのファイル名最大文字数（ディレクトリ名含む）
#define SHADER_FILE_DIR				"..\\Shader\\"	//シェーダーファイルの保存ディレクトリ
#define ATTRIB_INFO_MAX				128				//アトリビュート変数管理用の最大数
#define ATTRIB_INFO_NAME_MAX		64				//アトリビュート変数名の最大文字数
#define UNIFORM_INFO_MAX			128				//ユニフォーム変数管理用の最大数
#define UNIFORM_INFO_NAME_MAX		64				//ユニフォーム変数名の最大文字数

class ShaderManager
{

public:

	//コンストラクタ
	ShaderManager();

	//デストラクタ
	~ShaderManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　バーテックス・フラグメントシェーダーのソースを指定されたファイルから読み込み、
	*	　コンパイル及びリンクして、プログラムオブジェクトを作成する
	*	引数
	*	　p_vertex_file_name			：[I/ ]　バーテックスシェーダーのファイル名
	*	　p_fragment_file_name			：[I/ ]　フラグメントシェーダーのファイル名
	*	　p_geometry_file_name			：[I/ ]　ジオメトリシェーダーのファイル名（使用しない場合はNULLを指定）
	*	　p_tess_control_file_name		：[I/ ]　テッセレーションコントロールシェーダーのファイル名（使用しない場合はNULLを指定）
	*	　p_tess_evaluation_file_name	：[I/ ]　テッセレーション評価シェーダーのファイル名（使用しない場合はNULLを指定）
	*
	*	※どのファイル名も[Shader]フォルダ以降のファイルパスを入力してください
	*	　ディレクトリをまたぐときは「\\」で区切ってください。（例「xxx\\xxx.vert」)
	*
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void ShaderManager::CreateShaderProgram(const char* p_vertex_file_name, const char* p_fragment_file_name, const char* p_geometry_file_name, const char* p_tess_control_file_name, const char* p_tess_evaluation_file_name);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Attribute変数のロケーションを生成（ほぼ glGetAttribLocation と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_name		：[I/ ]　シェーダーで使用するAttribute変数の名前
	*	戻り値
	*	　Attribute変数のロケーションを呼び出すためのインデックス値
	*
	*	　インデックス値ではなく、素のAttribute変数のロケーションを取得したい場合は、
	*	　本関数実行後に「GetAttribLocationOriginal」関数を利用し取得してください。
	*-------------------------------------------------------------------------------*/
	GLint GetAttribLocation(const GLchar* p_name);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数のロケーションを生成（ほぼ glGetUniformLocation と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_name		：[I/ ]　シェーダーで使用するUniform変数の名前
	*	戻り値
	*	　Uniform変数のロケーションを呼び出すためのインデックス値
	*
	*	　インデックス値ではなく、素のUniform変数のロケーションを取得したい場合は、
	*	　本関数実行後に「GetUniformLocationOriginal」関数を利用し取得してください。
	*-------------------------------------------------------------------------------*/
	GLint GetUniformLocation(const GLchar* p_name);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Attribute変数を有効にします。（ほぼ glEnableVertexAttribArray と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
	*					　		（GetAttribLocationで取得した返り値）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void EnableVertexAttribArray(const GLint p_index);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Attribute変数へデータを送信（関連付け）します。（ほぼ glVertexAttribPointer と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
	*					　		（GetAttribLocationで取得した返り値）
	*	　p_size		：[I/ ]　頂点データの要素数
	*	　p_type		：[I/ ]　頂点データの型
	*	　p_normalized	：[I/ ]　頂点データを正規化して頂点シェーダーに渡す場合は「GL_TRUE」を指定、
	*							 入力そのままに頂点シェーダーに渡す場合は「GL_FALSE」を指定
	*	　p_stride		：[I/ ]　頂点の先頭位置ごとのオフセット値、0指定可能
	*	　p_pointer		：[I/ ]　関連付ける頂点の先頭ポインタ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void VertexAttribPointer(const GLint p_index, const GLint p_size, const GLenum p_type, const GLboolean p_normalized, const GLsizei p_stride, const GLvoid *p_pointer);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数へデータを送信（関連付け）します。（ほぼ glUniform1f, glUniform2f, glUniform3f, glUniform4f と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*					　		（GetUniformLocationで取得した返り値）
	*	　p_scalar		：[I/ ]　転送するデータの個数（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → vec4）
	*							 ※ 要約すると [1]を指定すれば → glUniform1f、[4]を指定すれば → glUniform4f がコールされる ※
	*					----------------------------------------------------------
	*					下記成分については、引数「p_scalar」で指定した数分を「データ1」から詰めて入力する
	*					（使用しない引数が出てくると思われるが、その引数には「0」を指定すること）
	*	　p_param1		：[I/ ]　転送するデータ 1（シェーダー内変数の Xベクトル成分に該当）
	*	　p_param2		：[I/ ]　転送するデータ 2（シェーダー内変数の Yベクトル成分に該当）
	*	　p_param3		：[I/ ]　転送するデータ 3（シェーダー内変数の Zベクトル成分に該当）
	*	　p_param4		：[I/ ]　転送するデータ 4（シェーダー内変数の Wベクトル成分に該当）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UniformXf(const GLint p_index, const GLint p_scalar, const GLfloat p_param1, const GLfloat p_param2, const GLfloat p_param3, const GLfloat p_param4);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数へデータを送信（関連付け）します。（ほぼ glUniform1i, glUniform2i, glUniform3i, glUniform4i と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*					　		（GetUniformLocationで取得した返り値）
	*	　p_scalar		：[I/ ]　転送するデータの個数（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → ivec4）
	*							 ※ 要約すると [1]を指定すれば → glUniform1i、[4]を指定すれば → glUniform4i がコールされる ※
	*					----------------------------------------------------------
	*					下記成分については、引数「p_scalar」で指定した数分を「データ1」から詰めて入力する
	*					（使用しない引数が出てくると思われるが、その引数には「0」を指定すること）
	*	　p_param1		：[I/ ]　転送するデータ 1（シェーダー内変数の Xベクトル成分に該当）
	*	　p_param2		：[I/ ]　転送するデータ 2（シェーダー内変数の Yベクトル成分に該当）
	*	　p_param3		：[I/ ]　転送するデータ 3（シェーダー内変数の Zベクトル成分に該当）
	*	　p_param4		：[I/ ]　転送するデータ 4（シェーダー内変数の Wベクトル成分に該当）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UniformXi(const GLint p_index, const GLint p_scalar, const GLint p_param1, const GLint p_param2, const GLint p_param3, const GLint p_param4);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数へデータを送信（関連付け）します。（ほぼ glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*					　		（GetUniformLocationで取得した返り値）
	*	　p_scalar		：[I/ ]　転送するデータの個数（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → vec4）
	*							 ※ 要約すると [1]を指定すれば → glUniform1fv、[4]を指定すれば → glUniform4fv がコールされる ※
	*					----------------------------------------------------------
	*	　p_count		：[I/ ]　転送するデータの配列数（「p_scalar」引数で設定したデータの個数を何セット送るか　例)[4] → vec? Example[4]）
	*	　value			：[I/ ]　転送するデータの先頭ポインタ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UniformXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLfloat *p_value);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数へデータを送信（関連付け）します。（ほぼ glUniform1iv, glUniform2iv, glUniform3iv, glUniform4iv と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*					　		（GetUniformLocationで取得した返り値）
	*	　p_scalar		：[I/ ]　転送するデータの個数（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → ivec4）
	*							 ※ 要約すると [1]を指定すれば → glUniform1iv、[4]を指定すれば → glUniform4iv がコールされる ※
	*					----------------------------------------------------------
	*	　p_count		：[I/ ]　転送するデータの配列数（「p_scalar」引数で設定したデータの個数を何セット送るか　例)[4] → ivec? Example[4]）
	*	　value			：[I/ ]　転送するデータの先頭ポインタ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UniformXiv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLint *p_value);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数へデータを送信（関連付け）します。（ほぼ glUniformMatrix2fv, glUniformMatrix3fv, glUniformMatrix4fv と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*					　		（GetUniformLocationで取得した返り値）
	*	　p_scalar		：[I/ ]　転送する行列のサイズ（？×？ の [？]の部分）（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → mat4）
	*							 ※ 要約すると [2]を指定すれば → glUniformMatrix2fv、[4]を指定すれば → glUniformMatrix4fv がコールされる ※
	*					----------------------------------------------------------
	*	　p_count		：[I/ ]　転送するの行列の配列数（「p_scalar」引数で設定した行列のサイズを何セット送るか　例)[4] → mat? Example[4]）
	*	　p_transpose	：[I/ ]　頂点データを転置してシェーダーに渡す場合は「GL_TRUE」を指定、
	*								 入力そのままに頂点シェーダーに渡す場合は「GL_FALSE」を指定
	*	　value			：[I/ ]　転送するデータの先頭ポインタ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UniformMatrixXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLboolean p_transpose, const GLfloat *p_value);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　シェーダープログラムの利用を開始する（ほぼ glUseProgram と同じです）
	*	　エラーや情報管理を一元化して利便性の向上を図っています。
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void UseProgram(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　プログラムオブジェクトを取得する
	*	引数
	*	　なし
	*	戻り値
	*	　シェーダーのプログラムオブジェクト
	*-------------------------------------------------------------------------------*/
	inline GLint GetProgramObject(void)
	{
		return m_ProgramObject;
	}

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Attribute変数のロケーションを取得する
	*	　本関数は既に生成したロケーションを取得するための関数です。
	*
	*	　新規でAttribute変数のロケーションを生成したい場合は、「GetAttribLocation」関数を利用してください。
	*	引数
	*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
	*						　		（GetAttribLocationで取得した返り値）
	*	戻り値
	*	　Attribute変数のロケーション
	*-------------------------------------------------------------------------------*/
	inline GLint GetAttribLocationOriginal(GLint p_index)
	{
		return m_AttribInfo[p_index].Location;
	}

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Uniform変数のロケーションを取得する
	*	　本関数は既に生成したロケーションを取得するための関数です。
	*
	*	　新規でUniform変数のロケーションを生成したい場合は、「GetUniformLocation」関数を利用してください。
	*	引数
	*	　p_index		：[I/ ]　Uniform変数のロケーションを呼び出すためのインデックス値
	*						　		（GetUniformLocationで取得した返り値）
	*	戻り値
	*	　Attribute変数のロケーション
	*-------------------------------------------------------------------------------*/
	inline GLint GetUniformLocationOriginal(GLint p_index)
	{
		return m_UniformInfo[p_index].Location;
	}

private:

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　シェーダーオブジェクトの作成を行う
	*	引数
	*	　p_file_name		：[I/ ]　シェーダーのファイル名
	*	　gl_xxxx_shader	：[I/ ]　作成するシェーダーオブジェクトの種類
	*								（GL_GEOMETRY_SHADER or GL_FRAGMENT_SHADER or GL_VERTEX_SHADER）
	*	戻り値
	*	　シェーダーオブジェクト
	*-------------------------------------------------------------------------------*/
	GLuint ShaderManager::CreateShader(const char* p_file_name, const GLuint p_gl_xxxx_shader);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　シェーダーファイルの読み込みを行う
	*	引数
	*	　p_file_name		：[I/ ]　シェーダーのファイル名
	*
	*	※[Shader]フォルダ以降のファイルパスを入力してください
	*	　ディレクトリをまたぐときは「\\」で区切ってください。（例「xxx\\xxx.vert」)
	*
	*	戻り値
	*	　シェーダーソースへの先頭ポインタ
	*-------------------------------------------------------------------------------*/
	char* ShaderManager::ShaderFileLoad(const char* p_file_name);

	///////////////////////////////
	//構造体定義

	//アトリビュート変数管理用の構造体
	typedef struct
	{
		char Name[ATTRIB_INFO_NAME_MAX];		//変数名
		GLint Location;							//ロケーション
	}AttribInfo;

	//ユニフォーム変数管理用の構造体
	typedef struct
	{
		char Name[UNIFORM_INFO_NAME_MAX];		//変数名
		GLint Location;							//ロケーション
	}UniformInfo;


	//変数定義
	GLint m_ProgramObject;		//プログラムオブジェクト
	char m_vertex_file_name[SHADER_FILE_NAME_MAX];			//バーテックスシェーダーファイル名
	char m_fragment_file_name[SHADER_FILE_NAME_MAX];		//フラグメントシェーダーファイル名
	char m_geometry_file_name[SHADER_FILE_NAME_MAX];		//フラグメントシェーダーファイル名
	char m_tess_control_file_name[SHADER_FILE_NAME_MAX];	//テッセレーションコントロールシェーダーのオブジェクト
	char m_tess_evaluation_file_name[SHADER_FILE_NAME_MAX];	//テッセレーション評価シェーダーのオブジェクト

	AttribInfo m_AttribInfo[ATTRIB_INFO_MAX];			//アトリビュート変数管理用の変数
	int m_AttribInfoIndex;								//アトリビュート変数管理用のインデックス値
	UniformInfo m_UniformInfo[UNIFORM_INFO_MAX];		//ユニフォーム変数管理用の変数
	int m_UniformInfoIndex;								//ユニフォーム変数管理用のインデックス値
};
#endif