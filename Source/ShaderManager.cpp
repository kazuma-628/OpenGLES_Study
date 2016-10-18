#include "ShaderManager.h"

//コンストラクタ
ShaderManager::ShaderManager()
{
	m_ProgramObject = 0;
	m_UniformInfoIndex = 0;
	m_AttribInfoIndex = 0;
	m_vertex_file_name = NULL;
	m_fragment_file_name = NULL;
	m_geometry_file_name = NULL;
	m_tess_control_file_name = NULL;
	m_tess_evaluation_file_name = NULL;
	m_AllShaderFileName = NULL;
	memset(m_AttribInfo, 0, sizeof(m_AttribInfo));
	memset(m_UniformInfo, 0, sizeof(m_UniformInfo));
}

//デストラクタ
ShaderManager::~ShaderManager()
{
	//破棄処理する
	DeleteShaderProgram();
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　各シェーダーのソースを指定されたファイルから読み込み、
*	　コンパイル及びリンクして、プログラムオブジェクトを作成する
*	　既にプログラムオブジェクトが作成されている場合は、データを破棄（メモリ解放）してから新しく読み込みします。
*	引数
*	　p_vertex_file_name			：[I/ ]　バーテックスシェーダーのファイル名
*	　p_fragment_file_name			：[I/ ]　フラグメントシェーダーのファイル名
*	　p_geometry_file_name			：[I/ ]　ジオメトリシェーダーのファイル名（使用しない場合はNULLを指定）
*	　p_tess_control_file_name		：[I/ ]　テッセレーションコントロールシェーダーのファイル名（使用しない場合はNULLを指定）
*	　p_tess_evaluation_file_name	：[I/ ]　テッセレーション評価シェーダーのファイル名（使用しない場合はNULLを指定）
*	　p_TransformFeedbackInfo		：[I/ ]　トランスフォームフィードバックの設定情報（使用しない場合はNULLを指定）
*
*	※どのファイル名も[Shader]フォルダ以降のファイルパスを入力してください
*	　ディレクトリをまたぐときは「/」で区切ってください。（例「xxx/xxx.vert」）
*
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::CreateShaderProgram(const char* p_vertex_file_name,
										const char* p_fragment_file_name, 
										const char* p_geometry_file_name, 
										const char* p_tess_control_file_name, 
										const char* p_tess_evaluation_file_name, 
										const TransformFeedbackInfo *p_TransformFeedbackInfo)
{
	GLuint vertex_shader = 0;				//バーテックスシェーダーのオブジェクト
	GLuint fragment_shader = 0;				//フラグメントシェーダーのオブジェクト
	GLuint geometry_shader = 0;				//ジオメトリシェーダーのオブジェクト
	GLuint tess_control_shader = 0;			//テッセレーションコントロールシェーダーのオブジェクト
	GLuint tess_evaluation_shader = 0;		//テッセレーション評価シェーダーのオブジェクト
	int StrLength = 0;						//読み込む各シェーダーファイル名の長さ（バイト数）
	int AllStrLength = 0;					//読み込む各シェーダーファイル名の合計の長さ（バイト数）

	//既にプログラムオブジェクトが作成されているかの確認
	if (0 != m_ProgramObject)
	{
		//作成されていれば破棄してから新規作成
		DeleteShaderProgram();

		//本来であれば上書きはしない事が多いので、警告メッセージを表示しておく
		WARNING_MESSAGE("プログラムオブジェクトの再作成がされました。\n" \
						"破棄処理を忘れていませんか？\n");
	}

	//引数チェック
	if (NULL == p_vertex_file_name || NULL == p_fragment_file_name)
	{
		ERROR_MESSAGE("バーテックスシェーダー及びフラグメントシェーダーは最低でも設定する必要があります。\n" \
					  "バーテックスシェーダー = %s | フラグメントシェーダー = %s\n", p_vertex_file_name, p_fragment_file_name);
	}

	//////////////////////////////////////
	// 読み込むシェーダー名を記憶
	// 文字列の長さを取得してメモリ確保をしてファイル名を保存
	//（終端を明確にするため +1 する。[\0]となる）

	//バーテックスシェーダー
	StrLength = strlen(p_vertex_file_name);
	m_vertex_file_name = (char*)calloc(StrLength + 1, sizeof(char));
	strcpy(m_vertex_file_name, p_vertex_file_name);
	AllStrLength += StrLength;

	//フラグメントシェーダー
	StrLength = strlen(p_fragment_file_name);
	m_fragment_file_name = (char*)calloc(StrLength + 1, sizeof(char));
	strcpy(m_fragment_file_name, p_fragment_file_name);
	AllStrLength += StrLength;

	//ジオメトリシェーダーが指定されている場合
	if (NULL != p_geometry_file_name)
	{
		StrLength = strlen(p_geometry_file_name);
		m_geometry_file_name = (char*)calloc(StrLength + 1, sizeof(char));
		strcpy(m_geometry_file_name, p_geometry_file_name);
		AllStrLength += StrLength;
	}
	//テッセレーションコントロールシェーダーが指定されている場合
	if (NULL != p_tess_control_file_name)
	{
		//テッセレーションコントロールシェーダー
		StrLength = strlen(p_tess_control_file_name);
		m_tess_control_file_name = (char*)calloc(StrLength + 1, sizeof(char));
		strcpy(m_tess_control_file_name, p_tess_control_file_name);
		AllStrLength += StrLength;
	}
	//テッセレーション評価シェーダーが指定されている場合
	if (NULL != p_tess_evaluation_file_name)
	{
		//テッセレーション評価シェーダー
		StrLength = strlen(p_tess_evaluation_file_name);
		m_tess_evaluation_file_name = (char*)calloc(StrLength + 1, sizeof(char));
		strcpy(m_tess_evaluation_file_name, p_tess_evaluation_file_name);
		AllStrLength += StrLength;
	}

	//////////////////////////////////////
	// 全シェーダーのファイル名をまとめた文字列を保存
	// 「 [ ] 」分の文字列数を考慮してメモリ確保する。
	//（更に終端を明確にするため +1 する。[\0]となる）

	m_AllShaderFileName = (char*)calloc(AllStrLength + 11, sizeof(char));

	sprintf(m_AllShaderFileName, "[%s][%s]", m_vertex_file_name, m_fragment_file_name);

	//ジオメトリシェーダーが指定されている場合
	if (NULL != m_geometry_file_name)
	{
		sprintf(m_AllShaderFileName, "%s[%s]", m_AllShaderFileName, m_geometry_file_name);
	}
	//テッセレーションコントロールシェーダーが指定されている場合
	if (NULL != m_tess_control_file_name)
	{
		sprintf(m_AllShaderFileName, "%s[%s]", m_AllShaderFileName, m_tess_control_file_name);
	}
	//テッセレーション評価シェーダーが指定されている場合
	if (NULL != m_tess_evaluation_file_name)
	{
		sprintf(m_AllShaderFileName, "%s[%s]", m_AllShaderFileName, m_tess_evaluation_file_name);
	}

	//////////////////////////////////////

	//プログラムオブジェクトの生成
	GLuint ProgramObject = glCreateProgram();
	//エラーチェック
	if (0 == ProgramObject)
	{
		//エラーなのでプログラムオブジェクトには0にする
		m_ProgramObject = 0;

		ERROR_MESSAGE("プログラムオブジェクトの作成に失敗しました。");

		return;
	}

	//////////////////////////////////////
	// 各シェーダーオブジェクトの作成

	//バーテックスのシェーダーオブジェクト作成
	vertex_shader = CreateShader(p_vertex_file_name, GL_VERTEX_SHADER);
	//エラーチェック
	if (0 == vertex_shader)
	{
		//破棄処理する
		DeleteShaderProgram();

		return;
	}
	glAttachShader(ProgramObject, vertex_shader);		// バーテックスシェーダーとプログラムを関連付ける

	//フラグメントのシェーダーオブジェクト作成
	fragment_shader = CreateShader(p_fragment_file_name, GL_FRAGMENT_SHADER);
	//エラーチェック
	if (0 == fragment_shader)
	{
		//メモリ解放
		glDeleteShader(vertex_shader);
		
		//破棄処理する
		DeleteShaderProgram();

		return;
	}
	glAttachShader(ProgramObject, fragment_shader);		// フラグメントシェーダーとプログラムを関連付ける

	//ジオメトリシェーダーの読み込み（指定されている場合）
	if (NULL != p_geometry_file_name)
	{
		//ジオメトリのシェーダーオブジェクト作成
		geometry_shader = CreateShader(p_geometry_file_name, GL_GEOMETRY_SHADER);
		//エラーチェック
		if (0 == geometry_shader)
		{
			//メモリ解放
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			//破棄処理する
			DeleteShaderProgram();

			return;
		}

		glAttachShader(ProgramObject, geometry_shader);		// フラグメントシェーダーとプログラムを関連付ける
	}

	//テッセレーションコントロールシェーダーの読み込み（指定されている場合）
	if (NULL != p_tess_control_file_name)
	{
		//ジオメトリのシェーダーオブジェクト作成
		tess_control_shader = CreateShader(p_tess_control_file_name, GL_TESS_CONTROL_SHADER);
		//エラーチェック
		if (0 == tess_control_shader)
		{
			//メモリ解放
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteShader(geometry_shader);

			//破棄処理する
			DeleteShaderProgram();
			
			return;
		}

		glAttachShader(ProgramObject, tess_control_shader);		// フラグメントシェーダーとプログラムを関連付ける
	}

	//テッセレーション評価シェーダーの読み込み（指定されている場合）
	if (NULL != p_tess_evaluation_file_name)
	{
		//ジオメトリのシェーダーオブジェクト作成
		tess_evaluation_shader = CreateShader(p_tess_evaluation_file_name, GL_TESS_EVALUATION_SHADER);
		//エラーチェック
		if (0 == tess_evaluation_shader)
		{
			//メモリ解放
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteShader(geometry_shader);
			glDeleteShader(tess_control_shader);

			//破棄処理する
			DeleteShaderProgram();

			return;
		}

		glAttachShader(ProgramObject, tess_evaluation_shader);		// フラグメントシェーダーとプログラムを関連付ける
	}

	//////////////////////////////////////

	//トランスフォームフィードバックの設定（指定されている場合）
	if (NULL != p_TransformFeedbackInfo)
	{
		glTransformFeedbackVaryings(ProgramObject, p_TransformFeedbackInfo->count, p_TransformFeedbackInfo->varyings, p_TransformFeedbackInfo->bufferMode);
	}


	// シェーダープログラムのリンクを行う
	printf("シェーダープログラムのリンクを開始します... ");
	glLinkProgram(ProgramObject);

	// リンクエラーをチェックする
	GLint linkSuccess = 0;
	glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linkSuccess);
	if (GL_FALSE == linkSuccess)
	{
		// エラーが発生した
		printf("失敗\n");

		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetProgramiv(ProgramObject, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetProgramInfoLog(ProgramObject, infoLen, NULL, message);

			//エラーメッセージ表示
			printf("\nリンクエラーの情報は以下です。\n");
			printf("%s", message);
			SAFE_FREE(message);

			//破棄処理する
			DeleteShaderProgram();

			ERROR_MESSAGE("シェーダープログラムのリンクに失敗しました。");
		}
	}
	else
	{
		printf("完了\n");
	}

	//////////////////////////////////////
	// シェーダーオブジェクト破棄

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//ジオメトリシェーダーオブジェクト破棄（指定されている場合）
	if (NULL != p_geometry_file_name)
	{
		glDeleteShader(geometry_shader);
	}

	//テッセレーションコントロールシェーダーオブジェクト破棄（指定されている場合）
	if (NULL != p_tess_control_file_name)
	{
		glDeleteShader(tess_control_shader);
	}

	//テッセレーション評価シェーダーオブジェクト破棄（指定されている場合）
	if (NULL != p_tess_evaluation_file_name)
	{
		glDeleteShader(tess_evaluation_shader);
	}

	//リンク済みのプログラムを記憶する
	m_ProgramObject = ProgramObject;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　コンパイル及びリンクしたプログラムオブジェクトを削除する
*	　また、プログラムオブジェクト作成時に確保した各メンバ変数のメモリも開放・初期化する
*	引数
*	　なし
*	戻り値
*	　シェーダーオブジェクト
*-------------------------------------------------------------------------------*/
void ShaderManager::DeleteShaderProgram(void)
{
	//プログラムオブジェクトが作成されていれば破棄する
	if (0 != m_ProgramObject)
	{
		glDeleteProgram(m_ProgramObject);
		m_ProgramObject = 0;
	}

	//////////////////////////////////////
	// 読み込んだシェーダーファイル名を破棄する

	SAFE_FREE(m_vertex_file_name);
	SAFE_FREE(m_fragment_file_name);
	SAFE_FREE(m_geometry_file_name);
	SAFE_FREE(m_tess_control_file_name);
	SAFE_FREE(m_tess_evaluation_file_name);
	SAFE_FREE(m_AllShaderFileName);

	//////////////////////////////////////
	// アトリビュート・ユニフォーム変数の管理用データを破棄する

	for (int index = 0; index < ATTRIB_INFO_MAX; index++)
	{
		//変数名が保存されていない = これ以上は未使用領域なのでループを抜ける
		if (NULL == m_AttribInfo[index].Name)
		{
			break;
		}
		//変数名保存用のメモリを開放
		SAFE_FREE(m_AttribInfo[index].Name);
	}
	//0で初期化
	memset(m_AttribInfo, 0, sizeof(m_AttribInfo));
	//インデックス値を初期化
	m_AttribInfoIndex = 0;

	for (int index = 0; index < UNIFORM_INFO_MAX; index++)
	{
		//変数名が保存されていない = これ以上は未使用領域なのでループを抜ける
		if (NULL == m_UniformInfo[index].Name)
		{
			break;
		}
		//変数名保存用のメモリを開放
		SAFE_FREE(m_UniformInfo[index].Name);
	}
	//0で初期化
	memset(m_UniformInfo, 0, sizeof(m_UniformInfo));
	//インデックス値を初期化
	m_UniformInfoIndex = 0;
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
	int StrLength = 0;			//生成するロケーションの変数名の長さ（バイト数）

	printf("シェーダー[%s]用の\n", m_vertex_file_name);
	printf("　アトリビュート変数「%s」のロケーションの生成を開始します... ", p_name);

	GLint Location = glGetAttribLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("失敗\n");
		printf("\n■■■ エラー ■■■\n");
		printf("シェーダーに変数「%s」が定義されていない可能性があります\n\n", p_name);
		ERROR_MESSAGE_SUB("");
	}
	else
	{ 
		printf("完了\n");
	}

	//変数名とロケーションIDを保存（終端を明確にするため +1 する。[\0]となる）
	StrLength = strlen(p_name);
	m_AttribInfo[m_UniformInfoIndex].Name = (char*)calloc(StrLength + 1, sizeof(char));
	strcpy(m_AttribInfo[m_UniformInfoIndex].Name, p_name);

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
	int StrLength = 0;			//生成するロケーションの変数名の長さ（バイト数）

	printf("シェーダー%s用の\n", m_AllShaderFileName);
	printf("　ユニホーム変数「%s」のロケーションの生成を開始します... ", p_name);

	GLint Location = glGetUniformLocation(m_ProgramObject, p_name);

	if (Location < 0)
	{
		printf("失敗\n");
		printf("\n■■■ エラー ■■■\n");
		printf("シェーダーに変数「%s」が定義されていない可能性があります\n\n", p_name);
		ERROR_MESSAGE_SUB("");

	}
	else
	{
		printf("完了\n");
	}

	//変数名とロケーションIDを保存（終端を明確にするため +1 する。[\0]となる）
	StrLength = strlen(p_name);
	m_UniformInfo[m_UniformInfoIndex].Name = (char*)calloc(StrLength + 1, sizeof(char));
	strcpy(m_UniformInfo[m_UniformInfoIndex].Name, p_name);

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
		ERROR_MESSAGE_SUB("シェーダー[%s]用の\n"\
						  "アトリビュート変数「%s」の有効化に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n"\
						  , m_vertex_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glEnableVertexAttribArray(m_AttribInfo[p_index].Location);
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Attribute変数を無効にします。（ほぼ glDisableVertexAttribArray と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
*					　		（GetAttribLocationで取得した返り値）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::DisableVertexAttribArray(const GLint p_index)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("シェーダー[%s]用の\n"\
						  "アトリビュート変数「%s」の無効化に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n"\
						  , m_vertex_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glDisableVertexAttribArray(m_AttribInfo[p_index].Location);
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
*	　p_pointer		：[I/ ]　関連付ける頂点の先頭ポインタ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ShaderManager::VertexAttribPointer(const GLint p_index, const GLint p_size, const GLenum p_type, const GLboolean p_normalized, const GLsizei p_stride, const GLvoid *p_pointer)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("シェーダー[%s]用の\n"\
						  "アトリビュート変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n"\
						  , m_vertex_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		glVertexAttribPointer(m_AttribInfo[p_index].Location, p_size, p_type, p_normalized, p_stride, p_pointer);
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Attribute変数へデータを送信（関連付け）します。（ほぼ glVertexAttrib1f, glVertexAttrib2f, glVertexAttrib3f, glVertexAttrib4f と同じです）
*	　エラーや情報管理を一元化して利便性の向上を図っています。
*	引数
*	　p_index		：[I/ ]　Attribute変数のロケーションを呼び出すためのインデックス値
*					　		（GetAttribLocationで取得した返り値）
*	　p_scalar		：[I/ ]　転送するデータの個数（シェーダー内変数のベクトル成分と同じ数を入力　例)[4] → vec4）
*							 ※ 要約すると [1]を指定すれば → glVertexAttrib1f、[4]を指定すれば → glVertexAttrib4f がコールされる ※
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
void ShaderManager::VertexAttribXf(const GLint p_index, const GLint p_scalar, const GLfloat p_param1, const GLfloat p_param2, const GLfloat p_param3, const GLfloat p_param4)
{
	if (-1 == m_AttribInfo[p_index].Location)
	{
		ERROR_MESSAGE_SUB("シェーダー[%s]用の\n"\
						  "アトリビュート変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n"\
						  , m_vertex_file_name, m_AttribInfo[p_index].Name);
	}
	else
	{
		if (1 == p_scalar)
		{
			glVertexAttrib1f(m_AttribInfo[p_index].Location, p_param1);
		}
		else if (2 == p_scalar)
		{
			glVertexAttrib2f(m_AttribInfo[p_index].Location, p_param1, p_param2);
		}
		else if (3 == p_scalar)
		{
			glVertexAttrib3f(m_AttribInfo[p_index].Location, p_param1, p_param2, p_param3);
		}
		else if (4 == p_scalar)
		{
			glVertexAttrib4f(m_AttribInfo[p_index].Location, p_param1, p_param2, p_param3, p_param4);
		}
		else
		{
			ERROR_MESSAGE("シェーダー[%s]用の\n"\
						  "アトリビュート変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_AttribInfo[p_index].Name, p_scalar);
		}
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
		ERROR_MESSAGE_SUB("シェーダー%s用の\n"\
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n\n"\
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name);
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
			ERROR_MESSAGE("シェーダー%s用の\n" \
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n" \
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name, p_scalar);
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
		ERROR_MESSAGE_SUB("シェーダー%s用の\n"\
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n\n"\
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name);
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
			ERROR_MESSAGE("シェーダー%s用の\n" \
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n" \
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name, p_scalar);
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
		ERROR_MESSAGE_SUB("シェーダー%s用の\n"\
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n\n"\
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name);
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
			ERROR_MESSAGE("シェーダー%s用の\n" \
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n" \
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name, p_scalar);
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
		ERROR_MESSAGE_SUB("シェーダー%s用の\n"\
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n\n"\
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name);
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
			ERROR_MESSAGE("シェーダー%s用の\n" \
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n" \
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name, p_scalar);
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
		ERROR_MESSAGE_SUB("シェーダー%s用の\n"\
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n"\
						  "シェーダーに変数が定義されていない可能性があります\n\n"\
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name);
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
			ERROR_MESSAGE("シェーダー%s用の\n" \
						  "ユニフォーム変数「%s」へのデータの送信（関連付け）に失敗しました\n" \
						  "「p_scalar」引数のエラーです → 設定値：%d\n" \
						  , m_AllShaderFileName, m_UniformInfo[p_index].Name, p_scalar);
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
	//有効なプログラムオブジェクトの場合
	if (0 != m_ProgramObject)
	{
		// シェーダープログラムの利用を開始する
		glUseProgram(m_ProgramObject);
	}
	else
	{
		ERROR_MESSAGE("シェーダー%s用の\n" \
					  "シェーダープログラムの利用に失敗しました。", m_AllShaderFileName);
	}
}


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
GLuint ShaderManager::CreateShader(const char* p_file_name, const GLuint p_gl_xxxx_shader)
{
	//ファイルからシェーダーソースを読み込む（「Shader」フォルダ配下に格納されている必要があります）
	GLchar *shader_source = ShaderFileLoad(p_file_name);

	//シェーダーオブジェクトの生成
	GLuint shader = glCreateShader(p_gl_xxxx_shader);
	if (0 == shader)
	{
		ERROR_MESSAGE("シェーダーオブジェクトの作成に失敗しました");

		//メモリ解放
		SAFE_FREE(shader_source);

		return 0;
	}

	//ソースプログラムを読み込む
	glShaderSource(shader, 1, &shader_source, NULL);

	//シェーダーのコンパイルを開始
	printf("シェーダーのコンパイルを開始します... ");
	glCompileShader(shader);

	// コンパイルエラーをチェックする
	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (GL_FALSE == compileSuccess)
	{
		// エラーが発生した
		printf("失敗\n");
		
		GLint infoLen = 0;
		// エラーメッセージを取得
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			GLchar *message = (GLchar*)calloc(infoLen, sizeof(GLchar));
			glGetShaderInfoLog(shader, infoLen, NULL, message);

			//エラーメッセージ表示
			printf("\nコンパイルエラーの情報は以下です。\n");
			printf("%s", message);
			
			//メモリ解放
			SAFE_FREE(message);
			glDeleteShader(shader);
			shader = 0;

			ERROR_MESSAGE("シェーダーのコンパイルに失敗しました。");

		}
	}
	else
	{
		printf("完了\n");
	}

	//シェーダーソース用のメモリ解放
	SAFE_FREE(shader_source);

	return shader;
}

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
char* ShaderManager::ShaderFileLoad(const char* p_file_name)
{
	char *shader_dir_file_name = NULL;	//シェーダーファイルへのパス
	FILE *fp = NULL;		//ファイルポインタ宣言
	int StrLength = 0;		//読み込むシェーダーファイル名の長さ（バイト数）

	// 文字列の長さを取得してメモリ確保（終端を明確にするため +1 する。[\0]となる）
	StrLength = strlen(SHADER_FILE_DIR) + strlen(p_file_name);
	shader_dir_file_name = (char*)calloc(StrLength + 1, sizeof(char));

	//シェーダーファイルへのパスを生成する
	sprintf(shader_dir_file_name, "%s%s", SHADER_FILE_DIR, p_file_name);

	//ファイルのオープン
	printf("「%s」シェーダーファイルの読み込みを開始します... ", p_file_name);
	
	fp = fopen(shader_dir_file_name, "rb");
	if (NULL == fp)
	{
		printf("失敗\n");
		ERROR_MESSAGE("シェーダーファイルのオープンに失敗しました。\n"\
					  "「Shader」フォルダに格納されていますか？\n"\
					  "ファイル名が間違っていませんか？");

		//シェーダーファイルへのパス名破棄
		SAFE_FREE(shader_dir_file_name);

		return NULL;
	}

	//ファイルのサイズを取得する
	fseek(fp, 0, SEEK_END);
	int FileSize = ftell(fp);
	//空ファイルの場合
	if (0 == FileSize)
	{
		printf("失敗\n");
		ERROR_MESSAGE("空ファイルです。");

		//シェーダーファイルへのパス名破棄
		SAFE_FREE(shader_dir_file_name);
		//ファイルクローズ
		fclose(fp);

		return NULL;
	}

	//ファイルサイズ取得が完了したので先頭に戻す
	fseek(fp, 0, SEEK_SET);

	//ファイルの読み込み（終端を明確にするため +1 する。[\0]となる）
	GLchar *shader_source = (GLchar*)calloc(FileSize + 1, sizeof(char));
	fread((void*)shader_source, sizeof(char), FileSize, fp);

	//ファイルクローズ
	fclose(fp);
	//シェーダーファイルへのパス名破棄
	SAFE_FREE(shader_dir_file_name);

	printf("完了\n");

	return shader_source;
}
