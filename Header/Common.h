#ifndef COMMON_H
#define COMMON_H

//include定義（ほとんどのファイルで必要になるはずなので一括定義）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>

//続行不可能なエラーが発生した場合のメッセージ出力用定義
#define ERROR_MESSAGE(Message) (error_message_func(Message, __FILE__ ,__LINE__))


/*-------------------------------------------------------------------------------
*	関数説明
*	　本関数は外部からユーザーが使うことはありません。
*	　エラーメッセージを表示したい場合は、「ERROR_MESSAGE」マクロを使用してしてください。
*
*	　続行不可能なエラーが発生した場合、メッセージボックスを表示して、自滅リセットする関数です。
*	　
*	引数
*	　Message	：[I/ ]　表示したいエラーメッセージ
*	　File		：[I/ ]　エラーが発生したファイル名
*	　Line		：[I/ ]　エラーが発生した行数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
//Define定義
#define ERR_ALL_MES_MAX 512		//エラーメッセージの全文の最大文字数
#define ERR_TMP_MES_MAX 256		//エラーメッセージのテンプ領域の最大文字数

inline void error_message_func(char* Message, char* File, int Line)
{
	char All_Message[ERR_ALL_MES_MAX] = { 0 };
	char tmp_char[ERR_TMP_MES_MAX] = { 0 };
	char* Err_Message = "\n\n続行不可能なエラーが発生しました。\n"\
						"情報はコマンドプロンプトを確認してください。\n\n";

	//エラーが発生したファイルと行数を文字列として生成
	sprintf_s(tmp_char, sizeof(tmp_char), "%s%s\n%s%d", "ファイル：", File, "行数：", Line);
	
	//デバック情報の文字列を結合
	strcat_s(All_Message, sizeof(All_Message), Message);
	strcat_s(All_Message, sizeof(All_Message), Err_Message);
	strcat_s(All_Message, sizeof(All_Message), tmp_char);

	//メッセージボックス表示
	MessageBox(NULL, All_Message, "Debug Message", MB_OK | MB_ICONSTOP);

	//デバックで呼び出し履歴が分かるように自滅リセット
	//エラーが発生したら「中断（デバッグの停止じゃない）」して、
	//メニューバーの「ウィンドウ」→「デバッグ」→「呼び出し履歴」で関数コール順序が見れるます。
	free((void*)0xFF);		
	
	exit(EXIT_FAILURE);		//プログラムを終了する（自滅リセットでここまで来ることはないと思うけど。。。）
}

#endif