#include "ModelManager.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "OBJLoader.h"

/////////////////////////////////////////////
//static変数の実体を定義

const string ModelManager::MODEL_FILE_DIR = "../Resource/Model/";	//モデルファイルの保存ディレクトリ

shared_ptr<ShaderManager> ModelManager::m_ModelShader = nullptr;	//モデル描画用のシェーダーオブジェクト
//ロケーション
GLint ModelManager::m_attr_Position = -1;			//頂点座標のロケーション
GLint ModelManager::m_attr_Normal = -1;				//法線ロケーション
GLint ModelManager::m_attr_Color = -1;				//カラーロケーション
GLint ModelManager::m_attr_TexCoord = -1;			//テクスチャ座標のロケーション
GLint ModelManager::m_unif_ModelFormat = -1;		//モデルデータのフォーマットのロケーション
GLint ModelManager::m_unif_ModelViewMat = -1;		//モデルビューマトリクスのロケーション
GLint ModelManager::m_unif_ProjectionMat = -1;		//プロジェクションマトリクスのロケーション
GLint ModelManager::m_unif_RotateMat = -1;			//回転行列のロケーション
GLint ModelManager::m_unif_Ambient = -1;			//アンビエント値のロケーション
GLint ModelManager::m_unif_Diffuse = -1;			//ディフューズ値のロケーション
GLint ModelManager::m_unif_Specular = -1;			//スペキュラ値のロケーション
GLint ModelManager::m_unif_Shininess = -1;			//シャイネス値のロケーション
GLint ModelManager::m_unif_Alpha = -1;				//アルファ値のロケーション
GLint ModelManager::m_unif_AmbientTexFlag = -1;		//テクスチャ（アンビエント） 有り・無しフラグのロケーション
GLint ModelManager::m_unif_DiffuseTexFlag = -1;		//テクスチャ（ディフューズ） 有り・無しフラグのロケーション
GLint ModelManager::m_unif_SpecularTexFlag = -1;	//テクスチャ（スペキュラ）有り・無しフラグのロケーション
GLint ModelManager::m_unif_BumpMapTexFlag = -1;		//テクスチャ（バンプマップ）有り・無しフラグのロケーション
GLint ModelManager::m_unif_AmbientTex = -1;			//テクスチャ（アンビエント） のロケーション
GLint ModelManager::m_unif_DiffuseTex = -1;			//テクスチャ（ディフューズ）のロケーション
GLint ModelManager::m_unif_SpecularTex = -1;		//テクスチャ（スペキュラ）のロケーション
GLint ModelManager::m_unif_BumpMapTex = -1;			//テクスチャ（バンプマップ）のロケーション

//コンストラクタ
ModelManager::ModelManager()
{
	//データが作成されていなければ
	if (nullptr == m_ModelShader)
	{
		//モデル管理シェーダーの生成
		m_ModelShader = make_shared<ShaderManager>();

		//シェーダーの読み込みを行う
		//「Shader」フォルダに格納されている必要があります。
		m_ModelShader->CreateShaderProgram("ModelManager.vert", "ModelManager.frag", NULL, NULL, NULL, NULL);

		///////////////////////////////////////////////////
		// シェーダー内で使用する変数のロケーションを取得
		
		//頂点座標
		m_attr_Position = m_ModelShader->GetAttribLocation("attr_Position");

		//法線
		m_attr_Normal = m_ModelShader->GetAttribLocation("attr_Normal");

		//カラー
		m_attr_Color = m_ModelShader->GetAttribLocation("attr_Color");

		//テクスチャ座標
		m_attr_TexCoord = m_ModelShader->GetAttribLocation("attr_TexCoord");

		//モデルデータのフォーマット
		m_unif_ModelFormat = m_ModelShader->GetUniformLocation("unif_ModelFormat");

		//モデルビューマトリクス
		m_unif_ModelViewMat = m_ModelShader->GetUniformLocation("unif_ModelViewMat");

		//プロジェクションマトリクス
		m_unif_ProjectionMat = m_ModelShader->GetUniformLocation("unif_ProjectionMat");

		//回転行列
		m_unif_RotateMat = m_ModelShader->GetUniformLocation("unif_RotateMat");

		//アンビエント値
		m_unif_Ambient = m_ModelShader->GetUniformLocation("unif_Ambient");

		//ディフューズ値
		m_unif_Diffuse = m_ModelShader->GetUniformLocation("unif_Diffuse");

		//スペキュラ値
		m_unif_Specular = m_ModelShader->GetUniformLocation("unif_Specular");

		//シャイネス値
		m_unif_Shininess = m_ModelShader->GetUniformLocation("unif_Shininess");

		//アルファ値
		m_unif_Alpha = m_ModelShader->GetUniformLocation("unif_Alpha");

		//テクスチャ（アンビエント）有り・無しフラグ
		m_unif_AmbientTexFlag = m_ModelShader->GetUniformLocation("unif_AmbientTexFlag");

		//テクスチャ（ディフューズ） 有り・無しフラグ
		m_unif_DiffuseTexFlag = m_ModelShader->GetUniformLocation("unif_DiffuseTexFlag");

		//テクスチャ（スペキュラ）有り・無しフラグ
		m_unif_SpecularTexFlag = m_ModelShader->GetUniformLocation("unif_SpecularTexFlag");

		//テクスチャ（バンプマップ）有り・無しフラグ
		m_unif_BumpMapTexFlag = m_ModelShader->GetUniformLocation("unif_BumpMapTexFlag");

		//テクスチャ（アンビエント）
		m_unif_AmbientTex = m_ModelShader->GetUniformLocation("unif_AmbientTex");

		//テクスチャ（ディフューズ）
		m_unif_DiffuseTex = m_ModelShader->GetUniformLocation("unif_DiffuseTex");

		//テクスチャ（スペキュラ）
		m_unif_SpecularTex = m_ModelShader->GetUniformLocation("unif_SpecularTex");

		//テクスチャ（バンプマップ）
		m_unif_BumpMapTex = m_ModelShader->GetUniformLocation("unif_BumpMapTex");
	}
}

//デストラクタ
ModelManager::~ModelManager()
{
	//既にモデルデータが読み込まれているかの確認
	if (ModelFormat::UNDEFINED != m_ModelInfo.ModelFormat)
	{
		//作成されていれば念のため破棄処理する
		FileDataFree();

		//本来であれば破棄されているべきなので、警告メッセージを表示しておく
		WARNING_MESSAGE("破棄処理される前にデストラクタが呼ばれました。\n" \
						"破棄処理を忘れていませんか？\n");
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　モデルファイルからモデルデータの読み込みを行います。
*	　既にモデルデータが読み込まれている場合は、データを破棄（メモリ解放）してから新しく読み込みします。
*	　読み込んだモデルデータの描画は「ModelDataDraw」関数で行います。
*	引数
*	　p_FileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
*							 [Resource/Model/]フォルダ以降のファイルパスを入力してください。
*							 また、ディレクトリをまたぐときは「/」で区切ってください（例「xxx/xxx.obj」）
*					　　　※「p_ModelFormat」で自作モデルデータ（特殊パターン）を指定するときは、
*							「p_FileName」は「空("")」を指定してください。
*	　p_ModelFormat	：[I/ ]　モデルファイルのフォーマット（詳細は定義部分のコメント参照）
*
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::FileDataLoad(const string &p_FileName, ModelFormat p_ModelFormat)
{
	printf("モデルデータ「%s」の読み込みを開始します...", p_FileName.c_str());

	//引数チェック
	if (ModelFormat::UNDEFINED == p_ModelFormat)
	{
		printf("失敗\n");
		ERROR_MESSAGE("モデルデータの読み込み 引数エラー\n" \
					  "p_FileName = %s, p_ModelFormat = %d\n", p_FileName.c_str(), p_ModelFormat);
		return;
	}

	//既にモデルデータが読み込まれているかの確認
	if (ModelFormat::UNDEFINED != m_ModelInfo.ModelFormat)
	{
		//作成されていれば破棄してから新規作成
		FileDataFree();

		//本来であれば上書きはしない事が多いので、警告メッセージを表示しておく
		WARNING_MESSAGE("モデルデータが再作成がされました。\n" \
						"破棄処理を忘れていませんか？\n");
	}

	///////////////////////////////
	// モデルファイルへのパスを作成

	string model_dir_file_name;			//モデルファイルへのパス

	//モデルファイルが指定されている場合（独自フォーマットの場合は作成しない）
	if (0 != p_FileName.length())
	{
		//モデルファイルへのパスを生成する（マルチバイト文字）
		model_dir_file_name = MODEL_FILE_DIR + p_FileName;
	}

	///////////////////////////////
	// モデルファイルの読み込み

	//読み込むフォーマットを記憶
	m_ModelInfo.ModelFormat = p_ModelFormat;

	//モデルファイルのフォーマットによって処理を分岐
	switch (p_ModelFormat)
	{
		//OBJファイル
		case ModelFormat::OBJ:
			FileLoad_OBJ(model_dir_file_name);
			break;

		//////////////////
		// 以下、自作モデルデータ（特殊パターン）

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ModelFormat::ORIGINAL_PIERCED_CUBE:
			DataLoad_PiercedCube();
			break;

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ModelFormat::ORIGINAL_PIERCED_CUBE2:
			DataLoad_PiercedCube2();
			break;

		default:
			printf("失敗\n");
			ERROR_MESSAGE("ピクセルフォーマットの引数が不正です。\n"\
						  "p_ModelFormat = %d", p_ModelFormat);

			break;
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　モデルデータを破棄（メモリ解放）します
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::FileDataFree(void)
{
	//データが格納されていれば破棄処理する
	if (0 != m_ModelInfo.BufferObj_v)
	{
		glDeleteBuffers(1, &m_ModelInfo.BufferObj_v);
	}
	if (0 != m_ModelInfo.BufferObj_i)
	{
		glDeleteBuffers(1, &m_ModelInfo.BufferObj_i);
	}

	//テクスチャオブジェクト破棄
	for (auto &Material : m_ModelInfo.Material)
	{
		glDeleteTextures(1, &Material.ambientTexObj);
		glDeleteTextures(1, &Material.diffuseTexObj);
		glDeleteTextures(1, &Material.specularTexObj);
		glDeleteTextures(1, &Material.bumpMapTexObj);
	}

	//要素を削除
	m_ModelInfo.DrawElements.clear();
	m_ModelInfo.Material.clear();
	//余分なメモリ解放
	m_ModelInfo.DrawElements.shrink_to_fit();
	m_ModelInfo.Material.shrink_to_fit();
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　モデルデータを描画します。
*	　予めモデルデータを「FileDataLoad」関数で読み込んでおく必要があります。
*
*	　※本関数では描画のみしか実行しません
*　　　「glClearColor, glClear, glViewport」などの設定は関数コール前に必要に応じて行ってください。
*	引数
*	　p_ModelViewMat	：[I/ ]　描画に使用するモデルビューマトリクス
*	　p_ProjectionMat	：[I/ ]　描画に使用するプロジェクションマトリクス
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::DataDraw(const mat4 &p_ModelViewMat, const mat4 &p_ProjectionMat)
{
	if (ModelFormat::UNDEFINED == m_ModelInfo.ModelFormat)
	{
		ERROR_MESSAGE("モデルデータを読み込んでいない状態で描画しようとしました。\n"\
					  "モデルデータの読み込みを行ってから描画を実行してください。");
		return;
	}
	// シェーダープログラムの利用を開始する
	m_ModelShader->UseProgram();

	//バッファーを有効化
	glBindBuffer(GL_ARRAY_BUFFER, m_ModelInfo.BufferObj_v);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModelInfo.BufferObj_i);

	//////////////////////////////////
	// 必ず送る変数を先に設定

	//頂点座標設定
	m_ModelShader->EnableVertexAttribArray(m_attr_Position);
	m_ModelShader->VertexAttribPointer(m_attr_Position, m_ModelInfo.Position.size, m_ModelInfo.Position.type,
									  m_ModelInfo.Position.normalized, m_ModelInfo.Position.stride, m_ModelInfo.Position.pointer);

	//モデルデータのフォーマットを設定
	m_ModelShader->UniformXi(m_unif_ModelFormat, 1, static_cast<GLint>(m_ModelInfo.ModelFormat), 0, 0, 0);

	//モデルビューマトリクスを設定
	m_ModelShader->UniformMatrixXfv(m_unif_ModelViewMat, 4, 1, GL_FALSE, &p_ModelViewMat);

	//プロジェクションマトリクスを設定
	m_ModelShader->UniformMatrixXfv(m_unif_ProjectionMat, 4, 1, GL_FALSE, &p_ProjectionMat);

	//モデルビューマトリクスから回転成分を算出する
	mat4 RotateMat = inverseTranspose(p_ModelViewMat);

	//回転行列を設定
	m_ModelShader->UniformMatrixXfv(m_unif_RotateMat, 4, 1, GL_FALSE, &RotateMat);

	//////////////////////////////////
	// 残りの変数の初期値を設定

	//法線
	m_ModelShader->DisableVertexAttribArray(m_attr_Normal);
	m_ModelShader->VertexAttribXf(m_attr_Normal, 3, 0.0f, 0.0f, 0.0f, 0.0f);

	//カラー
	m_ModelShader->DisableVertexAttribArray(m_attr_Color);
	m_ModelShader->VertexAttribXf(m_attr_Color, 4, 0.0f, 0.0f, 0.0f, 0.0f);

	//テクスチャ座標
	m_ModelShader->DisableVertexAttribArray(m_attr_TexCoord);
	m_ModelShader->VertexAttribXf(m_attr_TexCoord, 2, 0.0f, 0.0f, 0.0f, 0.0f);

	//カラー関連の係数
	m_ModelShader->UniformXi(m_unif_Ambient, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_Diffuse, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_Specular, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_Shininess, 1, 0, 0, 0, 0); 
	m_ModelShader->UniformXi(m_unif_Alpha, 1, 0, 0, 0, 0);

	//テクスチャフラグとテクスチャ
	m_ModelShader->UniformXi(m_unif_AmbientTexFlag, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_DiffuseTexFlag, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_SpecularTexFlag, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_BumpMapTexFlag, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_AmbientTex, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_DiffuseTex, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_SpecularTex, 1, 0, 0, 0, 0);
	m_ModelShader->UniformXi(m_unif_BumpMapTex, 1, 0, 0, 0, 0);

	//////////////////////////////////
	// 以下のロケーションの設定はファイルフォーマットによって個別設定する必要あり
	// m_attr_Normal			//法線
	// m_attr_Color				//カラー
	// m_attr_TexCoord			//テクスチャ座標
	// m_unif_xxxxx				//カラー関連の係数
	// m_unif_xxxxxTexFlag		//テクスチャ有り・無しフラグ
	// m_unif_xxxxxTex			//テクスチャ

	//深度テストを有効
	glEnable(GL_DEPTH_TEST);

	//シェーダーへの設定（モデルファイルのフォーマットによって処理を分岐）
	switch (m_ModelInfo.ModelFormat)
	{
		//OBJファイル
		case ModelFormat::OBJ:
			//法線設定
			m_ModelShader->EnableVertexAttribArray(m_attr_Normal);
			m_ModelShader->VertexAttribPointer(m_attr_Normal, m_ModelInfo.Normal.size, m_ModelInfo.Normal.type,
											  m_ModelInfo.Normal.normalized, m_ModelInfo.Normal.stride, m_ModelInfo.Normal.pointer);

			//テクスチャ座標設定
			m_ModelShader->EnableVertexAttribArray(m_attr_TexCoord);
			m_ModelShader->VertexAttribPointer(m_attr_TexCoord, m_ModelInfo.TexCoord.size, m_ModelInfo.TexCoord.type,
											  m_ModelInfo.TexCoord.normalized, m_ModelInfo.TexCoord.stride, m_ModelInfo.TexCoord.pointer);

			break;

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ModelFormat::ORIGINAL_PIERCED_CUBE:
			//カラー設定
			m_ModelShader->EnableVertexAttribArray(m_attr_Color);
			m_ModelShader->VertexAttribPointer(m_attr_Color, m_ModelInfo.Color.size, m_ModelInfo.Color.type,
											  m_ModelInfo.Color.normalized, m_ModelInfo.Color.stride, m_ModelInfo.Color.pointer);

			break;

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ModelFormat::ORIGINAL_PIERCED_CUBE2:
			//カラー設定
			m_ModelShader->EnableVertexAttribArray(m_attr_Color);
			m_ModelShader->VertexAttribPointer(m_attr_Color, m_ModelInfo.Color.size, m_ModelInfo.Color.type,
											  m_ModelInfo.Color.normalized, m_ModelInfo.Color.stride, m_ModelInfo.Color.pointer);

			break;

		default:

			break;
	}

	//描画実行
	for (auto &DrawElements : m_ModelInfo.DrawElements)
	{
		//描画実行（モデルファイルのフォーマットによって処理を分岐）
		switch (m_ModelInfo.ModelFormat)
		{
			//OBJファイル
			case ModelFormat::OBJ:
			{
				//テクスチャ（アンビエント）がある場合は設定する
				if (0 != m_ModelInfo.Material[DrawElements.MaterialIndex].ambientTexObj)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, m_ModelInfo.Material[DrawElements.MaterialIndex].ambientTexObj);
					m_ModelShader->UniformXi(m_unif_AmbientTexFlag, 1, 1, 0, 0, 0);
					m_ModelShader->UniformXi(m_unif_AmbientTex, 1, 0, 0, 0, 0);
				}
				else
				{
					m_ModelShader->UniformXi(m_unif_AmbientTexFlag, 1, 0, 0, 0, 0);
				}

				//テクスチャ（ディフューズ）がある場合は設定する
				if (0 != m_ModelInfo.Material[DrawElements.MaterialIndex].diffuseTexObj)
				{
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, m_ModelInfo.Material[DrawElements.MaterialIndex].diffuseTexObj);
					m_ModelShader->UniformXi(m_unif_DiffuseTexFlag, 1, 1, 0, 0, 0);
					m_ModelShader->UniformXi(m_unif_DiffuseTex, 1, 1, 0, 0, 0);
				}
				else
				{
					m_ModelShader->UniformXi(m_unif_DiffuseTexFlag, 1, 0, 0, 0, 0);
				}

				//テクスチャ（スペキュラ）がある場合は設定する
				if (0 != m_ModelInfo.Material[DrawElements.MaterialIndex].specularTexObj)
				{
					glActiveTexture(GL_TEXTURE2);
					glBindTexture(GL_TEXTURE_2D, m_ModelInfo.Material[DrawElements.MaterialIndex].specularTexObj);
					m_ModelShader->UniformXi(m_unif_SpecularTexFlag, 1, 1, 0, 0, 0);
					m_ModelShader->UniformXi(m_unif_SpecularTex, 1, 2, 0, 0, 0);
				}
				else
				{
					m_ModelShader->UniformXi(m_unif_SpecularTexFlag, 1, 0, 0, 0, 0);
				}

				//テクスチャ（バンプマップ）がある場合は設定する
				if (0 != m_ModelInfo.Material[DrawElements.MaterialIndex].bumpMapTexObj)
				{
					glActiveTexture(GL_TEXTURE3);
					glBindTexture(GL_TEXTURE_2D, m_ModelInfo.Material[DrawElements.MaterialIndex].bumpMapTexObj);
					m_ModelShader->UniformXi(m_unif_BumpMapTexFlag, 1, 1, 0, 0, 0);
					m_ModelShader->UniformXi(m_unif_BumpMapTex, 1, 3, 0, 0, 0);
				}
				else
				{
					m_ModelShader->UniformXi(m_unif_BumpMapTexFlag, 1, 0, 0, 0, 0);
				}

				//カラー関連の係数設定
				m_ModelShader->UniformXf(m_unif_Ambient, 3, m_ModelInfo.Material[DrawElements.MaterialIndex].ambient.r, 
														   m_ModelInfo.Material[DrawElements.MaterialIndex].ambient.g,
														   m_ModelInfo.Material[DrawElements.MaterialIndex].ambient.b, 0);
				m_ModelShader->UniformXf(m_unif_Diffuse, 3, m_ModelInfo.Material[DrawElements.MaterialIndex].diffuse.r,
														   m_ModelInfo.Material[DrawElements.MaterialIndex].diffuse.g,
														   m_ModelInfo.Material[DrawElements.MaterialIndex].diffuse.b, 0);
				m_ModelShader->UniformXf(m_unif_Specular, 3, m_ModelInfo.Material[DrawElements.MaterialIndex].specular.r,
															m_ModelInfo.Material[DrawElements.MaterialIndex].specular.g,
															m_ModelInfo.Material[DrawElements.MaterialIndex].specular.b, 0);
				m_ModelShader->UniformXf(m_unif_Shininess, 1, m_ModelInfo.Material[DrawElements.MaterialIndex].shininess, 0 ,0, 0);
				m_ModelShader->UniformXf(m_unif_Alpha, 1, m_ModelInfo.Material[DrawElements.MaterialIndex].alpha, 0, 0, 0);

				break;
			}

			default:

				break;
		}

		glDrawElements(DrawElements.mode, DrawElements.count, DrawElements.type, DrawElements.indices);
	}

	//シェーダーの変数を無効化
	m_ModelShader->DisableVertexAttribArray(m_attr_Position);
	m_ModelShader->DisableVertexAttribArray(m_attr_Normal);
	m_ModelShader->DisableVertexAttribArray(m_attr_Color);
	m_ModelShader->DisableVertexAttribArray(m_attr_TexCoord);

	//バッファーを無効化
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//テクスチャユニットフォデフォルトに戻す
	glActiveTexture(GL_TEXTURE0);

	//テクスチャを解除
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　OBJ形式のモデルファイルからモデルデータの読み込みを行います
*	引数
*	　p_DirFileName	：[I/ ]　読み込みを行う拡張子付きのモデルファイル名
*					　		（ディレクトリ構造も含んだフルパスを設定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::FileLoad_OBJ(const string &p_DirFileName)
{
	//引数チェック
	if (0 == p_DirFileName.length())
	{
		printf("失敗\n");
		ERROR_MESSAGE("OBJファイルの読み込み 引数エラー\n" \
					  "p_DirFileName = %s\n", p_DirFileName.c_str());
		return;
	}

	//OBJ, MTLファイルを読み込む
	OBJMESH mesh;
	mesh.LoadFile(p_DirFileName.c_str());

	//頂点数とデータを取得
	uint32_t NumVertices = mesh.GetNumVertices();
	OBJVERTEX *Vertices = mesh.GetVertices();

	//サブセット数とデータを取得
	uint32_t NumSubsets = mesh.GetNumSubsets();
	OBJSUBSET *Subsets = mesh.GetSubsets();

	//マテリアル数とデータを取得
	uint32_t NumMaterials = mesh.GetNumMaterials();
	OBJMATERIAL *Materials = mesh.GetMaterials();

	//インデックス数とデータを取得
	uint32_t NumIndices = mesh.GetNumIndices();
	uint32_t* Indices = mesh.GetIndices();

	//頂点座標の設定
	m_ModelInfo.Position.size = sizeof(Vertices->position) / sizeof(Vertices->position.x);
	m_ModelInfo.Position.type = GL_FLOAT;
	m_ModelInfo.Position.normalized = GL_FALSE;
	m_ModelInfo.Position.stride = sizeof(OBJVERTEX);
	m_ModelInfo.Position.pointer = 0;

	//法線の設定
	m_ModelInfo.Normal.size = sizeof(Vertices->normal) / sizeof(Vertices->normal.x);
	m_ModelInfo.Normal.type = GL_FLOAT;
	m_ModelInfo.Normal.normalized = GL_FALSE;
	m_ModelInfo.Normal.stride = sizeof(OBJVERTEX);
	m_ModelInfo.Normal.pointer = reinterpret_cast<GLvoid*>(sizeof(Vertices->position));

	//テクスチャ座標の設定
	m_ModelInfo.TexCoord.size = sizeof(Vertices->texcoord) / sizeof(Vertices->texcoord.x);
	m_ModelInfo.TexCoord.type = GL_FLOAT;
	m_ModelInfo.TexCoord.normalized = GL_FALSE;
	m_ModelInfo.TexCoord.stride = sizeof(OBJVERTEX);
	m_ModelInfo.TexCoord.pointer = reinterpret_cast<GLvoid*>(sizeof(Vertices->position) + sizeof(Vertices->normal));

	//描画情報の設定
	for (uint32_t cnt = 0; cnt < NumSubsets; cnt++)
	{
		DrawElementsInfo DrawElements = { 0 };
		DrawElements.mode = GL_TRIANGLES;
		DrawElements.count = Subsets[cnt].faceCount;
		DrawElements.type = GL_UNSIGNED_INT;
		DrawElements.indices = reinterpret_cast<GLvoid*>(Subsets[cnt].faceStart * sizeof(uint32_t));

		//特殊パラメータ（glDrawElementsには直接使用しない）
		//どのマテリアル情報を使用すればよいのかを示すパラメータを保存
		DrawElements.MaterialIndex = Subsets[cnt].materialIndex;

		//描画情報を追加
		m_ModelInfo.DrawElements.push_back(DrawElements);
	}

	//バッファーデータ設定
	glGenBuffers(1, &m_ModelInfo.BufferObj_v);
	glBindBuffer(GL_ARRAY_BUFFER, m_ModelInfo.BufferObj_v);
	glBufferData(GL_ARRAY_BUFFER, NumVertices * sizeof(OBJVERTEX), reinterpret_cast<GLvoid*>(Vertices), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ModelInfo.BufferObj_i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModelInfo.BufferObj_i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumIndices * sizeof(uint32_t), reinterpret_cast<GLvoid*>(Indices), GL_STATIC_DRAW);

	//バッファーを無効化
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//マテリアルデータの読み込み（数値部分のみ）
	for (uint32_t cnt = 0; cnt < NumMaterials; cnt++)
	{
		MaterialInfo Material = { 0 };

		//アンビエント値
		memmove(&Material.ambient, &Materials->ambient, sizeof(Material.ambient));

		//ディフューズ値
		memmove(&Material.diffuse, &Materials->diffuse, sizeof(Material.diffuse));

		//スペキュラ値
		memmove(&Material.specular, &Materials->specular, sizeof(Material.specular));

		//シャイネス値
		Material.shininess = Materials->shininess;

		//アルファ値
		Material.alpha = Materials->alpha;

		m_ModelInfo.Material.push_back(Material);
	}

	printf("完了\n");


	//////////////////////////////////
	// モデルデータのマテリアルデータに記載されていたテクスチャの読み込みを行う

	for (uint32_t cnt = 0; cnt < NumMaterials; cnt++)
	{
		//以下、簡略化出来る要素あり
		MaterialTex MaterialTex[] =	{
			{ Materials[cnt].ambientMapName,  &m_ModelInfo.Material[cnt].ambientTexObj },		//アンビエント
			{ Materials[cnt].diffuseMapName,  &m_ModelInfo.Material[cnt].diffuseTexObj },		//ディフューズ
			{ Materials[cnt].specularMapName, &m_ModelInfo.Material[cnt].specularTexObj},		//スペキュラ
			{ Materials[cnt].bumpMapName,	  &m_ModelInfo.Material[cnt].bumpMapTexObj },		//バンプマップ
		};

		//マテリアルの要素数を算出
		uint32_t MaterialCnt = sizeof(MaterialTex) / sizeof(MaterialTex[0]);
		for (uint32_t index = 0; index < MaterialCnt; index++)
		{
			//テクスチャが指定されていれば読み込む
			if (0 != MaterialTex[index].Name.length())
			{
				//テクスチャ読み込み（ディレクトリ構造を含まない文字列でデバッグ表示する）
				printf("モデルデータ「%s」用の\n　", p_DirFileName.substr(p_DirFileName.rfind("/") + 1).c_str());
				TextureInfo TextureData = { 0 };
				Texture::FileDataLoad(MaterialTex[index].Name, true, PixelFotmat::RGB_24BIT, &TextureData);

				//テクスチャオブジェクト作成
				GLuint TextureObj;
				glGenTextures(1, &TextureObj);
				glBindTexture(GL_TEXTURE_2D, TextureObj);
				glTexImage2D(GL_TEXTURE_2D, 0, TextureData.internalFormat, TextureData.width, TextureData.height, TextureData.border, TextureData.format, TextureData.type, TextureData.data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				//テクスチャオブジェクトを保存
				*MaterialTex[index].TexObj = TextureObj;

				//テクスチャデータを破棄
				Texture::FileDataFree(&TextureData);
			}
		}
	}

	//テクスチャを解除
	glBindTexture(GL_TEXTURE_2D, 0);

	//メモリ解放
	mesh.Release();
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する（エッジ有り）
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::DataLoad_PiercedCube(void)
{
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

	// インデックスデータ
	GLubyte index[] =
	{
		// v0  1  2  3  4  5  6  7  8  9  10 11 12 13
		0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
	};

	//頂点とインデックスのメモリを確保してコピーする
	GLvoid* PiercedCube_vertex = reinterpret_cast<GLvoid*>(calloc(sizeof(vertex), sizeof(byte)));
	GLvoid* PiercedCube_index = reinterpret_cast<GLvoid*>(calloc(sizeof(index), sizeof(byte)));
	memmove(PiercedCube_vertex, vertex, sizeof(vertex));
	memmove(PiercedCube_index, index, sizeof(index));

	//モデルデータ設定（頂点情報）
	m_ModelInfo.Position.size = sizeof(vertex[0].Position) / sizeof(vertex[0].Position.x);
	m_ModelInfo.Position.type = GL_FLOAT;
	m_ModelInfo.Position.normalized = GL_FALSE;
	m_ModelInfo.Position.stride = sizeof(Vec3_bColor3);
	m_ModelInfo.Position.pointer = 0;

	//モデルデータ設定（カラー情報）
	m_ModelInfo.Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	m_ModelInfo.Color.type = GL_UNSIGNED_BYTE;
	m_ModelInfo.Color.normalized = GL_TRUE;
	m_ModelInfo.Color.stride = sizeof(Vec3_bColor3);
	m_ModelInfo.Color.pointer = reinterpret_cast<GLvoid*>(sizeof(vertex[0].Position));

	//描画情報設定
	DrawElementsInfo DrawElements = { 0 };
	DrawElements.mode = GL_TRIANGLE_STRIP;
	DrawElements.count = sizeof(index) / sizeof(index[0]);
	DrawElements.type = GL_UNSIGNED_BYTE;
	DrawElements.indices = 0;
	m_ModelInfo.DrawElements.push_back(DrawElements);

	//バッファーデータ設定（頂点）
	glGenBuffers(1, &m_ModelInfo.BufferObj_v);
	glBindBuffer(GL_ARRAY_BUFFER, m_ModelInfo.BufferObj_v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), PiercedCube_vertex, GL_STATIC_DRAW);

	//バッファーデータ設定（インデックス）
	glGenBuffers(1, &m_ModelInfo.BufferObj_i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModelInfo.BufferObj_i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), PiercedCube_index, GL_STATIC_DRAW);

	//バッファーを無効化
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//メモリ解放
	SAFE_FREE(PiercedCube_vertex);
	SAFE_FREE(PiercedCube_index);

	printf("完了\n");
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　穴あきキューブを取得する（エッジ無し）
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void ModelManager::DataLoad_PiercedCube2(void)
{
	// 頂点データ
	Vec3_bColor3 vertex[] =
	{
		// v0
		{ { -10.0f, -10.0f, 10.0f },{ 90, 0, 0 } },
		// v1
		{ { -10.0f, -10.0f, -10.0f },{ 0, 90, 0 } },
		// v2
		{ { -10.0f, 10.0f, 10.0f },{ 0, 0, 90 } },
		// v3
		{ { -10.0f, 10.0f, -10.0f },{ 180, 0, 0 } },
		// v4
		{ { 10.0f, 10.0f, 10.0f },{ 0, 180, 0 } },
		// v5
		{ { 10.0f, 10.0f, -10.0f },{ 0, 0, 180 } },
		// v6
		{ { 10.0f, -10.0f, 10.0f },{ 250, 0, 0 } },
		// v7
		{ { 10.0f, -10.0f, -10.0f },{ 0, 250, 0 } },
	};

	// インデックスデータ
	GLubyte index[] =
	{
		// v0  1  2  3  4  5  6  7  8  9  10 11 12 13
		0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 1, 3, 7, 5,
	};

	//頂点とインデックスのメモリを確保してコピーする
	GLvoid* PiercedCube_vertex = reinterpret_cast<GLvoid*>(calloc(sizeof(vertex), sizeof(byte)));
	GLvoid* PiercedCube_index = reinterpret_cast<GLvoid*>(calloc(sizeof(index), sizeof(byte)));
	memmove(PiercedCube_vertex, vertex, sizeof(vertex));
	memmove(PiercedCube_index, index, sizeof(index));

	//モデルデータ設定（頂点情報）
	m_ModelInfo.Position.size = sizeof(vertex[0].Position) / sizeof(vertex[0].Position.x);
	m_ModelInfo.Position.type = GL_FLOAT;
	m_ModelInfo.Position.normalized = GL_FALSE;
	m_ModelInfo.Position.stride = sizeof(Vec3_bColor3);
	m_ModelInfo.Position.pointer = 0;

	//モデルデータ設定（カラー情報）
	m_ModelInfo.Color.size = sizeof(vertex[0].Color) / sizeof(vertex[0].Color.r);
	m_ModelInfo.Color.type = GL_UNSIGNED_BYTE;
	m_ModelInfo.Color.normalized = GL_TRUE;
	m_ModelInfo.Color.stride = sizeof(Vec3_bColor3);
	m_ModelInfo.Color.pointer = reinterpret_cast<GLvoid*>(sizeof(vertex[0].Position));

	//描画情報設定
	DrawElementsInfo DrawElements = { 0 };
	DrawElements.mode = GL_TRIANGLE_STRIP;
	DrawElements.count = sizeof(index) / sizeof(index[0]);
	DrawElements.type = GL_UNSIGNED_BYTE;
	DrawElements.indices = 0;
	m_ModelInfo.DrawElements.push_back(DrawElements);

	//バッファーデータ設定（頂点）
	glGenBuffers(1, &m_ModelInfo.BufferObj_v);
	glBindBuffer(GL_ARRAY_BUFFER, m_ModelInfo.BufferObj_v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), PiercedCube_vertex, GL_STATIC_DRAW);

	//バッファーデータ設定（インデックス）
	glGenBuffers(1, &m_ModelInfo.BufferObj_i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModelInfo.BufferObj_i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), PiercedCube_index, GL_STATIC_DRAW);

	//バッファーを無効化
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//メモリ解放
	SAFE_FREE(PiercedCube_vertex);
	SAFE_FREE(PiercedCube_index);

	printf("完了\n");
}