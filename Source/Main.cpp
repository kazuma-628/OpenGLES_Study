﻿/*------------------------------------------------------------------------------------------
*　■プログラム説明■
*　OpenGLESの勉強を始めようとする人向けのプロジェクトです。
*　まだ作り始めであまり出来ることがありませんが、より便利になるよう様々な機能を提供していく予定です。
*
*	■主機能クラスについて
*	・WindowManager.cpp	：ウィンドウを管理・制御するクラスです。
*	・DeviceManager.cpp	：マウスやキーボードなどのデバイス系を管理・制御するクラスです。
*	・ShaderManager.cpp	：プログラムオブジェクトの生成や頂点データ転送など、シェーダー関連を管理・制御するクラスです。
*	・Texture.cpp		：テクスチャデータの読み込みなどを行うためのクラスです。
*	・ScreenString.cpp	：画面上に文字を描画するためのクラスです。
*	・ModelManager.cpp	：モデルデータを読み込んで描画するなど、モデル関連を管理・制御するクラスです。
*
*	※「ShaderManager.cpp」についての補足
*	　「ShaderManager」クラスは、基本的にOpenGLESのコマンドをもっと簡単に使えるようにしたもの（補助関数）です。
*	　シェーダーソースの読み込みやエラー処理、プログラムオブジェクトの状態管理などを一元化して分かりやすくしました。
*	　「glコマンド」名の「gl」を取ったものが補助関数名となっている場合が多いのです。（glUseProgram は UseProgram など）
*	　ただ、CreateShaderProgramは別で、中でいろいろ処理しています。がお決まりの処理がほとんどなので気にしなくてよいです。
*	　とりあえず、ファイル名を指定したら、そこからプログラムオブジェクトを作成してくれるんだな程度で問題ありません。
*
*	■変数名について
*	・「 p_ 」で始まるものは関数の引数（パラメーター）を表しています。
*	・「 m_ 」で始まるものはクラスの変数（メンバ）を表しています。（main関数は特別にクラスでなくても付与してます）
*
*	■DEBUG用のメッセージ処理について
*	・ERROR_MESSAGE("ここにテキストを記述します");	//続行不可能なエラーが発生した場合はこのマクロを使用することで、
*													//メッセージボックスを表示して処理を中断できます。
*	・printf("ここにテキストを記述します");			//続行不可能なエラー以外はprintfで普通に表示してください
*
*	■ベクトル/マトリクス変数・演算について
*	　ベクトル/マトリクス変数・演算についてはGLMライブラリを使用しています。
*	　GLSL言語で使用する変数をC言語でも使用できるようにするライブラリで、GLSL言語の記述とほぼ同等の扱いができます。
*	　マニュアルは「Library/GLM/Manual.pdf」にあるので、必要に応じて読んで下さい。
*
*	■操作について
*	・右クリック 及び 左クリック 及び スクロールの操作に対応しています。
*	　サンプルプログラムでは、「右クリック = 移動、左クリック = 回転、スクロール = 拡大、スペース = 初期位置」となっています。
*	・描画データの選択(種類)はキーボードの「1 ～ 9」で切り替えることが出来ます。
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
	shared_ptr<WindowManager> m_Window = make_shared<WindowManager>();

	//グローバルデータ生成
	GlobalData m_Global = { 0 };


	//////////////////////////////////////////////////////
	//	各描画オブジェクト生成 と 描画開始キー設定

	//描画するクラスの管理リスト
	const DarwClassInfo DrawClass[] =
	{
		// { 描画を開始(選択)するキー, 描画するクラス }
		//	（英数字(大文字)のみ）

		{ '0', make_shared<HelloWorld>() },		//ハローワールド描画（OpenGLの基本的な描画）
		{ '1', make_shared<HelloModel>() },		//ハローモデル描画（モデルデータのお試し描画）
	};

	//描画するクラスの最大数
	uint16_t DrawClassMax = sizeof(DrawClass) / sizeof(DrawClass[0]);


	//////////////////////////////////////////////////////
	//	各オブジェクト初期化 及び 準備
	
	//ウインドウを作成
	m_Window->CreateNewWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLES_Study");
	//ウィンドウサイズをグローバル領域に保存
	m_Global.WindowSize = m_Window->GetWindowSize();

	//初回描画アイテムを設定（リストの一番最初）
	TmpGlobal.LastKey = DrawClass[0].Key;

	//画面に文字列を表示する用のクラスの準備
	ScreenString::Prepare(m_Global);


	//////////////////////////////////////////////////////
	//	描画メインループ

	//ウィンドウが開いている間はループ
	while (GL_FALSE == m_Window->GetWindowShouldClose())
	{

		/////////////////////////////
		// 各種情報の更新

		//イベント取り出し（マウス状態などのイベントを取得）
		glfwPollEvents();

		//描画に必要な各種情報を設定/更新
		SetVarietyOfInformation(m_Window, &m_Global);


		/////////////////////////////
		// 資源の再作成

		//ウィンドウサイズに変更があった場合
		if (true == TmpGlobal.ChangeWindowSize)
		{
			//描画リスト分ループ
			for (uint16_t index = 0; index < DrawClassMax; index++)
			{
				//描画の再準備（資源の再作成）フラグを立てる
				//個々の描画準備のときにフラグをチェックして必要であれば再準備処理する
				DrawClass[index].Class->SetRePrepareFlag(true);
			}

			//資源の再作成
			ScreenString::RePrepare(m_Global);

			//フラグを落とす
			TmpGlobal.ChangeWindowSize = false;
		}


		/////////////////////////////
		// 各種描画
		// 選択されたキーによって描画を切り替える
		// 切替時に描画が2重で行われる不効率さがあるが現状維持とする。

		//描画リスト分ループ
		for (uint16_t index = 0; index < DrawClassMax; index++)
		{
			if (DrawClass[index].Key == m_Window->GetDevice()->GetKeyInfo().LastKey ||
				DrawClass[index].Key == TmpGlobal.LastKey)
			{
				//選択したキーを保存
				TmpGlobal.LastKey = DrawClass[index].Key;

				//選択した描画クラス名を保存
				TmpGlobal.DrawClass = typeid(*DrawClass[index].Class).name();

				//描画準備
				DrawClass[index].Class->Prepare(m_Global);

				//描画実行
				DrawClass[index].Class->Drawing(m_Global);
			}
		}
		
		//デバッグ表示の描画を実行する
		//デバッグ表示が最前面に来るようにするため一番最後に描画する
		ScreenString::DebugDrawing(m_Global);


		/////////////////////////////
		// 描画反映処理

		m_Window->DrawingOnWindow();

		//GLエラーチェック
		if (GL_NO_ERROR != GL_GET_ERROR())
		{
			ERROR_MESSAGE("プログラム内のどこかでGL関連のエラーが発生しました。\n原因を追求してください\n");
		}
	}


	//////////////////////////////////////////////////////
	//	不要なデータの破棄処理

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
void SetVarietyOfInformation(const shared_ptr<WindowManager> p_WindowManager, GlobalData *p_Global)
{
	//ウィンドウサイズの取得
	const uvec2 WindowSize = p_WindowManager->GetWindowSize();
	//マウスの情報を取得
	const MouseInfo MouseButton = p_WindowManager->GetDevice()->GetMouseInfo();
	//キー（キーボード）の情報を取得
	const KeyInfo KeyBoard = p_WindowManager->GetDevice()->GetKeyInfo();

	//今描画している(選択している)クラスと、表示している位置と回転の座標を表示
	//（1フレーム前の情報だけど、一番上に表示したいので良しとする）
	ScreenString::DebugPrint(*p_Global, "描画クラス：%s", TmpGlobal.DrawClass.c_str() + 6);		//「+6」は不要な「class 」の部分を読み飛ばして表示するためのもの
	ScreenString::DebugPrint(*p_Global, "位置 X：%.0f, Y：%.0f, Z：%.0f"\
							 ,p_Global->TranslateAmount.x, p_Global->TranslateAmount.y, p_Global->TranslateAmount.z);
	ScreenString::DebugPrint(*p_Global, "回転 X：%.0f, Y：%.0f, Z：%.0f"\
							 ,p_Global->RotateAmount.y / RotateSpeedWeight, p_Global->RotateAmount.x / RotateSpeedWeight, p_Global->RotateAmount.z / RotateSpeedWeight);

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
		ScreenString::DebugPrint(*p_Global, "左クリック：%d, %d", MouseButton.Position.x, MouseButton.Position.y);
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
		ScreenString::DebugPrint(*p_Global, "右クリック：%d, %d", MouseButton.Position.x, MouseButton.Position.y);
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
	mat4 ModelViewMat;

	//3D空間にするための行列
	mat4 ProjectionMat;

	//アスペクト比（幅 ÷ 高さ）を算出
	GLfloat Aspect = static_cast<GLfloat>(WindowSize.x) / WindowSize.y;

	//カメラの映る位置に移動させる
	ModelViewMat *= translate(vec3(0.0f, 0.0f, -40.0f));
	//マウスでのオブジェクトの移動
	ModelViewMat *= translate(vec3(p_Global->TranslateAmount.x / 6.0f, -p_Global->TranslateAmount.y / 6.0f, p_Global->TranslateAmount.z));

	//マウスでのオブジェクトの回転
	ModelViewMat *= rotate(radians(p_Global->RotateAmount.y / RotateSpeedWeight), vec3(1.0f, 0.0f, 0.0f));
	ModelViewMat *= rotate(radians(p_Global->RotateAmount.x / RotateSpeedWeight), vec3(0.0f, 1.0f, 0.0f));

	//投資投影行列で使用する値をグローバル領域に保存
	p_Global->NearClip = 1.0f;
	p_Global->FarClip = 1000.0f;
	//透視投影行列を適用する（歪みも補正）
	ProjectionMat = perspective(1.0f, Aspect, p_Global->NearClip, p_Global->FarClip);

	///////////////////////////////////
	// 各種情報を保存

	//アスペクト比（幅 ÷ 高さ）を保存
	p_Global->Aspect = Aspect;

	//各種行列を保存する
	p_Global->ModelViewMat = ModelViewMat;
	p_Global->ProjectionMat = ProjectionMat;

	//ウィンドウサイズの変更チェック
	if (p_Global->WindowSize.x != WindowSize.x || p_Global->WindowSize.y != WindowSize.y)
	{
		//ウィンドウマネージャーで通知するのではなく、実際に変更と判断してから通知する
		printf("ウィンドウサイズが変更されました → （%d × %d）\n", WindowSize.x, WindowSize.y);

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

