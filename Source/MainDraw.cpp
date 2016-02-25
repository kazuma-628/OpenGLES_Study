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

	//シェーダー内で使用する変数を取得します（オブジェクト移動用のマトリックス）
	m_ModelView_matrix = m_MainShader->GetUniformLocation("ModelView_matrix");

	//シェーダー内で使用する変数を取得します（3D空間にするためのマトリクス）
	m_Proj_matrix = m_MainShader->GetUniformLocation("Proj_matrix");

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
	Matrix ModelView;

	Matrix Projection;

	//座標を弄る用の変数
	double x_pos = 0;
	double y_pos = 0;
	double x_pos2 = 0;
	double y_pos2 = 0;

	//マウスの座標を取得します。
	//ウィンドウ系の座標が入ります。
	glfwGetCursorPos(p_window, &x_pos, &y_pos);

	//ウィンドウ座標が、-10～10にマッチするように変換します。
	x_pos2 = (20.0 / WINDOW_WIDTH) * x_pos - 10.0;
	y_pos2 = (20.0 / WINDOW_HEIGHT) * (WINDOW_HEIGHT - y_pos) - 10.0;

	//デバッグ用プリント文
//	printf("x_pos = %lf x_pos2 = %lf y_pos = %lf y_pos2 = %lf\n", x_pos, x_pos2, y_pos, y_pos2);

	//カメラの映る位置に移動させ、マウスでも移動できるようにする。
	ModelView.Translate(x_pos2, y_pos2, -20.0);
	
	//回転させる
	ModelView.Rotate(1000 * move_y, 0.0, 1.0, 0.0);
	
	//移動量を増加させる。
//	move_x = move_x + 0.001f;
	move_y = move_y + 0.001f;

	//値をリセットする（動作確認用の一時的なプログラム）
	if (move_x > 10 || move_y > 10 )
	{
		move_x = move_y = 0;
	}

	//透視投影行列を適用する
	Projection.Perspective(-10.0, 10.0, -10.0, 10.0, 10.0, 30.0);

	//シェーダーの変数を有効化
	glEnableVertexAttribArray(m_attr_pos);
	glEnableVertexAttribArray(m_attr_color);


	// 画面中央へ描画する
	const GLfloat position[] =
	{
		// v0
		-10.0f, 10.0f, 0.0f,
		// v1
		10.0f, 10.0f, 0.0f,
		// v2
		10.0f, -10.0f, 0.0f,
		// v3
		-10.0f, -10.0f, 0.0f
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
	glVertexAttribPointer(m_attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	glVertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	glUniformMatrix4fv(m_ModelView_matrix, 1, GL_FALSE, ModelView.GetMatrix());
	glUniformMatrix4fv(m_Proj_matrix, 1, GL_FALSE, Projection.GetMatrix());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//描画処理
	glfwSwapBuffers(p_window);
}

