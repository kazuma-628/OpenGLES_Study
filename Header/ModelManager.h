#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

//include��`
#include "Common.h"

////////////////////////////////////
// ���f���f�[�^���\����

//���_�p�����[�^���i[VertexAttribPointer]�p�j
typedef struct
{
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid *pointer;
}VertexAttribPointerInfo;

//[glDrawArrays]�p�p�����[�^���
typedef struct
{
	GLenum mode;
	GLint first;
	GLsizei count;
}DrawArraysInfo;

//[glDrawElements]�p�p�����[�^���
typedef struct
{
	GLenum mode;
	GLsizei count;
	GLenum type;
	const void *indices;
}DrawElementsInfo;

//�o�b�t�@�[�f�[�^�p�iglBufferData���j�p�����[�^���
typedef struct
{
	GLsizei size;		//�S���_�̃T�C�Y�ibyte�j
	GLvoid *data;		//�S���_���i�[���ꂽ�擪�A�h���X
}BufferDataInfo;

//���f���f�[�^���
typedef struct
{
	VertexAttribPointerInfo Vertex;		//���_���
	VertexAttribPointerInfo Color;		//�J���[���
	DrawArraysInfo DrawArrays;			//�`����
	BufferDataInfo BufferData;			//�o�b�t�@�[���
}ModelDataInfo;

//���f���f�[�^�i�C���f�b�N�X�g�p�Łj���
typedef struct
{
	VertexAttribPointerInfo Vertex;		//���_���
	VertexAttribPointerInfo Color;		//�J���[���
	DrawElementsInfo DrawElements;		//�`����
	BufferDataInfo BufferData;			//�o�b�t�@�[���
}ModelDataInfo_index;

class ModelManager
{

public:
	//�R���X�g���N�^
	ModelManager();

	//�f�X�g���N�^
	~ModelManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�������L���[�u���擾����
	*	�@�i[glDrawArrays]�Ƃ��ēo�^���郂�f���f�[�^�j
	*	����
	*	�@p_ModelData		�F[ /O]�@���f���f�[�^���
	*	�@p_vbo				�F[I/ ]�@���f���f�[�^��VBO�Ƃ��ēo�^/�g�p����ꍇ�́utrue�v�����łȂ��ꍇ�́ufalse�v���w��
	*						�@		 VBO�Ƃ��Ďg�p����ꍇ�A�uglBufferData�v�Ńf�[�^��o�^���邵�Ă���uglDrawArrays�v����B
	*								 �o�^����f�[�^��[size]�ɁuBufferData.size�v���A[data]�ɁuBufferData.data�v���w�肷��Ηǂ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	static void GetPiercedCube(ModelDataInfo *p_ModelData, bool p_vbo);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�������L���[�u���擾����i�C���f�b�N�X�Łj
	*	�@�i[glDrawElements]�p�p�����[�^���j
	*	����
	*	�@p_ModelData		�F[ /O]�@���f���f�[�^���
	*	�@p_vbo				�F[I/ ]�@���f���f�[�^��VBO�Ƃ��ēo�^/�g�p����ꍇ�́utrue�v�����łȂ��ꍇ�́ufalse�v���w��
	*						�@		 VBO�Ƃ��Ďg�p����ꍇ�A�uglBufferData�v�Ńf�[�^��o�^���邵�Ă���uglDrawElements�v����B
	*								 �o�^����f�[�^��[size]�ɁuBufferData.size�v���A[data]�ɁuBufferData.data�v���w�肷��Ηǂ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	static void GetPiercedCube_index(ModelDataInfo_index *p_ModelData, bool p_vbo);

private:

	///////////////////////////////
	// �\���̒�`

	// ���_�f�[�^�\����
	typedef struct
	{
		Vec2 Vector;
		bColor3 Color;
	}Vec2_bColor3;

	// ���_�f�[�^�\����
	typedef struct
	{
		Vec2 Vector;
		bColor4 Color;
	}Vec2_bColor4;

	// ���_�f�[�^�\����
	typedef struct
	{
		Vec3 Vector;
		bColor3 Color;
	}Vec3_bColor3;

	// ���_�f�[�^�\����
	typedef struct
	{
		Vec3 Vector;
		bColor4 Color;
	}Vec3_bColor4;

	// ���_�|�C���^�\����
	typedef struct
	{
		GLvoid *vertex;
	}Vertex;

	// ���_�|�C���^�\����
	typedef struct
	{
		GLvoid *vertex;
		GLvoid *index;
	}Vertex_index;

	///////////////////////////////
	// �ϐ�

	static Vertex		m_PiercedCube;				//�������L���[�u�p�̒��_�f�[�^
	static Vertex_index	m_PiercedCube_index;		//�������L���[�u�p�̒��_�f�[�^�i�C���f�b�N�X�Łj
};

#endif