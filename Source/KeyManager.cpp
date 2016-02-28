#include "KeyManager.h"

/////////////////////////////////////////////
//static変数の実体を定義

MouseInfo KeyManager::m_MouseInfo;			//マウスボタンの情報
CursorPos KeyManager::m_OldCursorPos;			//直前（1イベント前）のカーソル座標		

//コンストラクタ
KeyManager::KeyManager()
{
	m_window = NULL;

	memset(&m_MouseInfo.Right, 0, sizeof(m_MouseInfo.Right));
	m_MouseInfo.Right.State = GLFW_RELEASE;

	memset(&m_MouseInfo.Left, 0, sizeof(m_MouseInfo.Right));
	m_MouseInfo.Right.State = GLFW_RELEASE;
}

//デストラクタ
KeyManager::~KeyManager()
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
void KeyManager::Initialize(GLFWwindow* const p_window)
{
	//ウィンドウ情報を保存
	m_window = p_window;

	//マウスボタンが変化した時用のコールバックを登録
	glfwSetMouseButtonCallback(m_window, KeyManager::MouseButtonCallback);

	//マウスホイールが変化した時用のコールバックを登録
	glfwSetScrollCallback(m_window, KeyManager::ScrollCallback);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスボタンが変化した時にコールバックされる関数
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_button	：[I/ ]　どのボタンが変化したか
*	　p_button	：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
*	　p_button	：[I/ ]　よくわからない
*	　詳細は下記URL参照のこと
*	　http://www.glfw.org/docs/latest/group__input.html#ga1e008c7a8751cea648c8f42cc91104cf
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void KeyManager::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
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
				glfwSetCursorPosCallback(p_window, KeyManager::CursorPosCallback);
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
				glfwSetCursorPosCallback(p_window, KeyManager::CursorPosCallback);
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
void KeyManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{

	//ひとまずスクロール上下しか使わない予定なので「p_yoffset」のみ取得
	m_MouseInfo.Scroll = (float)p_yoffset;

	/////////////////////////////////////////////
	//	デバッグ用

//	printf("p_xoffset = %f, p_yoffset = %f\n", p_xoffset, p_yoffset);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　マウスカーソルが動いた時にコールバックされる関数
*	　（ただし特定のマウスボタンが押されている最中のみ有効にしてある
*　　　　ので、タイミングは右記関数参照　KeyManager::MouseButtonCallback）
*	引数
*	　p_window	：[I/ ]　ウィンドウハンドル
*	　p_xpos	：[I/ ]　X 座標
*	　p_xpos	：[I/ ]　Y 座標
*	　詳細は下記URL参照のこと
*	　http://www.glfw.org/docs/latest/group__input.html#ga592fbfef76d88f027cb1bc4c36ebd437
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void KeyManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
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