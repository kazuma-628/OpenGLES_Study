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
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void CreateNewWindow();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　作成したウィンドウハンドルを取得する
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	inline GLFWwindow* const GetWindow()
	{
		return m_window;
	}

private:

	GLFWwindow* m_window;		//生成したウィンドウハンドル
};
#endif