#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

//include定義
#include "Common.h"

//Define定義


/////////////////////////////////////////////
//	マウス関連の構造体定義

//マウスの詳細情報
typedef struct
{
	int State;				//マウスのクリック状態（押されている（GLFW_PRESS） or 離されている（GLFW_RELEASE））
	Vec2 ClickDiffPos;		//マウスがクリックされた座標からの差分座標（クリックされていない時は [0] ）
							//　例：[x:50][y:50]でクリックして、ドラッグ状態で[x:40][y:60]に移動させた場合、
							//　　　格納される値は[x:-10][y:10]となる
}MouseDetail;

//マウスの情報
typedef struct
{
	MouseDetail Right;			//マウスの右クリックの情報
	MouseDetail Left;			//マウスの左クリックの情報
//	MouseDetail Middle;			//マウスの中央クリックの情報
	Vec2 Position;				//マウスのカーソル座標
	Vec2 ScrollAmount;			//スクロールの合計量、初期状態は[x:0（横[左右]スクロール）][y:0（縦[上下]スクロール）]で、
								//　スクロールした分だけ値が蓄積（加算/減算）されていく
}MouseInfo;

/////////////////////////////////////////////
//	キー（キーボード）関連の構造体定義

//各キー（キーボード）の情報
//各変数に保存される値やその意味は「KeyInfo」構造体のメンバを参照すること
typedef struct
{
	int Key_A; int Key_B; int Key_C; int Key_D; int Key_E; int Key_F; int Key_G;
	int Key_H; int Key_I; int Key_J; int Key_K; int Key_L; int Key_M; int Key_N;
	int Key_O; int Key_P; int Key_Q; int Key_R; int Key_S; int Key_T; int Key_U;
	int Key_V; int Key_W; int Key_X; int Key_Y; int Key_Z;
	int Key_0; int Key_1; int Key_2; int Key_3; int Key_4; int Key_5; int Key_6;
	int Key_7; int Key_8; int Key_9;
	int Key_DIVIDE; int Key_MULTIPLY; int Key_SUBTRACT; int Key_ADD;
	int Key_SHIFT; int Key_CONTROL; int Key_ALT; int Key_SPACE;
	int Key_RIGHT; int Key_LEFT; int Key_DOWN; int Key_UP;
}KeyState;

//キー（キーボード）の情報
typedef struct
{
	KeyState Change;		//キーが押されていると「GLFW_PRESS」、離されていると「GLFW_RELEASE」（キー状態でチェンジする）
	KeyState Keep;			//キーを押すたびに「true」と「false」が交互に切り替わる（キー状態をキープする）
}KeyInfo;


/////////////////////////////////////////////
//	クラス定義

class DeviceManager
{

public:
	//コンストラクタ
	DeviceManager();

	//デストラクタ
	~DeviceManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Key管理マネージャーを初期化する
	*	　/※ ウィンドウを複数生成して、それぞれKey管理することはまだ対応していないので注意 ※
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void Initialize(GLFWwindow* const p_window);

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
	static void MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods);

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
	static void CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);

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
	static void ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　キー（キーボード）が変化した時にコールバックされる関数
	*	引数
	*	　p_window		：[I/ ]　ウィンドウハンドル
	*	　p_key			：[I/ ]　キーボードのキー
	*	　p_scancode	：[I/ ]　よくわからない（システム固有のどうたらこうたら）
	*	　p_action		：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
	*	　p_mods		：[I/ ]　ShiftやCtrlなどが押されているかの判断（定義名はURL参照）
	*	　詳細は下記URL参照のこと
	*	　[http://www.glfw.org/docs/latest/group__input.html]の[GLFWkeyfun]関数
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　マウスの情報を取得
	*	引数
	*	　なし
	*	戻り値
	*	　マウスの情報
	*-------------------------------------------------------------------------------*/
	inline MouseInfo GetMouseInfo(void)
	{
		return m_MouseInfo;
	}

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　キー（キーボード）の情報を取得
	*	引数
	*	　なし
	*	戻り値
	*	　キー（キーボード）の情報
	*-------------------------------------------------------------------------------*/
	inline KeyInfo GetKeyInfo(void)
	{
		return m_KeyInfo;
	}

private:

	//キー情報を一元管理するための構造体
	typedef struct
	{
		char* KeyChar;		//キーの文字列
		int KeyDef;			//キーの定義値
		int *Change;		//「KeyInfo」の「Change」メンバと同等（詳細は左記メンバ参照のこと）
		int *Keep;			//「KeyInfo」の「Keep」メンバと同等（詳細は左記メンバ参照のこと）
	}KeyInfoSummary;

	GLFWwindow* m_window;			//ウィンドウハンドル
	static MouseInfo m_MouseInfo;	//マウスの情報
	static KeyInfo m_KeyInfo;		//キー（キーボード）の情報
	static Vec2 m_RightClickPos;	//マウスが右クリックされた時のカーソル座標
	static Vec2 m_LeftClickPos;	//マウスが左クリックされた時のカーソル座標
	static Vec2 m_MiddleClickPos;	//マウスが中央クリックされた時のカーソル座標


};

#endif