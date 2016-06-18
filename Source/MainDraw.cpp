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
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag", "Main.geom");

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
*	　p_DeviceManager		：[I/ ]　Key管理オブジェクト
*	　p_ResourceManager		：[I/ ]　リソース管理オブジェクト
*	  p_ModelManager		：[I/ ]	 モデルデータ管理オブジェクト
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(WindowManager* p_WindowManager, DeviceManager* p_DeviceManager, ResourceManager *p_ResourceManager, ModelManager *p_ModelManager)
{
	//ウィンドウサイズの取得
	WindowSize const WindowSize = p_WindowManager->GetWindowSize();
	//マウスの情報を取得
	MouseInfo MouseButton = p_DeviceManager->GetMouseInfo();
	//キー（キーボード）の情報を取得
	KeyInfo KeyBoard = p_DeviceManager->GetKeyInfo();
	
	// シェーダープログラムの利用を開始する
	m_MainShader->UseProgram();

	//オブジェクトを移動させるための行列
	Matrix ModelView;

	//3D空間にするための行列
	Matrix Projection;


	///////////////////////////////////
	// オブジェクト移動関係の処理

	//スペースで初期位置に戻す
	if (true == KeyBoard.Change.Key_SPACE)
	{
		memset(&m_Translate, 0, sizeof(m_Translate));
		memset(&m_Rotate, 0, sizeof(m_Rotate));
	}

	//平行移動用の変数にマウス情報の座標を加える
	m_Translate.x = m_Translate.x + MouseButton.Left.DiffPos.x;
	m_Translate.y = m_Translate.y + MouseButton.Left.DiffPos.y;
	m_Translate.z = m_Translate.z + MouseButton.Scroll;
	//更にキーボードの情報を加える
	if (GLFW_PRESS == KeyBoard.Change.Key_W)
	{
		m_Translate.z = m_Translate.z + 0.5f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_S)
	{
		m_Translate.z = m_Translate.z - 0.5f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_A)
	{
		m_Translate.x = m_Translate.x + 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_D)
	{
		m_Translate.x = m_Translate.x - 1.0f;
	}

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
	
	//透視投影行列を適用する
	Projection.Perspective(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	//もう一つの方法
//	Projection.Perspective(1.0, 100.0, 60.0, WindowSize.Width / WindowSize.Height);

	//シェーダーの変数を有効化
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	//キューブ形状のモデルデータを取得する
	ModelDataInfo PiercedCube;
	p_ModelManager->GetPiercedCube(&PiercedCube, false);

	//キューブ形状のモデルデータを取得する（インデックス版）
	ModelDataInfo_index PiercedCube_index;
	p_ModelManager->GetPiercedCube_index(&PiercedCube_index, false);

	//震度テストを有効
	glEnable(GL_DEPTH_TEST);

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, WindowSize.Width, WindowSize.Height);

	//変数を転送
	m_MainShader->UniformMatrixXfv(m_ModelView_matrix, 4, 1, GL_FALSE, ModelView.GetMatrix());
	m_MainShader->UniformMatrixXfv(m_Proj_matrix, 4, 1, GL_FALSE, Projection.GetMatrix());

	// [glDrawArrays]を使用した描画（一番オーソドックス（初歩的）な描画方法）
	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube.Vertex.size, PiercedCube.Vertex.type, PiercedCube.Vertex.normalized, PiercedCube.Vertex.stride, PiercedCube.Vertex.pointer);
	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube.Color.size, PiercedCube.Color.type, PiercedCube.Color.normalized, PiercedCube.Color.stride, PiercedCube.Color.pointer);
	glDrawArrays(PiercedCube.DrawArrays.mode, PiercedCube.DrawArrays.first, PiercedCube.DrawArrays.count);

	// [glDrawElements]を使用した描画（インデックスバッファを使用する場合）
//	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube_index.Vertex.size, PiercedCube_index.Vertex.type, PiercedCube_index.Vertex.normalized, PiercedCube_index.Vertex.stride, PiercedCube_index.Vertex.pointer);
//	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube_index.Color.size, PiercedCube_index.Color.type, PiercedCube_index.Color.normalized, PiercedCube_index.Color.stride, PiercedCube_index.Color.pointer);
//	glDrawElements(PiercedCube_index.DrawElement.mode, PiercedCube_index.DrawElement.count, PiercedCube_index.DrawElement.type, PiercedCube_index.DrawElement.indices);

	//描画処理
	p_WindowManager->DrawingOnWindow();
}

