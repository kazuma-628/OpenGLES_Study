#include "MainDraw.h"

//コンストラクタ
MainDraw::MainDraw()
{
	//Mainシェーダー管理用のオブジェクト生成
	m_MainShader = new ShaderManager;

	//変数初期化
	memset(&m_Rotate, 0, sizeof(m_Rotate));
	memset(&m_Translate, 0, sizeof(m_Translate));
	m_attr_pos = -1;
	m_attr_color = -1;
	m_ModelView_matrix = 0;
	m_Proj_matrix = 0;

}

//デストラクタ
MainDraw::~MainDraw()
{
	//Mainシェーダー管理用のオブジェクト破棄
	delete m_MainShader;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　メイン描画の準備をする
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void MainDraw::Prepare()
{
	//シェーダーの読み込みを行う
	//「Shader」フォルダに格納されている必要があります。
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag");

	//シェーダー内で使用する変数を取得します（頂点データ）
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//シェーダー内で使用する変数を取得します（カラーデータ）
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//シェーダー内で使用する変数を取得します（オブジェクト移動用のマトリックス）
	m_ModelView_matrix = m_MainShader->GetUniformLocation("ModelView_matrix");

	//シェーダー内で使用する変数を取得します（3D空間にするためのマトリクス）
	m_Proj_matrix = m_MainShader->GetUniformLocation("Proj_matrix");

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　メイン描画を開始する
*	引数
*	　p_WindowManager		：[I/ ]　ウィンドウ管理オブジェクト
*	　p_KeyManager			：[I/ ]　Key管理オブジェクト
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(WindowManager* p_WindowManager, KeyManager* p_KeyManager)
{
	//作成したウィンドウハンドルを取得
	GLFWwindow* const window = p_WindowManager->GetWindow();
	//マウスの情報を取得
	MouseInfo MouseButton = p_KeyManager->GetMouseInfo();
	//キー（キーボード）の情報を取得
	KeyInfo KeyBoard = p_KeyManager->GetKeyInfo();
	
	// シェーダープログラムの利用を開始する
	m_MainShader->UseProgram();

	//オブジェクトを移動させるための行列
	Matrix ModelView;

	//3D空間にするための行列
	Matrix Projection;


	///////////////////////////////////
	// オブジェクト移動関係の処理

	//平行移動用の変数にマウス情報の座標を加える
	m_Translate.x = m_Translate.x + MouseButton.Left.DiffPos.x;
	m_Translate.y = m_Translate.y + MouseButton.Left.DiffPos.y;
	m_Translate.z = m_Translate.z + MouseButton.Scroll;
	//回転用の変数にマウス情報の座標を加える
	//本来であれば360度回転したら変数を初期化した方が良いが、サンプルなので割愛
	m_Rotate.x = m_Rotate.x + MouseButton.Right.DiffPos.x;
	m_Rotate.y = m_Rotate.y + MouseButton.Right.DiffPos.y;

	//カメラの映る位置に移動させる
	ModelView.Translate(0.0, 0.0, -35.0f);
	//マウスでのオブジェクトの移動
	ModelView.Translate(m_Translate.x / 6.0f, -m_Translate.y / 6.0f, m_Translate.z);
	
	//マウスでのオブジェクトの回転
	ModelView.Rotate(-m_Rotate.x / 2.0f, 0.0f, 1.0f, 0.0f);
	ModelView.Rotate(-m_Rotate.y / 2.0f, 1.0f, 0.0f, 0.0f);
	//四角の穴が目の前に現れるように回転
	ModelView.Rotate(-90, 0.0f, 1.0f, 0.0f);

	
	//透視投影行列を適用する
	Projection.Perspective(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

	//シェーダーの変数を有効化
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	// 画面中央へ描画する
	const GLfloat position[] =
	{
		// v1
		-10.0f, 10.0f, 10.0f,
		// v2
		10.0f, 10.0f, 10.0f,
		// v3
		-10.0f, -10.0f, 10.0f,
		// v4
		10.0f, -10.0f, 10.0f,

		// v5
		-10.0f, -10.0f, -10.0f,
		// v6
		10.0f, -10.0f, -10.0f,

		// v7
		-10.0f, 10.0f, -10.0f,
		// v8
		10.0f, 10.0f, -10.0f,

		// v9
		-10.0f, 10.0f, 10.0f,
		// v10
		10.0f, 10.0f, 10.0f,

		// v11
		10.0f, 10.0f, 10.0f,
		// v12
		10.0f, -10.0f, 10.0f,
		// v13
		10.0f, 10.0f, -10.0f,
		// v14
		10.0f, -10.0f, -10.0f,
	};

	// 頂点カラーを設定する
	const GLubyte color[] =
	{
		// v1 rgb
		50, 50, 50,
		// v2 rgb
		90, 0, 0,
		// v3 rgb
		0, 90, 0,
		// v4 rgb
		0, 0, 90,

		// v5 rgb
		130, 0, 0,
		// v6 rgb
		0, 130, 0,

		// v7 rgb
		0, 0, 130,
		// v8 rgb
		170, 0, 0,

		// v9 rgb
		0, 170, 0,
		// v10 rgb
		0, 0, 170,

		// v11 rgb
		210, 0, 0,
		// v12 rgb
		0, 210, 0,
		// v13 rgb
		0, 0, 210,
		// v14 rgb
		250, 0, 0,
	};

	//震度テストを有効
	glEnable(GL_DEPTH_TEST);

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//変数を転送
	m_MainShader->VertexAttribPointer(m_attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	m_MainShader->VertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	m_MainShader->glUniformMatrixXfv(m_ModelView_matrix, 4, 1, GL_FALSE, ModelView.GetMatrix());
	m_MainShader->glUniformMatrixXfv(m_Proj_matrix, 4, 1, GL_FALSE, Projection.GetMatrix());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

	//描画処理
	glfwSwapBuffers(window);
}

