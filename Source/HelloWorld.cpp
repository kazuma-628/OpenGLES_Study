#include "HelloWorld.h"
#include "ShaderManager.h"

//コンストラクタ
HelloWorld::HelloWorld()
{
}

//デストラクタ
HelloWorld::~HelloWorld()
{
}

void HelloWorld::TestFunc0(const GlobalData &p_Global) {
	std::this_thread::sleep_for(std::chrono::seconds(100));
	int aaa = 10;
}

void HelloWorld::TestFunc2(const GlobalData &p_Global) {
	//ここでおかしなことになる（例外で落ちてんのかなー）
	abcdefg_.join();		//[abcdefg_]はメンバ変数
	int aaa = 20;
}

void HelloWorld::TestFunc(const GlobalData &p_Global) {
	std::thread hijklmn([&] { TestFunc2(p_Global); });

	hijklmn.join();
}

//ここがはじめに呼ばれる
void HelloWorld::Drawing(const GlobalData &p_Global)
{
	abcdefg_ = std::thread([&] { TestFunc0(p_Global); });		//[abcdefg_]はメンバ変数
	TestFunc(p_Global);
}


/*-------------------------------------------------------------------------------
*	関数説明
*	　ハローワールド描画（OpenGLの基本的な描画）の準備をする
*	引数
*	　p_Global			：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void HelloWorld::Prepare(const GlobalData &p_Global)
{
	//描画準備が未完了の場合
	if (false == PrepareCompFlag)
	{
		//データが作成されていなければ
		if (nullptr == m_MainShader)
		{
			//Mainシェーダー管理用のオブジェクト生成
			m_MainShader = make_shared<ShaderManager>();

			//シェーダーの読み込みを行う
			//「Shader」フォルダに格納されている必要があります。
			m_MainShader->CreateShaderProgram("HelloWorld.vert", "HelloWorld.frag", "", "", "", nullptr);

			///////////////////////////////////////////////////
			// シェーダー内で使用する変数のロケーションを取得

			//頂点データ
			m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

			//カラーデータ
			m_attr_color = m_MainShader->GetAttribLocation("attr_color");

			//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
			m_ProjModel_matrix = m_MainShader->GetUniformLocation("ProjModel_matrix");
		}

		//描画準備完了とする
		PrepareCompFlag = true;
	}
}




