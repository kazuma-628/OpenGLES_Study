#ifndef TEXTURE_H
#define TEXTURE_H

//include定義
#include "Common.h"
#include <gdiplus.h>

//#define定義
#define TEXTURE_FILE_DIR				"../Resource/Texture/"	//リソースファイルの保存ディレクトリ


typedef enum
{
	PIXELFORMAT_24BIT_RGB = PixelFormat24bppRGB,	//1色が8bitで透過情報が含まれていないPNG形式やBMP形式JPG形式など（GL_RGBに相当）
	PIXELFORMAT_32BIT_RGBA = PixelFormat32bppARGB	//1色が8bitで透過情報が含まれているPNG形式など（GL_RGBAに相当）
}PixelFotmat;

//テクスチャデータの情報
typedef struct
{
	//各変数は[glTexImage2D(3D,etc...)]の引数となるもの（そのまま引数に設定すれば良い）
	GLint internalFormat;		//ピクセル内部フォーマット
	GLsizei width;				//幅
	GLsizei height;				//高さ
	GLint border;				//OpenGLとの互換のためにある存在（OpenGLESは常に[0]）
	GLenum format;				//ピクセルフォーマット（ピクセル内部フォーマットと同じものが設定される）
	GLenum type;				//ピクセル情報の型
	GLvoid *data;				//ピクセルデータ
}TextureInfo;


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
	*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きの画像ファイル名
	*							 [Resource]フォルダ以降のファイルパスを入力してください。
	*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.vert」）
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 [PIXELFORMAT_24BIT_RGB] or [PIXELFORMAT_32BIT_RGBA] で指定（詳細は定義部分のコメント参照）
	*	　p_TextureData	：[ /O]　テクスチャデータ
	*							 [TextureData]構造体の[data]変数は不要になった時点で必ず[free]でメモリ解放してください。
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void FileDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat, TextureInfo *p_TextureData);

private:

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　色情報「BGR(A)」を「RGB(A)」に変換する
	*	引数
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA で指定（詳細は定義部分のコメント参照）
	*	　p_BitmapData	：[I/ ]　変換元のテクスチャデータ（Gdiplus::Bitmap クラスの LockBits関数で読み込んだしたデータ）
	*	　p_TextureData	：[ /O]　変換先のテクスチャデータ　
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void DataBRGtoRGB(const int p_PixelFotmat, const Gdiplus::BitmapData* p_BitmapData, TextureInfo* p_TextureData);

};
#endif