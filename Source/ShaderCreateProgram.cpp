/*------------------------------------------------------------------------------------------
 *　■プログラム説明■
 *	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
 *　まだ作り始めで何もできませんが（最低限の動作確認しかできません）、
 *	今後、行列を簡単に設定できるようにしたり、マウスでの操作など様々な機能を提供していく予定です。
 *------------------------------------------------------------------------------------------*/

#include "ShaderCreateProgram.h"

/*-------------------------------------------------------------------------------
*	関数説明
*	　頂点・フラグメントシェーダーをリンクし、ShaderProgramを作成する
*	引数
*	　vertex_shader_file	：[I/ ]　バーテックスシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　fragment_shader_file	：[I/ ]　フラグメントシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	戻り値
*	　リンク済みのプログラム
*-------------------------------------------------------------------------------*/
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file)
{

	//ファイルからソースを読み込む（「Shader」フォルダに格納されている必要があります）
	char vertex_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//頂点シェーダ
	Shader_FileLoad(vertex_shader_file, vertex_shader_source, SHADER_STRING_ALL_MAX);
	char fragment_shader_source[SHADER_STRING_ALL_MAX] = { 0 };	//フラグメントシェーダ
	Shader_FileLoad(fragment_shader_file, fragment_shader_source, SHADER_STRING_ALL_MAX);

	//ソースをアップロードする
	const GLuint vertex_shader = Shader_SourceLoad(vertex_shader_source, GL_VERTEX_SHADER);			//頂点シェーダ
	const GLuint fragment_shader = Shader_SourceLoad(fragment_shader_source, GL_FRAGMENT_SHADER);	//フラグメントシェーダ

	//Programの生成
	const GLuint program = glCreateProgram();
	assert(GL_NO_ERROR == glGetError());
	assert(program != 0);

	glAttachShader(program, vertex_shader);		// バーテックスシェーダーとプログラムを関連付ける
	glAttachShader(program, fragment_shader);	// フラグメントシェーダーとプログラムを関連付ける
	assert(GL_NO_ERROR == glGetError());

	// コンパイルを行う
	glLinkProgram(program);

	// リンクエラーをチェックする
	GLint linkSuccess = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
	if (GL_FALSE == linkSuccess) {
		// エラーが発生した
		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetProgramInfoLog(program, infoLen, NULL, message);
			printf("%s", message);
			free((void*)message);
		}
	}
	assert(linkSuccess == GL_TRUE);

	// リンク済みのため、個々のシェーダーオブジェクトの解放フラグを立てる
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// リンク済みのプログラムを返す
	return program;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーファイルの読み込みを行う
*	引数
*	　shader_file_name	：[I/ ]　各シェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　shader_source		：[ /O]　各シェーダーのソース
*	　source_size		：[I/ ]　シェーダーの全文の最大文字数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Shader_FileLoad(const char* shader_file_name, char* shader_source, int source_size)
{

	FILE *fp;		//ファイルポインタ宣言
	char String_Line[SHADER_STRING_LINE_MAX] = { 0 };		//1行の読み込み最大数

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = "..\\Shader\\";

	strcat_s(shader_dir_file_name, shader_file_name);

	//ファイルのオープン
	assert(0 == fopen_s(&fp, shader_dir_file_name, "r"));

	//ファイルの読み込み
	while (fgets(String_Line, sizeof(String_Line), fp) != NULL)
	{
		//1行つづ読み込むので文字列を結合
		assert(0 == strcat_s(shader_source, source_size, String_Line));
	}

	//ファイルクローズ
	fclose(fp);
}


/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーソースの読み込みを行う
*	引数
*	　shader_source		：[I/ ]　各シェーダーのソースデータ
*	　gl_xxxx_shader	：[I/ ]　作成するシェーダーオブジェクト（バーテックス or フラグメント）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
GLint Shader_SourceLoad(const char* shader_source, const GLuint gl_xxxx_shader)
{

	const GLint shader = glCreateShader(gl_xxxx_shader);
	assert(GL_NO_ERROR == glGetError());

	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	// コンパイルエラーをチェックする
	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (GL_FALSE == compileSuccess) {
		// エラーが発生した
		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetShaderInfoLog(shader, infoLen, NULL, message);
			if (GL_VERTEX_SHADER == gl_xxxx_shader)
			{
				printf("GL_VERTEX_SHADER ERROR\n");
			}
			else
			{
				printf("GL_FRAGMENT_SHADER ERROR\n");
			}
			printf("%s", message);
			free((void*)message);
		}
	}

	// コンパイル失敗していたらここでプログラムを停止する
	assert(GL_TRUE == compileSuccess);

	return shader;
}