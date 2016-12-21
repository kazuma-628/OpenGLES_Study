#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

//include定義
#include "Common.h"


/////////////////////////////////////////////
//	マウス関連の構造体定義

//マウスの詳細情報
struct MouseDetail
{
	bool StateChange;		//マウスがクリックされていると「true」、されていないと「false」（クリック状態でチェンジする）							
	bool StateKeep;			//マウスをクリックするたびに「true」と「false」が交互に切り替わる（クリック状態をキープする）
	uint16_t PushCount;		//マウスを押した（クリックした）合計回数
							//　初期状態は[0]で、押した（クリックした）回数分、値が加算されていく
	ivec2 ClickDiffPos;		//マウスがクリックされた座標からの差分座標（クリックされていない時は [0] ）
							//　例：[x:50][y:50]でクリックして、ドラッグ状態で[x:40][y:60]に移動させた場合、
							//　　　格納される値は[x:-10][y:10]となる
};

//マウスの情報
struct MouseInfo
{
	MouseDetail Right;			//マウスの右クリックの情報
	MouseDetail Left;			//マウスの左クリックの情報
//	MouseDetail Middle;			//マウスの中央クリックの情報
	ivec2 Position;				//マウスのカーソル座標
	ivec2 ScrollAmount;			//スクロールの合計量、初期状態は[x:0（横[左右]スクロール）][y:0（縦[上下]スクロール）]で、
								//　スクロールした分だけ値が蓄積（加算/減算）されていく
};

/////////////////////////////////////////////
//	キー（キーボード）関連の構造体定義

//各キー（キーボード）の情報
//各変数に保存される値やその意味は「KeyInfo」構造体のメンバを参照すること
struct KeyState
{
	bool Key_A; bool Key_B; bool Key_C; bool Key_D; bool Key_E; bool Key_F; bool Key_G;
	bool Key_H; bool Key_I; bool Key_J; bool Key_K; bool Key_L; bool Key_M; bool Key_N;
	bool Key_O; bool Key_P; bool Key_Q; bool Key_R; bool Key_S; bool Key_T; bool Key_U;
	bool Key_V; bool Key_W; bool Key_X; bool Key_Y; bool Key_Z;
	bool Key_0; bool Key_1; bool Key_2; bool Key_3; bool Key_4; bool Key_5; bool Key_6;
	bool Key_7; bool Key_8; bool Key_9;
	bool Key_DIVIDE; bool Key_MULTIPLY; bool Key_SUBTRACT; bool Key_ADD;
	bool Key_SHIFT; bool Key_CONTROL; bool Key_ALT; bool Key_SPACE;
	bool Key_RIGHT; bool Key_LEFT; bool Key_DOWN; bool Key_UP;
};

//キー（キーボード）の情報
struct KeyInfo
{
	KeyState StateChange;		//キーが押されていると「true」、離されていると「false」（キー状態でチェンジする）
	KeyState StateKeep;			//キーを押すたびに「true」と「false」が交互に切り替わる（キー状態をキープする）
	KeyState PushCount;			//キーを押した合計回数
								//　初期値は[0]で、押した回数分、値が加算されていく
	char LastKey;				//一番最後に押されたキー（アルファベット(大文字)・数字のみ）が「1文字」として格納される（例:[B],[5]）
								//　最後の動作が「キーが離された」の場合は[0]が設定される（初期値も[0]）
};


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
	*	　p_window	：[I/ ]　ウィンドウハンドル
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
	inline const MouseInfo& GetMouseInfo(void) const
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
	inline const KeyInfo& GetKeyInfo(void) const
	{
		return m_KeyInfo;
	}

private:

	//キー情報を一元管理するための構造体
	struct KeyInfoSummary
	{
		char *KeyChar;			//キーの文字列
		uint32_t KeyDefine;		//キーの定義値
		bool *StateChange;		//「KeyInfo」の「StateChange」メンバと同等（詳細は左記メンバ参照のこと）
		bool *StateKeep;		//「KeyInfo」の「StateKeep」メンバと同等（詳細は左記メンバ参照のこと）
		bool *PushCount;		//「KeyInfo」の「PushCount」メンバと同等（詳細は左記メンバ参照のこと）
	};

	MouseInfo m_MouseInfo = { 0 };	//マウスの情報
	KeyInfo m_KeyInfo = { 0 };		//キー（キーボード）の情報
	ivec2 m_RightClickPos = { 0 };	//マウスが右クリックされた時のカーソル座標
	ivec2 m_LeftClickPos = { 0 };	//マウスが左クリックされた時のカーソル座標
	ivec2 m_MiddleClickPos = { 0 };	//マウスが中央クリックされた時のカーソル座標

};

#endif