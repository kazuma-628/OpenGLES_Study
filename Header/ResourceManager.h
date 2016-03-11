#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//include定義
#include "Common.h"
#include <gdiplus.h>

//#define定義

#define PIXELFORMAT_24BIT_RGB	(PixelFormat24bppRGB)	//透過情報が含まれていないPNG形式やBMP形式JPG形式など
														//「glTexImage2D」などでは「GL_RGB」を指定すること
#define PIXELFORMAT_32BIT_RGBA	(PixelFormat32bppARGB)	//透過情報が含まれているPNG形式など
														//「glTexImage2D」などでは「GL_RGBA」を指定すること
#define TEXTURE_DATA_MAX			128			//テクスチャ管理用の最大数
#define TEXTURE_FILE_NAME_MAX		64			//テクスチャファイル名の最大文字数（ディレクトリ含む）


//テクスチャデータの情報
typedef struct
{
	char Name[TEXTURE_FILE_NAME_MAX];
	unsigned int Width;		//幅
	unsigned int Height;	//高さ
	int PixelFormat;		//ピクセルフォーマット
	void* PixelData;		//ピクセルデータ
}TextureData;


class ResourceManager
{

public:
	//コンストラクタ
	ResourceManager();

	//デストラクタ
	~ResourceManager();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　画像ファイルからテクスチャデータの読み込みを行います
	*	引数
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きの画像ファイル名（[例] texture.png）
	*								→※ Resourceフォルダに格納されている必要があります ※
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA で指定（詳細は定義部分のコメント参照）
	*	戻り値
	*	　テクスチャデータ（幅,高さ,ピクセルデータなど → 詳細は[TextureData]構造体参照）
	*-------------------------------------------------------------------------------*/
	TextureData* TextureDataLoad(const char* p_FileName, const int p_PixelFotmat);

private:

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　既に画像ファイルからテクスチャデータの読み込みが完了しているか検索します
	*	引数
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きの画像ファイル名（[例] texture.png）　
	*	戻り値
	*	　テクスチャデータを既に読み込んでいる場合 
	*		→テクスチャデータ（幅,高さ,ピクセルデータなど → 詳細は[TextureData]構造体参照）
	*	　テクスチャデータがまだ読み込まれていない場合
	*		→NULL
	*-------------------------------------------------------------------------------*/
	TextureData* TextureDataSearch(const char* p_FileName);

	TextureData m_TextureData[TEXTURE_DATA_MAX];	//テクスチャ管理用の変数
	int m_AttribInfoIndex;							//テクスチャ変数管理用のインデックス値


	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　色情報「BGR(A)」を「RGB(A)」に変換する
	*	引数
	*	　p_BitmapData	：[I/ ]　変換元のテクスチャデータ（Gdiplus::Bitmap クラスの LockBits関数で読み込んだしたデータ）
	*	　p_TextureData	：[ /O]　変換先のテクスチャデータ　
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA で指定（詳細は定義部分のコメント参照）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	void TextureDataBRGtoRGB(const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData, const int p_PixelFotmat);

};
#endif