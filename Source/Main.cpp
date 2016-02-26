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
*	・「 m_ 」で始まるものはクラスの変数（メンバ）を表しています。（main関数は特別にクラスでなくても付与してます）
*
*	DEBUG用のメッセージ処理について
*	・ERROR_MESSAGE("ここにテキストを記述します");	//続行不可能なエラーが発生した場合、メッセージボックスを表示します
*	・printf("ここにテキストを記述します");			//続行不可能なエラー以外はprintfで普通に表示してください
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
	/*
	GLFWwindow *const m_window = OpenGLES_init();
	GLFWwindow *const m_window2 = OpenGLES_init();
	GLFWwindow *const m_window3 = OpenGLES_init();
	*/

	//////////////////////////////////////////////////////
	//	各オブジェクト生成

	//メイン描画用のオブジェクト生成
	MainDraw *m_MainDraw = new MainDraw;

	//Key管理用のオブジェクト生成
	KeyManager *m_KeyManager = new KeyManager;

	//ウィンドウ管理用のオブジェクト生成
	WindowManager *m_WindowManager = new WindowManager;


	//////////////////////////////////////////////////////
	//	各オブジェクト初期化
	
	//キー管理用のオブジェクト初期化（マウスやキーボード制御のコールバックなどを登録）
	m_KeyManager->Initialize();

	//ウインドウを作成
	m_WindowManager->CreateNewWindow();

	//メイン描画準備
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	メインループ
	GLFWwindow* const Window = m_WindowManager->GetWindow();

	//ウィンドウが開いている間はループ
	while (glfwWindowShouldClose(Window) == GL_FALSE)
	{
		//イベント取り出し（マウス状態などのイベントを取得）
		glfwPollEvents();

		//メイン描画開始
		m_MainDraw->Drawing(Window);
	}

	//////////////////////////////////////////////////////
	//	生成したオブジェクトの破棄

	//終了処理
	delete m_MainDraw;
	delete m_KeyManager;
	delete m_WindowManager;

}