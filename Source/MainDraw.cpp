#include "MainDraw.h"

//�R���X�g���N�^
MainDraw::MainDraw()
{
	//Main�V�F�[�_�[�Ǘ��p�̃I�u�W�F�N�g����
	m_MainShader = new ShaderManager;

	//�ϐ�������
	m_attr_pos = -1;
	m_attr_color = -1;
	m_ProjModel_matrix = 0;

}

//�f�X�g���N�^
MainDraw::~MainDraw()
{
	//Main�V�F�[�_�[�Ǘ��p�̃I�u�W�F�N�g�j��
	delete m_MainShader;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���C���`��̏���������
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void MainDraw::Prepare()
{
	//�V�F�[�_�[�̓ǂݍ��݂��s��
	//�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��B
	m_MainShader->CreateShaderProgram("Main\\Main.vert", "Main\\Main.frag", "Main\\Main.geom", NULL, NULL);

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i���_�f�[�^�j
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�J���[�f�[�^�j
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i���W�ϊ��}�g���N�X�i�v���W�F�N�V�����}�g���N�X �~ ���f���r���[�}�g���b�N�X�j�j
	m_ProjModel_matrix = m_MainShader->GetUniformLocation("ProjModel_matrix");

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���C���`����J�n����
*	����
*	�@p_Global				�F[I/O]�@�O���[�o���f�[�^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(GlobalData *p_Global)
{
	// �V�F�[�_�[�v���O�����̗��p���J�n����
	m_MainShader->UseProgram();

	//���W�ϊ��}�g���N�X�i�v���W�F�N�V�����}�g���N�X �~ ���f���r���[�}�g���b�N�X�j
	Matrix ProjModel;
	ProjModel.SetMatrix(p_Global->ProjectionMatrix);
	ProjModel = ProjModel * p_Global->ModelViewMatrix;

	//�V�F�[�_�[�̕ϐ���L����
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	//�L���[�u�`��̃��f���f�[�^���擾����
	ModelDataInfo PiercedCube;
	ModelManager::GetPiercedCube(&PiercedCube, false);

	//�L���[�u�`��̃��f���f�[�^���擾����i�C���f�b�N�X�Łj
	ModelDataInfo_index PiercedCube_index;
	ModelManager::GetPiercedCube_index(&PiercedCube_index, false);

	//�k�x�e�X�g��L��
	glEnable(GL_DEPTH_TEST);

	//�w�i�F�w��
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//�F������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�r���[�|�[�g��ݒ肷��
	glViewport(0, 0, p_Global->WindowSize.Width, p_Global->WindowSize.Height);

	//�ϐ���]��
	m_MainShader->UniformMatrixXfv(m_ProjModel_matrix, 4, 1, GL_FALSE, ProjModel.GetMatrix());

	// [glDrawArrays]���g�p�����`��i��ԃI�[�\�h�b�N�X�i�����I�j�ȕ`����@�j
	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube.Vertex.size, PiercedCube.Vertex.type, PiercedCube.Vertex.normalized, PiercedCube.Vertex.stride, PiercedCube.Vertex.pointer);
	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube.Color.size, PiercedCube.Color.type, PiercedCube.Color.normalized, PiercedCube.Color.stride, PiercedCube.Color.pointer);
	glDrawArrays(PiercedCube.DrawArrays.mode, PiercedCube.DrawArrays.first, PiercedCube.DrawArrays.count);

	// [glDrawElements]���g�p�����`��i�C���f�b�N�X�o�b�t�@���g�p����ꍇ�j
//	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube_index.Vertex.size, PiercedCube_index.Vertex.type, PiercedCube_index.Vertex.normalized, PiercedCube_index.Vertex.stride, PiercedCube_index.Vertex.pointer);
//	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube_index.Color.size, PiercedCube_index.Color.type, PiercedCube_index.Color.normalized, PiercedCube_index.Color.stride, PiercedCube_index.Color.pointer);
//	glDrawElements(PiercedCube_index.DrawElement.mode, PiercedCube_index.DrawElement.count, PiercedCube_index.DrawElement.type, PiercedCube_index.DrawElement.indices);

}

