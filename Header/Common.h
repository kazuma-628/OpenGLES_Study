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
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>


////////////////////////////////////////
// Defineベクトル構造体

//続行不可能なエラーが発生した場合のメッセージ出力用定義
#define ERROR_MESSAGE(Message)		error_message_func(Message, __FILE__, __FUNCTION__ ,__LINE__);

//続行不可能なエラーの可能性があるが、デバッグ中は一時的にエラーになる可能性がある場合のメッセージ出力定義
//デバック中はメッセージを有効にすると大量のメッセージが出力される可能性がありますので、
//最終的に動作が上手くいかないなどのエラー確認の時のみコメントを外して見てください
#define ERROR_MESSAGE_SUB(...)		//printf(__VA_ARGS__); error_message_sub_func(__FILE__, __FUNCTION__ ,__LINE__);

#define WINDOW_WIDTH				1024			//ウィンドウサイズ（幅）
#define WINDOW_HEIGHT				768				//ウィンドウサイズ（高さ）
#define GL_GET_ERROR()				GL_NO_ERROR	//glGetError()	//gl関連のエラーを取得したい場合はコメントの文と入れ替える

////////////////////////////////////
// ベクトル構造体

typedef struct
{
	GLfloat x;
	GLfloat y;
}Vec2;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vec3;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
}Vec4;

typedef struct
{
	GLint x;
	GLint y;
}iVec2;

typedef struct
{
	GLint x;
	GLint y;
	GLint z;
}iVec3;

typedef struct
{
	GLint x;
	GLint y;
	GLint z;
	GLint w;
}iVec4;

////////////////////////////////////
// ベクトル構造体
typedef struct
{
	GLfloat m[2][2];
}Mat2;

typedef struct
{
	GLfloat m[3][3];
}Mat3;

typedef struct
{
	GLfloat m[4][4];
}Mat4;

////////////////////////////////////
// カラーベクトル構造体

typedef struct
{
	GLfloat r;
	GLfloat g;
}Color2;

typedef struct
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
}Color3;

typedef struct
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
}Color4;

typedef struct
{
	GLubyte r;
	GLubyte g;
}bColor2;

typedef struct
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}bColor3;

typedef struct
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
}bColor4;

////////////////////////////////////
// ザイズ構造体
typedef struct
{
	GLsizei  Width;
	GLsizei  Height;
}Size;

////////////////////////////////////

// 構造体
typedef struct
{
	Mat4 ModelViewMatrix;		//メインとなるモデルビューマトリクス（大元のマトリクスデータ）
	Mat4 ProjectionMatrix;		//メインとなるプロジェクションマトリクス（大元のマトリクスデータ）
	Size WindowSize;					//ウィンドウの全体サイズ
	Vec3 Translate;						//初期位置（X,Y,Z）からの移動量
	Vec3 Rotate;						//初期位置（X,Y,Z）からの回転量
}GlobalData;

/*-------------------------------------------------------------------------------
*	関数説明
*	　本関数は外部からユーザーが使うことはありません。
*	　本エラーメッセージを表示したい場合は、「ERROR_MESSAGE」マクロを使用してしてください。
*	　本マクロの意味については、「Define」定義のコメントを確認してください。
*
*	　続行不可能なエラーが発生した場合、メッセージボックスを表示して、自滅リセットする関数です。
*	　
*	引数
*	　Message	：[I/ ]　メッセージボックスに表示したいエラーメッセージ
*	　File		：[I/ ]　エラーが発生したファイル名
*	　Line		：[I/ ]　エラーが発生した行数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
//Define定義
#define ERR_ALL_MES_MAX 512		//エラーメッセージの全文の最大文字数
#define ERR_TMP_MES_MAX 256		//エラーメッセージのテンプ領域の最大文字数

inline void error_message_func(const char* Message, const char* File, const char* func, const int Line)
{
	char All_Message[ERR_ALL_MES_MAX] = { 0 };
	char tmp_char[ERR_TMP_MES_MAX] = { 0 };
	char* Err_Message = "\n\n続行不可能なエラーが発生しました。\n"\
						"情報はコマンドプロンプトを確認してください。\n\n";

	//エラーが発生したファイルと行数を文字列として生成
	sprintf(tmp_char, "%s%s\n%s%s\n%s%d", "ファイル：", File, "関数名：", func, "行数：", Line);
	
	//デバック情報の各文字列を結合
	strcat_s(All_Message, sizeof(All_Message), Message);
	strcat_s(All_Message, sizeof(All_Message), Err_Message);
	strcat_s(All_Message, sizeof(All_Message), tmp_char);

	//メッセージボックス表示
	MessageBox(NULL, All_Message, "Debug Message", MB_OK | MB_ICONSTOP);

	//デバックで呼び出し履歴が分かるように自滅リセットさせる（有効にする場合はコメントを外す）
	//エラーが発生したら「中断（デバッグの停止じゃない）」して、
	//メニューバーの「ウィンドウ」→「デバッグ」→「呼び出し履歴」で関数コール順序が見れます。	
//	typedef char(*ResetFunc)(char);
//	ResetFunc test = (ResetFunc)0xFF;
//	test(0);

	exit(EXIT_FAILURE);		//プログラムを終了する
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　本関数は外部からユーザーが使うことはありません。
*	　本エラーメッセージを表示したい場合は、「ERROR_MESSAGE_SUB」マクロを使用してしてください。
*	　本マクロの意味については、「Define」定義のコメントを確認してください。
*
*	　続行不可能なエラーの可能性があるが、デバッグ中は一時的にエラーになる可能性がある場合、
*	　メッセージボックスを表示して、自滅リセットする関数です。
*	　
*	引数
*	　File			：[I/ ]　エラーが発生したファイル名
*	　Line			：[I/ ]　エラーが発生した行数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
inline void error_message_sub_func(const char* File, const char* func, const int Line)
{
	//メッセージボックスへのエラーメッセージの作成
	char *Message = "Attribute/Uniform変数のロケーション生成、\n"\
		"もしくはデータの送信（関連付け）に失敗しました。";

	//デバッグ情報と共にメッセージボックスを表示する
	error_message_func(Message, File, func, Line);
}

#endif