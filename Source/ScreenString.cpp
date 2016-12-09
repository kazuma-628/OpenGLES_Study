#include "ScreenString.h"

/////////////////////////////////////////////
//static変数の実体を定義

ShaderManager *(ScreenString::m_StringShader) = NULL;	//文字列描画シェーダー
GLint ScreenString::m_attr_pos = -1;					//頂点座標
GLint ScreenString::m_unif_tex = -1;					//テクスチャ
GLint ScreenString::m_attr_tex_coord = -1;				//テクスチャ座標
GLint ScreenString::m_unif_char_color = -1;				//文字カラー
GLint ScreenString::m_unif_back_color = -1;				//背景カラー

FT_Library ScreenString::m_ft_Library = { 0 };			//FreeTypeライブラリ
FT_Face ScreenString::m_ft_Face = { 0 };				//FreeTypeのフォントフェース

std::vector<GLchar> ScreenString::DebugString;			//デバッグ表示用の文字列データ

unsigned int ScreenString::DebugMaxWidth = 0;			//デバッグ表示用の文字列の最大幅
unsigned int ScreenString::DebugSumRows = 0;			//デバッグ表示用の文字列の合計高さ（＝最大高さ）

//コンストラクタ
ScreenString::ScreenString()
{

}

//デストラクタ
ScreenString::~ScreenString()
{

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　画面上に文字列を表示するための準備をします
*	引数
*	　p_Global		：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ScreenString::Prepare(const GlobalData &p_Global)
{
	//データが作成されていなければ
	if (NULL == m_StringShader)
	{
		//文字列描画シェーダー管理用のオブジェクト生成
		m_StringShader = new ShaderManager;

		//シェーダーの読み込みを行う
		m_StringShader->CreateShaderProgram("ScreenString.vert", "ScreenString.frag", NULL, NULL, NULL, NULL);

		//シェーダー内で使用する変数を取得します（頂点座標）
		m_attr_pos = m_StringShader->GetAttribLocation("attr_pos");

		//シェーダー内で使用する変数を取得します（テクスチャ）
		m_unif_tex = m_StringShader->GetUniformLocation("unif_tex");

		//シェーダー内で使用する変数を取得します（テクスチャ座標）
		m_attr_tex_coord = m_StringShader->GetAttribLocation("attr_tex_coord");

		//シェーダー内で使用する変数を取得します（文字カラー）
		m_unif_char_color = m_StringShader->GetUniformLocation("unif_string_color");

		//シェーダー内で使用する変数を取得します（背景文字列）
		m_unif_back_color = m_StringShader->GetUniformLocation("unif_back_color");

		//FreeTypeライブラリの初期化
		FT_Init_FreeType(&m_ft_Library);

		//フォントファイルを読み込む
		FT_New_Face(m_ft_Library, FT_FONT_FILE, 0, &m_ft_Face);

		RePrepare(p_Global);
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　資源の再準備
*	引数
*	　p_Global		：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ScreenString::RePrepare(const GlobalData &p_Global)
{
	//サイズを変更して初期化する
	DebugString.assign(p_Global.WindowSize.x * p_Global.WindowSize.y, 0);

	//本当はここで[shrink_to_fit]を呼び、余分なメモリ解放するべき
	//（VisualStudio2013(C++11)からしか対応してないので、ひとまず互換性を優先して放置）
}


/*-------------------------------------------------------------------------------
*	関数説明
*	　破棄(終了)処理（変数などを破棄します）
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ScreenString::Destroy(void)
{
	//文字列描画シェーダー管理用のオブジェクト破棄
	SAFE_DELETE(m_StringShader);

	//FreeTypeのデータを破棄
	FT_Done_Face(m_ft_Face);
	FT_Done_FreeType(m_ft_Library);
}

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
void ScreenString::DebugPrint(const GlobalData &p_Global, const char* p_String, ...)
{
	//引数チェック
	if (NULL == p_String)
	{
		ERROR_MESSAGE("画面上にデバック表示（設定）をする 引数エラー\n" \
			"p_String = %x\n", (unsigned int)p_String);
		return;
	}

	//////////////////////////////////////////
	// マルチバイト文字 から ワイド文字 に変換

	//1回関数コールで描画出来る文字数を設定
	//※ 本当はちゃんと[va_arg]で内容を把握してメモリ確保しながらやったほうがいい、とりあえず暫定※
	char AllString[256] = { 0 };

	//可変個数引数のリストを初期化
	//[p_String]より後ろの全引数をリストに格納する
	va_list args;
	va_start(args, p_String);

	//可変長引数リストのデータを文字配列に書き込む
	vsprintf(AllString, p_String, args);

	//可変引数の取り出し処理を終了する
	va_end(args);

	//////////////////////////////////////////
	// マルチバイト文字 から ワイド文字 に変換

	wchar_t *w_String = NULL;	//テクスチャファイルへのパス（ワイド文字）
	int StrLength = 0;			//読み込むテクスチャファイル名の長さ（バイト数）

	//ロケールを日本に設定
	setlocale(LC_CTYPE, "jpn");

	//マルチバイト文字の文字数を取得して、ワイド文字に変換した場合のバイト数を算出する
	StrLength = _mbstrlen(AllString) * 2;

	// 文字列の長さを取得してメモリ確保（終端を明確にするため +2(ワイド文字なので) する。[\0]となる）
	w_String = (wchar_t*)calloc(StrLength + 2, sizeof(char));

	//マルチバイト文字列 → ワイド文字列に変換（[\0]までコピー）
	mbstowcs(w_String, AllString, _mbstrlen(AllString) + 1);

	//////////////////////////////////////////
	// FreeTypeで文字をラスタライズ

	unsigned int DebugSumWidth = WIDTH_SPACING;		//デバッグ表示用の文字列の合計幅
	FT_Bitmap bitmap;		//FreeTypeでラスタライズしたビットマップデータ

	//ビットマップフォントのサイズ（幅と高さ）を指定
	//第2引数（幅）、第3引数(高さ）のどちらかが[0]のときはもう一方の値と同じになる
	FT_Set_Pixel_Sizes(m_ft_Face, 0, DEBUG_FONT_SIZE);

	//文字数分ループして文字列を作り出す
	for (int index = 0; L'\0' != w_String[index]; index++)
	{
		//FreeTypeで処理しても結果が得られないものがあるので自前で処理する
		switch (w_String[index])
		{
		case L'　':
			//全角空白相当を文字列の合計幅に加算
			DebugSumWidth += DEBUG_ROWS_SPACING / 2;
			break;

		case L' ':
			//半角空白相当を文字列の合計幅に加算
			DebugSumWidth += DEBUG_ROWS_SPACING / 4;
			break;

		case L'\n':
			//改行のため文字列の合計高さを加算
			DebugSumRows += DEBUG_ROWS_SPACING;

			//今の行の合計幅が今までの合計幅より大きかったら更新する
			if (DebugSumWidth > DebugMaxWidth)
			{
				DebugMaxWidth = DebugSumWidth;
			}

			//改行なので合計幅を初期化する
			DebugSumWidth = WIDTH_SPACING;

			break;

		default:
			//1文字ラスタライズ
			FT_Load_Char(m_ft_Face, w_String[index], FT_LOAD_RENDER);

			//ラスタライズ結果のビットマップ情報を取得
			bitmap = m_ft_Face->glyph->bitmap;

			//文字がウィンドウの幅を超えるのであれば改行する
			if (DebugSumWidth + bitmap.width >= (unsigned int)p_Global.WindowSize.x)
			{
				//改行のため文字列の合計高さを加算
				DebugSumRows += DEBUG_ROWS_SPACING;

				//今の行の合計幅が今までの合計幅より大きかったら更新する
				if (DebugSumWidth > DebugMaxWidth)
				{
					DebugMaxWidth = DebugSumWidth;
				}

				//改行なので合計幅を初期化する
				DebugSumWidth = WIDTH_SPACING;
			}
			
			//ラスタライズ結果のピクセル分ループ
			for (unsigned int Rows = 0; Rows < bitmap.rows; Rows++)
			{
				for (unsigned int Width = 0; Width < bitmap.width; Width++)
				{
					//文字を格納する場所を計算する
					int PixelPos =
						//高さの計算
						(((DebugSumRows + Rows) + (DEBUG_FONT_SIZE - m_ft_Face->glyph->bitmap_top)) * p_Global.WindowSize.x)
						// 幅の計算
						+ (DebugSumWidth + Width);

					//ウィンドウサイズサイズ内のみ表示する
					if (PixelPos < p_Global.WindowSize.x * p_Global.WindowSize.y)
					{
						//ピクセルデータを格納する
						DebugString[PixelPos] = bitmap.buffer[(Rows * bitmap.width) + Width];
					}
				}
			}

			//描画したピクセル幅を、文字列の合計幅に加算する（[+CHAR_SPACING]は文字間の空白分の値）
			DebugSumWidth += bitmap.width + WIDTH_SPACING;
			break;
		}
	}

	//メモリ解放
	SAFE_FREE(w_String);
	
	//デバッグ表示がコールされるたびに改行を行う
	//改行のため文字列の合計高さを加算
	DebugSumRows += DEBUG_ROWS_SPACING;
	
	//今の行の合計幅が今までの合計幅より大きかったら更新する
	if (DebugSumWidth > DebugMaxWidth)
	{
		DebugMaxWidth = DebugSumWidth;
	}

}


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
void ScreenString::DebugDrawing(const GlobalData &p_Global)
{
	//デバッグ文字列がない場合は描画命令しない
	if(0 == DebugMaxWidth)
	{
		return;
	}

	// シェーダープログラムの利用を開始する
	m_StringShader->UseProgram();

	////////////////////////////////
	// テクスチャの用意

	//テクスチャオブジェクト生成
	GLuint TextureObj;
	glGenTextures(1, &TextureObj);

	//ユニットを指定してからバインド
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureObj);

	//ピクセル格納モードを設定（FreeTypeは1バイトづつ入っている）
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//テクスチャデータアップロード
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, p_Global.WindowSize.x, p_Global.WindowSize.y, 0, GL_RED, GL_UNSIGNED_BYTE, (void*)&DebugString[0]);

	//パラメータ設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	////////////////////////////////
	// 頂点の設定

	//フォントの描画エリアの最大幅・高さを、[pixel単位]から[0～1]に変換（シェーダーでの頂点指定用）
	GLfloat CoordWidth = (GLfloat)DebugMaxWidth / p_Global.WindowSize.x;
	GLfloat CoordRows = (GLfloat)DebugSumRows / p_Global.WindowSize.y;

	// 頂点座標
	vec2 vertex[] =
	{
		{ -1.0f	,					-(CoordRows * 2.0f - 1.0f) },
		{ CoordWidth * 2.0f - 1.0f, -(CoordRows * 2.0f - 1.0f) },
		{ -1.0f	,					1.0f					   },
		{ CoordWidth * 2.0f - 1.0f, 1.0f					   },
	};

	//テクスチャ座標
	vec2 tex_coord[] =
	{
		{ 0.0f,		  CoordRows },
		{ CoordWidth, CoordRows },
		{ 0.0f,		  0.0f		},
		{ CoordWidth, 0.0f		},
	};

	////////////////////////////////
	// 描画設定・描画

	//ビューポートを設定する
	glViewport(0, 0, p_Global.WindowSize.x, p_Global.WindowSize.y);

	//ブレンドを有効にする
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//シェーダーの変数を有効化
	m_StringShader->EnableVertexAttribArray(m_attr_pos);
	m_StringShader->EnableVertexAttribArray(m_attr_tex_coord);

	//テクスチャのユニット設定
	m_StringShader->UniformXi(m_unif_tex, 1, 0, 0, 0, 0);

	//頂点を設定
	m_StringShader->VertexAttribPointer(m_attr_pos, 2, GL_FLOAT, GL_FALSE, 0, vertex);

	//テクスチャ座標を設定
	m_StringShader->VertexAttribPointer(m_attr_tex_coord, 2, GL_FLOAT, GL_FALSE, 0, tex_coord);

	//文字色を設定
	m_StringShader->UniformXf(m_unif_char_color, 4, 1.0, 1.0, 1.0, 1.0);

	//背景色を設定
	m_StringShader->UniformXf(m_unif_back_color, 4, 0.0, 0.0, 0.0, 0.5);

	//描画
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	////////////////////////////////
	// 後処理

	//破棄処理
	glDeleteTextures(1, &TextureObj);

	//パラメータを元に戻す（普通は4バイトごと、多分）
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	//ブレンドを無効にする
	glDisable(GL_BLEND);

	//シェーダーの変数を無効化
	m_StringShader->DisableVertexAttribArray(m_attr_pos);
	m_StringShader->DisableVertexAttribArray(m_attr_tex_coord);

	//デバッグ表示を描画したので、関連する変数を初期化する
	DebugMaxWidth = 0;
	DebugSumRows = 0;
	RePrepare(p_Global);
}