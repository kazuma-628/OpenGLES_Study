#include "MainDraw.h"

//�R���X�g���N�^
MainDraw::MainDraw()
{
	//Main�V�F�[�_�[�Ǘ��p�̃I�u�W�F�N�g����
	m_MainShader = new ShaderManager;

	//�ړ��ʊǗ��̕ϐ�������
	move_x = 0;
	move_y = 0;
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
void MainDraw::Prep()
{
	//�V�F�[�_�[�̓ǂݍ��݂��s��
	//�uShader�v�t�H���_�Ɋi�[����Ă���K�v������܂��B
	m_MainShader->CreateShaderProgram("Main.vert", "Main.frag");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i���_�f�[�^�j
	m_attr_pos = m_MainShader->GetAttribLocation("attr_pos");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�J���[�f�[�^�j
	m_attr_color = m_MainShader->GetAttribLocation("attr_color");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�}�g���b�N�X�f�[�^�j
	m_move_matrix = m_MainShader->GetUniformLocation("move_matrix");

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���C���`����J�n����
*	����
*	�@window		�F[I/ ]�@�`���̃E�B���h�E���w�肷��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void MainDraw::Draw(GLFWwindow *const p_window)
{
	// �V�F�[�_�[�v���O�����̗��p���J�n����
	m_MainShader->UseProgram();

	//�I�u�W�F�N�g���ړ������邽�߂̍s���錾
	Matrix Move;

	//�w��ʈړ�������
	Move.Translate(move_x, move_y, 0.5);
	Move.Scale(move_x, move_y, 0.5);
	Move.Rotate(1000 * move_x * move_y, 1.0, 0.0, 0.0);

	//�ړ��ʂ𑝉�������B
	move_x = move_x + 0.001f;
	move_y = move_y + 0.001f;

	//�l�����Z�b�g����i����m�F�p�̈ꎞ�I�ȃv���O�����j
	if (move_x > 1.0 || move_y > 1.0)
	{
		move_x = move_y = 0;
	}

	//�V�F�[�_�[�̕ϐ���L����
	glEnableVertexAttribArray(m_attr_pos);
	glEnableVertexAttribArray(m_attr_color);


	// ��ʒ����֕`�悷��
	const GLfloat position[] =
	{
		// v0
		-0.8f, 0.0f,
		// v1
		0.0f, 0.0f,
		// v2
		0.0f, -0.8f,
		// v3
		-0.8f, -0.8f
	};

	// ���_�J���[��ݒ肷��
	const GLubyte color[] =
	{
		// v0 rgb
		200, 200, 200,
		// v1 rgb
		200, 0, 0,
		// v2 rgb
		0, 200, 0,
		// v3 rgb
		0, 0, 200
	};

	//�w�i�F�w��
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);

	//�F������
	glClear(GL_COLOR_BUFFER_BIT);

	//�r���[�|�[�g��ݒ肷��
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//�ϐ���]��
	glVertexAttribPointer(m_attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	glVertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	glUniformMatrix4fv(m_move_matrix, 1, GL_FALSE, Move.GetMatrix());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//�`�揈��
	glfwSwapBuffers(p_window);
}

