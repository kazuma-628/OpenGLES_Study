﻿/*------------------------------------------------------------------------------------------
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

	//グローバルデータ生成
	GlobalData m_Global = { 0 };

	//////////////////////////////////////////////////////
	//	各シェーダーオブジェクト生成

	//メイン描画用のオブジェクト生成
	HelloWorld *m_HelloWorld = new HelloWorld;

	//////////////////////////////////////////////////////
	//	各オブジェクト初期化 及び 準備
	
	//ウインドウを作成
	//※ ウィンドウを複数生成することにはまだ対応していないので注意 ※
	m_WindowManager->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//ウィンドウサイズをグローバル領域に保存
	m_Global.WindowSize = m_WindowManager->GetWindowSize();

	//デバイス管理用のオブジェクト初期化（マウスやキーボード制御のコールバックなどを登録）
	//この関数コールの前にウィンドウが生成されている必要がある
	//※ ウィンドウを複数生成して、それぞれKey管理することはまだ対応していないので注意 ※
	m_DeviceManager->Initialize( m_WindowManager->GetWindow() );

	//メイン描画準備
	m_HelloWorld->Prepare();

	//画面に文字列を表示する用のクラスの準備
	ScreenString::Prepare(m_Global);

	//////////////////////////////////////////////////////
	//	描画メインループ

	//ウィンドウが開いている間はループ
	while (GL_FALSE == m_WindowManager->GetWindowShouldClose())
	{
		/////////////////////////////
		// 各種情報の更新

		//イベント取り出し（マウス状態などのイベントを取得）
		glfwPollEvents();

		//描画に必要な各種情報を設定/更新
		SetVarietyOfInformation(m_WindowManager, m_DeviceManager, &m_Global);

		//ウィンドウサイズに変更があった場合
		if (true == TmpGlobal.ChangeWindowSize)
		{
			/////////////////////////////
			// 資源の再作成

			ScreenString::RePrepare(m_Global);

			//再作成完了
			TmpGlobal.ChangeWindowSize = false;
		}

		/////////////////////////////
		// 各種描画

		//メイン描画開始
		m_HelloWorld->Drawing(m_Global);

		//デバッグ表示の描画を実行する
		//デバッグ表示が最前面に来るようにするため一番最後に描画する
		ScreenString::DebugDrawing(m_Global);

		/////////////////////////////
		// 描画反映処理

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
	delete m_HelloWorld;
	delete m_WindowManager;
	delete m_DeviceManager;
	ScreenString::Destroy();
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

	///////////////////////////////////
	// オブジェクト移動関係の処理

	//スペースで初期位置に戻す
	if (true == KeyBoard.StateChange.Key_SPACE)
	{
		memset(&p_Global->TranslateAmount, 0, sizeof(p_Global->TranslateAmount));
		memset(&p_Global->RotateAmount, 0, sizeof(p_Global->RotateAmount));
	}

	//平行移動用の変数にマウス情報の座標を加える
	if (GLFW_PRESS == MouseButton.Left.StateChange)
	{
		//デバッグ表示する
		ScreenString::DebugPrint(*p_Global, "左クリック：%d, %d", (int)MouseButton.Position.x, (int)MouseButton.Position.y);
		p_Global->TranslateAmount.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->TranslateAmount.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
	}
	else
	{
		//左クリックされていない状態 かつ 1イベント前では左クリックされていた場合
		//（要するにフリックされた）
		if (TmpGlobal.OldLeftState != MouseButton.Left.StateChange)
		{
			//フリック速度に応じた1イベント分の惰性量を算出
			TmpGlobal.InertiaTranslate.x = MouseButton.Position.x - TmpGlobal.OldPosition.x;
			TmpGlobal.InertiaTranslate.y = MouseButton.Position.y - TmpGlobal.OldPosition.y;
		}

		//X方向の惰性がある場合
		if (0 != TmpGlobal.InertiaTranslate.x)
		{
			//惰性量を減衰させる
			p_Global->TranslateAmount.x += TmpGlobal.InertiaTranslate.x;
			TmpGlobal.InertiaTranslate.x -= TmpGlobal.InertiaTranslate.x * InertiaTranslateWeight;

		}
		//Y方向の惰性がある場合
		if (0 != TmpGlobal.InertiaTranslate.y)
		{
			//惰性量を減衰させる
			p_Global->TranslateAmount.y += TmpGlobal.InertiaTranslate.y;
			TmpGlobal.InertiaTranslate.y -= TmpGlobal.InertiaTranslate.y * InertiaTranslateWeight;
		}
	}

	//更にキーボードの情報を加える
	if (GLFW_PRESS == KeyBoard.StateChange.Key_W)
	{
		p_Global->TranslateAmount.y += 2.0f;
	}
	if (GLFW_PRESS == KeyBoard.StateChange.Key_S)
	{
		p_Global->TranslateAmount.y -= 2.0f;
	}
	if (GLFW_PRESS == KeyBoard.StateChange.Key_A)
	{
		p_Global->TranslateAmount.x += 2.0f;
	}
	if (GLFW_PRESS == KeyBoard.StateChange.Key_D)
	{
		p_Global->TranslateAmount.x -= 2.0f;
	}

	//スクロールはボタンが押されていなくても適応する
	p_Global->TranslateAmount.z += MouseButton.ScrollAmount.y - TmpGlobal.OldScrollAmount.y;

	///////////////////////////////////
	// オブジェクト回転関係の処理

	//回転用の変数にマウス情報の座標を加える
	//本来であれば360度回転したら変数を初期化した方が良いが、サンプルなので割愛
	if (GLFW_PRESS == MouseButton.Right.StateChange)
	{
		ScreenString::DebugPrint(*p_Global, "右クリック：%d, %d", (int)MouseButton.Position.x, (int)MouseButton.Position.y);
		p_Global->RotateAmount.x += MouseButton.Position.x - TmpGlobal.OldPosition.x;
		p_Global->RotateAmount.y += MouseButton.Position.y - TmpGlobal.OldPosition.y;
		//360度を超えたら0度に戻す（360度と0度は同じなので）
		p_Global->RotateAmount.x = fmodf(p_Global->RotateAmount.x, 360.0 * RotateSpeedWeight);
		p_Global->RotateAmount.y = fmodf(p_Global->RotateAmount.y, 360.0 * RotateSpeedWeight);
	}
	else
	{
		//右クリックされていない状態 かつ 1イベント前では右クリックされていた場合
		//（要するにフリックされた）
		if (TmpGlobal.OldRightState != MouseButton.Right.StateChange)
		{
			//フリック速度に応じた1イベント分の惰性量を算出
			TmpGlobal.InertiaRotate.x = MouseButton.Position.x - TmpGlobal.OldPosition.x;
			TmpGlobal.InertiaRotate.y = MouseButton.Position.y - TmpGlobal.OldPosition.y;
		}

		//X方向の惰性がある場合
		if (0 != TmpGlobal.InertiaRotate.x)
		{
			//惰性量を減衰させる
			p_Global->RotateAmount.x += TmpGlobal.InertiaRotate.x;
			TmpGlobal.InertiaRotate.x -= TmpGlobal.InertiaRotate.x * InertiaRotateWeight;

		}
		//Y方向の惰性がある場合
		if (0 != TmpGlobal.InertiaRotate.y)
		{
			//惰性量を減衰させる
			p_Global->RotateAmount.y += TmpGlobal.InertiaRotate.y;
			TmpGlobal.InertiaRotate.y -= TmpGlobal.InertiaRotate.y * InertiaRotateWeight;
		}
	}

	////////////////////////////////////
	// メインとなるモデルビューマトリクスの作成（大元のマトリクスデータ）

	//オブジェクトを移動させるための行列
	Matrix ModelView;

	//3D空間にするための行列
	Matrix Projection;

	//カメラの映る位置に移動させる
	ModelView.Translate(0.0, 0.0, -35.0f);
	//マウスでのオブジェクトの移動
	ModelView.Translate(p_Global->TranslateAmount.x / 6.0f, -p_Global->TranslateAmount.y / 6.0f, p_Global->TranslateAmount.z);

	//アスペクト比（幅 ÷ 高さ）を算出、歪み補正する
	GLfloat Aspect = (GLfloat)WindowSize.Width / WindowSize.Height;
	ModelView.Scale(1.0f, Aspect, 1.0);

	//マウスでのオブジェクトの回転
	ModelView.Rotate(-p_Global->RotateAmount.y / RotateSpeedWeight, 1.0f, 0.0f, 0.0f);
	ModelView.Rotate(-p_Global->RotateAmount.x / RotateSpeedWeight, 0.0f, 1.0f, 0.0f);

	//投資投影行列で使用する値をグローバル領域に保存
	p_Global->NearClip = 1.0f;
	p_Global->FarClip = 300.0f;
	//透視投影行列を適用する
	Projection.Perspective(-1.0f, 1.0f, -1.0f, 1.0f, p_Global->NearClip, p_Global->FarClip);

	///////////////////////////////////
	// 各種情報を保存

	//アスペクト比（幅 ÷ 高さ）を保存
	p_Global->Aspect = Aspect;

	//各種行列を保存する
	p_Global->ModelViewMatrix = ModelView.GetMatrix();
	p_Global->ProjectionMatrix = Projection.GetMatrix();

	//ウィンドウサイズの変更チェック
	if (p_Global->WindowSize.Width != WindowSize.Width || p_Global->WindowSize.Height != WindowSize.Height)
	{
		//ウィンドウマネージャーで通知するのではなく、実際に変更と判断してから通知する
		printf("ウィンドウサイズが変更されました → （%d × %d）\n", WindowSize.Width, WindowSize.Height);

		TmpGlobal.ChangeWindowSize = true;
	}
	//ウィンドウサイズ保存
	p_Global->WindowSize = WindowSize;

	//1イベント前の情報を保存する
	TmpGlobal.OldPosition = MouseButton.Position;
	TmpGlobal.OldScrollAmount = MouseButton.ScrollAmount;
	TmpGlobal.OldLeftState = MouseButton.Left.StateChange;
	TmpGlobal.OldRightState = MouseButton.Right.StateChange;
}

