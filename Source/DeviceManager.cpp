#include "DeviceManager.h"

/////////////////////////////////////////////
//static変数の実体を定義

MouseInfo DeviceManager::m_MouseInfo;			//マウスボタンの情報
CursorPos DeviceManager::m_OldCursorPos;		//直前（1イベント前）のカーソル座標		
KeyInfo DeviceManager::m_KeyInfo;				//キー（キーボード）の情報

//コンストラクタ
DeviceManager::DeviceManager()
{
	m_window = NULL;

	memset(&m_MouseInfo, 0, sizeof(m_MouseInfo));
	m_MouseInfo.Right.State = GLFW_RELEASE;
	m_MouseInfo.Left.State = GLFW_RELEASE;

	memset(&m_OldCursorPos, 0, sizeof(m_OldCursorPos));
	memset(&m_KeyInfo.Change, GLFW_RELEASE, sizeof(m_KeyInfo.Change));
	memset(&m_KeyInfo.Keep, false, sizeof(m_KeyInfo.Keep));
}

//デストラクタ
DeviceManager::~DeviceManager()
{

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　Key管理マネージャーを初期化する
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::Initialize(GLFWwindow* const p_window)
{
	//ウィンドウ情報を保存
	m_window = p_window;

	//マウスボタンが変化した時用のコールバックを登録
	glfwSetMouseButtonCallback(m_window, DeviceManager::MouseButtonCallback);

	//マウスホイールが変化した時用のコールバックを登録
	glfwSetScrollCallback(m_window, DeviceManager::ScrollCallback);

	//キー（キーボード）が変化した時用のコールバック
	glfwSetKeyCallback(m_window, DeviceManager::KeyCallback);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスボタンが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_button	：[I/ ]　どのボタンが変化したか
*	　p_action	：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
*	　p_mods	：[I/ ]　よくわからない
*	　詳細は下記URL参照のこと
*	　http://www.glfw.org/docs/latest/group__input.html#ga1e008c7a8751cea648c8f42cc91104cf
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	//座標を取得用の一時変数
	double PosX = 0.0;
	double PosY = 0.0;

	//カーソルの座標を取得します（ウィンドウ系の座標が入ります）
	glfwGetCursorPos(p_window, &PosX, &PosY);

	//座標管理用の変数宣言
	//　座標取得APIの引数が[double]の為、無駄だが仕方なくこのような橋渡しをしている
	//　（このようにしないと、コンパイラでワーニングが出るので）
	CursorPos Pos;
	Pos.x = (float)PosX;
	Pos.y = (float)PosY;

	//カーソルの座標を保存
	m_OldCursorPos.x = Pos.x;
	m_OldCursorPos.y = Pos.y;

	//右クリックに関する処理
	if (GLFW_MOUSE_BUTTON_RIGHT == p_button)
	{
		//押された場合
		if (GLFW_PRESS == p_action)
		{
			printf("右クリックが押されました\n");

			//他のボタンがクリックされていない時に処理する
			if (GLFW_PRESS != m_MouseInfo.Left.State)
			{
				//マウスが動いた時にコールバックされるようにする
				glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);
			}

			//押されたことを記憶
			m_MouseInfo.Right.State = GLFW_PRESS;

			//押された時の座標を記憶
			m_MouseInfo.Right.Pos.x = Pos.x;
			m_MouseInfo.Right.Pos.y = Pos.y;
			m_MouseInfo.Right.ClickPos.x = Pos.x;
			m_MouseInfo.Right.ClickPos.y = Pos.y;
		}
		//離された場合
		else if (GLFW_RELEASE == p_action)
		{
			//他のボタンがクリックされていない時に処理する
			if (GLFW_PRESS != m_MouseInfo.Left.State)
			{
				//マウスが動いた時にコールバックされないようにする
				glfwSetCursorPosCallback(p_window, NULL);
			}

			//離されたことを記憶
			m_MouseInfo.Right.State = GLFW_RELEASE;

			//保持していた座標を初期化
			m_MouseInfo.Right.DiffPos.x = 0;
			m_MouseInfo.Right.DiffPos.y = 0;
			m_MouseInfo.Right.ClickDiffPos.x = 0;
			m_MouseInfo.Right.ClickDiffPos.y = 0;
		}
	}

	//左クリックに関する処理
	else if (GLFW_MOUSE_BUTTON_LEFT == p_button)
	{
		//押された場合
		if (GLFW_PRESS == p_action)
		{
			printf("左クリックが押されました\n");

			//他のボタンがクリックされていない時に処理する
			if (GLFW_PRESS != m_MouseInfo.Right.State)
			{
				//マウスが動いた時にコールバックされるようにする
				glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);
			}

			//押されたことを記憶
			m_MouseInfo.Left.State = GLFW_PRESS;

			//押された時の座標を記憶NULL
			m_MouseInfo.Left.Pos.x = Pos.x;
			m_MouseInfo.Left.Pos.y = Pos.y;
			m_MouseInfo.Left.ClickPos.x = Pos.x;
			m_MouseInfo.Left.ClickPos.y = Pos.y;
		}
		//離された場合
		else if (GLFW_RELEASE == p_action)
		{
			//他のボタンがクリックされていない時に処理する
			if (GLFW_PRESS != m_MouseInfo.Right.State)
			{
				//マウスが動いた時にコールバックされないようにする
				glfwSetCursorPosCallback(p_window, NULL);
			}

			//離されたことを記憶
			m_MouseInfo.Left.State = GLFW_RELEASE;

			//保持していた座標を初期化
			m_MouseInfo.Left.DiffPos.x = 0;
			m_MouseInfo.Left.DiffPos.y = 0;
			m_MouseInfo.Left.ClickDiffPos.x = 0;
			m_MouseInfo.Left.ClickDiffPos.y = 0;
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
*	　http://www.glfw.org/docs/latest/group__input.html#ga592fbfef76d88f027cb1bc4c36ebd437
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
{

	//座標用の変数宣言
	//　コールバック用APIの引数が[double]の為、無駄だが仕方なくこのような橋渡しをしている
	//　（このようにしないと、コンパイラでワーニングが出るので）
	CursorPos Pos;
	Pos.x = (float)p_xpos;
	Pos.y = (float)p_ypos;

	//右クリックが押されている場合
	if (GLFW_PRESS == m_MouseInfo.Right.State)
	{
		//現在の座標を更新
		m_MouseInfo.Right.Pos.x = Pos.x;
		m_MouseInfo.Right.Pos.y = Pos.y;

		//直前のカーソル位置からの差分を更新
		m_MouseInfo.Right.DiffPos.x = Pos.x - m_OldCursorPos.x;
		m_MouseInfo.Right.DiffPos.y = Pos.y - m_OldCursorPos.y;

		//クリックされた時からの差分を更新
		m_MouseInfo.Right.ClickDiffPos.x = Pos.x - m_MouseInfo.Right.ClickPos.x;
		m_MouseInfo.Right.ClickDiffPos.y = Pos.y - m_MouseInfo.Right.ClickPos.y;
	}

	//左クリックが押されている場合
	if (GLFW_PRESS == m_MouseInfo.Left.State)
	{
		//現在の座標を更新
		m_MouseInfo.Left.Pos.x = Pos.x;
		m_MouseInfo.Left.Pos.y = Pos.y;

		//直前のカーソル位置からの差分を更新
		m_MouseInfo.Left.DiffPos.x = Pos.x - m_OldCursorPos.x;
		m_MouseInfo.Left.DiffPos.y = Pos.y - m_OldCursorPos.y;

		//クリックされた時からの差分を更新
		m_MouseInfo.Left.ClickDiffPos.x = Pos.x - m_MouseInfo.Left.ClickPos.x;
		m_MouseInfo.Left.ClickDiffPos.y = Pos.y - m_MouseInfo.Left.ClickPos.y;
	}

	//カーソルの座標を保存
	m_OldCursorPos.x = Pos.x;
	m_OldCursorPos.y = Pos.y;

	/////////////////////////////////////////////
	//	デバッグ用

	//	printf("Right.ClickDiffPos.x = %f, Right.ClickDiffPos.y = %f\n", m_MouseInfo.Right.ClickDiffPos.x, m_MouseInfo.Right.ClickDiffPos.y);
	//	printf("Left.ClickDiffPos.x = %f, Left.ClickDiffPos.y = %f\n", m_MouseInfo.Left.ClickDiffPos.x, m_MouseInfo.Left.ClickDiffPos.y);

	//	printf("Right.DiffPos.x = %f, Right.DiffPos.y = %f\n", m_MouseInfo.Right.DiffPos.x, m_MouseInfo.Right.DiffPos.y);
	//	printf("Left.DiffPos.x = %f, Left.DiffPos.y = %f\n", m_MouseInfo.Left.DiffPos.x, m_MouseInfo.Left.DiffPos.y);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスホイールが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_xoffset	：[I/ ]　スクロールのX軸オフセット
*	　p_yoffset	：[I/ ]　スクロールのY軸オフセット
*	　詳細は下記URL参照のこと
*	　http://www.glfw.org/docs/latest/group__input.html#ga6228cdf94d28fbd3a9a1fbb0e5922a8a
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{

	//ひとまずスクロール上下しか使わない予定なので「p_yoffset」のみ取得
	m_MouseInfo.Scroll = (float)p_yoffset;

	/////////////////////////////////////////////
	//	デバッグ用

//	printf("p_xoffset = %f, p_yoffset = %f\n", p_xoffset, p_yoffset);
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
*	　http://www.glfw.org/docs/latest/group__input.html#ga6228cdf94d28fbd3a9a1fbb0e5922a8a
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void DeviceManager::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{

	//キーの情報と格納する変数をまとめて管理する
	KeyInfoSummary KeySummary[KEY_SUMMARY_MAX] =
	{
		//アルファベット（26個）
		{ "A", GLFW_KEY_A , &m_KeyInfo.Change.Key_A, &m_KeyInfo.Keep.Key_A },
		{ "B", GLFW_KEY_B, &m_KeyInfo.Change.Key_B, &m_KeyInfo.Keep.Key_B },
		{ "C", GLFW_KEY_C , &m_KeyInfo.Change.Key_C, &m_KeyInfo.Keep.Key_C },
		{ "D", GLFW_KEY_D, &m_KeyInfo.Change.Key_D, &m_KeyInfo.Keep.Key_D },
		{ "E", GLFW_KEY_E , &m_KeyInfo.Change.Key_E, &m_KeyInfo.Keep.Key_E },
		{ "F", GLFW_KEY_F, &m_KeyInfo.Change.Key_F, &m_KeyInfo.Keep.Key_F },
		{ "G", GLFW_KEY_G , &m_KeyInfo.Change.Key_G, &m_KeyInfo.Keep.Key_G },
		{ "H", GLFW_KEY_H, &m_KeyInfo.Change.Key_H, &m_KeyInfo.Keep.Key_H },
		{ "I", GLFW_KEY_I , &m_KeyInfo.Change.Key_I, &m_KeyInfo.Keep.Key_I },
		{ "J", GLFW_KEY_J, &m_KeyInfo.Change.Key_J, &m_KeyInfo.Keep.Key_J },
		{ "K", GLFW_KEY_K , &m_KeyInfo.Change.Key_K, &m_KeyInfo.Keep.Key_K },
		{ "L", GLFW_KEY_L, &m_KeyInfo.Change.Key_L, &m_KeyInfo.Keep.Key_L },
		{ "M", GLFW_KEY_M , &m_KeyInfo.Change.Key_M, &m_KeyInfo.Keep.Key_M },
		{ "N", GLFW_KEY_N, &m_KeyInfo.Change.Key_N, &m_KeyInfo.Keep.Key_N },
		{ "O", GLFW_KEY_O , &m_KeyInfo.Change.Key_O, &m_KeyInfo.Keep.Key_O },
		{ "P", GLFW_KEY_P, &m_KeyInfo.Change.Key_P, &m_KeyInfo.Keep.Key_P },
		{ "Q", GLFW_KEY_Q , &m_KeyInfo.Change.Key_Q, &m_KeyInfo.Keep.Key_Q },
		{ "R", GLFW_KEY_R, &m_KeyInfo.Change.Key_R, &m_KeyInfo.Keep.Key_R },
		{ "S", GLFW_KEY_S , &m_KeyInfo.Change.Key_S, &m_KeyInfo.Keep.Key_S },
		{ "T", GLFW_KEY_T, &m_KeyInfo.Change.Key_T, &m_KeyInfo.Keep.Key_T },
		{ "U", GLFW_KEY_U , &m_KeyInfo.Change.Key_U, &m_KeyInfo.Keep.Key_U },
		{ "V", GLFW_KEY_V, &m_KeyInfo.Change.Key_V, &m_KeyInfo.Keep.Key_V },
		{ "W", GLFW_KEY_W , &m_KeyInfo.Change.Key_W, &m_KeyInfo.Keep.Key_W },
		{ "X", GLFW_KEY_X, &m_KeyInfo.Change.Key_X, &m_KeyInfo.Keep.Key_X },
		{ "Y", GLFW_KEY_Y , &m_KeyInfo.Change.Key_Y, &m_KeyInfo.Keep.Key_Y },
		{ "Z", GLFW_KEY_Z, &m_KeyInfo.Change.Key_Z, &m_KeyInfo.Keep.Key_Z },

		//数字、テンキー数字（20個）
		{ "0", GLFW_KEY_0, &m_KeyInfo.Change.Key_0, &m_KeyInfo.Keep.Key_0 },
		{ "0", GLFW_KEY_KP_0, &m_KeyInfo.Change.Key_0, &m_KeyInfo.Keep.Key_0 },
		{ "1", GLFW_KEY_1, &m_KeyInfo.Change.Key_1, &m_KeyInfo.Keep.Key_1 },
		{ "1", GLFW_KEY_KP_1, &m_KeyInfo.Change.Key_1, &m_KeyInfo.Keep.Key_1 },
		{ "2", GLFW_KEY_2, &m_KeyInfo.Change.Key_2, &m_KeyInfo.Keep.Key_2 },
		{ "2", GLFW_KEY_KP_2, &m_KeyInfo.Change.Key_2, &m_KeyInfo.Keep.Key_2 },
		{ "3", GLFW_KEY_3, &m_KeyInfo.Change.Key_3, &m_KeyInfo.Keep.Key_3 },
		{ "3", GLFW_KEY_KP_3, &m_KeyInfo.Change.Key_3, &m_KeyInfo.Keep.Key_3 },
		{ "4", GLFW_KEY_4, &m_KeyInfo.Change.Key_4, &m_KeyInfo.Keep.Key_4 },
		{ "4", GLFW_KEY_KP_4, &m_KeyInfo.Change.Key_4, &m_KeyInfo.Keep.Key_4 },
		{ "5", GLFW_KEY_5, &m_KeyInfo.Change.Key_5, &m_KeyInfo.Keep.Key_5 },
		{ "5", GLFW_KEY_KP_5, &m_KeyInfo.Change.Key_5, &m_KeyInfo.Keep.Key_5 },
		{ "6", GLFW_KEY_6, &m_KeyInfo.Change.Key_6, &m_KeyInfo.Keep.Key_6 },
		{ "6", GLFW_KEY_KP_6, &m_KeyInfo.Change.Key_6, &m_KeyInfo.Keep.Key_6 },
		{ "7", GLFW_KEY_7, &m_KeyInfo.Change.Key_7, &m_KeyInfo.Keep.Key_7 },
		{ "7", GLFW_KEY_KP_7, &m_KeyInfo.Change.Key_7, &m_KeyInfo.Keep.Key_7 },
		{ "8", GLFW_KEY_8, &m_KeyInfo.Change.Key_8, &m_KeyInfo.Keep.Key_8 },
		{ "8", GLFW_KEY_KP_8, &m_KeyInfo.Change.Key_8, &m_KeyInfo.Keep.Key_8 },
		{ "9", GLFW_KEY_9, &m_KeyInfo.Change.Key_9, &m_KeyInfo.Keep.Key_9 },
		{ "9", GLFW_KEY_KP_9, &m_KeyInfo.Change.Key_9, &m_KeyInfo.Keep.Key_9 },

		//記号など(16個）
		{ "/", GLFW_KEY_KP_DIVIDE , &m_KeyInfo.Change.Key_DIVIDE, &m_KeyInfo.Keep.Key_DIVIDE },
		{ "*", GLFW_KEY_KP_MULTIPLY, &m_KeyInfo.Change.Key_MULTIPLY, &m_KeyInfo.Keep.Key_MULTIPLY },
		{ "-", GLFW_KEY_KP_SUBTRACT , &m_KeyInfo.Change.Key_SUBTRACT, &m_KeyInfo.Keep.Key_SUBTRACT },
		{ "+", GLFW_KEY_KP_ADD, &m_KeyInfo.Change.Key_ADD, &m_KeyInfo.Keep.Key_ADD },
		{ "Shift", GLFW_KEY_LEFT_SHIFT , &m_KeyInfo.Change.Key_SHIFT, &m_KeyInfo.Keep.Key_SHIFT },
		{ "Shift", GLFW_KEY_RIGHT_SHIFT, &m_KeyInfo.Change.Key_SHIFT, &m_KeyInfo.Keep.Key_SHIFT },
		{ "Ctrl", GLFW_KEY_LEFT_CONTROL, &m_KeyInfo.Change.Key_CONTROL, &m_KeyInfo.Keep.Key_CONTROL },
		{ "Ctrl", GLFW_KEY_RIGHT_CONTROL, &m_KeyInfo.Change.Key_CONTROL, &m_KeyInfo.Keep.Key_CONTROL },
		{ "Alt", GLFW_KEY_LEFT_ALT, &m_KeyInfo.Change.Key_ALT, &m_KeyInfo.Keep.Key_ALT },
		{ "Alt", GLFW_KEY_RIGHT_ALT, &m_KeyInfo.Change.Key_ALT, &m_KeyInfo.Keep.Key_ALT },
		{ " (スペース)", GLFW_KEY_SPACE , &m_KeyInfo.Change.Key_SPACE, &m_KeyInfo.Keep.Key_SPACE },
		{ "→", GLFW_KEY_RIGHT, &m_KeyInfo.Change.Key_RIGHT, &m_KeyInfo.Keep.Key_RIGHT },
		{ "←", GLFW_KEY_LEFT, &m_KeyInfo.Change.Key_LEFT, &m_KeyInfo.Keep.Key_LEFT },
		{ "↓", GLFW_KEY_DOWN , &m_KeyInfo.Change.Key_DOWN, &m_KeyInfo.Keep.Key_DOWN },
		{ "↑", GLFW_KEY_UP, &m_KeyInfo.Change.Key_UP, &m_KeyInfo.Keep.Key_UP },
	};
	
	//押された or 離されば場合のみ情報更新（押し続けの時はスルーする）
	if (GLFW_PRESS == p_action || GLFW_RELEASE == p_action)
	{
		//各キー（キーボード）の情報分ループする
		for (int index = 0; KEY_SUMMARY_MAX > index; index++)
		{
			//該当するキーがあれば
			if (KeySummary[index].KeyDef == p_key)
			{
				//Changeには 押された「GLFW_PRESS」 or 離された「GLFW_RELEASE」 をそのまま格納
				*KeySummary[index].Change = p_action;

				//押された場合
				if (GLFW_PRESS == p_action)
				{
					//Keepには 押すたびに「true」と「false」を交互に切り替える
					*KeySummary[index].Keep = !*KeySummary[index].Keep;

					printf("[%s]キーが押されました\n", KeySummary[index].KeyChar);
				}
				break;
			}
		}
	}
}
