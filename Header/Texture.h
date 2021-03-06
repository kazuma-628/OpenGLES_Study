﻿#ifndef TEXTURE_H
#define TEXTURE_H

//include定義
#include "Common.h"
#include "ModelManager.h"
#include <gdiplus.h>

//ピクセルフォーマット
enum class PixelFotmat : uint32_t
{
	RGB_24BIT = PixelFormat24bppRGB,	//1色が8bitで透過情報が含まれていないPNG形式やBMP形式JPG形式など（GL_RGBに相当）
	RGBA_32BIT = PixelFormat32bppARGB	//1色が8bitで透過情報が含まれているPNG形式など（GL_RGBAに相当）
};

//テクスチャデータの情報
struct TextureInfo
{
	//各変数は[glTexImage2D(3D,etc...)]の引数となるもの（そのまま引数に設定すれば良い）
	//ここに用意されてない引数は各自使用用途に合わせて設定すること
	GLint internalFormat;		//ピクセル内部フォーマット
	GLsizei width;				//幅
	GLsizei height;				//高さ
	GLint border;				//OpenGLとの互換のためにある存在（OpenGLESは常に[0]）
	GLenum format;				//ピクセルフォーマット（ピクセル内部フォーマットと同じものが設定される）
	GLenum type;				//ピクセル情報の型
	GLvoid *data;				//ピクセルデータ
};


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
	*							 [Resource/Texture/]フォルダ以降のファイルパスを入力してください。（例外あり、「p_FullPathFlag」引数を参照）
	*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.png」）
	*	　p_FullPathFlag：[I/ ]　フルパスでファイル名を指定する場合は「ture」にしてください
	*							 （[Resource/Texture/]フォルダ以降のファイル名を入力したくない場合に「ture」にする）
	*							 ※現状は「モデルデータのテクスチャを読み込む」場合に使用
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 [RGB_24BIT] or [RGBA_32BIT] で指定（詳細は定義部分のコメント参照）
	*	　p_TextureData	：[ /O]　テクスチャデータ
	*							 ※注意※
	*							 テクスチャデータが不要になった時点で、必ず[FileDataFree]をコールしてください。
	*							（テクスチャデータのメモリを解放します）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void FileDataLoad(const string &p_FileName, const bool p_FullPathFlag, const PixelFotmat p_PixelFotmat, TextureInfo *p_TextureData);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　テクスチャデータのメモリを解放します
	*	引数
	*	　p_TextureData	：[ /O]　テクスチャデータ（メモリを解放後「nullptr」が格納されるという意味で[ /O]指定）
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void FileDataFree(TextureInfo *p_TextureData);

private:

	static const string TEXTURE_FILE_DIR;		//テクスチャファイルの保存ディレクトリ

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　色情報「BGR(A)」を「RGB(A)」に変換しつつ、上下を反転させる
	*	　（VRAMにアップロードするときに上下が反転するので予め反転させておく）
	*	引数
	*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
	*							 RGB_24BIT or RGBA_32BIT で指定（詳細は定義部分のコメント参照）
	*	　p_BitmapData	：[I/ ]　変換元のテクスチャデータ（Gdiplus::Bitmap クラスの LockBits関数で読み込んだしたデータ）
	*	　p_TextureData	：[ /O]　変換先のテクスチャデータ　
	*	戻り値
	*	　なし
	*-------------------------------------------------------------------------------*/
	static void DataBRGtoRGB_invert(const PixelFotmat p_PixelFotmat, const Gdiplus::BitmapData &p_BitmapData, TextureInfo* p_TextureData);

};
#endif