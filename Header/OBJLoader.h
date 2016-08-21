//-----------------------------------------------------------------------
// 「.obj」ファイルの読み込み処理に関して、
//　「PROJECT ASURA」サイト様で紹介されているソースコードをお借りしました。
//　技術的なお話もされていますので、興味がある方は一度訪問をお勧めいたします。
//　※ソースコードはほぼそのままですが、本プロジェクトに対応させるため一部改変しています。
//
//　メッシュを読み込む！！(1)　～OBJファイル～
//　http://asura.iaigiri.com/OpenGL/gl15_2.html
//-----------------------------------------------------------------------

#pragma region File Description
//-----------------------------------------------------------------------
// File : OBJLoader.h
// Desc : Alias Wavefron OBJ File Loader
// Date : Mar. 04, 2009
// Version : 2.1
// Author : Pocol
// Memo : 4角形対応済み。5角形以上はサポートしない
//-----------------------------------------------------------------------
#pragma endregion

#ifndef _OBJ_LOADER_H_INCLUDED_
#define _OBJ_LOADER_H_INCLUDED_

#pragma region Includes
//
// Includes
//
#include "Common.h"
#pragma endregion

#pragma region Using Statemetns
//
// Using Statements
//
using namespace std;
#pragma endregion

#pragma region Defines
//
// Defines
//
#define OBJ_BUFFER_LENGTH 1024
#define OBJ_NAME_LENGTH 256
#pragma region

/////////////////////////////////////////////////////////////////////////
// OBJVEC2
/////////////////////////////////////////////////////////////////////////
struct OBJVEC2
{
	float x;
	float y;
	OBJVEC2( float nx=0.0f, float ny=0.0f );
	operator float* ();
	operator const float* () const;
};

/////////////////////////////////////////////////////////////////////////
// OBJVEC3
/////////////////////////////////////////////////////////////////////////
struct OBJVEC3
{
	float x;
	float y;
	float z;
	OBJVEC3( float nx=0.0f, float ny=0.0f, float nz=0.0f );
	operator float* ();
	operator const float* () const;
};

/////////////////////////////////////////////////////////////////////////
// OBJVERTEX
/////////////////////////////////////////////////////////////////////////
struct OBJVERTEX
{
	OBJVEC3 position;
	OBJVEC3 normal;
	OBJVEC2 texcoord;
	OBJVERTEX(){}
};

/////////////////////////////////////////////////////////////////////////
// OBJSUBSET
/////////////////////////////////////////////////////////////////////////
struct OBJSUBSET
{
	unsigned int materialIndex;
	unsigned int faceStart;
	unsigned int faceCount;
	OBJSUBSET(){}
};

/////////////////////////////////////////////////////////////////////////
// OBJMATERIAL
/////////////////////////////////////////////////////////////////////////
struct OBJMATERIAL
{
	char name[OBJ_NAME_LENGTH];
	OBJVEC3 ambient;
	OBJVEC3 diffuse;
	OBJVEC3 specular;
	float shininess;
	float alpha;
	char ambientMapName[OBJ_NAME_LENGTH];
	char diffuseMapName[OBJ_NAME_LENGTH];
	char specularMapName[OBJ_NAME_LENGTH];
	char bumpMapName[OBJ_NAME_LENGTH];
	OBJMATERIAL(){}
};

/////////////////////////////////////////////////////////////////////////
// OBJBOUNDINGBOX
/////////////////////////////////////////////////////////////////////////
struct OBJBOUNDINGBOX
{
	OBJVEC3 maximum;
	OBJVEC3 minimum;
	OBJVEC3 size;
	void Merge( OBJVEC3 value );
	OBJBOUNDINGBOX() {}
	OBJBOUNDINGBOX( OBJVEC3 value );
};

/////////////////////////////////////////////////////////////////////////
// OBJBOUNDINGSPHERE
/////////////////////////////////////////////////////////////////////////
struct OBJBOUNDINGSPHERE
{
	OBJVEC3 center;
	float radius;
	void Create( OBJBOUNDINGBOX box );
	OBJBOUNDINGSPHERE() {}
};

/////////////////////////////////////////////////////////////////////////
// OBJMESH
/////////////////////////////////////////////////////////////////////////
class OBJMESH
{
private:
	OBJVERTEX* m_Vertices;
	OBJSUBSET* m_Subsets;
	OBJMATERIAL* m_Materials;
	unsigned int* m_Indices;
	unsigned int m_NumVertices;
	unsigned int m_NumSubsets;
	unsigned int m_NumMaterials;
	unsigned int m_NumIndices;
	OBJBOUNDINGBOX m_Box;
	OBJBOUNDINGSPHERE m_Sphere;
	char m_directoryPath[OBJ_NAME_LENGTH];

	bool LoadMTLFile( const char* filename );
	bool LoadOBJFile( const char* filename );

public:
	OBJMESH();
	~OBJMESH();

	bool LoadFile( const char* filename );
	void Release();
	void Draw();
	unsigned int GetNumVertices();
	unsigned int GetNumSubsets();
	unsigned int GetNumMaterials();
	unsigned int GetNumIndices();
	unsigned int  GetIndexData( unsigned int index );
	unsigned int* GetIndices();
	OBJVERTEX  GetVertex( unsigned int index );
	OBJVERTEX* GetVertices();
	OBJSUBSET  GetSubset( unsigned int index );
	OBJSUBSET* GetSubsets();
	OBJMATERIAL  GetMaterial( unsigned int index );
	OBJMATERIAL* GetMaterials();
	OBJBOUNDINGBOX GetBox();
	OBJBOUNDINGSPHERE GetSphere();
};

#endif	//　_OBJ_LOADER_H_INCLUDED_