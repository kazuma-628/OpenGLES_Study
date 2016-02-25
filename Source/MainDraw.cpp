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

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X�j
	m_ModelView_matrix = m_MainShader->GetUniformLocation("ModelView_matrix");

	//�V�F�[�_�[���Ŏg�p����ϐ����擾���܂��i3D��Ԃɂ��邽�߂̃}�g���N�X�j
	m_Proj_matrix = m_MainShader->GetUniformLocation("Proj_matrix");

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
	Matrix ModelView;

	Matrix Projection;

	//���W��M��p�̕ϐ�
	double x_pos = 0;
	double y_pos = 0;
	double x_pos2 = 0;
	double y_pos2 = 0;

	//�}�E�X�̍��W���擾���܂��B
	//�E�B���h�E�n�̍��W������܂��B
	glfwGetCursorPos(p_window, &x_pos, &y_pos);

	//�E�B���h�E���W���A-10�`10�Ƀ}�b�`����悤�ɕϊ����܂��B
	x_pos2 = (20.0 / WINDOW_WIDTH) * x_pos - 10.0;
	y_pos2 = (20.0 / WINDOW_HEIGHT) * (WINDOW_HEIGHT - y_pos) - 10.0;

	//�f�o�b�O�p�v�����g��
//	printf("x_pos = %lf x_pos2 = %lf y_pos = %lf y_pos2 = %lf\n", x_pos, x_pos2, y_pos, y_pos2);

	//�J�����̉f��ʒu�Ɉړ������A�}�E�X�ł��ړ��ł���悤�ɂ���B
	ModelView.Translate(x_pos2, y_pos2, -20.0);
	
	//��]������
	ModelView.Rotate(1000 * move_y, 0.0, 1.0, 0.0);
	
	//�ړ��ʂ𑝉�������B
//	move_x = move_x + 0.001f;
	move_y = move_y + 0.001f;

	//�l�����Z�b�g����i����m�F�p�̈ꎞ�I�ȃv���O�����j
	if (move_x > 10 || move_y > 10 )
	{
		move_x = move_y = 0;
	}

	//�������e�s���K�p����
	Projection.Perspective(-10.0, 10.0, -10.0, 10.0, 10.0, 30.0);

	//�V�F�[�_�[�̕ϐ���L����
	glEnableVertexAttribArray(m_attr_pos);
	glEnableVertexAttribArray(m_attr_color);


	// ��ʒ����֕`�悷��
	const GLfloat position[] =
	{
		// v0
		-10.0f, 10.0f, 0.0f,
		// v1
		10.0f, 10.0f, 0.0f,
		// v2
		10.0f, -10.0f, 0.0f,
		// v3
		-10.0f, -10.0f, 0.0f
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
	glVertexAttribPointer(m_attr_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
	glVertexAttribPointer(m_attr_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
	glUniformMatrix4fv(m_ModelView_matrix, 1, GL_FALSE, ModelView.GetMatrix());
	glUniformMatrix4fv(m_Proj_matrix, 1, GL_FALSE, Projection.GetMatrix());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//�`�揈��
	glfwSwapBuffers(p_window);
}

