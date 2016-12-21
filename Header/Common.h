#ifndef COMMON_H
#define COMMON_H

//Visual Studioで「fopen,strcat,strcpy」などの関数を使用することによるエラー/ワーニングを出さないようにする
#define _CRT_SECURE_NOWARNINGS
#pragma warning(disable:4996)

////////////////////////////////////
// 定義済みのヘッダーファイル読み込み
//（ほとんどのファイルで必要になるはずなので一括定義）
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include <locale.h>
#include <vector> 
#include <fstream>
#include <string>
#include <memory>
#include <cstdint>
using namespace std;	//stdライブラリの名前空間を適応
//以下GLSL言語で使用する変数をC言語でも使用できるようにするヘッダー
//#define GLM_FORCE_EXPLICIT_CTOR
#include <glm/glm.hpp>		//標準型ヘッダー（vec4, mat4 など）
#include <glm/ext.hpp>		//演算用拡張ヘッダー（ranslate, rotate, scale など）
using namespace glm;	//glmライブラリの名前空間を適応

////////////////////////////////////////
// Define定義（デバッグ情報表示意外の定義）

#define WINDOW_WIDTH				1024					//ウィンドウサイズ（幅）
#define WINDOW_HEIGHT				768						//ウィンドウサイズ（高さ）
#define GL_GET_ERROR()				GL_NO_ERROR	//glGetError()	//gl関連のエラーを取得したい場合はコメントの文と入れ替える
#define PI							3.141592653589793
//セーフティー処理のマクロ
#define SAFE_FREE(ptr)				free(ptr);	ptr = nullptr		//「free」したら必ず「nullptr」を代入するマクロ
#define SAFE_DELETE(ptr)			delete ptr;	ptr = nullptr		//「delete」したら必ず「nullptr」を代入するマクロ

////////////////////////////////////////
// デバッグ情報表示関係の処理など（Define定義・関数定義）

//デバッグメッセージ出力用マクロ（ユーザーが直接使用することはありません）
//エラー・ワーニングメッセージを出力したい場合は「ERROR_MESSAGE」又は「WARNING_MESSAGE」を使用してください。
#define DEBUG_PRINT(Level, String, ...)		printf("\n■■■ " Level " ■■■　\nファイル：%s　\n行数：%d　関数名：%s　\n" String "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);

//続行不可能なエラーが発生した場合のメッセージ出力用定義
#define ERROR_MESSAGE(String, ...)			DEBUG_PRINT("エラー", String, __VA_ARGS__);	error_message_func();

//続行不可能ではないが、修正が必要な可能性がある場合のメッセージ出力用定義
#define WARNING_MESSAGE(String, ...)		DEBUG_PRINT("ワーニング", String, __VA_ARGS__);

//続行不可能なエラーの可能性はあるが、デバッグ中は一時的にエラーになる可能性がある場合のメッセージ出力定義
//動くはずのプログラムが動作しないなどのエラー確認時のみコメントを外して見てください。なにか見つかるかもしれません。
#define ERROR_MESSAGE_SUB(String, ...)	//ERROR_PRINT(String, __VA_ARGS__);	error_message_func();

/*-------------------------------------------------------------------------------
*	関数説明
*	　本関数は外部からユーザーが使うことはありません。
*	　エラーメッセージを表示したい場合は、「ERROR_MESSAGE」マクロを使用してしてください。
*
*	　続行不可能なエラーが発生した場合、メッセージボックスを表示して、自滅リセットする関数です。
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/

inline void error_message_func(void)
{
	char* ErrorMessage = "続行不可能なエラーが発生しました。\n" \
						 "情報はコマンドプロンプトを確認してください。\n\n" \
						 "関数の呼び出し履歴を見たい場合は、\n" \
						 "[error_message_func]関数の自滅リセットを有効にしてください。\n\n" \
						 "OKを押すとプログラムを終了 又は デバッグします。";

	//メッセージボックス表示
	MessageBox(NULL, ErrorMessage, "Error Message", MB_OK | MB_ICONSTOP);

	//デバックで呼び出し履歴が分かるように自滅リセットさせる（有効にする場合はコメントを外す）
	//エラーが発生したら「中断（デバッグの停止じゃない）」して、
	//メニューバーの「ウィンドウ」→「デバッグ」→「呼び出し履歴」で関数コール順序が見れます。	
	//	typedef char(*ResetFunc)(char);
	//	ResetFunc test = (ResetFunc)0xFF;
	//	test(0);

	//プログラムを終了する
	exit(EXIT_FAILURE);
}

////////////////////////////////////
// GLMで足りないベクトル構造体を定義

//(signed)8ビット, 一般的なsigned charを想定
typedef tvec4<int8_t, highp>	cvec4;
typedef tvec3<int8_t, highp>	cvec3;
typedef tvec2<int8_t, highp>	cvec2;
typedef tvec1<int8_t, highp>	cvec1;

//(unsigned)8ビット, 一般的なunsigned charを想定
typedef tvec4<uint8_t, highp>	ucvec4;
typedef tvec3<uint8_t, highp>	ucvec3;
typedef tvec2<uint8_t, highp>	ucvec2;
typedef tvec1<uint8_t, highp>	ucvec1;

//(signed)16ビット, 一般的なsigned shortを想定
typedef tvec4<int16_t, highp>	svec4;
typedef tvec3<int16_t, highp>	svec3;
typedef tvec2<int16_t, highp>	svec2;
typedef tvec1<int16_t, highp>	svec1;

//(unsigned)16ビット, 一般的なunsigned shortを想定
typedef tvec4<uint16_t, highp>	usvec4;
typedef tvec3<uint16_t, highp>	usvec3;
typedef tvec2<uint16_t, highp>	usvec2;
typedef tvec1<uint16_t, highp>	usvec1;

////////////////////////////////////

// 構造体
struct GlobalData
{
	mat4 ModelViewMat;			//モデルビューマトリクス（大元のマトリクスデータ）
	mat4 ProjectionMat;			//プロジェクションマトリクス（大元のマトリクスデータ）
	GLfloat NearClip;			//プロジェクションマトリクス生成時に使用したNear値（大元のマトリクスデータ）
	GLfloat FarClip;			//プロジェクションマトリクス生成時に使用したFar値（大元のマトリクスデータ）
	uvec2 WindowSize;			//ウィンドウの全体サイズ
	GLfloat Aspect;				//アスペクト比（幅 ÷ 高さ）（横の大きさを[?]とした時、縦の大きさは[? * Aspect]となる）
	vec3 TranslateAmount;		//初期位置（X,Y,Z）からの移動量
	vec3 RotateAmount;			//初期位置（X,Y,Z）からの回転量
};



#endif