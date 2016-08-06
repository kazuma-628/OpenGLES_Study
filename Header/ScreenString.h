#ifndef SCREEN_STRING_H
#define SCREEN_STRING_H

//include定義
#include "Common.h"
#include "ShaderManager.h"
#include "ft2build.h"
#include FT_FREETYPE_H

//Defien
#define FT_FONT_FILE		"../Resource/Font/GenEiGothicN/GenEiGothicN-Bold.otf"		//FreeTypeで使用するフォントファイル
#define DEBUG_FONT_SIZE		20			//デバッグ表示のフォントサイズ指定（ピクセル単位）
#define DEBUG_ROWS_SPACING	(DEBUG_FONT_SIZE + (unsigned int)ceil((DEBUG_FONT_SIZE / 3.0)))	//デバッグ用の文字と文字との縦方向の間隔（ピクセル単位）　※こちらは普段変更しない定義
#define WIDTH_SPACING		3			//文字と文字との横方向の間隔（ピクセル単位）
class ScreenString
{

public:

	//コンストラクタ
	ScreenString();

	//デストラクタ
	~ScreenString();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　画面上に文字列を表示するための準備をします
	*	引数
	*	　p_Global		：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void Prepare(const GlobalData &p_Global);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　資源の再準備
	*	引数
	*	　p_Global		：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void RePrepare(const GlobalData &p_Global);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　破棄(終了)処理（変数などを破棄します）
	*	引数
	*	　なし
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void Destroy(void);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　画面上にデバック表示（設定）をします。
	*	　※この時点では描画は実行しません
	*	　　すべての描画が完了した時点で最前面に描画したいので、
	*		[DebugDrawing]をコールしたタイミングで描画を行います。
	*	引数
	*	　p_Global		：[I/ ]　グローバルデータ
	*	　p_String		：[I/ ]　画面に表示したいデバッグメッセージ
	*							 この関数を呼ぶたびに自動的に改行を行います。　
	*	  ...			：[I/ ]　可変引数です。
	*							 引数[p_String]には通常の[printf]のようにパラメータを含むこと(表示)が可能です
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void DebugPrint(const GlobalData &p_Global, const char* p_String, ...);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　[DebugPrint]で表示（設定）した文字列を描画します。
	*	　この関数はすべての描画が完了してから最後にコールしてください
	*	　（デバッグ表示が最前面に来るようにするため）
	*	引数
	*	　p_Global		：[I/ ]　グローバルデータ
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void DebugDrawing(const GlobalData &p_Global);

private:

	static ShaderManager *m_StringShader;		//文字列描画シェーダーオブジェクト
	static GLint m_attr_pos;					//頂点座標
	static GLint m_unif_tex;					//テクスチャ
	static GLint m_attr_tex_coord;				//テクスチャ座標
	static GLint m_unif_char_color;				//文字カラー
	static GLint m_unif_back_color;				//背景カラー

	static FT_Library m_ft_Library;				//FreeTypeライブラリ
	static FT_Face m_ft_Face;					//FreeTypeのフォントフェース

	static std::vector<GLchar> DebugString;		//デバッグ表示用の文字列データ

	static unsigned int DebugMaxWidth;			//デバッグ表示用の文字列の合計最大幅
	static unsigned int DebugSumRows;			//デバッグ表示用の文字列の合計高さ（＝最大高さ）
};
#endif