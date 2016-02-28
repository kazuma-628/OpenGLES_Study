#include "KeyManager.h"

/////////////////////////////////////////////
//static�ϐ��̎��̂��`

MouseInfo KeyManager::m_MouseInfo;			//�}�E�X�{�^���̏��
CursorPos KeyManager::m_OldCursorPos;			//���O�i1�C�x���g�O�j�̃J�[�\�����W		

//�R���X�g���N�^
KeyManager::KeyManager()
{
	m_window = NULL;

	memset(&m_MouseInfo.Right, 0, sizeof(m_MouseInfo.Right));
	m_MouseInfo.Right.State = GLFW_RELEASE;

	memset(&m_MouseInfo.Left, 0, sizeof(m_MouseInfo.Right));
	m_MouseInfo.Right.State = GLFW_RELEASE;
}

//�f�X�g���N�^
KeyManager::~KeyManager()
{

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Key�Ǘ��}�l�[�W���[������������
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void KeyManager::Initialize(GLFWwindow* const p_window)
{
	//�E�B���h�E����ۑ�
	m_window = p_window;

	//�}�E�X�{�^�����ω��������p�̃R�[���o�b�N��o�^
	glfwSetMouseButtonCallback(m_window, KeyManager::MouseButtonCallback);

	//�}�E�X�z�C�[�����ω��������p�̃R�[���o�b�N��o�^
	glfwSetScrollCallback(m_window, KeyManager::ScrollCallback);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�}�E�X�{�^�����ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_button	�F[I/ ]�@�ǂ̃{�^�����ω�������
*	�@p_button	�F[I/ ]�@�����ꂽ�iGLFW_PRESS�j or �����ꂽ�iGLFW_RELEASE�j
*	�@p_button	�F[I/ ]�@�悭�킩��Ȃ�
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga1e008c7a8751cea648c8f42cc91104cf
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void KeyManager::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	//���W���擾�p�̈ꎞ�ϐ�
	double PosX = 0.0;
	double PosY = 0.0;

	//�J�[�\���̍��W���擾���܂��i�E�B���h�E�n�̍��W������܂��j
	glfwGetCursorPos(p_window, &PosX, &PosY);

	//���W�Ǘ��p�̕ϐ��錾
	//�@���W�擾API�̈�����[double]�ׁ̈A���ʂ����d���Ȃ����̂悤�ȋ��n�������Ă���
	//�@�i���̂悤�ɂ��Ȃ��ƁA�R���p�C���Ń��[�j���O���o��̂Łj
	CursorPos Pos;
	Pos.x = (float)PosX;
	Pos.y = (float)PosY;

	//�J�[�\���̍��W��ۑ�
	m_OldCursorPos.x = Pos.x;
	m_OldCursorPos.y = Pos.y;

	//�E�N���b�N�Ɋւ��鏈��
	if (GLFW_MOUSE_BUTTON_RIGHT == p_button)
	{
		//�����ꂽ�ꍇ
		if (GLFW_PRESS == p_action)
		{
			printf("�E�N���b�N��������܂���\n");

			//���̃{�^�����N���b�N����Ă��Ȃ����ɏ�������
			if (GLFW_PRESS != m_MouseInfo.Left.State)
			{
				//�}�E�X�����������ɃR�[���o�b�N�����悤�ɂ���
				glfwSetCursorPosCallback(p_window, KeyManager::CursorPosCallback);
			}

			//�����ꂽ���Ƃ��L��
			m_MouseInfo.Right.State = GLFW_PRESS;

			//�����ꂽ���̍��W���L��
			m_MouseInfo.Right.Pos.x = Pos.x;
			m_MouseInfo.Right.Pos.y = Pos.y;
			m_MouseInfo.Right.ClickPos.x = Pos.x;
			m_MouseInfo.Right.ClickPos.y = Pos.y;
		}
		//�����ꂽ�ꍇ
		else if (GLFW_RELEASE == p_action)
		{
			//���̃{�^�����N���b�N����Ă��Ȃ����ɏ�������
			if (GLFW_PRESS != m_MouseInfo.Left.State)
			{
				//�}�E�X�����������ɃR�[���o�b�N����Ȃ��悤�ɂ���
				glfwSetCursorPosCallback(p_window, NULL);
			}

			//�����ꂽ���Ƃ��L��
			m_MouseInfo.Right.State = GLFW_RELEASE;

			//�ێ����Ă������W��������
			m_MouseInfo.Right.DiffPos.x = 0;
			m_MouseInfo.Right.DiffPos.y = 0;
			m_MouseInfo.Right.ClickDiffPos.x = 0;
			m_MouseInfo.Right.ClickDiffPos.y = 0;
		}
	}

	//���N���b�N�Ɋւ��鏈��
	else if (GLFW_MOUSE_BUTTON_LEFT == p_button)
	{
		//�����ꂽ�ꍇ
		if (GLFW_PRESS == p_action)
		{
			printf("���N���b�N��������܂���\n");

			//���̃{�^�����N���b�N����Ă��Ȃ����ɏ�������
			if (GLFW_PRESS != m_MouseInfo.Right.State)
			{
				//�}�E�X�����������ɃR�[���o�b�N�����悤�ɂ���
				glfwSetCursorPosCallback(p_window, KeyManager::CursorPosCallback);
			}

			//�����ꂽ���Ƃ��L��
			m_MouseInfo.Left.State = GLFW_PRESS;

			//�����ꂽ���̍��W���L��NULL
			m_MouseInfo.Left.Pos.x = Pos.x;
			m_MouseInfo.Left.Pos.y = Pos.y;
			m_MouseInfo.Left.ClickPos.x = Pos.x;
			m_MouseInfo.Left.ClickPos.y = Pos.y;
		}
		//�����ꂽ�ꍇ
		else if (GLFW_RELEASE == p_action)
		{
			//���̃{�^�����N���b�N����Ă��Ȃ����ɏ�������
			if (GLFW_PRESS != m_MouseInfo.Right.State)
			{
				//�}�E�X�����������ɃR�[���o�b�N����Ȃ��悤�ɂ���
				glfwSetCursorPosCallback(p_window, NULL);
			}

			//�����ꂽ���Ƃ��L��
			m_MouseInfo.Left.State = GLFW_RELEASE;

			//�ێ����Ă������W��������
			m_MouseInfo.Left.DiffPos.x = 0;
			m_MouseInfo.Left.DiffPos.y = 0;
			m_MouseInfo.Left.ClickDiffPos.x = 0;
			m_MouseInfo.Left.ClickDiffPos.y = 0;
		}
	}

	//�^�񒆃N���b�N�Ɋւ��鏈���i���g�͏������݂̂Ŗ������j
	else if (GLFW_MOUSE_BUTTON_MIDDLE == p_button)
	{
		//�����ꂽ�ꍇ
		if (GLFW_PRESS == p_action)
		{
			printf("�^�񒆃N���b�N��������܂���\n");
		}
		//�����ꂽ�ꍇ
		else if (GLFW_RELEASE == p_action)
		{
			
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�}�E�X�z�C�[�����ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_xoffset	�F[I/ ]�@�X�N���[����X���I�t�Z�b�g
*	�@p_yoffset	�F[I/ ]�@�X�N���[����Y���I�t�Z�b�g
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga6228cdf94d28fbd3a9a1fbb0e5922a8a
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void KeyManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{

	//�ЂƂ܂��X�N���[���㉺�����g��Ȃ��\��Ȃ̂Łup_yoffset�v�̂ݎ擾
	m_MouseInfo.Scroll = (float)p_yoffset;

	/////////////////////////////////////////////
	//	�f�o�b�O�p

//	printf("p_xoffset = %f, p_yoffset = %f\n", p_xoffset, p_yoffset);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�}�E�X�J�[�\�������������ɃR�[���o�b�N�����֐�
*	�@�i����������̃}�E�X�{�^����������Ă���Œ��̂ݗL���ɂ��Ă���
*�@�@�@�@�̂ŁA�^�C�~���O�͉E�L�֐��Q�Ɓ@KeyManager::MouseButtonCallback�j
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_xpos	�F[I/ ]�@X ���W
*	�@p_xpos	�F[I/ ]�@Y ���W
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga592fbfef76d88f027cb1bc4c36ebd437
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void KeyManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
{

	//���W�p�̕ϐ��錾
	//�@�R�[���o�b�N�pAPI�̈�����[double]�ׁ̈A���ʂ����d���Ȃ����̂悤�ȋ��n�������Ă���
	//�@�i���̂悤�ɂ��Ȃ��ƁA�R���p�C���Ń��[�j���O���o��̂Łj
	CursorPos Pos;
	Pos.x = (float)p_xpos;
	Pos.y = (float)p_ypos;

	//�E�N���b�N��������Ă���ꍇ
	if (GLFW_PRESS == m_MouseInfo.Right.State)
	{
		//���݂̍��W���X�V
		m_MouseInfo.Right.Pos.x = Pos.x;
		m_MouseInfo.Right.Pos.y = Pos.y;

		//���O�̃J�[�\���ʒu����̍������X�V
		m_MouseInfo.Right.DiffPos.x = Pos.x - m_OldCursorPos.x;
		m_MouseInfo.Right.DiffPos.y = Pos.y - m_OldCursorPos.y;

		//�N���b�N���ꂽ������̍������X�V
		m_MouseInfo.Right.ClickDiffPos.x = Pos.x - m_MouseInfo.Right.ClickPos.x;
		m_MouseInfo.Right.ClickDiffPos.y = Pos.y - m_MouseInfo.Right.ClickPos.y;
	}
	
	//���N���b�N��������Ă���ꍇ
	if (GLFW_PRESS == m_MouseInfo.Left.State)
	{
		//���݂̍��W���X�V
		m_MouseInfo.Left.Pos.x = Pos.x;
		m_MouseInfo.Left.Pos.y = Pos.y;

		//���O�̃J�[�\���ʒu����̍������X�V
		m_MouseInfo.Left.DiffPos.x = Pos.x - m_OldCursorPos.x;
		m_MouseInfo.Left.DiffPos.y = Pos.y - m_OldCursorPos.y;

		//�N���b�N���ꂽ������̍������X�V
		m_MouseInfo.Left.ClickDiffPos.x = Pos.x - m_MouseInfo.Left.ClickPos.x;
		m_MouseInfo.Left.ClickDiffPos.y = Pos.y - m_MouseInfo.Left.ClickPos.y;
	}

	//�J�[�\���̍��W��ۑ�
	m_OldCursorPos.x = Pos.x;
	m_OldCursorPos.y = Pos.y;
	
	/////////////////////////////////////////////
	//	�f�o�b�O�p

	//	printf("Right.ClickDiffPos.x = %f, Right.ClickDiffPos.y = %f\n", m_MouseInfo.Right.ClickDiffPos.x, m_MouseInfo.Right.ClickDiffPos.y);
	//	printf("Left.ClickDiffPos.x = %f, Left.ClickDiffPos.y = %f\n", m_MouseInfo.Left.ClickDiffPos.x, m_MouseInfo.Left.ClickDiffPos.y);

	//	printf("Right.DiffPos.x = %f, Right.DiffPos.y = %f\n", m_MouseInfo.Right.DiffPos.x, m_MouseInfo.Right.DiffPos.y);
	//	printf("Left.DiffPos.x = %f, Left.DiffPos.y = %f\n", m_MouseInfo.Left.DiffPos.x, m_MouseInfo.Left.DiffPos.y);
}