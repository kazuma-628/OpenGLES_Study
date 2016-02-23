#include "ShaderManager.h"

//コンストラクタ
ShaderManager::ShaderManager()
{
	m_ProgramObject = -1;
	memset(m_vertex_shader_file, 0, sizeof(m_vertex_shader_file));
	memset(m_fragment_shader_file, 0, sizeof(m_fragment_shader_file));
}

//デストラクタ
ShaderManager::~ShaderManager()
{
	//プログラムオブジェクトを削除する
	glDeleteProgram(m_ProgramObject);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　バーテックス・フラグメントシェーダーのソースを指定されたファイルから読み込み、
*	　コンパイル及びリンクして、プログラムオブジェクトを作成する
*	引数
*	　p_vertex_shader_file		：[I/ ]　バーテックスシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　p_fragment_shader_file	：[I/ ]　フラグメントシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::CreateShaderProgram(const char* p_vertex_shader_file, const char* p_fragment_shader_file)
{
	//読み込むシェーダー名を記憶
	strcat_s(m_vertex_shader_file, sizeof(m_vertex_shader_file), p_vertex_shader_file);
	strcat_s(m_fragment_shader_file, sizeof(m_fragment_shader_file), p_vertex_shader_file);

	//ファイルからバーテックスソースを読み込む（「Shader」フォルダに格納されている必要があります）
	char vertex_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//頂点シェーダ
	Shader_FileLoad(p_vertex_shader_file, vertex_shader_source, SHADER_STRING_ALL_MAX);
	//ソースをアップロードする
	const GLuint vertex_shader = Shader_SourceLoad(vertex_shader_source, GL_VERTEX_SHADER);			//頂点シェーダ

	//ファイルからフラグメントソースを読み込む（「Shader」フォルダに格納されている必要があります）
	char fragment_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//フラグメントシェーダ
	Shader_FileLoad(p_fragment_shader_file, fragment_shader_source, SHADER_STRING_ALL_MAX);
	//ソースをアップロードする
	const GLuint fragment_shader = Shader_SourceLoad(fragment_shader_source, GL_FRAGMENT_SHADER);	//フラグメントシェーダ


	//プログラムオブジェクトの生成
	const GLuint ProgramObject = glCreateProgram();
	if (GL_NO_ERROR != glGetError() || 0 == ProgramObject)
	{
		ERROR_MESSAGE("プログラムオブジェクトの作成に失敗しました。");
	}

	glAttachShader(ProgramObject, vertex_shader);		// バーテックスシェーダーとプログラムを関連付ける
	glAttachShader(ProgramObject, fragment_shader);	// フラグメントシェーダーとプログラムを関連付ける
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("シェーダーとシェーダープログラムの関連付けに失敗しました。");
	}

	// シェーダープログラムのリンクを行う
	printf("シェーダープログラムのリンクを開始します... ");
	glLinkProgram(ProgramObject);

	// リンクエラーをチェックする
	GLint linkSuccess = 0;
	glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linkSuccess);
	if (GL_FALSE == linkSuccess) {
		// エラーが発生した
		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetProgramiv(ProgramObject, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetProgramInfoLog(ProgramObject, infoLen, NULL, message);

			//エラーメッセージ表示
			printf("\n\nリンクエラーの情報は以下です。\n");
			printf("%s", message);
			free((void*)message);
		}
	}
	if (GL_TRUE != linkSuccess)
	{
		ERROR_MESSAGE("シェーダープログラムのリンクに失敗しました。");
	}
	printf("完了\n");

	// リンク済みのため、個々のシェーダーオブジェクトの解放フラグを立てる
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//リンク済みのプログラムを記憶する
	m_ProgramObject = ProgramObject;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Attribute変数のロケーションIDを生成（ほぼ glGetAttribLocation と同じです）
*	　分かりやすいように引数を少なくしたのと、エラー管理を一元化した点が違うのみです。
*	引数
*	　p_attribute_name			：[I/ ]　シェーダーで使用するAttribute変数の名前
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetAttribLocation(const GLchar* p_attribute_name)
{
	printf("シェーダー「%s」用の\n", m_vertex_shader_file);
	printf("アトリビュート変数「%s」のロケーションIDの生成を開始します... ", p_attribute_name);

	GLint AttribLocationID = glGetAttribLocation(m_ProgramObject, p_attribute_name);

	if (AttribLocationID < 0)
	{
		ERROR_MESSAGE("Attribute変数のロケーションIDを生成に失敗しました。");
	}
	printf("完了\n");

	return AttribLocationID;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Uniform変数のロケーションIDを生成（ほぼ glGetUniformLocation と同じです）
*	　分かりやすいように引数を少なくしたのと、エラー管理を一元化した点が違うのみです。
*	引数
*	　p_uniform_name			：[I/ ]　シェーダーで使用するUniform変数の名前
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetUniformLocation(const GLchar* p_uniform_name)
{
	printf("シェーダー「%s」及び「%s」用の\n", m_vertex_shader_file, m_fragment_shader_file);
	printf("ユニホーム変数「%s」のロケーションIDの生成を開始します... ", p_uniform_name);

	GLint UniformLocationID = glGetUniformLocation(m_ProgramObject, p_uniform_name);

	if (UniformLocationID < 0)
	{
		ERROR_MESSAGE("Uniform変数のロケーションIDを生成に失敗しました。");
	}
	printf("完了\n");

	return UniformLocationID;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダープログラムの利用を開始する（ほぼ glUseProgram と同じです）
*	　分かりやすいように引数を少なくしたのと、エラー管理を一元化した点が違うのみです。
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::UseProgram(void)
{
	// シェーダープログラムの利用を開始する
	glUseProgram(m_ProgramObject);

	if (GL_NO_ERROR != glGetError())
	{
		printf("シェーダー「%s」及び「%s」用の処理でエラーが発生しました。\n", m_vertex_shader_file, m_fragment_shader_file);
		ERROR_MESSAGE("シェーダープログラムの利用に失敗しました。");
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーファイルの読み込みを行う
*	引数
*	　p_shader_file_name	：[I/ ]　各シェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　p_shader_source		：[ /O]　各シェーダーのソース
*	　source_size			：[I/ ]　シェーダーの全文の最大文字数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::Shader_FileLoad(const char* p_shader_file_name, char* p_shader_source, const int p_source_size)
{

	FILE *fp;		//ファイルポインタ宣言
	char String_Line[SHADER_STRING_LINE_MAX] = { 0 };		//1行の読み込み最大数

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = "..\\Shader\\";

	strcat_s(shader_dir_file_name, p_shader_file_name);

	//ファイルのオープン
	printf("「%s」シェーダーファイルの読み込みを開始します... ", p_shader_file_name);
	if (0 != fopen_s(&fp, shader_dir_file_name, "r"))
	{
		ERROR_MESSAGE("シェーダーファイルのオープンに失敗しました");
	}

	//ファイルの読み込み
	while (fgets(String_Line, sizeof(String_Line), fp) != NULL)
	{
		//1行つづ読み込むので文字列を結合
		if (0 != strcat_s(p_shader_source, p_source_size, String_Line))
		{
			ERROR_MESSAGE("ファイルの読み込みに失敗しました。");
		}
	}

	//ファイルクローズ
	fclose(fp);

	printf("完了\n");
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
GLint ShaderManager::Shader_SourceLoad(const char* p_shader_source, const GLuint p_gl_xxxx_shader)
{

	//シェーダーオブジェクトの生成
	const GLint shader = glCreateShader(p_gl_xxxx_shader);
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("シェーダーオブジェクトの作成に失敗しました");
	}

	//ソースプログラムを読み込む
	glShaderSource(shader, 1, &p_shader_source, NULL);

	//シェーダーのコンパイルを開始
	printf("シェーダーのコンパイルを開始します... ");
	glCompileShader(shader);

	// コンパイルエラーをチェックする
	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (GL_FALSE == compileSuccess)
	{
		// エラーが発生した
		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetShaderInfoLog(shader, infoLen, NULL, message);

			//エラーメッセージ表示
			printf("\n\nコンパイルエラーの情報は以下です。\n");
			printf("%s", message);
			free((void*)message);
		}
	}

	// コンパイル失敗していたらここでプログラムを停止する
	if (GL_TRUE != compileSuccess)
	{
		ERROR_MESSAGE("シェーダーのコンパイルに失敗しました。");
	}

	printf("完了\n");
	
	return shader;
}