#include "ModelManager.h"

/////////////////////////////////////////////
//static変数の実体を定義

ModelManager::Vertex ModelManager::m_PiercedCube;					//穴あきキューブ用の頂点データ
ModelManager::Vertex_index ModelManager::m_PiercedCube_index;		//穴あきキューブ用の頂点データ（インデックス版）

//コンストラクタ
ModelManager::ModelManager()
{
	//初期化
	memset(&m_PiercedCube, 0, sizeof(m_PiercedCube));
	memset(&m_PiercedCube_index, 0, sizeof(m_PiercedCube_index));
}

//デストラクタ
ModelManager::~ModelManager()
{
	//メモリ解放
	if (NULL != m_PiercedCube.vertex)
	{
		free(m_PiercedCube.vertex);
		memset(&m_PiercedCube, 0, sizeof(m_PiercedCube));
	}
	if (NULL != m_PiercedCube_index.vertex)
	{
		free(m_PiercedCube_index.vertex);
		free(m_PiercedCube_index.index);
		memset(&m_PiercedCube_index, 0, sizeof(m_PiercedCube_index));
	}
}


/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する
*	　（[glDrawArrays]として登録するモデルデータ）
*	引数
*	　p_ModelData		：[ /O]　モデルデータ情報
*	　p_vbo				：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
*						　		 VBOとして使用する場合、「glBufferData」でデータを登録するしてから「glDrawArrays」する。
*								 登録するデータは[size]に「BufferData.size」を、[data]に「BufferData.data」を指定すれば良い				 
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::GetPiercedCube(ModelDataInfo *p_ModelData, bool p_vbo)
{
	// 頂点データ
	Vec3_bColor3 vertex[] =
	{
		// v0
		{ { -10.0f, -10.0f, 10.0f }, { 50, 50, 50 } },
		// v1
		{ { -10.0f, -10.0f, -10.0f }, { 90, 0, 0 } },
		// v2
		{ { -10.0f, 10.0f, 10.0f }, { 0, 90, 0 } },
		// v3
		{ { -10.0f, 10.0f, -10.0f }, { 0, 0, 90 } },
		// v4
		{ { 10.0f, 10.0f, 10.0f }, { 130, 0, 0 } },
		// v5
		{ { 10.0f, 10.0f, -10.0f }, { 0, 130, 0 } },
		// v6
		{ { 10.0f, -10.0f, 10.0f }, { 0, 0, 130 } },
		// v7
		{ { 10.0f, -10.0f, -10.0f }, { 170, 0, 0 } },
		// v8
		{ { -10.0f, -10.0f, 10.0f }, { 0, 170, 0 } },
		// v9
		{ { -10.0f, -10.0f, -10.0f }, { 0, 0, 170 } },
		// v10
		{ { -10.0f, -10.0f, -10.0f }, { 210, 0, 0 } },
		// v11
		{ { -10.0f, 10.0f, -10.0f }, { 0, 210, 0 } },
		// v12
		{ { 10.0f, -10.0f, -10.0f }, { 0, 0, 210 } },
		// v13
		{ { 10.0f, 10.0f, -10.0f }, { 250, 0, 0 } },
	};

	//一度も読み込んだことがない場合
	if (NULL == m_PiercedCube.vertex)
	{
		//メモリを確保してコピーする
		m_PiercedCube.vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
		memmove(m_PiercedCube.vertex, vertex, sizeof(vertex));
	}

	//モデルデータ設定（頂点情報）
	p_ModelData->Vertex.size = sizeof(vertex[0].Vector) / sizeof(vertex[0].Vector.x);
	p_ModelData->Vertex.type = GL_FLOAT;
	p_ModelData->Vertex.normalized = GL_FALSE;
	p_ModelData->Vertex.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Vertex.pointer = 0;
	}
	else
	{
		p_ModelData->Vertex.pointer = m_PiercedCube.vertex;
	}

	//モデルデータ設定（カラー情報）
	p_ModelData->Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	p_ModelData->Color.type = GL_UNSIGNED_BYTE;
	p_ModelData->Color.normalized = GL_TRUE;
	p_ModelData->Color.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Color.pointer = (GLvoid*)sizeof(vertex[0].Vector);
	}
	else
	{
		p_ModelData->Color.pointer = (GLvoid*)((byte*)m_PiercedCube.vertex + sizeof(vertex[0].Vector));
	}

	//バッファーデータ設定
	p_ModelData->BufferData.size = sizeof(vertex);
	p_ModelData->BufferData.data = m_PiercedCube.vertex;

	//描画情報設定
	p_ModelData->DrawArrays.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawArrays.first = 0;
	p_ModelData->DrawArrays.count = sizeof(vertex) / sizeof(vertex[0]);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する（インデックス版）
*	　（[glDrawElements]用パラメータ情報）
*	引数
*	　p_ModelData		：[ /O]　モデルデータ情報
*	　p_vbo				：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
*						　		 VBOとして使用する場合、「glBufferData」でデータを登録するしてから「glDrawElements」する。
*								 登録するデータは[size]に「BufferData.size」を、[data]に「BufferData.data」を指定すれば良い
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::GetPiercedCube_index(ModelDataInfo_index *p_ModelData, bool p_vbo)
{
	// 頂点データ
	Vec3_bColor3 vertex[] =
	{
		// v0
		{ { -10.0f, -10.0f, 10.0f }, { 90, 0, 0 } },
		// v1
		{ { -10.0f, -10.0f, -10.0f }, { 0, 90, 0 } },
		// v2
		{ { -10.0f, 10.0f, 10.0f }, { 0, 0, 90 } },
		// v3
		{ { -10.0f, 10.0f, -10.0f }, { 180, 0, 0 } },
		// v4
		{ { 10.0f, 10.0f, 10.0f }, { 0, 180, 0 } },
		// v5
		{ { 10.0f, 10.0f, -10.0f }, { 0, 0, 180 } },
		// v6
		{ { 10.0f, -10.0f, 10.0f }, { 250, 0, 0 } },
		// v7
		{ { 10.0f, -10.0f, -10.0f }, { 0, 250, 0 } },
	};

	// インデックスデータ
	GLubyte index[] =
	{
	// v0  1  2  3  4  5  6  7  8  9  10 11 12 13
		0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 1, 3, 7, 5,
	};

	//一度も読み込んだことがない場合
	if (NULL == m_PiercedCube_index.vertex)
	{
		//メモリを確保してコピーする
		m_PiercedCube_index.vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
		m_PiercedCube_index.index = (GLvoid*)calloc(sizeof(index), sizeof(byte));
		memmove(m_PiercedCube_index.vertex, vertex, sizeof(vertex));
		memmove(m_PiercedCube_index.index, index, sizeof(index));
	}

	//モデルデータ設定（頂点情報）
	p_ModelData->Vertex.size = sizeof(vertex[0].Vector) / sizeof(vertex[0].Vector.x);
	p_ModelData->Vertex.type = GL_FLOAT;
	p_ModelData->Vertex.normalized = GL_FALSE;
	p_ModelData->Vertex.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Vertex.pointer = 0;
	}
	else
	{
		p_ModelData->Vertex.pointer = m_PiercedCube_index.vertex;
	}

	//モデルデータ設定（カラー情報）
	p_ModelData->Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	p_ModelData->Color.type = GL_UNSIGNED_BYTE;
	p_ModelData->Color.normalized = GL_TRUE;
	p_ModelData->Color.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Color.pointer = (GLvoid*)sizeof(vertex[0].Vector);
	}
	else
	{
		p_ModelData->Color.pointer = (GLvoid*)((byte*)m_PiercedCube_index.vertex + sizeof(vertex[0].Vector));
	}

	//バッファーデータ設定
	p_ModelData->BufferData.size = sizeof(vertex);
	p_ModelData->BufferData.data = m_PiercedCube_index.vertex;

	//描画情報設定
	p_ModelData->DrawElements.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawElements.count = sizeof(index) / sizeof(index[0]);
	p_ModelData->DrawElements.type = GL_UNSIGNED_BYTE;
	p_ModelData->DrawElements.indices = m_PiercedCube_index.index;
}
