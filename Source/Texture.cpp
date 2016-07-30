#include "Texture.h"

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
*							 [Resource/Texture/]フォルダ以降のファイルパスを入力してください。
*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.vert」）
*	　p_PixelFotmat	：[I/ ]　画像ファイルのフォーマット
*							 [PIXELFORMAT_24BIT_RGB] or [PIXELFORMAT_32BIT_RGBA] で指定（詳細は定義部分のコメント参照）
*	　p_TextureData	：[ /O]　テクスチャデータ
*							 [TextureData]構造体の[data]変数は不要になった時点で必ず[free]でメモリ解放してください。
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Texture::TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat, TextureData *p_TextureData)
{
	printf("テクスチャ「%s」の読み込みを開始します...", p_FileName);

	//引数チェック
	if (NULL == p_FileName || NULL == p_TextureData)
	{
		printf("失敗\n");
		ERROR_MESSAGE("テクスチャデータの読み込み 引数エラー\n" \
			"p_FileName = %s, p_TextureData = %x\n" \
			, p_FileName, (unsigned int)p_TextureData);
		return;
	}

	//////////////////////////////////////////
	// テクスチャファイルへのパス（ワイド文字）を作成

	char *texture_dir_file_name = NULL;			//テクスチャファイルへのパス（マルチバイト文字）
	wchar_t *w_texture_dir_file_name = NULL;	//テクスチャファイルへのパス（ワイド文字）
	int StrLength = 0;		//読み込むテクスチャファイル名の長さ（バイト数）

							// 文字列の長さを取得してメモリ確保（終端を明確にするため +1 する。[\0]となる）
	StrLength = strlen(TEXTURE_FILE_DIR) + strlen(p_FileName);
	texture_dir_file_name = (char*)calloc(StrLength + 1, sizeof(char));

	//テクスチャファイルへのパスを生成する（マルチバイト文字）
	sprintf(texture_dir_file_name, "%s%s", TEXTURE_FILE_DIR, p_FileName);

	//ロケールを日本に設定
	setlocale(LC_CTYPE, "jpn");

	//マルチバイト文字の文字数を取得して、ワイド文字に変換した場合のバイト数を算出する
	StrLength = _mbstrlen(texture_dir_file_name) * 2;

	// 文字列の長さを取得してメモリ確保（終端を明確にするため +2(ワイド文字なので) する。[\0]となる）
	w_texture_dir_file_name = (wchar_t*)calloc(StrLength + 2, sizeof(char));

	//マルチバイト文字列 → ワイド文字列に変換含む（[\0]までコピー）
	mbstowcs(w_texture_dir_file_name, texture_dir_file_name, _mbstrlen(texture_dir_file_name) + 1);

	//////////////////////////////////////////
	// [GDI+]を使用してテクスチャを読み込み

	//GDI+の初期化
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&token, &input, NULL);

	//テクスチャ読み込み
	Gdiplus::Bitmap* Texture = new Gdiplus::Bitmap(w_texture_dir_file_name);

	//テクスチャを読み込んだのでファイルパスを保存していたメモリを開放する
	free(texture_dir_file_name);
	free(w_texture_dir_file_name);

	//テクスチャデータ読み込み
	Gdiplus::BitmapData BitmapData;
	if (0 != Texture->LockBits(0, Gdiplus::ImageLockModeRead, p_PixelFotmat, &BitmapData))
	{
		printf("失敗\n");
		ERROR_MESSAGE("テクスチャファイルの読み込みに失敗しました。\n"\
			"「Resource/Texture/」フォルダに格納されていますか？\n"\
			"ファイル名が間違っていませんか？");
		return;
	}

	/////////////////////////////////////////////////
	// 返却する情報の設定
	switch (p_PixelFotmat)
	{
	case PIXELFORMAT_24BIT_RGB:
		p_TextureData->internalFormat = GL_RGB;
		p_TextureData->format = GL_RGB;
		break;

	case PIXELFORMAT_32BIT_RGBA:
		p_TextureData->internalFormat = GL_RGBA;
		p_TextureData->format = GL_RGBA;
		break;
	default:
		printf("失敗\n");
		ERROR_MESSAGE("ピクセルフォーマットの引数が不正です。\n"\
			"p_PixelFotmat = %d", p_PixelFotmat);
		return;
	}

	p_TextureData->width = (GLsizei)BitmapData.Width;
	p_TextureData->height = (GLsizei)BitmapData.Height;
	p_TextureData->border = 0;
	p_TextureData->type = GL_UNSIGNED_BYTE;
	p_TextureData->data = (GLvoid*)calloc(BitmapData.Height * BitmapData.Stride, sizeof(byte));

	//ロードしたテクスチャは「BGR」で格納されているので「RGB」に変換しつつコピーする
	TextureDataBRGtoRGB(p_PixelFotmat, &BitmapData, p_TextureData);

	//読み込んだテクスチャ情報/データを破棄する
	Texture->UnlockBits(&BitmapData);
	delete Texture;

	//GDI+の終了
	Gdiplus::GdiplusShutdown(token);

	printf("完了\n");
}


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
void Texture::TextureDataBRGtoRGB(const int p_PixelFotmat, const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData)
{
	//1色分の情報のバイト数
	int ColorByte = 0;

	//画像のフォーマットから1色分の情報のバイト数を決定
	if (PIXELFORMAT_24BIT_RGB == p_PixelFotmat)
	{
		ColorByte = 3;
	}
	else if (PIXELFORMAT_32BIT_RGBA)
	{
		ColorByte = 4;
	}

	//高さピクセル分繰り返す
	for (unsigned int Height = 0; Height < p_BitmapData->Height; Height++)
	{
		//幅ピクセル × カラー色分繰り返す（幅分の変換量となる）
		for (unsigned int Width = 0; Width < p_BitmapData->Width * ColorByte; Width = Width + ColorByte)
		{
			//変換する1画素の先頭位置を算出する
			//（画像は4 バイト境界を意識して格納されているのでそれも考慮する）
			unsigned int DataPos = (Height * p_BitmapData->Stride) + Width;

			//R成分をコピー
			memmove((byte*)p_TextureData->data + DataPos, (byte*)p_BitmapData->Scan0 + DataPos + 2, sizeof(byte));

			//G成分を一時的に保存
			memmove((byte*)p_TextureData->data + DataPos + 1, (byte*)p_BitmapData->Scan0 + DataPos + 1, sizeof(byte));

			//B成分を一時的に保存
			memmove((byte*)p_TextureData->data + DataPos + 2, (byte*)p_BitmapData->Scan0 + DataPos, sizeof(byte));
		}
	}
}