#ifndef TEXTURE_H
#define TEXTURE_H

//include定義
#include "Common.h"
#include <gdiplus.h>

//#define定義
#define TEXTURE_DATA_MAX			128					//テクスチャ管理用の最大数
#define TEXTURE_FILE_NAME_MAX		64					//テクスチャファイル名の最大文字数（ディレクトリ含む）
#define TEXTURE_FILE_DIR				"..\\Resource\\"	//リソースファイルの保存ディレクトリ


typedef enum
{
	PIXELFORMAT_24BIT_RGB = PixelFormat24bppRGB,	//透過情報が含まれていないPNG形式やBMP形式JPG形式など（GL_RGBに相当）
	PIXELFORMAT_32BIT_RGBA = PixelFormat32bppARGB	//透過情報が含まれているPNG形式など（GL_RGBAに相当）
}PixelFotmat;

//テクスチャデータの情報
typedef struct
{
	char Name[TEXTURE_FILE_NAME_MAX];
	GLsizei Width;				//幅
	GLsizei Height;				//高さ
	GLint InternalFormat;		//ピクセルフォーマット（OpenGLに登録する内部フォーマット）
	GLvoid* PixelData;			//ピクセルデータ（OpenGLに登録するピクセルデータ）
}TextureData;


class Texture
{

public:
	//コンストラクタ
	Texture();

	//デストラクタ
	~Texture();

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
	*	　[TextureData]構造体の[PixelData]は不要になった時点で必ず[free]でメモリ解放してください。
	*-------------------------------------------------------------------------------*/
	static TextureData* TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat);

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
	static TextureData* TextureDataSearch(const char* p_FileName);

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
	static void TextureDataBRGtoRGB(const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData, const int p_PixelFotmat);

	static TextureData m_TextureData[TEXTURE_DATA_MAX];	//テクスチャ管理用の変数
	static int m_AttribInfoIndex;						//テクスチャ変数管理用のインデックス値
};
#endif