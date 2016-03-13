#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

//include定義
#include "Common.h"

typedef struct
{
	int Width;		//生成したウィンドウの幅
	int Height;		//生成したウィンドウの高さ
}WindowSize;

class WindowManager
{

public:
	//コンストラクタ
	WindowManager();

	//デストラクタ
	~WindowManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ウィンドウを作成する
	*	　※ ウィンドウを複数生成することにはまだ対応していないので注意 ※
	*	引数
	*	　p_Width	：[I/ ]　ウィンドウの幅
	*	　p_Height	：[I/ ]　ウィンドウの高さ
	*	　p_Title	：[I/ ]　ウィンドウの名前（ウィンドウ左上やタスクバーに表示される）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void CreateNewWindow(const int p_Width, const int p_Height, const char* p_Title);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ウィンドウに描画する（フロントバッファ / バックバッファ 共通）
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void DrawingOnWindow(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ウィンドウサイズが変化した時にコールバックされる関数
	*	引数
	*	　p_window	：[I/ ]　ウィンドウハンドル
	*	　p_Width	：[I/ ]　ウィンドウの幅
	*	　p_Height	：[I/ ]　ウィンドウの高さ
	*	　詳細は下記URL参照のこと
	*	　http://www.glfw.org/docs/latest/group__window.html#gaaca1c2715759d03da9834eac19323d4a
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void WindowSizeCallback(GLFWwindow* p_window, int p_Width, int p_Height);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　作成したウィンドウハンドルを取得する
	*	引数
	*	　なし
	*	戻り値
	*	　ウィンドウハンドル
	*-------------------------------------------------------------------------------*/
	inline GLFWwindow* const GetWindow()
	{
		return m_window;
	}

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　作成したウィンドウのサイズを取得する
	*	引数
	*	　なし
	*	戻り値
	*	　ウィンドウハンドル
	*-------------------------------------------------------------------------------*/
	inline WindowSize GetWindowSize()
	{
		return m_WindowSize;
	}

private:

	GLFWwindow* m_window;		//生成したウィンドウハンドル
	static WindowSize m_WindowSize;	//生成したウィンドウのサイズ（幅,高さ）
};
#endif