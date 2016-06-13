/*------------------------------------------------------------------------------------------
*　■プログラム説明■
*	OpenGLESの勉強を始めようとする人向けのプロジェクトです。
*　まだ作り始めであまり出来ることがありませんが、より便利になるよう様々な機能を提供していく予定です。
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
*	操作について
*	　右クリック 及び 左クリック 及び スクロールの操作に対応しています。
*	　サンプルプログラムでは、「右クリック = 移動、左クリック = 回転、スクロール = 拡大、スペース = 初期位置」となっています。
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
	//////////////////////////////////////////////////////
	//	各オブジェクト生成

	//メイン描画用のオブジェクト生成
	MainDraw *m_MainDraw = new MainDraw;

	//Key管理用のオブジェクト生成
	DeviceManager *m_DeviceManager = new DeviceManager;

	//ウィンドウ管理用のオブジェクト生成
	WindowManager *m_WindowManager = new WindowManager;

	//モデルデータ管理用のオブジェクト生成
	ModelData *m_ModelData = new ModelData;


	//////////////////////////////////////////////////////
	//	各オブジェクト初期化 及び 準備
	
	//ウインドウを作成
	//※ ウィンドウを複数生成することにはまだ対応していないので注意 ※
	m_WindowManager->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//作成したウィンドウハンドルを取得
	GLFWwindow* const window = m_WindowManager->GetWindow();

	//キー管理用のオブジェクト初期化（マウスやキーボード制御のコールバックなどを登録）
	//この関数コールの前にウィンドウが生成されている必要がある
	//※ ウィンドウを複数生成して、それぞれKey管理することはまだ対応していないので注意 ※
	m_DeviceManager->Initialize(window);

	//メイン描画準備
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	メインループ

	//ウィンドウが開いている間はループ
	while (GL_FALSE == m_WindowManager->GetWindowShouldClose())
	{
		//イベント取り出し（マウス状態などのイベントを取得）
		glfwPollEvents();

		//メイン描画開始
		m_MainDraw->Drawing(m_WindowManager, m_DeviceManager, m_ModelData);

		//GLエラーチェック
		if (GL_NO_ERROR != GL_GET_ERROR())
		{
			ERROR_MESSAGE("プログラム内のどこかでGL関連のエラーが発生しました。\n原因を追求してください");
		}
	}

	//////////////////////////////////////////////////////
	//	生成したオブジェクトの破棄

	//終了処理
	delete m_MainDraw;
	delete m_DeviceManager;
	delete m_WindowManager;
	delete m_ModelData;
}