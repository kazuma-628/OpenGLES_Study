//-----------------------------------------------------------------------
// 「.obj」ファイルの読み込み処理に関して、
//　「PROJECT ASURA」サイト様で紹介されているソースコードをお借りしました。
//　技術的なお話もされていますので、興味がある方は一度訪問をお勧めいたします。
//　※ソースコードはほぼそのままですが、本プロジェクトに対応させるため一部改変しています。
//
//　メッシュを読み込む！！(1)　〜OBJファイル〜
//　http://asura.iaigiri.com/OpenGL/gl15_2.html
//-----------------------------------------------------------------------

#pragma region File Description
//-----------------------------------------------------------------------
// File : OBJLoader.cpp
// Desc : Alias Wavefront OBJ File Loader
// Date : Mar. 04, 2009
// Version : 2.1
// Author : Pocol
// Memo : 4角形対応済み。5角形以上はサポートしない。
//-----------------------------------------------------------------------
#pragma endregion 

#pragma region Includes
//
// Includes
//
#include "OBJLoader.h"
#pragma endregion

#pragma region Defines
//
// Defines
//

// RtlZeroMemory Macro
#ifndef RtlZeroMemory
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

// ZeroMemory Macro
#ifndef ZeroMemory
#define ZeroMemory RtlZeroMemory
#endif

// SAFE_DELETE_ARRAY
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if (x) { delete [] (x); (x) = NULL; } }
#endif
#pragma endregion


//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : GetDirectionPath()
// Desc : 文字列からディレクトリを取得
//------------------------------------------------------------------------
char* GetDirectoryPath( const char* filename )
{
	char *strings = NULL;
	char *dir;
	dir = new char [strlen(filename)+1];
	strcpy(dir, filename);
	if ( strings = strrchr(dir, '/' ) ) strings[1] = '\0';
	else if ( strings = strrchr(dir, '\\') ) strings[1] ='\0';
	else dir[0] = '\0';
	return dir;
}

//-----------------------------------------------------------------------
// Name : CutDirectoryPath()
// Desc : 文字列からディレクトリを削除
//-----------------------------------------------------------------------
char* CutDirectoryPath( const char* filename )
{
	char *s=NULL;
	char *base=NULL;
	base = new char [strlen(filename)+1];
	strcpy( base, filename );
	if ( s = strrchr(base, '\\') )
	{
		s++;
		return s;
	}
	else if ( s = strrchr(base, '/') )
	{
		s++;
		return s;
	}
	else
	{ 
		return base;
	}
}

//-----------------------------------------------------------------------
// Name : SetDirectoryPath
// Desc : ディレクトリを前に付加して文字列を返す
//-----------------------------------------------------------------------
char* SetDirectoryPath( const char* dest, char* directory )
{
	char* str;
	str = new char[strlen(directory) + strlen(dest) + 1];
	strcpy( str, directory );
	strcat( str, dest );
	return str;
}

//-----------------------------------------------------------------------
// Name : InitMaterial()
// Desc : マテリアルの初期化
//-----------------------------------------------------------------------
void InitMaterial( OBJMATERIAL* pMaterial )
{
	ZeroMemory( pMaterial, sizeof( OBJMATERIAL ) );
	pMaterial->ambient = OBJVEC3( 0.2f, 0.2f, 0.2f );
	pMaterial->diffuse = OBJVEC3( 0.8f, 0.8f, 0.8f );
	pMaterial->specular = OBJVEC3( 1.0f, 1.0f, 1.0f );
	pMaterial->shininess = 0.0f;
	pMaterial->alpha = 1.0f;
}

//-----------------------------------------------------------------------
// Name : SetMaterial()
// Desc : マテリアルを設定する
//-----------------------------------------------------------------------
void SetMaterial( OBJMATERIAL* pMaterial )
{
	//OpenGL ESでは使用できない関数があるためコメントアウト
	/*
	glColor4f( pMaterial->diffuse.x, pMaterial->diffuse.y, pMaterial->diffuse.z, pMaterial->alpha );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &pMaterial->shininess );
	*/
}

//-----------------------------------------------------------------------
// Name : OBJVEC3Scale()
// Desc : スケール倍する
//-----------------------------------------------------------------------
OBJVEC3 OBJVEC3Scale( OBJVEC3 v, float scale )
{ return OBJVEC3( v.x * scale, v.y * scale, v.z * scale ); }

//-----------------------------------------------------------------------
// Name : OBJVEC3Add()
// Desc : 足し算する
//-----------------------------------------------------------------------
OBJVEC3 OBJVEC3Add( OBJVEC3 v1, OBJVEC3 v2 )
{ return OBJVEC3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }

//-----------------------------------------------------------------------
// Name : OBJVEC3Substract()
// Desc : 引き算する
//-----------------------------------------------------------------------
OBJVEC3 OBJVEC3Substract( OBJVEC3 v1, OBJVEC3 v2 )
{ return OBJVEC3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }

//-----------------------------------------------------------------------
// Name : OBJVEC3Length()
// Desc : 長さを求める
//-----------------------------------------------------------------------
float OBJVEC3Length( OBJVEC3 v )
{ return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }

//-----------------------------------------------------------------------
// Name : OBJVEC3Max()
// Desc : 最大値を求める
//-----------------------------------------------------------------------
OBJVEC3 OBJVEC3Max( OBJVEC3 v, OBJVEC3 _max )
{
	OBJVEC3 result;
	result.x = ( v.x > _max.x ? v.x : _max.x );
	result.y = ( v.y > _max.y ? v.y : _max.y );
	result.z = ( v.z > _max.z ? v.z : _max.z );
	return result;
}

//------------------------------------------------------------------------
// Name : OBJVEC3Min()
// Desc : 最小値を求める
//------------------------------------------------------------------------
OBJVEC3 OBJVEC3Min( OBJVEC3 v, OBJVEC3 _min )
{
	OBJVEC3 result;
	result.x = ( v.x < _min.x ? v.x : _min.x );
	result.y = ( v.y < _min.y ? v.y : _min.y );
	result.z = ( v.z < _min.z ? v.z : _min.z );
	return result;
}

//////////////////////////////////////////////////////////////////////////
// OBJVEC2
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : OBJVEC2()
// Desc : コンストラクタ
//------------------------------------------------------------------------
OBJVEC2::OBJVEC2( float nx, float ny )
: x(nx), y(ny)
{
}

//-----------------------------------------------------------------------
// operator float*
//-----------------------------------------------------------------------
OBJVEC2::operator float * () 
{ return (float*)&x; }

//-----------------------------------------------------------------------
// operator const float*
//-----------------------------------------------------------------------
OBJVEC2::operator const float *() const 
{ return (const float*)&x; }


//////////////////////////////////////////////////////////////////////////
// OBJVEC3
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : OBJVEC3()
// Desc : コンストラクタ
//------------------------------------------------------------------------
OBJVEC3::OBJVEC3( float nx, float ny, float nz )
: x(nx), y(ny), z(nz)
{
}

//------------------------------------------------------------------------
// operator float*
//------------------------------------------------------------------------
OBJVEC3::operator float *() 
{ return (float*)&x; }

//------------------------------------------------------------------------
// operator const float*
//------------------------------------------------------------------------
OBJVEC3::operator const float *() const
{ return (const float*)&x; }

//////////////////////////////////////////////////////////////////////////
// OBJBOUNDINGBOX
/////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
// Name : OBJBOUNDINGBOX()
// Desc : コンストラクタ
//-----------------------------------------------------------------------
OBJBOUNDINGBOX::OBJBOUNDINGBOX( OBJVEC3 value )
: minimum( value ), maximum( value )
{
}

//-----------------------------------------------------------------------
// Name : Merage()
// Desc : 
//-----------------------------------------------------------------------
void OBJBOUNDINGBOX::Merge(OBJVEC3 value)
{
	maximum = OBJVEC3Max( value, maximum );
	minimum = OBJVEC3Min( value, minimum );
	size = OBJVEC3Substract( maximum, minimum );
}

//////////////////////////////////////////////////////////////////////////
// OBJBOUNDINGSPHERE
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : Create()
// Desc :
//------------------------------------------------------------------------
void OBJBOUNDINGSPHERE::Create( OBJBOUNDINGBOX box )
{
	center = OBJVEC3Add( box.maximum, box.minimum );
	center = OBJVEC3Scale( center, 0.5f );

	OBJVEC3 half;
	half = OBJVEC3Substract( box.maximum, center );
	radius = OBJVEC3Length( half );
}


/////////////////////////////////////////////////////////////////////////
// OBJMESH
/////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
// Name : OBJMESH()
// Desc : コンストラクタ
//-----------------------------------------------------------------------
OBJMESH::OBJMESH()
{
	m_NumVertices = 0;
	m_NumMaterials = 0;
	m_NumSubsets = 0;
	m_NumIndices = 0;

	m_Vertices = 0;
	m_Materials = 0;
	m_Subsets = 0;
	m_Indices = 0;
}

//-----------------------------------------------------------------------
// Name : ~OBJMESH()
// Desc : デストラクタ
//-----------------------------------------------------------------------
OBJMESH::~OBJMESH()
{
	Release();
};

//-----------------------------------------------------------------------
// Name : Release()
// Desc : メモリを破棄
//-----------------------------------------------------------------------
void OBJMESH::Release()
{
	SAFE_DELETE_ARRAY( m_Vertices );
	SAFE_DELETE_ARRAY( m_Materials );
	SAFE_DELETE_ARRAY( m_Subsets );
	SAFE_DELETE_ARRAY( m_Indices );
	
	m_NumVertices = 0;
	m_NumMaterials = 0;
	m_NumSubsets = 0;
	m_NumIndices = 0;
}

//-----------------------------------------------------------------------
// Name : LoadOBJFile()
// Desc : OBJファイルの読み込み
//-----------------------------------------------------------------------
bool OBJMESH::LoadOBJFile(const char *filename)
{
	ifstream file;

	char buf[OBJ_BUFFER_LENGTH] = {0};
	vector<OBJVEC3> positions;
	vector<OBJVEC3> normals;
	vector<OBJVEC2> texcoords;
	vector<OBJVERTEX> t_vertices;
	vector<OBJSUBSET> t_subsets;
	vector<unsigned int> t_indices;
	bool initBox = false;
	int prevSize = 0;

	unsigned long total = 0;

	OBJMATERIAL material;
	unsigned int dwFaceIndex = 0;
	unsigned int dwFaceCount = 0;
	unsigned int dwCurSubset = 0;

	//　ディレクトリを切り取り
	strcpy( m_directoryPath, GetDirectoryPath( filename ) );

	//　ファイルを開く
	file.open( filename, ios::in );

	//　チェック
	if ( !file.is_open() )
	{
		printf("失敗\n");
		ERROR_MESSAGE("OBJファイルのオープンに失敗しました。\n"\
					  "「Resource/Model」フォルダに格納されていますか？\n"\
					  "ファイル名が間違っていませんか？");
		return false;
	}

	//　ループ
	for( ;; )
	{
		file >> buf;
		if ( !file )
			break;

		//　コメント
		if ( 0 == strcmp( buf, "#" ) )
		{
			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

		//　頂点座標
		else if ( 0 == strcmp( buf, "v" ) )
		{
			float x, y, z;
			file >> x >> y >> z;
			OBJVEC3 v( x, y, z );
			positions.push_back( v );

			//　バウンディングボックスの初期化
			if ( !initBox )
			{
				m_Box = OBJBOUNDINGBOX( v );
				initBox = true;
			}

			//　バウンディングボックスの算出
			m_Box.Merge( v );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

		//　テクスチャ座標
		else if ( 0 == strcmp( buf, "vt" ) )
		{
			float u, v;
			file >> u >> v;
			texcoords.push_back( OBJVEC2( u, v ) );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

		//　法線ベクトル
		else if ( 0 == strcmp( buf, "vn" ) )
		{
			float x, y, z;
			file >> x >> y >> z;
			normals.push_back( OBJVEC3( x, y, z) );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

		//　面
		else if ( 0 == strcmp( buf, "f" ) )
		{
			unsigned int iPosition, iTexCoord, iNormal;
			unsigned int p[4] = { 0 }, t[4] = { 0 }, n[4] = { 0 };
			OBJVERTEX vertex;
			dwFaceIndex++;
			dwFaceCount++;
			int count = 0;
			unsigned int index = 0;

			//変数初期化
			memset(&p, -1, sizeof(p));
			memset(&t, -1, sizeof(t));
			memset(&n, -1, sizeof(n));
		
			//　三角形・四角形のみ対応
			for ( int iFace = 0; iFace < 4; iFace++ )
			{
				count++;	//　頂点数を数える
				ZeroMemory( &vertex, sizeof( OBJVERTEX ) );

				file >> iPosition;
				vertex.position = positions[ iPosition - 1 ];
				p[iFace] = iPosition -1;
				
				if ( '/' == file.peek() )
				{
					file.ignore();

					//　テクスチャ座標インデックス
					if ( '/' != file.peek() )
					{
						file >> iTexCoord;
						vertex.texcoord = texcoords[ iTexCoord - 1 ];
						t[iFace] = iTexCoord -1;
					}

					//　法線ベクトルインデックス
					if ( '/' == file.peek() )
					{
						file.ignore();

						file >> iNormal;
						vertex.normal = normals[ iNormal - 1 ];
						n[iFace] = iNormal -1;
					}
				}

				//　カウントが3未満
				if ( iFace < 3 )
				{
					t_vertices.push_back( vertex );
					index = t_vertices.size()-1;
					t_indices.push_back( index );
				}

				//　次が改行だったら終了
				if ( '\n' == file.peek() )
				{
					break;
				}

			}

			//　四角形ポリゴンの場合，三角形を追加する
			if ( count > 3 )
			{
				//　カウント
				dwFaceIndex++;
				dwFaceCount++;

				//　頂点とインデックスを追加
				for ( int iFace = 1; iFace < 4; iFace++ )
				{
					int j = (iFace+1)%4;
					ZeroMemory( &vertex, sizeof( OBJVERTEX ) );

					if ( p[j] != -1 ) vertex.position = positions[ p[j] ];
					if ( t[j] != -1 ) vertex.texcoord = texcoords[ t[j] ];
					if ( n[j] != -1 ) vertex.normal = normals[ n[j] ];

					t_vertices.push_back( vertex );
					index = t_vertices.size() - 1;
					t_indices.push_back( index );
				}

			}

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

		//　マテリアルファイル
		else if ( 0 == strcmp( buf, "mtllib" ) )
		{
			std::string mtlFileName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, mtlFileName);

			//　マテリアルファイルの読み込み
			if ( mtlFileName[0] )
			{
				//OBJファイルがあるディレクトリまでのパスを付加させる
				//最初の行には空白があるので1文字読み飛ばす（第一引数について）
				char *MTLNameFullPath = SetDirectoryPath(mtlFileName.c_str() + 1, m_directoryPath);

				if ( !LoadMTLFile( MTLNameFullPath ) )
				{
					//エラー処理等あればここに記載
					//MTLファイルが読み込めなかった時のエラーメッセージはロード関数先で出力済み

					return false;
				}

				//ファイル名を保持したメモリを破棄
				delete[] MTLNameFullPath;

			}
		}

		//　マテリアル
		else if ( 0 == strcmp( buf, "usemtl" ) )
		{
			std::string strName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, strName);

			OBJSUBSET subset;
			subset.faceCount = 1;

			for ( unsigned int i = 0; i < m_NumMaterials; i++ )
			{
				//最初の行には空白があるので1文字読み飛ばす（第一引数について）
				if ( 0 == strcmp( m_Materials[i].name, strName.c_str() + 1) )
				{
					dwCurSubset = i;
					break;
				}
			}

			subset.materialIndex = dwCurSubset;
			subset.faceStart = dwFaceIndex*3;
			prevSize = t_subsets.size();
			t_subsets.push_back( subset );
			if ( t_subsets.size() > 1 )
			{
				t_subsets[prevSize-1].faceCount = dwFaceCount*3;
				dwFaceCount = 0;
			}
		}

		else
		{
			//関係ない行は読み飛ばす
			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

	}

	//　サブセット
	if ( t_subsets.size() > 0 )
	{
		int maxSize = t_subsets.size();
		t_subsets[maxSize-1].faceCount = dwFaceCount*3;
	}

	//　ファイルを閉じる
	file.close();

	//　頂点データをコピー
	m_NumVertices = t_vertices.size();
	m_Vertices = new OBJVERTEX[ m_NumVertices ];
	for ( unsigned int i = 0; i<m_NumVertices; i++ )
		m_Vertices[i] = t_vertices[i];

	//　サブセットデータをコピー
	m_NumSubsets = t_subsets.size();
	m_Subsets = new OBJSUBSET[ m_NumSubsets ];
	for ( unsigned int i =0; i<m_NumSubsets; i++ )
		m_Subsets[i] = t_subsets[i];

	//　インデックスデータをコピー
	m_NumIndices = t_indices.size();
	m_Indices = new unsigned int [ m_NumIndices ];
	for ( unsigned int i = 0; i<m_NumIndices; i++ )
		m_Indices[i] = t_indices[i];

	//　バウンディングスフィアの作成
	m_Sphere.Create( m_Box );

	//　メモリ破棄
	positions.clear();
	normals.clear();
	texcoords.clear();
	t_vertices.clear();
	t_subsets.clear();
	t_indices.clear();

	//　正常終了
	return true;
}

//-----------------------------------------------------------------------
// Name : LoadMTLFile()
// Desc : MTLファイルの読み込み
//-----------------------------------------------------------------------
bool OBJMESH::LoadMTLFile( const char* filename )
{
	char buf[OBJ_BUFFER_LENGTH] = {0};
	int iMtlCount = -1;
	ifstream file;
	vector<OBJMATERIAL> t_materials;
	OBJMATERIAL material;
	InitMaterial( &material );

	//　ファイルを開く
	file.open( filename, ios::in );

	//　チェック
	if ( !file.is_open() )
	{
		printf("失敗\n");
		ERROR_MESSAGE("MTLファイルのオープンに失敗しました。\n"\
					  "「Resource/Model」フォルダに格納されていますか？\n"\
					  "ファイル名が間違っていませんか？"\
					  "OBJファイルに記載されていた、参照元のMTLファイルは下記です。"\
					  "→ %s\n", filename);
		return false;
	}

	//　ループ
	for( ;; )
	{
		file >> buf;
		if ( !file )
			break;

		// New Material
		if ( 0 == strcmp( buf, "newmtl" ) )
		{
			iMtlCount++;
			t_materials.push_back( material );

			std::string strName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, strName);
			
			strcpy( t_materials[iMtlCount].name, strName.c_str() + 1 );
		}
		// Ambient Color
		else if ( 0 == strcmp( buf, "Ka" ) )
		{
			float r, g, b;
			file >> r >> g >> b;
			t_materials[iMtlCount].ambient = OBJVEC3( r, g, b );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}
		// Diffuse Color
		else if ( 0 == strcmp( buf, "Kd" ) )
		{
			float r, g, b;
			file >> r >> g >> b;
			t_materials[iMtlCount].diffuse = OBJVEC3( r, g, b );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}
		// Specular Color
		else if ( 0 == strcmp( buf, "Ks" ) )
		{
			float r, g, b;
			file >> r >> g >> b;
			t_materials[iMtlCount].specular = OBJVEC3( r, g, b );

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}
		// Alpha
		else if ( 0 == strcmp( buf, "d" ) ||
				  0 == strcmp( buf, "Tr" ) )
		{
			file >> t_materials[iMtlCount].alpha;

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}
		// Shininess
		else if ( 0 == strcmp( buf, "Ns" ) )
		{
			file >> t_materials[iMtlCount].shininess;

			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}
		// Ambient Map
		else if ( 0 == strcmp( buf, "map_Ka" ) )
		{
			std::string mapKaName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, mapKaName);

			//OBJファイルがあるディレクトリまでのパスを付加させる
			//最初の行には空白があるので1文字読み飛ばす（第一引数について）
			char *mapKaNameFullPath = SetDirectoryPath(mapKaName.c_str() + 1, m_directoryPath);

			strcpy( t_materials[iMtlCount].ambientMapName, mapKaNameFullPath );

			//ファイル名を保持したメモリを破棄
			delete[] mapKaNameFullPath;
		}
		// Diffuse Map
		else if ( 0 == strcmp( buf, "map_Kd" ) )
		{
			std::string mapKdName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, mapKdName);
			
			//OBJファイルがあるディレクトリまでのパスを付加させる
			//最初の行には空白があるので1文字読み飛ばす（第一引数について）
			char *mapKdNameFullPath = SetDirectoryPath(mapKdName.c_str() + 1, m_directoryPath);

			strcpy( t_materials[iMtlCount].diffuseMapName, mapKdNameFullPath );

			//ファイル名を保持したメモリを破棄
			delete[] mapKdNameFullPath;
		}
		// Specular Map
		else if ( 0 == strcmp( buf, "map_Ks" ) )
		{
			std::string mapKsName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, mapKsName);

			//OBJファイルがあるディレクトリまでのパスを付加させる
			//最初の行には空白があるので1文字読み飛ばす（第一引数について）
			char *mapKsNameFullPath = SetDirectoryPath(mapKsName.c_str() + 1, m_directoryPath);

			strcpy( t_materials[iMtlCount].specularMapName, mapKsNameFullPath );

			//ファイル名を保持したメモリを破棄
			delete[] mapKsNameFullPath;
		}
		// Bump Map
		else if ( 0 == strcmp( buf, "map_Bump" ) )
		{
			std::string mapBumpName(OBJ_NAME_LENGTH, 0);

			//空白が含まれているファイル名でも読み込みできるように1行として読み込みする
			std::getline(file, mapBumpName);
			
			//OBJファイルがあるディレクトリまでのパスを付加させる
			//最初の行には空白があるので1文字読み飛ばす（第一引数について）
			char *mapBumpNameFullPath = SetDirectoryPath(mapBumpName.c_str() + 1, m_directoryPath);

			strcpy( t_materials[iMtlCount].bumpMapName, mapBumpNameFullPath );

			//ファイル名を保持したメモリを破棄
			delete[] mapBumpNameFullPath;
		}
		else
		{
			//関係ない行は読み飛ばす
			file.ignore(OBJ_BUFFER_LENGTH, '\n');
		}

	}

	//　ファイルを閉じる
	file.close();

	//　マテリアルデータをコピー
	m_NumMaterials = t_materials.size();
	m_Materials = new OBJMATERIAL[ m_NumMaterials ];
	for ( unsigned int i = 0; i<m_NumMaterials; i++ )
		m_Materials[i] = t_materials[i];

	//　メモリ破棄
	t_materials.clear();

	//　正常終了
	return true;
}

//-----------------------------------------------------------------------
// Name : LoadFile()
// Desc : メッシュファイルの読み込み
//-----------------------------------------------------------------------
bool OBJMESH::LoadFile( const char* filename )
{
	//　OBJ, MTLファイルを読み込み
	if ( !LoadOBJFile( filename ) )
	{
		//エラー処理等あればここに記載
		//OBJ, MTLファイルが読み込めなかった時のエラーメッセージはロード関数先で出力済み

		//　メッシュファイルの後片付け
		Release();

		return false;
	}

	//　正常終了
	return true;
}

			
//-----------------------------------------------------------------------
// Name : Draw()
// Desc : 描画処理
//-----------------------------------------------------------------------
void OBJMESH::Draw()
{
	//OpenGL ESでは使用できない関数があるためコメントアウト
	/*
	for ( unsigned int i = 0; i<m_NumSubsets; i++ )
	{
		//　マテリアル
		OBJMATERIAL* pMat = &m_Materials[m_Subsets[i].materialIndex];
		SetMaterial( pMat );	

		//　三角形描画
		glInterleavedArrays( GL_T2F_N3F_V3F, 0, m_Vertices );
		glDrawElements( GL_TRIANGLES, m_Subsets[i].faceCount, GL_UNSIGNED_INT, &m_Indices[m_Subsets[i].faceStart] );
	}
	*/
}


//------------------------------------------------------------------------
// Name : GetNumVertices()
// Desc : 頂点数を取得
//------------------------------------------------------------------------
unsigned int OBJMESH::GetNumVertices()
{ return m_NumVertices; }

//-----------------------------------------------------------------------
// Name : GetNumSubsets()
// Desc : サブセット数を取得
//-----------------------------------------------------------------------
unsigned int OBJMESH::GetNumSubsets()
{ return m_NumSubsets; }

//-----------------------------------------------------------------------
// Name : GetNumMaterials()
// Desc : マテリアル数を取得
//-----------------------------------------------------------------------
unsigned int OBJMESH::GetNumMaterials()
{ return m_NumMaterials; }

//-----------------------------------------------------------------------
// Name : GetNumIndices()
// Desc : インデックス数を取得
//-----------------------------------------------------------------------
unsigned int OBJMESH::GetNumIndices()
{ return m_NumIndices; }

//-----------------------------------------------------------------------
// Name : GetIndexData()
// Desc : 指定されたインデックスデータを取得
//-----------------------------------------------------------------------
unsigned int OBJMESH::GetIndexData( unsigned int index )
{ return m_Indices[index]; }

//-----------------------------------------------------------------------
// Name : GetVertex()
// Desc : 指定された頂点データを取得
//-----------------------------------------------------------------------
OBJVERTEX OBJMESH::GetVertex( unsigned int index )
{ return m_Vertices[index]; }

//-----------------------------------------------------------------------
// Name : GetSubsets()
// Desc : 指定されたサブセットデータを取得
//-----------------------------------------------------------------------
OBJSUBSET OBJMESH::GetSubset( unsigned int index )
{ return m_Subsets[index]; }

//-----------------------------------------------------------------------
// Name : GetMaterial()
// Desc : 指定されたマテリアルデータを取得
//-----------------------------------------------------------------------
OBJMATERIAL OBJMESH::GetMaterial( unsigned int index )
{ return m_Materials[index]; }

//-----------------------------------------------------------------------
// Name : GetVertices()
// Desc : 頂点データを取得
//-----------------------------------------------------------------------
OBJVERTEX* OBJMESH::GetVertices()
{ return m_Vertices; }

//-----------------------------------------------------------------------
// Name : GetSubsets()
// Desc : サブセットデータを取得
//-----------------------------------------------------------------------
OBJSUBSET* OBJMESH::GetSubsets()
{ return m_Subsets; }

//-----------------------------------------------------------------------
// Name : GetMaterails()
// Desc : マテリアルデータを取得
//-----------------------------------------------------------------------
OBJMATERIAL* OBJMESH::GetMaterials()
{ return m_Materials; }

//-----------------------------------------------------------------------
// Name : GetIndices()
// Desc : インデックスデータを取得
//-----------------------------------------------------------------------
unsigned int* OBJMESH::GetIndices()
{ return m_Indices; }
		
//-----------------------------------------------------------------------
// Name : GetBox()
// Desc : バウンディングボックスを取得
//-----------------------------------------------------------------------
OBJBOUNDINGBOX OBJMESH::GetBox()
{ return m_Box; }

//-----------------------------------------------------------------------
// Name : GetSphere()
// Desc : バウンディングスフィアを取得
//-----------------------------------------------------------------------
OBJBOUNDINGSPHERE OBJMESH::GetSphere()
{ return m_Sphere; }



					


			




