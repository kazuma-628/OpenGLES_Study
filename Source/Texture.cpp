﻿#include "Texture.h"

/////////////////////////////////////////////
//static変数の実体を定義

const string Texture::TEXTURE_FILE_DIR = "../Resource/Texture/";    //テクスチャファイルの保存ディレクトリ

//コンストラクタ
Texture::Texture()
{

}

//デストラクタ
Texture::~Texture()
{

}

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
void Texture::FileDataLoad(const string &p_FileName, const bool p_FullPathFlag, const PixelFotmat p_PixelFotmat, TextureInfo *p_TextureData)
{
	//モデルデータのテクスチャを読み込む場合は、
	//（長くなるので）格納されているディレクトリへのパスを読み飛ばしてファイル名を表示
	if (true == p_FullPathFlag)
	{
		printf("テクスチャ「%s」の読み込みを開始します...", p_FileName.substr(p_FileName.rfind("/") + 1).c_str());
	}
	else
	{
		printf("テクスチャ「%s」の読み込みを開始します...", p_FileName.c_str());
	}

	//引数チェック
	if (true == p_FileName.empty())
	{
		printf("失敗\n");
		ERROR_MESSAGE("テクスチャデータの読み込み 引数エラー\n" \
					  "p_FileName = %s, p_TextureData = %x\n" \
					  , p_FileName.c_str(), reinterpret_cast<uint32_t>(p_TextureData));
		return;
	}


	//////////////////////////////////////////
	// テクスチャファイルへのパス（ワイド文字）を作成

	string texture_dir_file_name;				//テクスチャファイルへのパス（マルチバイト文字）	
	wchar_t *w_texture_dir_file_name = nullptr;	//テクスチャファイルへのパス（ワイド文字）
	uint32_t StrLength = 0;						//読み込むテクスチャファイル名の長さ（バイト数）
	
	//モデルデータのテクスチャを読み込む場合とそれ以外で処理を分ける。
	//（モデルデータのテクスチャはフルパスが入っているのでそのまま使用して、
	//　それ以外はファイル名だけが入っているのでフルパスにする）
	if (true == p_FullPathFlag)
	{
		texture_dir_file_name = p_FileName;
	}
	else
	{
		texture_dir_file_name = TEXTURE_FILE_DIR + p_FileName;
	}

	//ロケールを日本に設定
	setlocale(LC_CTYPE, "jpn");

	//マルチバイト文字の文字数を取得して、ワイド文字に変換した場合のバイト数を算出する
	StrLength = _mbstrlen(texture_dir_file_name.c_str()) * 2;

	// 文字列の長さを取得してメモリ確保（終端を明確にするため +2(ワイド文字なので) する。[\0]となる）
	w_texture_dir_file_name = (wchar_t*)calloc(StrLength + 2, sizeof(char));

	//マルチバイト文字列 → ワイド文字列に変換（[\0]までコピー）
	mbstowcs(w_texture_dir_file_name, texture_dir_file_name.c_str(), _mbstrlen(texture_dir_file_name.c_str()) + 1);



	//////////////////////////////////////////
	// [GDI+]を使用してテクスチャを読み込み

	//GDI+の初期化
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&token, &input, NULL);

	//テクスチャ読み込み
	Gdiplus::Bitmap* Texture = new Gdiplus::Bitmap(w_texture_dir_file_name);

	//テクスチャを読み込んだのでファイルパスを保存していたメモリを開放する
	SAFE_FREE(w_texture_dir_file_name);

	//テクスチャデータ読み込み
	Gdiplus::BitmapData BitmapData;
	if (0 != Texture->LockBits(0, Gdiplus::ImageLockModeRead, static_cast<uint32_t>(p_PixelFotmat), &BitmapData))
	{
		printf("失敗\n");

		//モデルデータのテクスチャを読み込む場合とそれ以外で処理を分ける。
		//（読み込み元となる基礎フォルダが違うのでエラーメッセージを切り替える）
		if (true == p_FullPathFlag)
		{
			//「+3」は不要な「../」の部分を読み飛ばして表示するためのもの
			ERROR_MESSAGE("テクスチャファイルの読み込みに失敗しました。\n"\
						  "「%s」にファイルがありますか？\n"\
						  "マテリアルファイルに記載してあるテクスチャファイルへのパスが間違っていませんか？"\
						 , p_FileName.substr(3).c_str());
		}
		else
		{
			ERROR_MESSAGE("テクスチャファイルの読み込みに失敗しました。\n"\
						  "「Resource/Texture/」フォルダに格納されていますか？\n"\
						  "ファイル名が間違っていませんか？");
		}
		
		//オブジェクト破棄
		SAFE_DELETE(Texture);
		
		return;
	}

	/////////////////////////////////////////////////
	// 返却する情報の設定
	switch (p_PixelFotmat)
	{
	case PixelFotmat::RGB_24BIT:
		p_TextureData->internalFormat = GL_RGB;
		p_TextureData->format = GL_RGB;
		break;

	case PixelFotmat::RGBA_32BIT:
		p_TextureData->internalFormat = GL_RGBA;
		p_TextureData->format = GL_RGBA;
		break;
	default:
		printf("失敗\n");
		ERROR_MESSAGE("ピクセルフォーマットの引数が不正です。\n"\
					  "p_PixelFotmat = %d", p_PixelFotmat);

		//オブジェクト破棄
		SAFE_DELETE(Texture);
		
		return;
	}

	p_TextureData->width = static_cast<GLsizei>(BitmapData.Width);
	p_TextureData->height = static_cast<GLsizei>(BitmapData.Height);
	p_TextureData->border = 0;
	p_TextureData->type = GL_UNSIGNED_BYTE;
	p_TextureData->data = reinterpret_cast<GLvoid*>(calloc(BitmapData.Height * BitmapData.Stride, sizeof(byte)));

	//ロードしたテクスチャは「BGR」で格納されているので「RGB」に変換しつつ上下を反転しながらコピーする
	DataBRGtoRGB_invert(p_PixelFotmat, BitmapData, p_TextureData);

	//読み込んだテクスチャ情報/データを破棄する
	Texture->UnlockBits(&BitmapData);
	SAFE_DELETE(Texture);

	//GDI+の終了
	Gdiplus::GdiplusShutdown(token);

	printf("完了\n");
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　テクスチャデータのメモリを解放します
*	引数
*	　p_TextureData	：[ /O]　テクスチャデータ（メモリを解放後「nullptr」が格納されるという意味で[ /O]指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Texture::FileDataFree(TextureInfo *p_TextureData)
{
	//メモリを開放する
	SAFE_FREE(p_TextureData->data);

	p_TextureData = nullptr;
}

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
void Texture::DataBRGtoRGB_invert(const PixelFotmat p_PixelFotmat, const Gdiplus::BitmapData &p_BitmapData, TextureInfo* p_TextureData)
{
	//1色分の情報のバイト数
	uint32_t ColorByte = 0;

	//画像のフォーマットから1色分の情報のバイト数を決定
	if (PixelFotmat::RGB_24BIT == p_PixelFotmat)
	{
		ColorByte = 3;
	}
	else if (PixelFotmat::RGBA_32BIT == p_PixelFotmat)
	{
		ColorByte = 4;
	}

	//高さピクセル分繰り返す
	for (uint32_t Height = 0; Height < p_BitmapData.Height; Height++)
	{
		//幅ピクセル × カラー色分繰り返す（幅分の変換量となる）
		for (uint32_t Width = 0; Width < p_BitmapData.Width * ColorByte; Width = Width + ColorByte)
		{
			//「BGR(A)」を「RGB(A)」に変換する1画素の先頭位置を算出する。
			//GPU（VRAM）にアップロードするときに上下が反転するので、
			//それを修正するような先頭位置（上下が反転する位置）も算出する。
			//また、その際は「Stride」を考慮する

			//変換する1画素の先頭位置
			uint32_t DataPos = (Height * p_BitmapData.Stride) + Width;

			//「DataPos」と上下が反転する位置
			uint32_t DataPos_invert = ((p_BitmapData.Height - 1 - Height ) * p_BitmapData.Stride) + Width;

			//R成分をコピー
			memmove(static_cast<byte*>(p_TextureData->data) + DataPos, static_cast<byte*>(p_BitmapData.Scan0) + DataPos_invert + 2, sizeof(byte));

			//G成分をコピー
			memmove(static_cast<byte*>(p_TextureData->data) + DataPos + 1, static_cast<byte*>(p_BitmapData.Scan0) + DataPos_invert + 1, sizeof(byte));

			//B成分をコピー
			memmove(static_cast<byte*>(p_TextureData->data) + DataPos + 2, static_cast<byte*>(p_BitmapData.Scan0) + DataPos_invert, sizeof(byte));

			//RGBAフォーマットではA成分もコピー
			if (PixelFotmat::RGBA_32BIT == p_PixelFotmat)
			{
				memmove(static_cast<byte*>(p_TextureData->data) + DataPos + 3, static_cast<byte*>(p_BitmapData.Scan0) + DataPos_invert + 3, sizeof(byte));
			}
		}
	}
}