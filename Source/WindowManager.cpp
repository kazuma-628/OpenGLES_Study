#include "WindowManager.h"

/////////////////////////////////////////////
//static変数の実体を定義

Size WindowManager::m_WindowSize;			//マウスボタンの情報

//コンストラクタ
WindowManager::WindowManager()
{
	m_window = NULL;
	memset(&m_WindowSize, 0, sizeof(m_WindowSize));
}

//デストラクタ
WindowManager::~WindowManager()
{
	glfwDestroyWindow(m_window);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ウィンドウを作成する
*	　※ ウィンドウを複数生成することにはまだ対応していないので注意 ※
*	引数
*	　p_Width	：[I/ ]　ウィンドウの幅
*	　p_Height	：[I/ ]　ウィンドウの高さ
*	　p_Title	：[I/ ]　ウィンドウの名前（ウィンドウ左上やタスクバーに表示される）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void WindowManager::CreateNewWindow(const int p_Width, const int p_Height, const char* p_Title)
{

	//////////////////////////////////////////////////////
	//	GLFW初期化

	// GLFW初期化とエラーチェック
	printf("GLFWの初期化を開始します... ");
	if (GL_TRUE != glfwInit())
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


	//////////////////////////////////////////////////////
	//	ウィンドウ生成

	//ここでウィンドウサイズも指定しています。サイズを変更したい場合はDefine値を変更してください。
	printf("ウィンドウ（%d × %d）の生成を開始します... ", p_Width, p_Height);
	GLFWwindow *const window = glfwCreateWindow(p_Width, p_Height, p_Title, NULL, NULL);

	//ウィンドウが生成できているかチェック
	if (NULL == window)
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

	// カラーバッファの入れ替えタイミング（通常は1を入力）
	glfwSwapInterval(1);

	//////////////////////////////////////////////////////
	//	ウィンドウサイズが変化した時用のコールバックを登録

	glfwSetWindowSizeCallback(window, WindowManager::WindowSizeCallback);

	//////////////////////////////////////////////////////
	//	GLEW初期化

	// GLEWを初期化する
	printf("GLEWの初期化を開始します... ");
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		ERROR_MESSAGE("GLEWの初期化に失敗しました。");
	}
	printf("完了\n");
	
	//////////////////////////////////////////////////////
	//	生成した情報を保存

	//生成したウィンドウハンドルを保存
	m_window = window;

	//生成した時のウィンドウの幅高さを保存
	m_WindowSize.Width = p_Width;
	m_WindowSize.Height = p_Height;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ウィンドウに描画する（フロントバッファ / バックバッファ 共通）
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void WindowManager::DrawingOnWindow(void)
{
	glfwSwapBuffers(m_window);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ウィンドウサイズが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_Width	：[I/ ]　ウィンドウの幅
*	　p_Height	：[I/ ]　ウィンドウの高さ
*	　詳細は下記URL参照のこと
*	　http://www.glfw.org/docs/latest/group__window.html#gaaca1c2715759d03da9834eac19323d4a
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void WindowManager::WindowSizeCallback(GLFWwindow* p_window, int p_Width, int p_Height)
{
	//生成した時のウィンドウの幅高さを保存
	m_WindowSize.Width = p_Width;
	m_WindowSize.Height = p_Height;
}