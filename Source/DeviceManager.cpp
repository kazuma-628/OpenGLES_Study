#include "DeviceManager.h"
#include "WindowManager.h"

//コンストラクタ
DeviceManager::DeviceManager()
{
}

//デストラクタ
DeviceManager::~DeviceManager()
{

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Key管理マネージャーを初期化する
*	　/※ ウィンドウを複数生成して、それぞれKey管理することはまだ対応していないので注意 ※
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::Initialize(GLFWwindow* const p_window)
{
	//マウスボタンが変化した時用のコールバックを登録
	glfwSetMouseButtonCallback(p_window, DeviceManager::MouseButtonCallback);

	//マウス座標が変化した時用のコールバックを登録
	glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);

	//マウスホイールが変化した時用のコールバックを登録
	glfwSetScrollCallback(p_window, DeviceManager::ScrollCallback);

	//キー（キーボード）が変化した時用のコールバック
	glfwSetKeyCallback(p_window, DeviceManager::KeyCallback);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスボタンが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_button	：[I/ ]　どのボタンが変化したか
*	　p_action	：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
*	　p_mods	：[I/ ]　よくわからない
*	　詳細は下記参照のこと
*	　[http://www.glfw.org/docs/latest/group__input.html]の[GLFWmousebuttonfun]関数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	// ポインタからウィンドウクラスのインスタンスを取り出す
	WindowManager *Window = static_cast<WindowManager*>(glfwGetWindowUserPointer(p_window));
	shared_ptr<DeviceManager> Device = Window->GetDevice();

	//座標を取得用の一時変数
	double PosX = 0.0;
	double PosY = 0.0;

	//カーソルの座標を取得します（ウィンドウ系の座標が入ります）
	glfwGetCursorPos(p_window, &PosX, &PosY);

	//座標管理用の変数宣言
	//　座標取得APIの引数が[double]の為、無駄だが仕方なくこのような橋渡しをしている
	//　（このようにしないと、コンパイラでワーニングが出るので）
	vec2 Pos;
	Pos.x = (GLfloat)PosX;
	Pos.y = (GLfloat)PosY;

	//右クリックに関する処理
	if (GLFW_MOUSE_BUTTON_RIGHT == p_button)
	{
		//押された場合
		if (GLFW_PRESS == p_action)
		{
			printf("右クリックが押されました\n");

			//[StateChange]には、クリックされていると「true」を設定
			Device->m_MouseInfo.Right.StateChange = true;

			//[StateKeep]には、クリックするたびに「true」と「false」を交互に切り替える
			Device->m_MouseInfo.Right.StateKeep = !Device->m_MouseInfo.Right.StateKeep;

			//[PushCount]には、クリックするたびに値を加算していく
			Device->m_MouseInfo.Right.PushCount++;

			//押された時の座標を記憶
			Device->m_RightClickPos.x = Pos.x;
			Device->m_RightClickPos.y = Pos.y;
		}
		//離された場合
		else if (GLFW_RELEASE == p_action)
		{
			//[StateChange]には、クリックされていないと「false」を設定
			Device->m_MouseInfo.Right.StateChange = false;

			//保持していた座標を初期化
			memset(&Device->m_MouseInfo.Right.ClickDiffPos, 0, sizeof(m_MouseInfo.Right.ClickDiffPos));
			memset(&Device->m_RightClickPos, 0, sizeof(m_RightClickPos));
		}
	}

	//左クリックに関する処理
	else if (GLFW_MOUSE_BUTTON_LEFT == p_button)
	{
		//押された場合
		if (GLFW_PRESS == p_action)
		{
			printf("左クリックが押されました\n");

			//[StateChange]には、クリックされていると「true」を設定
			Device->m_MouseInfo.Left.StateChange = true;

			//[StateKeep]には、クリックするたびに「true」と「false」を交互に切り替える
			Device->m_MouseInfo.Left.StateKeep = !Device->m_MouseInfo.Left.StateKeep;

			//[PushCount]には、クリックするたびに値を加算していく
			Device->m_MouseInfo.Left.PushCount++;

			//押された時の座標を記憶
			Device->m_LeftClickPos.x = Pos.x;
			Device->m_LeftClickPos.y = Pos.y;
		}
		//離された場合
		else if (GLFW_RELEASE == p_action)
		{
			//[StateChange]には、クリックされていないと「false」を設定
			Device->m_MouseInfo.Left.StateChange = false;

			//保持していた座標を初期化
			memset(&Device->m_MouseInfo.Left.ClickDiffPos, 0, sizeof(m_MouseInfo.Left.ClickDiffPos));
			memset(&Device->m_LeftClickPos, 0, sizeof(m_LeftClickPos));
		}
	}

	//真ん中クリックに関する処理（中身は条件式のみで未実装）
	else if (GLFW_MOUSE_BUTTON_MIDDLE == p_button)
	{
		//押された場合
		if (GLFW_PRESS == p_action)
		{
			printf("真ん中クリックが押されました\n");
		}
		//離された場合
		else if (GLFW_RELEASE == p_action)
		{
			
		}
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスカーソルが動いた時にコールバックされる関数
*	　（ただし特定のマウスボタンが押されている最中のみ有効にしてある
*　　　　ので、タイミングは右記関数参照　DeviceManager::MouseButtonCallback）
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_xpos	：[I/ ]　X 座標
*	　p_xpos	：[I/ ]　Y 座標
*	　詳細は下記URL参照のこと
*	　[http://www.glfw.org/docs/latest/group__input.html]の[GLFWcursorposfun]関数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
{
	// ポインタからウィンドウクラスのインスタンスを取り出す
	WindowManager *Window = static_cast<WindowManager*>(glfwGetWindowUserPointer(p_window));
	shared_ptr<DeviceManager> Device = Window->GetDevice();

	//座標用の変数宣言
	//　コールバック用APIの引数が[double]の為、無駄だが仕方なくこのような橋渡しをしている
	//　（このようにしないと、コンパイラでワーニングが出るので）
	vec2 Pos;
	Pos.x = (GLfloat)p_xpos;
	Pos.y = (GLfloat)p_ypos;

	//座標をコピーして保存
	Device->m_MouseInfo.Position = Pos;

	//右クリックが押されている場合
	if (true == Device->m_MouseInfo.Right.StateChange)
	{
		//クリックされた時からの差分を更新
		Device->m_MouseInfo.Right.ClickDiffPos.x = Pos.x - Device->m_RightClickPos.x;
		Device->m_MouseInfo.Right.ClickDiffPos.y = Pos.y - Device->m_RightClickPos.y;
	}

	//左クリックが押されている場合
	if (true == Device->m_MouseInfo.Left.StateChange)
	{
		//クリックされた時からの差分を更新
		Device->m_MouseInfo.Left.ClickDiffPos.x = Pos.x - Device->m_LeftClickPos.x;
		Device->m_MouseInfo.Left.ClickDiffPos.y = Pos.y - Device->m_LeftClickPos.y;
	}

	/////////////////////////////////////////////
	//	デバッグ用

	//	printf("Right.ClickDiffPos.x = %f, Right.ClickDiffPos.y = %f\n", m_MouseInfo.Right.ClickDiffPos.x, m_MouseInfo.Right.ClickDiffPos.y);
	//	printf("Left.ClickDiffPos.x = %f, Left.ClickDiffPos.y = %f\n", m_MouseInfo.Left.ClickDiffPos.x, m_MouseInfo.Left.ClickDiffPos.y);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスホイールが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_xoffset	：[I/ ]　スクロールのX軸オフセット
*	　p_yoffset	：[I/ ]　スクロールのY軸オフセット
*	　詳細は下記URL参照のこと
*	　[http://www.glfw.org/docs/latest/group__input.html]の[GLFWscrollfun]関数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{
	// ポインタからウィンドウクラスのインスタンスを取り出す
	WindowManager *Window = static_cast<WindowManager*>(glfwGetWindowUserPointer(p_window));
	shared_ptr<DeviceManager> Device = Window->GetDevice();

	//ひとまずスクロール上下しか使わない予定なので「p_yoffset」のみ取得
	Device->m_MouseInfo.ScrollAmount.y += (GLfloat)p_yoffset;

	/////////////////////////////////////////////
	//	デバッグ用

//	printf("p_yoffset = %f\n", m_MouseInfo.ScrollAmount.y);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　キー（キーボード）が変化した時にコールバックされる関数
*	引数
*	　p_window		：[I/ ]　ウィンドウハンドル
*	　p_key			：[I/ ]　キーボードのキー情報（['A']とか['5']とか）
*	　p_scancode	：[I/ ]　よくわからない（システム固有のどうたらこうたら）
*	　p_action		：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
*	　p_mods		：[I/ ]　ShiftやCtrlなどが押されているかの判断（定義名はURL参照）
*	　詳細は下記URL参照のこと
*	　[http://www.glfw.org/docs/latest/group__input.html]の[GLFWkeyfun]関数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	// ポインタからウィンドウクラスのインスタンスを取り出す
	WindowManager *Window = static_cast<WindowManager*>(glfwGetWindowUserPointer(p_window));
	shared_ptr<DeviceManager> Device = Window->GetDevice();

	//キーの情報と格納する変数をまとめて管理する
	KeyInfoSummary KeySummary[] =
	{
		//アルファベット（26個）
		{ "A", GLFW_KEY_A, &Device->m_KeyInfo.StateChange.Key_A, &Device->m_KeyInfo.StateKeep.Key_A, &Device->m_KeyInfo.PushCount.Key_A },
		{ "B", GLFW_KEY_B, &Device->m_KeyInfo.StateChange.Key_B, &Device->m_KeyInfo.StateKeep.Key_B, &Device->m_KeyInfo.PushCount.Key_B },
		{ "C", GLFW_KEY_C, &Device->m_KeyInfo.StateChange.Key_C, &Device->m_KeyInfo.StateKeep.Key_C, &Device->m_KeyInfo.PushCount.Key_C },
		{ "D", GLFW_KEY_D, &Device->m_KeyInfo.StateChange.Key_D, &Device->m_KeyInfo.StateKeep.Key_D, &Device->m_KeyInfo.PushCount.Key_D },
		{ "E", GLFW_KEY_E, &Device->m_KeyInfo.StateChange.Key_E, &Device->m_KeyInfo.StateKeep.Key_E, &Device->m_KeyInfo.PushCount.Key_E },
		{ "F", GLFW_KEY_F, &Device->m_KeyInfo.StateChange.Key_F, &Device->m_KeyInfo.StateKeep.Key_F, &Device->m_KeyInfo.PushCount.Key_F },
		{ "G", GLFW_KEY_G, &Device->m_KeyInfo.StateChange.Key_G, &Device->m_KeyInfo.StateKeep.Key_G, &Device->m_KeyInfo.PushCount.Key_G },
		{ "H", GLFW_KEY_H, &Device->m_KeyInfo.StateChange.Key_H, &Device->m_KeyInfo.StateKeep.Key_H, &Device->m_KeyInfo.PushCount.Key_H },
		{ "I", GLFW_KEY_I, &Device->m_KeyInfo.StateChange.Key_I, &Device->m_KeyInfo.StateKeep.Key_I, &Device->m_KeyInfo.PushCount.Key_I },
		{ "J", GLFW_KEY_J, &Device->m_KeyInfo.StateChange.Key_J, &Device->m_KeyInfo.StateKeep.Key_J, &Device->m_KeyInfo.PushCount.Key_J },
		{ "K", GLFW_KEY_K, &Device->m_KeyInfo.StateChange.Key_K, &Device->m_KeyInfo.StateKeep.Key_K, &Device->m_KeyInfo.PushCount.Key_K },
		{ "L", GLFW_KEY_L, &Device->m_KeyInfo.StateChange.Key_L, &Device->m_KeyInfo.StateKeep.Key_L, &Device->m_KeyInfo.PushCount.Key_L },
		{ "M", GLFW_KEY_M, &Device->m_KeyInfo.StateChange.Key_M, &Device->m_KeyInfo.StateKeep.Key_M, &Device->m_KeyInfo.PushCount.Key_M },
		{ "N", GLFW_KEY_N, &Device->m_KeyInfo.StateChange.Key_N, &Device->m_KeyInfo.StateKeep.Key_N, &Device->m_KeyInfo.PushCount.Key_N },
		{ "O", GLFW_KEY_O, &Device->m_KeyInfo.StateChange.Key_O, &Device->m_KeyInfo.StateKeep.Key_O, &Device->m_KeyInfo.PushCount.Key_O },
		{ "P", GLFW_KEY_P, &Device->m_KeyInfo.StateChange.Key_P, &Device->m_KeyInfo.StateKeep.Key_P, &Device->m_KeyInfo.PushCount.Key_P },
		{ "Q", GLFW_KEY_Q, &Device->m_KeyInfo.StateChange.Key_Q, &Device->m_KeyInfo.StateKeep.Key_Q, &Device->m_KeyInfo.PushCount.Key_Q },
		{ "R", GLFW_KEY_R, &Device->m_KeyInfo.StateChange.Key_R, &Device->m_KeyInfo.StateKeep.Key_R, &Device->m_KeyInfo.PushCount.Key_R },
		{ "S", GLFW_KEY_S, &Device->m_KeyInfo.StateChange.Key_S, &Device->m_KeyInfo.StateKeep.Key_S, &Device->m_KeyInfo.PushCount.Key_S },
		{ "T", GLFW_KEY_T, &Device->m_KeyInfo.StateChange.Key_T, &Device->m_KeyInfo.StateKeep.Key_T, &Device->m_KeyInfo.PushCount.Key_T },
		{ "U", GLFW_KEY_U, &Device->m_KeyInfo.StateChange.Key_U, &Device->m_KeyInfo.StateKeep.Key_U, &Device->m_KeyInfo.PushCount.Key_U },
		{ "V", GLFW_KEY_V, &Device->m_KeyInfo.StateChange.Key_V, &Device->m_KeyInfo.StateKeep.Key_V, &Device->m_KeyInfo.PushCount.Key_V },
		{ "W", GLFW_KEY_W, &Device->m_KeyInfo.StateChange.Key_W, &Device->m_KeyInfo.StateKeep.Key_W, &Device->m_KeyInfo.PushCount.Key_W },
		{ "X", GLFW_KEY_X, &Device->m_KeyInfo.StateChange.Key_X, &Device->m_KeyInfo.StateKeep.Key_X, &Device->m_KeyInfo.PushCount.Key_X },
		{ "Y", GLFW_KEY_Y, &Device->m_KeyInfo.StateChange.Key_Y, &Device->m_KeyInfo.StateKeep.Key_Y, &Device->m_KeyInfo.PushCount.Key_Y },
		{ "Z", GLFW_KEY_Z, &Device->m_KeyInfo.StateChange.Key_Z, &Device->m_KeyInfo.StateKeep.Key_Z, &Device->m_KeyInfo.PushCount.Key_Z },

		//数字、テンキー数字（20個）
		{ "0", GLFW_KEY_0,    &Device->m_KeyInfo.StateChange.Key_0, &Device->m_KeyInfo.StateKeep.Key_0, &Device->m_KeyInfo.PushCount.Key_0 },
		{ "0", GLFW_KEY_KP_0, &Device->m_KeyInfo.StateChange.Key_0, &Device->m_KeyInfo.StateKeep.Key_0, &Device->m_KeyInfo.PushCount.Key_0 },
		{ "1", GLFW_KEY_1,    &Device->m_KeyInfo.StateChange.Key_1, &Device->m_KeyInfo.StateKeep.Key_1, &Device->m_KeyInfo.PushCount.Key_1 },
		{ "1", GLFW_KEY_KP_1, &Device->m_KeyInfo.StateChange.Key_1, &Device->m_KeyInfo.StateKeep.Key_1, &Device->m_KeyInfo.PushCount.Key_1 },
		{ "2", GLFW_KEY_2,    &Device->m_KeyInfo.StateChange.Key_2, &Device->m_KeyInfo.StateKeep.Key_2, &Device->m_KeyInfo.PushCount.Key_2 },
		{ "2", GLFW_KEY_KP_2, &Device->m_KeyInfo.StateChange.Key_2, &Device->m_KeyInfo.StateKeep.Key_2, &Device->m_KeyInfo.PushCount.Key_2 },
		{ "3", GLFW_KEY_3,    &Device->m_KeyInfo.StateChange.Key_3, &Device->m_KeyInfo.StateKeep.Key_3, &Device->m_KeyInfo.PushCount.Key_3 },
		{ "3", GLFW_KEY_KP_3, &Device->m_KeyInfo.StateChange.Key_3, &Device->m_KeyInfo.StateKeep.Key_3, &Device->m_KeyInfo.PushCount.Key_3 },
		{ "4", GLFW_KEY_4,    &Device->m_KeyInfo.StateChange.Key_4, &Device->m_KeyInfo.StateKeep.Key_4, &Device->m_KeyInfo.PushCount.Key_4 },
		{ "4", GLFW_KEY_KP_4, &Device->m_KeyInfo.StateChange.Key_4, &Device->m_KeyInfo.StateKeep.Key_4, &Device->m_KeyInfo.PushCount.Key_4 },
		{ "5", GLFW_KEY_5,    &Device->m_KeyInfo.StateChange.Key_5, &Device->m_KeyInfo.StateKeep.Key_5, &Device->m_KeyInfo.PushCount.Key_5 },
		{ "5", GLFW_KEY_KP_5, &Device->m_KeyInfo.StateChange.Key_5, &Device->m_KeyInfo.StateKeep.Key_5, &Device->m_KeyInfo.PushCount.Key_5 },
		{ "6", GLFW_KEY_6,    &Device->m_KeyInfo.StateChange.Key_6, &Device->m_KeyInfo.StateKeep.Key_6, &Device->m_KeyInfo.PushCount.Key_6 },
		{ "6", GLFW_KEY_KP_6, &Device->m_KeyInfo.StateChange.Key_6, &Device->m_KeyInfo.StateKeep.Key_6, &Device->m_KeyInfo.PushCount.Key_6 },
		{ "7", GLFW_KEY_7,    &Device->m_KeyInfo.StateChange.Key_7, &Device->m_KeyInfo.StateKeep.Key_7, &Device->m_KeyInfo.PushCount.Key_7 },
		{ "7", GLFW_KEY_KP_7, &Device->m_KeyInfo.StateChange.Key_7, &Device->m_KeyInfo.StateKeep.Key_7, &Device->m_KeyInfo.PushCount.Key_7 },
		{ "8", GLFW_KEY_8,    &Device->m_KeyInfo.StateChange.Key_8, &Device->m_KeyInfo.StateKeep.Key_8, &Device->m_KeyInfo.PushCount.Key_8 },
		{ "8", GLFW_KEY_KP_8, &Device->m_KeyInfo.StateChange.Key_8, &Device->m_KeyInfo.StateKeep.Key_8, &Device->m_KeyInfo.PushCount.Key_8 },
		{ "9", GLFW_KEY_9,    &Device->m_KeyInfo.StateChange.Key_9, &Device->m_KeyInfo.StateKeep.Key_9, &Device->m_KeyInfo.PushCount.Key_9 },
		{ "9", GLFW_KEY_KP_9, &Device->m_KeyInfo.StateChange.Key_9, &Device->m_KeyInfo.StateKeep.Key_9, &Device->m_KeyInfo.PushCount.Key_9 },

		//記号など(16個）
		{ "/",		GLFW_KEY_KP_DIVIDE,		&Device->m_KeyInfo.StateChange.Key_DIVIDE,   &Device->m_KeyInfo.StateKeep.Key_DIVIDE,   &Device->m_KeyInfo.PushCount.Key_DIVIDE   },
		{ "*",		GLFW_KEY_KP_MULTIPLY,	&Device->m_KeyInfo.StateChange.Key_MULTIPLY, &Device->m_KeyInfo.StateKeep.Key_MULTIPLY, &Device->m_KeyInfo.PushCount.Key_MULTIPLY },
		{ "-",		GLFW_KEY_KP_SUBTRACT,	&Device->m_KeyInfo.StateChange.Key_SUBTRACT, &Device->m_KeyInfo.StateKeep.Key_SUBTRACT, &Device->m_KeyInfo.PushCount.Key_SUBTRACT },
		{ "+",		GLFW_KEY_KP_ADD,		&Device->m_KeyInfo.StateChange.Key_ADD,      &Device->m_KeyInfo.StateKeep.Key_ADD,      &Device->m_KeyInfo.PushCount.Key_ADD      },
		{ "Shift",	GLFW_KEY_LEFT_SHIFT,	&Device->m_KeyInfo.StateChange.Key_SHIFT,    &Device->m_KeyInfo.StateKeep.Key_SHIFT,    &Device->m_KeyInfo.PushCount.Key_SHIFT    },
		{ "Shift",	GLFW_KEY_RIGHT_SHIFT,	&Device->m_KeyInfo.StateChange.Key_SHIFT,    &Device->m_KeyInfo.StateKeep.Key_SHIFT,    &Device->m_KeyInfo.PushCount.Key_SHIFT    },
		{ "Ctrl",	GLFW_KEY_LEFT_CONTROL,	&Device->m_KeyInfo.StateChange.Key_CONTROL,  &Device->m_KeyInfo.StateKeep.Key_CONTROL,  &Device->m_KeyInfo.PushCount.Key_CONTROL  },
		{ "Ctrl",	GLFW_KEY_RIGHT_CONTROL,	&Device->m_KeyInfo.StateChange.Key_CONTROL,  &Device->m_KeyInfo.StateKeep.Key_CONTROL,  &Device->m_KeyInfo.PushCount.Key_CONTROL  },
		{ "Alt",	GLFW_KEY_LEFT_ALT,		&Device->m_KeyInfo.StateChange.Key_ALT,      &Device->m_KeyInfo.StateKeep.Key_ALT,      &Device->m_KeyInfo.PushCount.Key_ALT      },
		{ "Alt",	GLFW_KEY_RIGHT_ALT,		&Device->m_KeyInfo.StateChange.Key_ALT,      &Device->m_KeyInfo.StateKeep.Key_ALT,      &Device->m_KeyInfo.PushCount.Key_ALT      },
		{ " ",		GLFW_KEY_SPACE,			&Device->m_KeyInfo.StateChange.Key_SPACE,    &Device->m_KeyInfo.StateKeep.Key_SPACE,    &Device->m_KeyInfo.PushCount.Key_SPACE    },
		{ "→",		GLFW_KEY_RIGHT,			&Device->m_KeyInfo.StateChange.Key_RIGHT,    &Device->m_KeyInfo.StateKeep.Key_RIGHT,    &Device->m_KeyInfo.PushCount.Key_RIGHT    },
		{ "←",		GLFW_KEY_LEFT,			&Device->m_KeyInfo.StateChange.Key_LEFT,     &Device->m_KeyInfo.StateKeep.Key_LEFT,     &Device->m_KeyInfo.PushCount.Key_LEFT     },
		{ "↓",		GLFW_KEY_DOWN,			&Device->m_KeyInfo.StateChange.Key_DOWN,     &Device->m_KeyInfo.StateKeep.Key_DOWN,     &Device->m_KeyInfo.PushCount.Key_DOWN     },
		{ "↑",		GLFW_KEY_UP,			&Device->m_KeyInfo.StateChange.Key_UP,       &Device->m_KeyInfo.StateKeep.Key_UP,       &Device->m_KeyInfo.PushCount.Key_UP       },
	};
	
	//押された or 離されば場合のみ情報更新（押し続けの時はスルーする）
	if (GLFW_PRESS == p_action || GLFW_RELEASE == p_action)
	{
		//各キー（キーボード）の情報分ループする
		for (int index = 0; (sizeof(KeySummary) / sizeof(KeySummary[0])) > index; index++)
		{
			//該当するキーがあれば
			if (KeySummary[index].KeyDefine == p_key)
			{
				//押された場合
				if (GLFW_PRESS == p_action)
				{
					//スペースキーは少しわかりづらいので補助文字を入れて表示する
					if (' ' == *KeySummary[index].KeyChar)
					{
						printf("[ (スペース)]キーが押されました\n");
					}
					else
					{
						printf("[%s]キーが押されました\n", KeySummary[index].KeyChar);
					}

					//[StateChange]には、押されていると「true」を設定
					*KeySummary[index].StateChange = true;

					//[StateKeep]には、押すたびに「true」と「false」を交互に切り替える
					*KeySummary[index].StateKeep = !*KeySummary[index].StateKeep;

					//[PushCount]には、押すたびに値を加算していく
					*(KeySummary[index].PushCount)++;

					//[LastKey]には、アルファベット・数字が押された場合のみその文字を設定する
					//（[46]は[KeySummary]に定義したアルファベットと数字までのテーブルを指す）
					if(46 > index)	
					{
						Device->m_KeyInfo.LastKey = *KeySummary[index].KeyChar;
					}
				}
				else if (GLFW_RELEASE == p_action)
				{
					//[StateChange]には、押されていないと「false」を設定
					*KeySummary[index].StateChange = false;

					//[LastKey]には、キーが離されたときに初期値を設定する
					Device->m_KeyInfo.LastKey = 0;
				}
				break;
			}
		}
	}
}
