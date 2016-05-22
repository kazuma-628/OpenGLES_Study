#include "ShaderManager.h"

//コンストラクタ
ShaderManager::ShaderManager()
{
	m_ProgramObject = -1;
	m_UniformInfoIndex = 0;
	m_AttribInfoIndex = 0;
	memset(m_vertex_file_name, 0, sizeof(m_vertex_file_name));
	memset(m_fragment_file_name, 0, sizeof(m_fragment_file_name));
	memset(m_AttribInfo, 0, sizeof(m_AttribInfo));
	memset(m_UniformInfo, 0, sizeof(m_UniformInfo));

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
*	　p_vertex_file_name		：[I/ ]　バーテックスシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　p_fragment_file_name		：[I/ ]　フラグメントシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　p_geometry_file_name		：[I/ ]　ジオメトリシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*										 ※使用しない場合は「NULL」を指定
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::CreateShaderProgram(const char* p_vertex_file_name, const char* p_fragment_file_name, const char* p_geometry_file_name)
{
	//読み込むシェーダー名を記憶
	strcat_s(m_vertex_file_name, sizeof(m_vertex_file_name), p_vertex_file_name);
	strcat_s(m_fragment_file_name, sizeof(m_fragment_file_name), p_fragment_file_name);

	//ファイルからバーテックスソースを読み込む（「Shader」フォルダに格納されている必要があります）
	char vertex_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//頂点シェーダ
	Shader_FileLoad(p_vertex_file_name, vertex_shader_source, SHADER_STRING_ALL_MAX);
	//ソースをアップロードする
	const GLuint vertex_shader = Shader_SourceLoad(vertex_shader_source, GL_VERTEX_SHADER);			//頂点シェーダ

	//ファイルからフラグメントソースを読み込む（「Shader」フォルダに格納されている必要があります）
	char fragment_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//フラグメントシェーダ
	Shader_FileLoad(p_fragment_file_name, fragment_shader_source, SHADER_STRING_ALL_MAX);
	//ソースをアップロードする
	const GLuint fragment_shader = Shader_SourceLoad(fragment_shader_source, GL_FRAGMENT_SHADER);	//フラグメントシェーダ

	//プログラムオブジェクトの生成
	const GLuint ProgramObject = glCreateProgram();
	if (GL_NO_ERROR != GL_GET_ERROR() || 0 == ProgramObject)
	{
		ERROR_MESSAGE("プログラムオブジェクトの作成に失敗しました。");
	}

	glAttachShader(ProgramObject, vertex_shader);		// バーテックスシェーダーとプログラムを関連付ける
	glAttachShader(ProgramObject, fragment_shader);		// フラグメントシェーダーとプログラムを関連付ける

	//ジオメトリシェーダーの読み込み
	if (NULL != p_geometry_file_name)
	{
		//ファイルからジオメトリソースを読み込む（「Shader」フォルダに格納されている必要があります）
		char geometry_shader_source[SHADER_STRING_ALL_MAX] = { 0 };		//ジオメトリシェーダ
		Shader_FileLoad(p_geometry_file_name, geometry_shader_source, SHADER_STRING_ALL_MAX);
		//ソースをアップロードする
		const GLuint geometry_shader = Shader_SourceLoad(geometry_shader_source, GL_GEOMETRY_SHADER);	//ジオメトリシェーダ

		glAttachShader(ProgramObject, geometry_shader);		// フラグメントシェーダーとプログラムを関連付ける
	}


	if (GL_NO_ERROR != GL_GET_ERROR())
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
*	　Attribute変数のロケーションを生成（ほぼ glGetAttribLocation と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_name		：[I/ ]　シェーダーで使用するAttribute変数の名前
*	戻り値
*	　Attribute変数のロケーションを呼び出すためのインデックス値
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetAttribLocation(const GLchar* p_name)
{
	printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
	printf("アトリビュート変数「%s」のロケーションの生成を開始します... ", p_name);

	GLint Location = glGetAttribLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("失敗\n\n");
		printf("■■■ エラー ■■■\n");
		printf("シェーダーに変数「%s」が定義されていない可能性があります\n\n", p_name);
		ERROR_MESSAGE_SUB("",0,0,0);
	}
	else
	{ 
		printf("完了\n");
	}

	//変数名とロケーションIDを保存
	memmove(m_AttribInfo[m_AttribInfoIndex].Name, p_name, strlen(p_name));
	m_AttribInfo[m_AttribInfoIndex].Location = Location;

	//インデックス値を1つ進める
	m_AttribInfoIndex++;

	//保存したインデックス値を返す
	return m_AttribInfoIndex - 1;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Uniform変数のロケーションを生成（ほぼ glGetUniformLocation と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_name		：[I/ ]　シェーダーで使用するUniform変数の名前
*	戻り値
*	　Uniform変数のロケーションを呼び出すためのインデックス値
*-------------------------------------------------------------------------------*/
GLint ShaderManager::GetUniformLocation(const GLchar* p_name)
{
	printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
	printf("ユニホーム変数「%s」のロケーションの生成を開始します... ", p_name);

	GLint Location = glGetUniformLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("失敗\n\n");
		printf("■■■ エラー ■■■\n");
		printf("シェーダーに変数「%s」が定義されていない可能性があります\n\n", p_name);
		ERROR_MESSAGE_SUB("", 0, 0, 0);

	}
	else
	{
		printf("完了\n");
	}

	//変数名とロケーションIDを保存
	memmove(m_UniformInfo[m_UniformInfoIndex].Name, p_name, strlen(p_name));
	m_UniformInfo[m_UniformInfoIndex].Location = Location;

	//インデックス値を1つ進める
	m_UniformInfoIndex++;

	//保存したインデックス値を返す
	return m_UniformInfoIndex - 1;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Attribute変数を有効にします。（ほぼ glEnableVertexAttribArray と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
*							　（GetAttribLocationで取得した返り値）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::EnableVertexAttribArray(const GLint p_index)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"アトリビュート変数「%s」の有効化に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glEnableVertexAttribArray(m_AttribInfo[p_index].Location);
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Attribute変数へデータを送信（関連付け）します。（ほぼ glVertexAttribPointer と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
*							　（GetAttribLocationで取得した返り値）
*	　p_size		：[I/ ]　頂点データの要素数
*	　p_type		：[I/ ]　頂点データの型
*	　p_normalized	：[I/ ]　頂点データを正規化して頂点シェーダーに渡す場合は「GL_TRUE」を指定、
*							 入力そのままに頂点シェーダーに渡す場合は「GL_FALSE」を指定
*	　p_stride		：[I/ ]　頂点の先頭位置ごとのオフセット値、0指定可能
*	　p_pointe		：[I/ ]　関連付ける頂点の先頭ポインタ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::VertexAttribPointer(const GLint p_index, const GLint p_size, const GLenum p_type, const GLboolean p_normalized, const GLsizei p_stride, const GLvoid *p_pointe)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"アトリビュート変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glVertexAttribPointer(m_AttribInfo[p_index].Location, p_size, p_type, p_normalized, p_stride, p_pointe);
	}
}

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
void ShaderManager::UniformXf(const GLint p_index, const GLint p_scalar, const GLfloat p_param1, const GLfloat p_param2, const GLfloat p_param3, const GLfloat p_param4)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if(1 == p_scalar)
		{
			glUniform1f(m_UniformInfo[p_index].Location, p_param1);
		}
		else if (2 == p_scalar)
		{
			glUniform2f(m_UniformInfo[p_index].Location, p_param1, p_param2);
		}
		else if (3 == p_scalar)
		{
			glUniform3f(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3);
		}
		else if (4 == p_scalar)
		{
			glUniform4f(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3, p_param4);
		}
		else
		{
			printf("\n■■■ エラー ■■■\n");
			printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
			printf("ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n", m_UniformInfo[p_index].Name);
			printf("「glUniformXf」関数「p_scalar」引数のエラーです\n");
			printf("正しい値が設定されていません → 設定値：%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform変数へのデータを送信（関連付け）に失敗しました。");
		}
	}
}

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
void ShaderManager::UniformXi(const GLint p_index, const GLint p_scalar, const GLint p_param1, const GLint p_param2, const GLint p_param3, const GLint p_param4)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1i(m_UniformInfo[p_index].Location, p_param1);
		}
		else if (2 == p_scalar)
		{
			glUniform2i(m_UniformInfo[p_index].Location, p_param1, p_param2);
		}
		else if (3 == p_scalar)
		{
			glUniform3i(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3);
		}
		else if (4 == p_scalar)
		{
			glUniform4i(m_UniformInfo[p_index].Location, p_param1, p_param2, p_param3, p_param4);
		}
		else
		{
			printf("\n■■■ エラー ■■■\n");
			printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
			printf("ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n", m_UniformInfo[p_index].Name);
			printf("「glUniformXi」関数「p_scalar」引数のエラーです\n");
			printf("正しい値が設定されていません → 設定値：%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform変数へのデータを送信（関連付け）に失敗しました。");
		}
	}
}

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
void ShaderManager::UniformXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLfloat *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (2 == p_scalar)
		{
			glUniform2fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniform3fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniform4fv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else
		{
			printf("\n■■■ エラー ■■■\n");
			printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
			printf("ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n", m_UniformInfo[p_index].Name);
			printf("「glUniformXfv」関数「p_scalar」引数のエラーです\n");
			printf("正しい値が設定されていません → 設定値：%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform変数へのデータを送信（関連付け）に失敗しました。");
		}
	}
}

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
void ShaderManager::UniformXiv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLint *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glUniform1iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (2 == p_scalar)
		{
			glUniform2iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniform3iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniform4iv(m_UniformInfo[p_index].Location, p_count, p_value);
		}
		else
		{
			printf("\n■■■ エラー ■■■\n");
			printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
			printf("ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n", m_UniformInfo[p_index].Name);
			printf("「glUniformXiv」関数「p_scalar」引数のエラーです\n");
			printf("正しい値が設定されていません → 設定値：%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform変数へのデータを送信（関連付け）に失敗しました。");
		}
	}
}

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
void ShaderManager::UniformMatrixXfv(const GLint p_index, const GLint p_scalar, const GLsizei p_count, const GLboolean p_transpose, const GLfloat *p_value)
{
	if (-1 == m_UniformInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("\n■■■ エラー ■■■\n"\
			"シェーダー「%s」及び「%s」用の\n"\
			"ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
			"シェーダーに変数が定義されていない可能性があります\n\n"\
			, m_vertex_file_name, m_fragment_file_name, m_UniformInfo[p_index].Name);
	}
	else
	{
		if (2 == p_scalar)
		{
			glUniformMatrix2fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else if (3 == p_scalar)
		{
			glUniformMatrix3fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else if (4 == p_scalar)
		{
			glUniformMatrix4fv(m_UniformInfo[p_index].Location, p_count, p_transpose, p_value);
		}
		else
		{
			printf("\n■■■ エラー ■■■\n");
			printf("シェーダー「%s」及び「%s」用の\n", m_vertex_file_name, m_fragment_file_name);
			printf("ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n", m_UniformInfo[p_index].Name);
			printf("「glUniformMatrixXfv」関数「p_scalar」引数のエラーです\n");
			printf("正しい値が設定されていません → 設定値：%d\n\n", p_scalar);
			ERROR_MESSAGE("Uniform変数へのデータを送信（関連付け）に失敗しました。");
		}
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダープログラムの利用を開始する（ほぼ glUseProgram と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::UseProgram(void)
{
	// シェーダープログラムの利用を開始する
	glUseProgram(m_ProgramObject);

	if (GL_NO_ERROR != GL_GET_ERROR())
	{
		printf("シェーダー「%s」及び「%s」用の処理でエラーが発生しました。\n", m_vertex_file_name, m_fragment_file_name);
		ERROR_MESSAGE("シェーダープログラムの利用に失敗しました。");
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーファイルの読み込みを行う
*	引数
*	　p_file_name		：[I/ ]　各シェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　p_shader_source	：[ /O]　各シェーダーのソース
*	　source_size		：[I/ ]　シェーダーの全文の最大文字数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::Shader_FileLoad(const char* p_file_name, char* p_shader_source, const int p_source_size)
{

	FILE *fp;		//ファイルポインタ宣言
	char String_Line[SHADER_STRING_LINE_MAX] = { 0 };		//1行の読み込み最大数

	char shader_dir_file_name[SHADER_FILE_NAME_MAX] = "..\\Shader\\";

	strcat_s(shader_dir_file_name, p_file_name);

	//ファイルのオープン
	printf("「%s」シェーダーファイルの読み込みを開始します... ", p_file_name);
	if (0 != fopen_s(&fp, shader_dir_file_name, "r"))
	{
		printf("失敗\n");
		ERROR_MESSAGE("シェーダーファイルのオープンに失敗しました。\n"\
			"「Shader」フォルダに格納されていますか？\n"\
			"ファイル名が間違っていませんか？");
	}

	//ファイルの読み込み
	while (fgets(String_Line, sizeof(String_Line), fp) != NULL)
	{
		//1行つづ読み込むので文字列を結合
		if (0 != strcat_s(p_shader_source, p_source_size, String_Line))
		{
			printf("失敗\n");
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
	if (GL_NO_ERROR != GL_GET_ERROR())
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