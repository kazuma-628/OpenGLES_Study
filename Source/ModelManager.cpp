#include "ModelManager.h"

/////////////////////////////////////////////
//static�ϐ��̎��̂��`

ModelManager::Vertex ModelManager::m_PiercedCube;					//�������L���[�u�p�̒��_�f�[�^
ModelManager::Vertex_index ModelManager::m_PiercedCube_index;		//�������L���[�u�p�̒��_�f�[�^�i�C���f�b�N�X�Łj

//�R���X�g���N�^
ModelManager::ModelManager()
{
	//������
	memset(&m_PiercedCube, 0, sizeof(m_PiercedCube));
	memset(&m_PiercedCube_index, 0, sizeof(m_PiercedCube_index));
}

//�f�X�g���N�^
ModelManager::~ModelManager()
{
	//���������
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
void ModelManager::GetPiercedCube(ModelDataInfo *p_ModelData, bool p_vbo)
{
	// ���_�f�[�^
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

	//��x���ǂݍ��񂾂��Ƃ��Ȃ��ꍇ
	if (NULL == m_PiercedCube.vertex)
	{
		//���������m�ۂ��ăR�s�[����
		m_PiercedCube.vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
		memmove(m_PiercedCube.vertex, vertex, sizeof(vertex));
	}

	//���f���f�[�^�ݒ�i���_���j
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

	//���f���f�[�^�ݒ�i�J���[���j
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

	//�o�b�t�@�[�f�[�^�ݒ�
	p_ModelData->BufferData.size = sizeof(vertex);
	p_ModelData->BufferData.data = m_PiercedCube.vertex;

	//�`����ݒ�
	p_ModelData->DrawArrays.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawArrays.first = 0;
	p_ModelData->DrawArrays.count = sizeof(vertex) / sizeof(vertex[0]);
}

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
void ModelManager::GetPiercedCube_index(ModelDataInfo_index *p_ModelData, bool p_vbo)
{
	// ���_�f�[�^
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

	// �C���f�b�N�X�f�[�^
	GLubyte index[] =
	{
	// v0  1  2  3  4  5  6  7  8  9  10 11 12 13
		0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 1, 3, 7, 5,
	};

	//��x���ǂݍ��񂾂��Ƃ��Ȃ��ꍇ
	if (NULL == m_PiercedCube_index.vertex)
	{
		//���������m�ۂ��ăR�s�[����
		m_PiercedCube_index.vertex = (GLvoid*)calloc(sizeof(vertex), sizeof(byte));
		m_PiercedCube_index.index = (GLvoid*)calloc(sizeof(index), sizeof(byte));
		memmove(m_PiercedCube_index.vertex, vertex, sizeof(vertex));
		memmove(m_PiercedCube_index.index, index, sizeof(index));
	}

	//���f���f�[�^�ݒ�i���_���j
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

	//���f���f�[�^�ݒ�i�J���[���j
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

	//�o�b�t�@�[�f�[�^�ݒ�
	p_ModelData->BufferData.size = sizeof(vertex);
	p_ModelData->BufferData.data = m_PiercedCube_index.vertex;

	//�`����ݒ�
	p_ModelData->DrawElements.mode = GL_TRIANGLE_STRIP;
	p_ModelData->DrawElements.count = sizeof(index) / sizeof(index[0]);
	p_ModelData->DrawElements.type = GL_UNSIGNED_BYTE;
	p_ModelData->DrawElements.indices = m_PiercedCube_index.index;
}
