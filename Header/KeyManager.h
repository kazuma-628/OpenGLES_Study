#ifndef KEYMANAGER_H
#define KEYMANAGER_H

//include定義
#include "Common.h"

/////////////////////////////////////////////
//	構造体を定義

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

class KeyManager
{

public:
	//コンストラクタ
	KeyManager();

	//デストラクタ
	~KeyManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　Key管理マネージャーを初期化する
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
	*	　p_button	：[I/ ]　押された（GLFW_PRESS） or 離された（GLFW_RELEASE）
	*	　p_button	：[I/ ]　よくわからない
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

private:

	static MouseInfo m_MouseInfo;		//マウスの情報
	static CursorPos m_OldCursorPos;	//直前（1イベント前）のカーソル座標
	GLFWwindow* m_window;		//ウィンドウハンドル
};

#endif