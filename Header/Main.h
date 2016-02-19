#ifndef MAIN_H
#define MAIN_H

#include "Common.h"

//Define定義
#define WINDOW_HEIGHT				480			//ウィンドウサイズ（高さ）
#define WINDOW_WIDTH				640			//ウィンドウサイズ（幅）


//関数定義
/*-------------------------------------------------------------------------------
*	関数説明
*	　OpenGLの初期化を行う
*	引数
*	　なし
*	戻り値
*	　ウィンドウハンドル
*-------------------------------------------------------------------------------*/
GLFWwindow *const OpenGLES_init();

#endif