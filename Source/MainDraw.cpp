#include "MainDraw.h"

//コンストラクタ
MainDraw::MainDraw()
{
	//Mainシェーダー管理用のオブジェクト生成
	m_MainShader = new ShaderManager;

	//変数初期化
	m_attr_pos = -1;
	m_attr_color = -1;
	m_ProjModel_matrix = 0;

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
	m_MainShader->CreateShaderProgram("Main\\Main.vert", "Main\\Main.frag", "Main\\Main.geom", NULL, NULL);

	//シェーダー内で使用する変数を取得します（頂点データ）
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//シェーダー内で使用する変数を取得します（カラーデータ）
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//シェーダー内で使用する変数を取得します（座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス））
	m_ProjModel_matrix = m_MainShader->GetUniformLocation("ProjModel_matrix");

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　メイン描画を開始する
*	引数
*	　p_Global				：[I/O]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(GlobalData *p_Global)
{
	// シェーダープログラムの利用を開始する
	m_MainShader->UseProgram();

	//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）
	Matrix ProjModel;
	ProjModel.SetMatrix(p_Global->ProjectionMatrix);
	ProjModel = ProjModel * p_Global->ModelViewMatrix;

	//シェーダーの変数を有効化
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	//キューブ形状のモデルデータを取得する
	ModelDataInfo PiercedCube;
	ModelManager::GetPiercedCube(&PiercedCube, false);

	//キューブ形状のモデルデータを取得する（インデックス版）
	ModelDataInfo_index PiercedCube_index;
	ModelManager::GetPiercedCube_index(&PiercedCube_index, false);

	//震度テストを有効
	glEnable(GL_DEPTH_TEST);

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, p_Global->WindowSize.Width, p_Global->WindowSize.Height);

	//変数を転送
	m_MainShader->UniformMatrixXfv(m_ProjModel_matrix, 4, 1, GL_FALSE, ProjModel.GetMatrix());

	// [glDrawArrays]を使用した描画（一番オーソドックス（初歩的）な描画方法）
	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube.Vertex.size, PiercedCube.Vertex.type, PiercedCube.Vertex.normalized, PiercedCube.Vertex.stride, PiercedCube.Vertex.pointer);
	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube.Color.size, PiercedCube.Color.type, PiercedCube.Color.normalized, PiercedCube.Color.stride, PiercedCube.Color.pointer);
	glDrawArrays(PiercedCube.DrawArrays.mode, PiercedCube.DrawArrays.first, PiercedCube.DrawArrays.count);

	// [glDrawElements]を使用した描画（インデックスバッファを使用する場合）
//	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube_index.Vertex.size, PiercedCube_index.Vertex.type, PiercedCube_index.Vertex.normalized, PiercedCube_index.Vertex.stride, PiercedCube_index.Vertex.pointer);
//	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube_index.Color.size, PiercedCube_index.Color.type, PiercedCube_index.Color.normalized, PiercedCube_index.Color.stride, PiercedCube_index.Color.pointer);
//	glDrawElements(PiercedCube_index.DrawElement.mode, PiercedCube_index.DrawElement.count, PiercedCube_index.DrawElement.type, PiercedCube_index.DrawElement.indices);

}

