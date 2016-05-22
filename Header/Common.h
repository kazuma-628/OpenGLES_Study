#ifndef COMMON_H
#define COMMON_H

//include定義（ほとんどのファイルで必要になるはずなので一括定義）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>

//続行不可能なエラーが発生した場合のメッセージ出力用定義
#define ERROR_MESSAGE(Message) (error_message_func(Message, __FILE__ ,__LINE__))


//続行不可能なエラーの可能性があるが、デバッグ中は一時的にエラーになる可能性がある場合のメッセージ出力定義
//デバック中はメッセージを有効にすると大量のメッセージが出力される可能性がありますので、
//最終的に動作が上手くいかないなどのエラー確認の時のみコメントを外して見てください

#define ERROR_MESSAGE_SUB(PrintMessage, param1, param2, param3) // (error_message_sub_func(PrintMessage, param1, param2, param3, __FILE__ ,__LINE__))


//Define定義
#define WINDOW_WIDTH				800			//ウィンドウサイズ（幅）
#define WINDOW_HEIGHT				600			//ウィンドウサイズ（高さ）
#define GL_GET_ERROR()				GL_NO_ERROR	//glGetError()	//gl関連のエラーを取得したい場合はコメントの文と入れ替える

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

inline void error_message_func(const char* Message, const char* File, const int Line)
{
	char All_Message[ERR_ALL_MES_MAX] = { 0 };
	char tmp_char[ERR_TMP_MES_MAX] = { 0 };
	char* Err_Message = "\n\n続行不可能なエラーが発生しました。\n"\
						"情報はコマンドプロンプトを確認してください。\n\n";

	//エラーが発生したファイルと行数を文字列として生成
	sprintf_s(tmp_char, sizeof(tmp_char), "%s%s\n%s%d", "ファイル：", File, "行数：", Line);
	
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
*	　PrintMessage	：[I/ ]　コマンドプロンプトに表示したいエラーメッセージ
*	　param1		：[I/ ]　エラーメッセージに組み込みたい任意の文字列 1
*	　param2		：[I/ ]　エラーメッセージに組み込みたい任意の文字列 2
*	　param3		：[I/ ]　エラーメッセージに組み込みたい任意の文字列 3
*	　File			：[I/ ]　エラーが発生したファイル名
*	　Line			：[I/ ]　エラーが発生した行数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
inline void error_message_sub_func(const char* PrintMessage, const char* param1, const char* param2, const char* param3, const char* File, const int Line)
{
	//コマンドプロンプトへのエラーメッセージの表示
	printf(PrintMessage, param1, param2, param3);

	//メッセージボックスへのエラーメッセージの作成
	char *Message = "Attribute/Uniform変数のロケーション生成、\n"\
		"もしくはデータの送信（関連付け）に失敗しました。";

	//デバッグ情報と共にメッセージボックスを表示する
	error_message_func(Message, File, Line);
}

#endif