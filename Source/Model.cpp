#include "Model.h"

//コンストラクタ
Model::Model()
{
}

//デストラクタ
Model::~Model()
{
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する
*	　（[glDrawArrays]として登録するモデルデータ）
*	引数
*	　p_vbo			：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
*					　		 VBOとして使用する場合、「glBufferData」でデータを登録してから「glDrawArrays」する。
*							 登録するデータは「BufferData」メンバに格納されている情報を使用すれば良い。
*							 ※「false」を指定した場合は「BufferData」メンバには情報が格納されないので扱いに注意
*	　p_ModelData	：[ /O]　モデルデータ情報
*							 ※注意※
*							 モデルデータが不要になった時点で、必ず[PiercedCube_free]をコールしてください。
*							 （モデルデータのメモリを解放します）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Model::GetPiercedCube(bool p_vbo, ModelInfo_Original *p_ModelData)
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

	//頂点とインデックスのメモリを確保してコピーする
	GLvoid* PiercedCube_vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
	memmove(PiercedCube_vertex, vertex, sizeof(vertex));

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
		p_ModelData->Vertex.pointer = PiercedCube_vertex;
	}

	//モデルデータ設定（カラー情報）
	p_ModelData->Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	p_ModelData->Color.type = GL_UNSIGNED_BYTE;
	p_ModelData->Color.normalized = GL_TRUE;
	p_ModelData->Color.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Color.pointer = (GLvoid*)sizeof(vertex[0].Vector);

		//バッファーデータ設定
		p_ModelData->BufferData.size = sizeof(vertex);
		p_ModelData->BufferData.data = PiercedCube_vertex;
	}
	else
	{
		p_ModelData->Color.pointer = (GLvoid*)((byte*)PiercedCube_vertex + sizeof(vertex[0].Vector));

		//バッファーデータ設定（VBO未使用が指定されているのでデータは詰めない）
		p_ModelData->BufferData.size = 0;
		p_ModelData->BufferData.data = NULL;
	}

	//描画情報設定
	p_ModelData->DrawArrays.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawArrays.first = 0;
	p_ModelData->DrawArrays.count = sizeof(vertex) / sizeof(vertex[0]);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　モデルデータのメモリを解放します
*	引数
*	　p_ModelData	：[ /O]　モデルデータ（メモリを解放後「NULL」が格納されるという意味で[ /O]指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Model::PiercedCube_free(ModelInfo_Original *p_ModelData)
{
	//データが格納されていれば開放する
	if (NULL != p_ModelData->Vertex.pointer)
	{
		free(p_ModelData->Vertex.pointer);
	}
	if (NULL != p_ModelData->BufferData.data)
	{
		free(p_ModelData->BufferData.data);
	}

	p_ModelData = NULL;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する（インデックス版）
*	　（[glDrawElements]用パラメータ情報）
*	引数
*	　p_vbo			：[I/ ]　モデルデータをVBOとして登録/使用する場合は「true」そうでない場合は「false」を指定
*						　	 VBOとして使用する場合、「glBufferData」でデータを登録してから「glDrawElements」する。
*							 登録するデータは「BufferData」メンバに格納されている情報を使用すれば良い。
*							 ※「false」を指定した場合は「BufferData」メンバには情報が格納されないので扱いに注意
*	　p_ModelData	：[ /O]　モデルデータ情報
*							 ※注意※
*							 モデルデータが不要になった時点で、必ず[PiercedCube_index_free]をコールしてください。
*							 （モデルデータのメモリを解放します）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Model::GetPiercedCube_index(bool p_vbo, ModelInfo_index_Original *p_ModelData)
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

	//頂点とインデックスのメモリを確保してコピーする
	GLvoid* PiercedCube_vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
	GLvoid* PiercedCube_index = (GLvoid*)calloc(sizeof(index), sizeof(byte));
	memmove(PiercedCube_vertex, vertex, sizeof(vertex));
	memmove(PiercedCube_index, index, sizeof(index));

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
		p_ModelData->Vertex.pointer = PiercedCube_vertex;
	}

	//モデルデータ設定（カラー情報）
	p_ModelData->Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	p_ModelData->Color.type = GL_UNSIGNED_BYTE;
	p_ModelData->Color.normalized = GL_TRUE;
	p_ModelData->Color.stride = sizeof(Vec3_bColor3);
	if (true == p_vbo)
	{
		p_ModelData->Color.pointer = (GLvoid*)sizeof(vertex[0].Vector);

		//バッファーデータ設定
		p_ModelData->BufferData.size = sizeof(vertex);
		p_ModelData->BufferData.data = PiercedCube_vertex;
	}
	else
	{
		p_ModelData->Color.pointer = (GLvoid*)((byte*)PiercedCube_vertex + sizeof(vertex[0].Vector));

		//バッファーデータ設定（VBO未使用が指定されているのでデータは詰めない）
		p_ModelData->BufferData.size = 0;
		p_ModelData->BufferData.data = NULL;
	}

	//描画情報設定
	p_ModelData->DrawElements.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawElements.count = sizeof(index) / sizeof(index[0]);
	p_ModelData->DrawElements.type = GL_UNSIGNED_BYTE;
	p_ModelData->DrawElements.indices = PiercedCube_index;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　モデルデータのメモリを解放します
*	引数
*	　p_ModelData	：[ /O]　モデルデータ（メモリを解放後「NULL」が格納されるという意味で[ /O]指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Model::PiercedCube_index_free(ModelInfo_index_Original *p_ModelData)
{
	//データが格納されていれば開放する
	if (NULL != p_ModelData->Vertex.pointer)
	{
		free(p_ModelData->Vertex.pointer);
	}
	if (NULL != p_ModelData->BufferData.data)
	{
		free(p_ModelData->BufferData.data);
	}

	p_ModelData = NULL;
}