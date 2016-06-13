#include "ResourceManager.h"

//コンストラクタ
ResourceManager::ResourceManager()
{
	m_AttribInfoIndex = 0;
	memset(m_TextureData, 0, sizeof(m_TextureData));
}

//デストラクタ
ResourceManager::~ResourceManager()
{
	//読み込み済みかを検索する
	for (int index = 0; index < TEXTURE_DATA_MAX; index++)
	{
		if (0 == strlen(m_TextureData[index].Name))
		{
			//読み込み済みの画像データは開放する
			free(m_TextureData[index].PixelData);
		}
	}
}

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
TextureData* ResourceManager::TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat)
{

	//一時的に使用するテクスチャデータ変数
	TextureData* t_TextureData;

	//既に画像ファイルからテクスチャデータの読み込みが完了しているか検索
	t_TextureData = TextureDataSearch(p_FileName);

	//既に読み込み済みの場合
	if (NULL != t_TextureData)
	{
		//読み込み済みのテクスチャデータを返却
		return t_TextureData;
	}
	else
	{
		printf("テクスチャ「%s」の新規読み込みを開始します...", p_FileName);

		//GDI+の初期化
		ULONG_PTR token;
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartup(&token, &input, NULL);

		char Dir_FileName[TEXTURE_FILE_NAME_MAX] = SHADER_FILE_DIR;

		strcat(Dir_FileName, p_FileName);

		//テクスチャ情報読み込み（マルチバイト文字列 → ワイド文字列に変換含む）
		wchar_t wchar_FileName[TEXTURE_FILE_NAME_MAX] = { 0 };
		size_t length;
		mbstowcs_s(&length, wchar_FileName, Dir_FileName, TEXTURE_FILE_NAME_MAX);
		Gdiplus::Bitmap* Texture = new Gdiplus::Bitmap(wchar_FileName);

		//テクスチャデータ読み込み
		Gdiplus::BitmapData BitmapData;
		if (0 != Texture->LockBits(0, Gdiplus::ImageLockModeRead, p_PixelFotmat, &BitmapData))
		{
			printf("失敗\n");
			ERROR_MESSAGE("テクスチャファイルの読み込みに失敗しました。\n"\
				"「Resource」フォルダに格納されていますか？\n"\
				"ファイル名が間違っていませんか？");
		}

		/////////////////////////////////////////////////
		// 返却する情報の設定

		memmove(m_TextureData[m_AttribInfoIndex].Name, p_FileName, strlen(p_FileName));
		m_TextureData[m_AttribInfoIndex].Width = BitmapData.Width;
		m_TextureData[m_AttribInfoIndex].Height = BitmapData.Height;
		m_TextureData[m_AttribInfoIndex].PixelFormat = BitmapData.PixelFormat;
		m_TextureData[m_AttribInfoIndex].PixelData = calloc(BitmapData.Height * BitmapData.Stride, sizeof(byte));

		//ロードしたテクスチャは「BGR」で格納されているので「RGB」に変換しつつコピーする
		TextureDataBRGtoRGB(&BitmapData, m_TextureData, p_PixelFotmat);

		//情報を設定したのでテクスチャ変数管理用のインデックス値をインクリメントする
		m_AttribInfoIndex++;

		//読み込んだテクスチャ情報/データを破棄する
		Texture->UnlockBits(&BitmapData);
		delete Texture;

		//GDI+の終了
		Gdiplus::GdiplusShutdown(token);

		printf("完了\n");
	}

	//今回設定したデータを返却
	return &m_TextureData[m_AttribInfoIndex - 1];
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　既に画像ファイルからテクスチャデータの読み込みが完了しているか検索します
*	　読み込みが完了している場合はそのデータを返します
*	引数
*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きの画像ファイル名（[例] texture.png）　
*	戻り値
*	　テクスチャデータを既に読み込んでいる場合
*		→テクスチャデータ（幅,高さ,ピクセルデータなど → 詳細は[TextureData]構造体参照）
*	　テクスチャデータがまだ読み込まれていない場合
*		→NULL
*-------------------------------------------------------------------------------*/
TextureData* ResourceManager::TextureDataSearch(const char* p_FileName)
{
	//読み込み済みかを検索する
	for (int index = 0; index < TEXTURE_DATA_MAX; index++)
	{
		if (0 == strncmp(m_TextureData[index].Name, p_FileName, TEXTURE_FILE_NAME_MAX))
		{
			return &m_TextureData[index];
		}
	}

	return NULL;
}

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
void ResourceManager::TextureDataBRGtoRGB(const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData, const int p_PixelFotmat)
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
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos, (byte*)p_BitmapData->Scan0 + DataPos + 2, sizeof(byte));

			//G成分を一時的に保存
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos + 1, (byte*)p_BitmapData->Scan0 + DataPos + 1, sizeof(byte));

			//B成分を一時的に保存
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos + 2, (byte*)p_BitmapData->Scan0 + DataPos, sizeof(byte));
		}
	}
}