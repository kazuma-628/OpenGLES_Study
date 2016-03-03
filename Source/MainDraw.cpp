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
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag");

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
*	�@p_KeyManager			�F[I/ ]�@Key�Ǘ��I�u�W�F�N�g
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void MainDraw::Drawing(WindowManager* p_WindowManager, KeyManager* p_KeyManager)
{
	//�쐬�����E�B���h�E�n���h�����擾
	GLFWwindow* const window = p_WindowManager->GetWindow();
	//�}�E�X�̏����擾
	MouseInfo MouseButton = p_KeyManager->GetMouseInfo();
	//�L�[�i�L�[�{�[�h�j�̏����擾
	KeyInfo KeyBoard = p_KeyManager->GetKeyInfo();
	
	// �V�F�[�_�[�v���O�����̗��p���J�n����
	m_MainShader->UseProgram();

	//�I�u�W�F�N�g���ړ������邽�߂̍s��
	Matrix ModelView;

	//3D��Ԃɂ��邽�߂̍s��
	Matrix Projection;


	///////////////////////////////////
	// �I�u�W�F�N�g�ړ��֌W�̏���

	//���s�ړ��p�̕ϐ��Ƀ}�E�X���̍��W��������
	m_Translate.x = m_Translate.x + MouseButton.Left.DiffPos.x;
	m_Translate.y = m_Translate.y + MouseButton.Left.DiffPos.y;
	m_Translate.z = m_Translate.z + MouseButton.Scroll;
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
	//�l�p�̌����ڂ̑O�Ɍ����悤�ɉ�]
	ModelView.Rotate(-90, 0.0f, 1.0f, 0.0f);

	
	//�������e�s���K�p����
	Projection.Perspective(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

	//�V�F�[�_�[�̕ϐ���L����
	m_MainShader->EnableVertexAttribArray(m_attr_pos);
	m_MainShader->EnableVertexAttribArray(m_attr_color);

	// ��ʒ����֕`�悷��
	const GLfloat position[] =
	{
		// v1
		-10.0f, 10.0f, 10.0f,
		// v2
		10.0f, 10.0f, 10.0f,
		// v3
		-10.0f, -10.0f, 10.0f,
		// v4
		10.0f, -10.0f, 10.0f,

		// v5
		-10.0f, -10.0f, -10.0f,
		// v6
		10.0f, -10.0f, -10.0f,

		// v7
		-10.0f, 10.0f, -10.0f,
		// v8
		10.0f, 10.0f, -10.0f,

		// v9
		-10.0f, 10.0f, 10.0f,
		// v10
		10.0f, 10.0f, 10.0f,

		// v11
		10.0f, 10.0f, 10.0f,
		// v12
		10.0f, -10.0f, 10.0f,
		// v13
		10.0f, 10.0f, -10.0f,
		// v14
		10.0f, -10.0f, -10.0f,
	};

	// ���_�J���[��ݒ肷��
	const GLubyte color[] =
	{
		// v1 rgb
		50, 50, 50,
		// v2 rgb
		90, 0, 0,
		// v3 rgb
		0, 90, 0,
		// v4 rgb
		0, 0, 90,

		// v5 rgb
		130, 0, 0,
		// v6 rgb
		0, 130, 0,

		// v7 rgb
		0, 0, 130,
		// v8 rgb
		170, 0, 0,

		// v9 rgb
		0, 170, 0,
		// v10 rgb
		0, 0, 170,

		// v11 rgb
		210, 0, 0,
		// v12 rgb
		0, 210, 0,
		// v13 rgb
		0, 0, 210,
		// v14 rgb
		250, 0, 0,
	};

	//�k�x�e�X�g��L��
	glEnable(GL_DEPTH_TEST);

	//�w�i�F�w��
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//�F������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�r���[�|�[�g��ݒ肷��
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//�ϐ���]��
	m_MainShader->VertexAttribPointer(m_attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	m_MainShader->VertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	m_MainShader->glUniformMatrixXfv(m_ModelView_matrix, 4, 1, GL_FALSE, ModelView.GetMatrix());
	m_MainShader->glUniformMatrixXfv(m_Proj_matrix, 4, 1, GL_FALSE, Projection.GetMatrix());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

	//�`�揈��
	glfwSwapBuffers(window);
}

