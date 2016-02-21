/*------------------------------------------------------------------------------------------
 *　■プログラム説明■
 *	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
 *　まだ作り始めで何もできませんが（最低限の動作確認しかできません）、
 *	今後、行列を簡単に設定できるようにしたり、マウスでの操作など様々な機能を提供していく予定です。
 *
 *	変数名について
 *	・「 p_ 」で始まるものは関数の引数（パラメーター）を表しています。
 *	・「 m_ 」で始まるものはクラスの変数（メンバ）を表しています。
 *
 *	DEBUG用のメッセージ処理について
 *	・ERROR_MESSAGE("ここにテキストを記述します");	//続行不可能なエラーが発生した場合、メッセージボックスを表示します
	・printf("ここにテキストを記述します");			//続行不可能なエラー以外はprintfで普通に表示してください
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

	//Mainシェーダー用のオブジェクト生成
	ShaderManager *MainShader = new ShaderManager;

	//シェーダーの読み込みを行う
	//「Shader」フォルダに格納されている必要があります。
	MainShader->CreateShaderProgram("Main.vert", "Main.frag");
	
	GLint attr_pos = MainShader->GetAttribLocation("attr_pos");

	GLint attr_color = MainShader->GetAttribLocation("attr_color");

	// シェーダープログラムの利用を開始する
	glUseProgram(MainShader->GetShaderProgram());
	if (GL_NO_ERROR != glGetError())
	{
		ERROR_MESSAGE("シェーダープログラムの利用に失敗しました。");
	}

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

	//終了処理
	delete MainShader;
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

	// GLFW初期化とエラーチェック
	printf("GLFWの初期化を開始します... ");
	if(GL_TRUE != glfwInit())
	{
		ERROR_MESSAGE("GLFWの初期化に失敗しました");
	}
	printf("完了\n");

	//プログラム終了時の処理を登録する（GLFWの終了処理をする）
	atexit(glfwTerminate);

	//OpenGLのバージョン及びプロファイル指定
	//OpenGLES3.0を指定したいところだが、NSIGHT（デバッカツール）を使用するために、GLES3.0に対応するGL4.3を指定する
	//バージョン等を変更したいときは「glfwWindowHint」で検索すればわかると思います。
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//ウィンドウ生成
	//ここでウィンドウサイズも指定しています。サイズを変更したい場合はDefine値を変更してください。
	printf("ウィンドウ（%d × %d）の生成を開始します... ", WINDOW_WIDTH, WINDOW_HEIGHT);
	GLFWwindow *const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study", NULL, NULL);
	
	//ウィンドウが生成できているかチェック
	if(NULL == window)
	{
		ERROR_MESSAGE("ウィンドウ生成に失敗しました。\n"\
					  "グラフィックがOpenGLESに対応していない可能性があります。\n"\
					  "グラフィックドライバを最新にしてみてください。\n"\
					  "それでもダメな場合は、残念ながらお使いの環境では使用することができません。\n"\
					  "設定では、OpenGLES3.0に対応するOpenGL4.3を設定しています。\n"\
					  "お使いの環境が対応しているかネットなどで調べてみてください。");
	}
	printf("完了\n");

	// 作成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(window);

	// GLEWを初期化する
	printf("GLEWの初期化を開始します... ");
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		ERROR_MESSAGE("GLEWの初期化に失敗しました。");
	}
	printf("完了\n");

	// カラーバッファの入れ替えタイミング（通常は1を入力）
	glfwSwapInterval(1);

	return window;
}