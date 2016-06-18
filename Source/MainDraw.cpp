#include "MainDraw.h"

//�R���X�g���N�^
MainDraw::MainDraw()
{
	//Main�V�F�[�_�[�Ǘ��p�̃I�u�W�F�N�g����
	m_MainShader = new ShaderManager;

	//�ϐ�������
	memset(&m_Rotate, 0, sizeof(m_Rotate));
	memset(&m_Translate, 0, sizeof(m_Translate));
	m_attr_pos = -1;
	m_attr_color = -1;
	m_ModelView_matrix = 0;
	m_Proj_matrix = 0;

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
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag", "Main.geom");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i���_�f�[�^�j
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�J���[�f�[�^�j
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X�j
	m_ModelView_matrix = m_MainShader->GetUniformLocation("ModelView_matrix");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i3D��Ԃɂ��邽�߂̃}�g���N�X�j
	m_Proj_matrix = m_MainShader->GetUniformLocation("Proj_matrix");

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���C���`����J�n����
*	����
*	�@p_WindowManager		�F[I/ ]�@�E�B���h�E�Ǘ��I�u�W�F�N�g
*	�@p_DeviceManager		�F[I/ ]�@Key�Ǘ��I�u�W�F�N�g
*	�@p_ResourceManager		�F[I/ ]�@���\�[�X�Ǘ��I�u�W�F�N�g
*	  p_ModelManager		�F[I/ ]	 ���f���f�[�^�Ǘ��I�u�W�F�N�g
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(WindowManager* p_WindowManager, DeviceManager* p_DeviceManager, ResourceManager *p_ResourceManager, ModelManager *p_ModelManager)
{
	//�E�B���h�E�T�C�Y�̎擾
	WindowSize const WindowSize = p_WindowManager->GetWindowSize();
	//�}�E�X�̏����擾
	MouseInfo MouseButton = p_DeviceManager->GetMouseInfo();
	//�L�[�i�L�[�{�[�h�j�̏����擾
	KeyInfo KeyBoard = p_DeviceManager->GetKeyInfo();
	
	// �V�F�[�_�[�v���O�����̗��p���J�n����
	m_MainShader->UseProgram();

	//�I�u�W�F�N�g���ړ������邽�߂̍s��
	Matrix ModelView;

	//3D��Ԃɂ��邽�߂̍s��
	Matrix Projection;


	///////////////////////////////////
	// �I�u�W�F�N�g�ړ��֌W�̏���

	//�X�y�[�X�ŏ����ʒu�ɖ߂�
	if (true == KeyBoard.Change.Key_SPACE)
	{
		memset(&m_Translate, 0, sizeof(m_Translate));
		memset(&m_Rotate, 0, sizeof(m_Rotate));
	}

	//���s�ړ��p�̕ϐ��Ƀ}�E�X���̍��W��������
	m_Translate.x = m_Translate.x + MouseButton.Left.DiffPos.x;
	m_Translate.y = m_Translate.y + MouseButton.Left.DiffPos.y;
	m_Translate.z = m_Translate.z + MouseButton.Scroll;
	//�X�ɃL�[�{�[�h�̏���������
	if (GLFW_PRESS == KeyBoard.Change.Key_W)
	{
		m_Translate.z = m_Translate.z + 0.5f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_S)
	{
		m_Translate.z = m_Translate.z - 0.5f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_A)
	{
		m_Translate.x = m_Translate.x + 1.0f;
	}
	if (GLFW_PRESS == KeyBoard.Change.Key_D)
	{
		m_Translate.x = m_Translate.x - 1.0f;
	}

	//��]�p�̕ϐ��Ƀ}�E�X���̍��W��������
	//�{���ł����360�x��]������ϐ������������������ǂ����A�T���v���Ȃ̂Ŋ���
	m_Rotate.x = m_Rotate.x + MouseButton.Right.DiffPos.x;
	m_Rotate.y = m_Rotate.y + MouseButton.Right.DiffPos.y;

	//�J�����̉f��ʒu�Ɉړ�������
	ModelView.Translate(0.0, 0.0, -35.0f);
	//�}�E�X�ł̃I�u�W�F�N�g�̈ړ�
	ModelView.Translate(m_Translate.x / 6.0f, -m_Translate.y / 6.0f, m_Translate.z);
	
	//�}�E�X�ł̃I�u�W�F�N�g�̉�]
	ModelView.Rotate(-m_Rotate.x / 2.0f, 0.0f, 1.0f, 0.0f);
	ModelView.Rotate(-m_Rotate.y / 2.0f, 1.0f, 0.0f, 0.0f);
	
	//�������e�s���K�p����
	Projection.Perspective(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	//������̕��@
//	Projection.Perspective(1.0, 100.0, 60.0, WindowSize.Width / WindowSize.Height);

	//�V�F�[�_�[�̕ϐ���L����
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	//�L���[�u�`��̃��f���f�[�^���擾����
	ModelDataInfo PiercedCube;
	p_ModelManager->GetPiercedCube(&PiercedCube, false);

	//�L���[�u�`��̃��f���f�[�^���擾����i�C���f�b�N�X�Łj
	ModelDataInfo_index PiercedCube_index;
	p_ModelManager->GetPiercedCube_index(&PiercedCube_index, false);

	//�k�x�e�X�g��L��
	glEnable(GL_DEPTH_TEST);

	//�w�i�F�w��
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//�F������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�r���[�|�[�g��ݒ肷��
	glViewport(0, 0, WindowSize.Width, WindowSize.Height);

	//�ϐ���]��
	m_MainShader->UniformMatrixXfv(m_ModelView_matrix, 4, 1, GL_FALSE, ModelView.GetMatrix());
	m_MainShader->UniformMatrixXfv(m_Proj_matrix, 4, 1, GL_FALSE, Projection.GetMatrix());

	// [glDrawArrays]���g�p�����`��i��ԃI�[�\�h�b�N�X�i�����I�j�ȕ`����@�j
	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube.Vertex.size, PiercedCube.Vertex.type, PiercedCube.Vertex.normalized, PiercedCube.Vertex.stride, PiercedCube.Vertex.pointer);
	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube.Color.size, PiercedCube.Color.type, PiercedCube.Color.normalized, PiercedCube.Color.stride, PiercedCube.Color.pointer);
	glDrawArrays(PiercedCube.DrawArrays.mode, PiercedCube.DrawArrays.first, PiercedCube.DrawArrays.count);

	// [glDrawElements]���g�p�����`��i�C���f�b�N�X�o�b�t�@���g�p����ꍇ�j
//	m_MainShader->VertexAttribPointer(m_attr_pos, PiercedCube_index.Vertex.size, PiercedCube_index.Vertex.type, PiercedCube_index.Vertex.normalized, PiercedCube_index.Vertex.stride, PiercedCube_index.Vertex.pointer);
//	m_MainShader->VertexAttribPointer(m_attr_color, PiercedCube_index.Color.size, PiercedCube_index.Color.type, PiercedCube_index.Color.normalized, PiercedCube_index.Color.stride, PiercedCube_index.Color.pointer);
//	glDrawElements(PiercedCube_index.DrawElement.mode, PiercedCube_index.DrawElement.count, PiercedCube_index.DrawElement.type, PiercedCube_index.DrawElement.indices);

	//�`�揈��
	p_WindowManager->DrawingOnWindow();
}

