#include "MainDraw.h"

//コンストラクタ
MainDraw::MainDraw()
{
	//Mainシェーダー用のオブジェクト生成
	m_MainShader = new ShaderManager;
}

//デストラクタ
MainDraw::~MainDraw()
{
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
void MainDraw::Prep()
{
	//シェーダーの読み込みを行う
	//「Shader」フォルダに格納されている必要があります。
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag");

	//シェーダー内で使用する変数を取得します（頂点データ）
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//シェーダー内で使用する変数を取得します（カラーデータ）
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　メイン描画を開始する
*	引数
*	　window		：[I/ ]　描画先のウィンドウを指定する
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void MainDraw::Draw(GLFWwindow *const p_window)
{
	// シェーダープログラムの利用を開始する
	m_MainShader->UseProgram();

	//シェーダーの変数を有効化
	glEnableVertexAttribArray(m_attr_pos);
	glEnableVertexAttribArray(m_attr_color);


	// 画面中央へ描画する
	const GLfloat position[] =
	{
		// v0
		-0.5f, 0.5f,
		// v1
		0.5f, 0.5f,
		// v2
		0.5f, -0.5f,
		// v3
		-0.5, -0.5
	};

	// 頂点カラーを設定する
	const GLubyte color[] =
	{
		// v0 rgb
		200, 200, 200,
		// v1 rgb
		200, 0, 0,
		// v2 rgb
		0, 200, 0,
		// v3 rgb
		0, 0, 200
	};

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//変数を転送
	glVertexAttribPointer(m_attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	glVertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//描画処理
	glfwSwapBuffers(p_window);
}

