#include "HelloWorld.h"

//コンストラクタ
HelloWorld::HelloWorld()
{
	//変数初期化
	m_MainShader = NULL;
	PrepareFlag = false;

	m_attr_pos = -1;
	m_attr_color = -1;
	m_ProjModel_matrix = 0;

}

//デストラクタ
HelloWorld::~HelloWorld()
{
	//Mainシェーダー管理用のオブジェクト破棄
	delete m_MainShader;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ハローワールド描画（OpenGLの基本的な描画）の準備をする
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void HelloWorld::Prepare()
{
	//描画準備が未完了の場合
	if (false == PrepareFlag)
	{
		//データが作成されていなければ
		if (NULL == m_MainShader)
		{
			//Mainシェーダー管理用のオブジェクト生成
			m_MainShader = new ShaderManager;

			//シェーダーの読み込みを行う
			//「Shader」フォルダに格納されている必要があります。
			m_MainShader->CreateShaderProgram("HelloWorld.vert", "HelloWorld.frag", NULL, NULL, NULL, NULL);

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
		PrepareFlag = true;
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ハローワールド描画（OpenGLの基本的な描画）を開始する
*	引数
*	　p_Global			：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void HelloWorld::Drawing(const GlobalData &p_Global)
{
	//描画準備
	Prepare();

	// シェーダープログラムの利用を開始する
	m_MainShader->UseProgram();

	//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
	mat4 ProjModel;
	ProjModel = p_Global.ProjectionMatrix * p_Global.ModelViewMatrix;

	//シェーダーの変数を有効化
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	//穴あきキューブ形状のモデルデータを作成する
	// 頂点データ
	Vec3_bColor3 vertex[] =
	{
		// v0
		{ { -10.0f, -10.0f, 10.0f },{ 50, 50, 50 } },
		// v1
		{ { -10.0f, -10.0f, -10.0f },{ 90, 0, 0 } },
		// v2
		{ { -10.0f, 10.0f, 10.0f },{ 0, 90, 0 } },
		// v3
		{ { -10.0f, 10.0f, -10.0f },{ 0, 0, 90 } },
		// v4
		{ { 10.0f, 10.0f, 10.0f },{ 130, 0, 0 } },
		// v5
		{ { 10.0f, 10.0f, -10.0f },{ 0, 130, 0 } },
		// v6
		{ { 10.0f, -10.0f, 10.0f },{ 0, 0, 130 } },
		// v7
		{ { 10.0f, -10.0f, -10.0f },{ 170, 0, 0 } },
		// v8
		{ { -10.0f, -10.0f, 10.0f },{ 0, 170, 0 } },
		// v9
		{ { -10.0f, -10.0f, -10.0f },{ 0, 0, 170 } },
		// v10
		{ { -10.0f, -10.0f, -10.0f },{ 210, 0, 0 } },
		// v11
		{ { -10.0f, 10.0f, -10.0f },{ 0, 210, 0 } },
		// v12
		{ { 10.0f, -10.0f, -10.0f },{ 0, 0, 210 } },
		// v13
		{ { 10.0f, 10.0f, -10.0f },{ 250, 0, 0 } },
	};

	//震度テストを有効
	glEnable(GL_DEPTH_TEST);

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, p_Global.WindowSize.Width, p_Global.WindowSize.Height);

	//変数を転送
	m_MainShader->UniformMatrixXfv(m_ProjModel_matrix, 4, 1, GL_FALSE, &ProjModel);

	// [glDrawArrays]を使用した描画（一番オーソドックス（初歩的）な描画方法）
	m_MainShader->VertexAttribPointer(m_attr_pos, sizeof(vertex[0].Vector) / sizeof(vertex[0].Vector.x), GL_FLOAT, GL_FALSE, sizeof(Vec3_bColor3), (GLvoid*)&vertex[0].Vector);
	m_MainShader->VertexAttribPointer(m_attr_color, sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r), GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vec3_bColor3), (GLvoid*)&vertex[0].Color);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertex) / sizeof(vertex[0]));

	//シェーダーの変数を無効化
	m_MainShader->DisableVertexAttribArray(m_attr_pos);
	m_MainShader->DisableVertexAttribArray(m_attr_color);
}

