#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

//include定義
#include "Common.h"

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

private:

	GLFWwindow* m_window;		//生成したウィンドウハンドル
	int m_Width;		//生成したウィンドウの幅
	int m_Height;		//生成したウィンドウの高さ
};
#endif