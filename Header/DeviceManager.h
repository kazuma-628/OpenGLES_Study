#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

//include定義
#include "Common.h"

//Define定義
#define KEY_SUMMARY_MAX	62		//キーの情報と格納する変数をまとめて管理する最大サイズ


/////////////////////////////////////////////
//	マウス関連の構造体定義

//カーソルの座標系
typedef struct
{
	float x;		//X座標
	float y;		//Y座標
}CursorPos;

//マウスの詳細情報
typedef struct
{
	int State;				//マウスのクリック状態（押されている（GLFW_PRESS） or 離されている（GLFW_RELEASE））
	CursorPos Pos;			//マウスのカーソル座標（マウスがクリックされている時だけ更新され、
							//　クリックされていない時は最後の情報が保持される）
	CursorPos DiffPos;		//直前（1イベント前）のカーソル位置からの差分座標（マウスがクリックされている時だけ更新される、それ以外は [0]）
							//　直前のカーソル位置からどれだけ移動したかで、マウスを動かさなければ [0] が入る
	CursorPos ClickPos;		//マウスがクリックされた時のカーソル座標（クリックされていない時は最後の情報が保持される）
	CursorPos ClickDiffPos;	//マウスがクリックされた時からの差分座標（クリックされていない時は [0] ）
}MouseDetailInfo;

//マウスの情報
typedef struct
{
	MouseDetailInfo Right;		//マウスの右クリックの情報
	MouseDetailInfo Left;		//マウスの左クリックの情報
	float Scroll;
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
	*	　詳細は下記URL参照のこと
	*	　http://www.glfw.org/docs/latest/group__input.html#ga1e008c7a8751cea648c8f42cc91104cf
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
	*	　http://www.glfw.org/docs/latest/group__input.html#ga592fbfef76d88f027cb1bc4c36ebd437
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
	*	　http://www.glfw.org/docs/latest/group__input.html#ga6228cdf94d28fbd3a9a1fbb0e5922a8a
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
	*	　http://www.glfw.org/docs/latest/group__input.html#ga592dd1919f8a1dc7576b13cdd8b7b695
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
	*	　右クリックの情報
	*-------------------------------------------------------------------------------*/
	inline MouseInfo GetMouseInfo(void)
	{
		//返却するために情報をコピーする
		//リターンした値の一部を初期化したいので
		MouseInfo tmp_MouseButton = m_MouseInfo;

		//情報を返却したので「直前のカーソル位置からの差分」を初期化
		m_MouseInfo.Left.DiffPos.x = 0.0;
		m_MouseInfo.Left.DiffPos.y = 0.0;
		m_MouseInfo.Right.DiffPos.x = 0.0;
		m_MouseInfo.Right.DiffPos.y = 0.0;
		m_MouseInfo.Scroll = 0.0;

		/////////////////////////////////////////////
		//	デバッグ用
//		printf("tmp_Right.DiffPos.x = %f, tmp_Right.DiffPos.y = %f\n", tmp_MouseButton.Right.DiffPos.x, tmp_MouseButton.Right.DiffPos.y);
//		printf("tmp_Left.DiffPos.x = %f, tmp_Left.DiffPos.y = %f\n", tmp_MouseButton.Left.DiffPos.x, tmp_MouseButton.Left.DiffPos.y);

		return tmp_MouseButton;
	}

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　キー（キーボード）の情報を取得
	*	引数
	*	　なし
	*	戻り値
	*	　右クリックの情報
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


	static MouseInfo m_MouseInfo;		//マウスの情報
	static CursorPos m_OldCursorPos;	//直前（1イベント前）のカーソル座標
	static KeyInfo m_KeyInfo;			//キー（キーボード）の情報
	GLFWwindow* m_window;		//ウィンドウハンドル

};

#endif