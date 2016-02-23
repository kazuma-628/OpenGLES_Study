#include "MainDraw.h"

//コンストラクタ
MainDraw::MainDraw()
{
	//Mainシェーダー管理用のオブジェクト生成
	m_MainShader = new ShaderManager;

	//移動量管理の変数初期化
	move_x = 0;
	move_y = 0;
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
void MainDraw::Prep()
{
	//シェーダーの読み込みを行う
	//「Shader」フォルダに格納されている必要があります。
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag");

	//シェーダー内で使用する変数を取得します（頂点データ）
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//シェーダー内で使用する変数を取得します（カラーデータ）
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//シェーダー内で使用する変数を取得します（マトリックスデータ）
	m_move_matrix = m_MainShader->GetUniformLocation("move_matrix");

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

	//オブジェクトを移動させるための行列を宣言
	Matrix Move;

	//指定量移動させる
	Move.Translate(move_x, move_y, 0.5);
	Move.Scale(move_x, move_y, 0.5);
	Move.Rotate(1000 * move_x * move_y, 1.0, 0.0, 0.0);

	//移動量を増加させる。
	move_x = move_x + 0.001f;
	move_y = move_y + 0.001f;

	//値をリセットする（動作確認用の一時的なプログラム）
	if (move_x > 1.0 || move_y > 1.0)
	{
		move_x = move_y = 0;
	}

	//シェーダーの変数を有効化
	glEnableVertexAttribArray(m_attr_pos);
	glEnableVertexAttribArray(m_attr_color);


	// 画面中央へ描画する
	const GLfloat position[] =
	{
		// v0
		-0.8f, 0.0f,
		// v1
		0.0f, 0.0f,
		// v2
		0.0f, -0.8f,
		// v3
		-0.8f, -0.8f
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
	glUniformMatrix4fv(m_move_matrix, 1, GL_FALSE, Move.GetMatrix());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//描画処理
	glfwSwapBuffers(p_window);
}

