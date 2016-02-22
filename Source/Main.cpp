/*------------------------------------------------------------------------------------------
*　■プログラム説明■
*	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
*　まだ作り始めで何もできませんが（最低限の動作確認しかできません）、
*	今後、行列を簡単に設定できるようにしたり、マウスでの操作など様々な機能を提供していく予定です。
*
*	関数について
*　「ShaderManager」クラスは、基本的にOpenGLESのコマンドをもっと簡単に使えるようにしたもの（補助関数）です。
*　シェーダーソースの読み込みやエラー処理、プログラムオブジェクトの状態管理などを一元化して分かりやすくしました。
*　「glコマンド」名の「gl」を取ったものが補助関数名となっている場合が多いのです。（glUseProgram は UseProgram など）
*	ただ、CreateShaderProgramは別で、中でいろいろ処理しています。がお決まりの処理がほとんどなので気にしなくてよいです。
*　とりあえず、ファイル名を指定したら、そこからプログラムオブジェクトを作成してくれるんだな程度で問題ありません。
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

	//メイン描画用のオブジェクト生成
	MainDraw *MainDrawing = new MainDraw;

	//メイン描画準備
	MainDrawing->Prep();

	//ウィンドウが開いている間はループ
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		//イベント取り出し（マウス状態などのイベント）
		glfwPollEvents();

		//メイン描画開始
		MainDrawing->Draw(window);
	}

	//終了処理
	delete MainDrawing;
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

	//ウィンドウ生成
	//ここでウィンドウサイズも指定しています。サイズを変更したい場合はDefine値を変更してください。
	printf("ウィンドウ（%d × %d）の生成を開始します... ", WINDOW_WIDTH, WINDOW_HEIGHT);
	GLFWwindow *const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study", NULL, NULL);

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