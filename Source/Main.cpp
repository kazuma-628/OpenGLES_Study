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
*	・ERROR_MESSAGE("ここにテキストを記述します");	//続行不可能なエラーが発生した場合はこのマクロを使用することでメッセージボックスを表示できます
*	・printf("ここにテキストを記述します");			//続行不可能なエラー以外はprintfで普通に表示してください
*------------------------------------------------------------------------------------------*/

#include "Main.h"

typedef struct
{
	Vec2 OldPosition;				//【1イベント前】マウスのカーソル座標
	Vec2 OldScrollAmount;			//【1イベント前】スクロールの合計量、初期状態は[x:0（横[左右]スクロール）][y:0（縦[上下]スクロール）]で、
									//　スクロールした分だけ値が蓄積（加算/減算）されていく
}TmpGlobalData;

static TmpGlobalData TmpGlobal = { 0 };

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

	//ウィンドウ管理用のオブジェクト生成
	WindowManager *m_WindowManager = new WindowManager;

	//デバイス管理用のオブジェクト生成
	DeviceManager *m_DeviceManager = new DeviceManager;

	//リソース管理用のオブジェクト生成
	//※このオブジェクトを直接操作することはないが、
	//　コンストラクタとデストラクタを明示的にコールさせるために生成する
	ResourceManager *m_ResourceManager = new ResourceManager;

	//モデルデータ管理用のオブジェクト生成
	//※このオブジェクトを直接操作することはないが、
	//　コンストラクタとデストラクタを明示的にコールさせるために生成する
	ModelManager *m_ModelManager = new ModelManager;

	//グローバルデータ生成
	GlobalData m_Global = { 0 };

	//////////////////////////////////////////////////////
	//	各シェーダーオブジェクト生成

	//メイン描画用のオブジェクト生成
	MainDraw *m_MainDraw = new MainDraw;

	//////////////////////////////////////////////////////
	//	各オブジェクト初期化 及び 準備
	
	//ウインドウを作成
	//※ ウィンドウを複数生成することにはまだ対応していないので注意 ※
	m_WindowManager->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//作成したウィンドウハンドルを取得
	GLFWwindow* const window = m_WindowManager->GetWindow();

	//デバイス管理用のオブジェクト初期化（マウスやキーボード制御のコールバックなどを登録）
	//この関数コールの前にウィンドウが生成されている必要がある
	//※ ウィンドウを複数生成して、それぞれKey管理することはまだ対応していないので注意 ※
	m_DeviceManager->Initialize(window);

	//メイン描画準備
	m_MainDraw->Prepare();

	//////////////////////////////////////////////////////
	//	描画メインループ

	//ウィンドウが開いている間はループ
	while (GL_FALSE == m_WindowManager->GetWindowShouldClose())
	{
		//イベント取り出し（マウス状態などのイベントを取得）
		glfwPollEvents();

		//描画に必要な各種情報を設定/更新
		SetVarietyOfInformation(m_WindowManager, m_DeviceManager, &m_Global);

		//メイン描画開始
		m_MainDraw->Drawing(&m_Global);

		//描画反映処理
		m_WindowManager->DrawingOnWindow();

		//GLエラーチェック
		if (GL_NO_ERROR != GL_GET_ERROR())
		{
			ERROR_MESSAGE("プログラム内のどこかでGL関連のエラーが発生しました。\n原因を追求してください\n");
		}
	}

	//////////////////////////////////////////////////////
	//	生成したオブジェクトの破棄

	//終了処理
	delete m_MainDraw;
	delete m_WindowManager;
	delete m_DeviceManager;
	delete m_ResourceManager;
	delete m_ModelManager;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　描画に必要な各種情報を設定/更新する
*	引数
*	　p_WindowManager		：[I/ ]　ウィンドウ管理オブジェクト
*	　p_DeviceManager		：[I/ ]　デバイス管理オブジェクト
*	　p_Global				：[ /O]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void SetVarietyOfInformation(WindowManager *p_WindowManager, DeviceManager *p_DeviceManager, GlobalData *p_Global)
{
	//ウィンドウサイズの取得
	Size const WindowSize = p_WindowManager->GetWindowSize();
	//マウスの情報を取得
	MouseInfo MouseButton = p_DeviceManager->GetMouseInfo();
	//キー（キーボード）の情報を取得
	KeyInfo KeyBoard = p_DeviceManager->GetKeyInfo();

	////////////////////////////////////
	// メインとなるモデルビューマトリクスの作成（大元のマトリクスデータ）

	//オブジェクトを移動させるための行列
	Matrix ModelView;

	//3D空間にするための行列
	Matrix Projection;

	///////////////////////////////////
	// オブジェクト移動関係の処理

	//スペースで初期位置に戻す
	if (true == KeyBoard.Change.Key_SPACE)
	{
		memset(&p_Global->Translate, 0, sizeof(p_Global->Translate));
		memset(&p_Global->Rotate, 0, sizeof(p_Global->Rotate));
	}

	//平行移動用の変数にマウス情報の座標を加える
	if (GLFW_PRESS == MouseButton.Left.State)
	{
		p_Global->Translate.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->Translate.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
	}
	//スクロールはボタンが押されていなくても適応する
	p_Global->Translate.z += MouseButton.ScrollAmount.y - TmpGlobal.OldScrollAmount.y;

	//回転用の変数にマウス情報の座標を加える
	//本来であれば360度回転したら変数を初期化した方が良いが、サンプルなので割愛
	if (GLFW_PRESS == MouseButton.Right.State)
	{
		p_Global->Rotate.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->Rotate.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
	}

	//更にキーボードの情報を加える
	if (GLFW_PRESS == KeyBoard.Change.Key_W)
	{
		p_Global->Translate.y += 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_S)
	{
		p_Global->Translate.y -= 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_A)
	{
		p_Global->Translate.x += 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_D)
	{
		p_Global->Translate.x -= 1.0f;
	}

	//カメラの映る位置に移動させる
	ModelView.Translate(0.0, 0.0, -35.0f);
	//マウスでのオブジェクトの移動
	ModelView.Translate(p_Global->Translate.x / 6.0f, -p_Global->Translate.y / 6.0f, p_Global->Translate.z);

	//マウスでのオブジェクトの回転
	ModelView.Rotate(-p_Global->Rotate.y / 2.0f, 1.0f, 0.0f, 0.0f);
	ModelView.Rotate(-p_Global->Rotate.x / 2.0f, 0.0f, 1.0f, 0.0f);

	//投資投影行列で使用する値をグローバル領域に保存
	p_Global->NearClip = 1.0f;
	p_Global->FarClip = 200.0f;
	//透視投影行列を適用する
	Projection.Perspective(-1.0f, 1.0f, -1.0f, 1.0f, p_Global->NearClip, p_Global->FarClip);

	///////////////////////////////////
	// 各種情報を保存

	//各種行列を保存する
	p_Global->ModelViewMatrix = ModelView.GetMatrix();
	p_Global->ProjectionMatrix = Projection.GetMatrix();

	//ウィンドウサイズを保存
	p_Global->WindowSize.Width = WindowSize.Width;
	p_Global->WindowSize.Height = WindowSize.Height;

	//1イベント前の情報を保存する
	TmpGlobal.OldPosition.x = MouseButton.Position.x;
	TmpGlobal.OldPosition.y = MouseButton.Position.y;
	TmpGlobal.OldScrollAmount.x = MouseButton.ScrollAmount.x;
	TmpGlobal.OldScrollAmount.y = MouseButton.ScrollAmount.y;
}


