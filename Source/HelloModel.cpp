﻿#include "HelloModel.h"
#include "ModelManager.h"

//コンストラクタ
HelloModel::HelloModel()
{
}

//デストラクタ
HelloModel::~HelloModel()
{
	if (nullptr != m_Model)
	{
		m_Model->FileDataFree();
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ハローモデル描画（モデルデータのお試し描画）の準備をする
*	引数
*	　p_Global			：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void HelloModel::Prepare(const GlobalData &p_Global)
{
	//描画準備が未完了の場合
	if (false == PrepareCompFlag)
	{
		//モデル管理オブジェクトが未生成の場合は、生成後にモデルデータの読み込みを行う
		if (nullptr == m_Model)
		{
			m_Model = make_shared<ModelManager>();
			m_Model->FileDataLoad("Handgun1/Handgun_obj.obj", ModelFormat::OBJ);
		}

		//描画準備完了とする
		PrepareCompFlag = true;
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ハローモデル描画（モデルデータのお試し描画）を開始する
*	引数
*	　p_Global			：[I/ ]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void HelloModel::Drawing(const GlobalData &p_Global)
{
	//モデルビューマトリクスをコピー
	mat4 ModelViewMat = p_Global.ModelViewMat;
	
	//モデルデータを拡大（元データが小さいので）
	ModelViewMat *= scale(vec3(15.0f, 15.0f, 15.0f));

	//背景色指定
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//色初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ビューポートを設定する
	glViewport(0, 0, p_Global.WindowSize.x, p_Global.WindowSize.y);

	//モデルデータの描画
	m_Model->DataDraw(ModelViewMat, p_Global.ProjectionMat);

	return;
}