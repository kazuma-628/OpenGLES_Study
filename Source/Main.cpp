/*------------------------------------------------------------------------------------------
 *　■プログラム説明■
 *	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
 *　まだ作り始めで何もできませんが（最低限の動作確認しかできません）、
 *	今後、行列を簡単に設定できるようにしたり、マウスでの操作など様々な機能を提供していく予定です。
 *------------------------------------------------------------------------------------------*/

#include "Main.h"
#include "ShaderCreateProgram.h"

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