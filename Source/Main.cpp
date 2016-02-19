/*------------------------------------------------------------------------------------------
 *　■プログラム説明■
 *	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
 *　まだ作り始めで何もできませんが（最低限の動作確認しかできません）、
 *	今後、行列を簡単に設定できるようにしたり、マウスでの操作など様々な機能を提供していく予定です。
 *------------------------------------------------------------------------------------------*/

#include <Main.hpp>

/*-------------------------------------------------------------------------------
*	関数説明
*	　メインエントリーポイント
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void main(void)
{
	//OpenGLの初期化 と ウィンドウハンドルの取得
	GLFWwindow *const window = OpenGLES_init();

	//シェーダーの読み込みを行う
	//「Shader」フォルダに格納されている必要があります。
	GLint shader_program = Shader_CreateProgram("Main.vert", "Main.frag");

	GLint attr_pos = glGetAttribLocation(shader_program, "attr_pos");
	assert(attr_pos >= 0);

	GLint attr_color = glGetAttribLocation(shader_program, "attr_color");
	assert(attr_color >= 0);

	// シェーダーの利用を開始する
	glUseProgram(shader_program);
	assert(glGetError() == GL_NO_ERROR);

	//シェーダーの変数を有効化
	glEnableVertexAttribArray(attr_pos);
	glEnableVertexAttribArray(attr_color);


	// 画面中央へ描画する
	const GLfloat position[] =
	{
		// v0
		-0.5f, 0.5f,
		// v1
		0.5f, 0.5f,
		// v2
		0.5f, -0.5f,
		// v3
		-0.5, -0.5
	};

	// 頂点カラーを設定する
	const GLubyte color[] =
	{
		// v0 rgb
		200, 200, 200,
		// v1 rgb
		200, 0, 0,
		// v2 rgb
		0, 200, 0,
		// v3 rgb
		0, 0, 200
	};


	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	int count = 0;
	//ウィンドウが開いている間はループ
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		//色初期化
		glClear(GL_COLOR_BUFFER_BIT);

		//ビューポートを設定する
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		//変数を転送
		glVertexAttribPointer(attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
		glVertexAttribPointer(attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		//描画処理
		glfwSwapBuffers(window);

		//イベント取り出し
		glfwPollEvents();
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　OpenGLの初期化を行う
*	引数
*	　なし
*	戻り値
*	　ウィンドウハンドル
*-------------------------------------------------------------------------------*/
GLFWwindow *const OpenGLES_init()
{
	// GLFW初期化
	assert(GL_TRUE == glfwInit());

	//プログラム終了時の処理を登録する（GLFWの終了処理をする）
	atexit(glfwTerminate);

	//OpenGLのバージョン及びプロファイル指定
	//OpenGLES3.0を指定したいところだが、NSIGHTを使用するために、GLES3.0に対応するGL4.3を指定する
	//バージョン等を変更したいときは「glfwWindowHint」で検索すればわかると思います。
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//ウィンドウ生成
	GLFWwindow *const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study", NULL, NULL);
	assert(NULL != window);

	// 作成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(window);

	// GLEWを初期化する
	glewExperimental = GL_TRUE;
	assert(GLEW_OK == glewInit());

	// カラーバッファの入れ替えタイミング（通常は1を入力）
	glfwSwapInterval(1);

	return window;
}

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