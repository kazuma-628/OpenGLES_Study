#include "DeviceManager.h"

/////////////////////////////////////////////
//static�ϐ��̎��̂��`

MouseInfo DeviceManager::m_MouseInfo;			//�}�E�X�{�^���̏��
CursorPos DeviceManager::m_OldCursorPos;		//���O�i1�C�x���g�O�j�̃J�[�\�����W		
KeyInfo DeviceManager::m_KeyInfo;				//�L�[�i�L�[�{�[�h�j�̏��

//�R���X�g���N�^
DeviceManager::DeviceManager()
{
	m_window = NULL;

	memset(&m_MouseInfo, 0, sizeof(m_MouseInfo));
	m_MouseInfo.Right.State = GLFW_RELEASE;
	m_MouseInfo.Left.State = GLFW_RELEASE;

	memset(&m_OldCursorPos, 0, sizeof(m_OldCursorPos));
	memset(&m_KeyInfo.Change, GLFW_RELEASE, sizeof(m_KeyInfo.Change));
	memset(&m_KeyInfo.Keep, false, sizeof(m_KeyInfo.Keep));
}

//�f�X�g���N�^
DeviceManager::~DeviceManager()
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
void DeviceManager::Initialize(GLFWwindow* const p_window)
{
	//�E�B���h�E����ۑ�
	m_window = p_window;

	//�}�E�X�{�^�����ω��������p�̃R�[���o�b�N��o�^
	glfwSetMouseButtonCallback(m_window, DeviceManager::MouseButtonCallback);

	//�}�E�X�z�C�[�����ω��������p�̃R�[���o�b�N��o�^
	glfwSetScrollCallback(m_window, DeviceManager::ScrollCallback);

	//�L�[�i�L�[�{�[�h�j���ω��������p�̃R�[���o�b�N
	glfwSetKeyCallback(m_window, DeviceManager::KeyCallback);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�}�E�X�{�^�����ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_button	�F[I/ ]�@�ǂ̃{�^�����ω�������
*	�@p_action	�F[I/ ]�@�����ꂽ�iGLFW_PRESS�j or �����ꂽ�iGLFW_RELEASE�j
*	�@p_mods	�F[I/ ]�@�悭�킩��Ȃ�
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga1e008c7a8751cea648c8f42cc91104cf
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
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
				glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);
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
				glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);
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
*	�@�}�E�X�J�[�\�������������ɃR�[���o�b�N�����֐�
*	�@�i����������̃}�E�X�{�^����������Ă���Œ��̂ݗL���ɂ��Ă���
*�@�@�@�@�̂ŁA�^�C�~���O�͉E�L�֐��Q�Ɓ@DeviceManager::MouseButtonCallback�j
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_xpos	�F[I/ ]�@X ���W
*	�@p_xpos	�F[I/ ]�@Y ���W
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga592fbfef76d88f027cb1bc4c36ebd437
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
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
void DeviceManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{

	//�ЂƂ܂��X�N���[���㉺�����g��Ȃ��\��Ȃ̂Łup_yoffset�v�̂ݎ擾
	m_MouseInfo.Scroll = (float)p_yoffset;

	/////////////////////////////////////////////
	//	�f�o�b�O�p

//	printf("p_xoffset = %f, p_yoffset = %f\n", p_xoffset, p_yoffset);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�L�[�i�L�[�{�[�h�j���ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window		�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_key			�F[I/ ]�@�L�[�{�[�h�̃L�[���i['A']�Ƃ�['5']�Ƃ��j
*	�@p_scancode	�F[I/ ]�@�悭�킩��Ȃ��i�V�X�e���ŗL�̂ǂ����炱������j
*	�@p_action		�F[I/ ]�@�����ꂽ�iGLFW_PRESS�j or �����ꂽ�iGLFW_RELEASE�j
*	�@p_mods		�F[I/ ]�@Shift��Ctrl�Ȃǂ�������Ă��邩�̔��f�i��`����URL�Q�Ɓj
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@http://www.glfw.org/docs/latest/group__input.html#ga6228cdf94d28fbd3a9a1fbb0e5922a8a
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{

	//�L�[�̏��Ɗi�[����ϐ����܂Ƃ߂ĊǗ�����
	KeyInfoSummary KeySummary[KEY_SUMMARY_MAX] =
	{
		//�A���t�@�x�b�g�i26�j
		{ "A", GLFW_KEY_A , &m_KeyInfo.Change.Key_A, &m_KeyInfo.Keep.Key_A },
		{ "B", GLFW_KEY_B, &m_KeyInfo.Change.Key_B, &m_KeyInfo.Keep.Key_B },
		{ "C", GLFW_KEY_C , &m_KeyInfo.Change.Key_C, &m_KeyInfo.Keep.Key_C },
		{ "D", GLFW_KEY_D, &m_KeyInfo.Change.Key_D, &m_KeyInfo.Keep.Key_D },
		{ "E", GLFW_KEY_E , &m_KeyInfo.Change.Key_E, &m_KeyInfo.Keep.Key_E },
		{ "F", GLFW_KEY_F, &m_KeyInfo.Change.Key_F, &m_KeyInfo.Keep.Key_F },
		{ "G", GLFW_KEY_G , &m_KeyInfo.Change.Key_G, &m_KeyInfo.Keep.Key_G },
		{ "H", GLFW_KEY_H, &m_KeyInfo.Change.Key_H, &m_KeyInfo.Keep.Key_H },
		{ "I", GLFW_KEY_I , &m_KeyInfo.Change.Key_I, &m_KeyInfo.Keep.Key_I },
		{ "J", GLFW_KEY_J, &m_KeyInfo.Change.Key_J, &m_KeyInfo.Keep.Key_J },
		{ "K", GLFW_KEY_K , &m_KeyInfo.Change.Key_K, &m_KeyInfo.Keep.Key_K },
		{ "L", GLFW_KEY_L, &m_KeyInfo.Change.Key_L, &m_KeyInfo.Keep.Key_L },
		{ "M", GLFW_KEY_M , &m_KeyInfo.Change.Key_M, &m_KeyInfo.Keep.Key_M },
		{ "N", GLFW_KEY_N, &m_KeyInfo.Change.Key_N, &m_KeyInfo.Keep.Key_N },
		{ "O", GLFW_KEY_O , &m_KeyInfo.Change.Key_O, &m_KeyInfo.Keep.Key_O },
		{ "P", GLFW_KEY_P, &m_KeyInfo.Change.Key_P, &m_KeyInfo.Keep.Key_P },
		{ "Q", GLFW_KEY_Q , &m_KeyInfo.Change.Key_Q, &m_KeyInfo.Keep.Key_Q },
		{ "R", GLFW_KEY_R, &m_KeyInfo.Change.Key_R, &m_KeyInfo.Keep.Key_R },
		{ "S", GLFW_KEY_S , &m_KeyInfo.Change.Key_S, &m_KeyInfo.Keep.Key_S },
		{ "T", GLFW_KEY_T, &m_KeyInfo.Change.Key_T, &m_KeyInfo.Keep.Key_T },
		{ "U", GLFW_KEY_U , &m_KeyInfo.Change.Key_U, &m_KeyInfo.Keep.Key_U },
		{ "V", GLFW_KEY_V, &m_KeyInfo.Change.Key_V, &m_KeyInfo.Keep.Key_V },
		{ "W", GLFW_KEY_W , &m_KeyInfo.Change.Key_W, &m_KeyInfo.Keep.Key_W },
		{ "X", GLFW_KEY_X, &m_KeyInfo.Change.Key_X, &m_KeyInfo.Keep.Key_X },
		{ "Y", GLFW_KEY_Y , &m_KeyInfo.Change.Key_Y, &m_KeyInfo.Keep.Key_Y },
		{ "Z", GLFW_KEY_Z, &m_KeyInfo.Change.Key_Z, &m_KeyInfo.Keep.Key_Z },

		//�����A�e���L�[�����i20�j
		{ "0", GLFW_KEY_0, &m_KeyInfo.Change.Key_0, &m_KeyInfo.Keep.Key_0 },
		{ "0", GLFW_KEY_KP_0, &m_KeyInfo.Change.Key_0, &m_KeyInfo.Keep.Key_0 },
		{ "1", GLFW_KEY_1, &m_KeyInfo.Change.Key_1, &m_KeyInfo.Keep.Key_1 },
		{ "1", GLFW_KEY_KP_1, &m_KeyInfo.Change.Key_1, &m_KeyInfo.Keep.Key_1 },
		{ "2", GLFW_KEY_2, &m_KeyInfo.Change.Key_2, &m_KeyInfo.Keep.Key_2 },
		{ "2", GLFW_KEY_KP_2, &m_KeyInfo.Change.Key_2, &m_KeyInfo.Keep.Key_2 },
		{ "3", GLFW_KEY_3, &m_KeyInfo.Change.Key_3, &m_KeyInfo.Keep.Key_3 },
		{ "3", GLFW_KEY_KP_3, &m_KeyInfo.Change.Key_3, &m_KeyInfo.Keep.Key_3 },
		{ "4", GLFW_KEY_4, &m_KeyInfo.Change.Key_4, &m_KeyInfo.Keep.Key_4 },
		{ "4", GLFW_KEY_KP_4, &m_KeyInfo.Change.Key_4, &m_KeyInfo.Keep.Key_4 },
		{ "5", GLFW_KEY_5, &m_KeyInfo.Change.Key_5, &m_KeyInfo.Keep.Key_5 },
		{ "5", GLFW_KEY_KP_5, &m_KeyInfo.Change.Key_5, &m_KeyInfo.Keep.Key_5 },
		{ "6", GLFW_KEY_6, &m_KeyInfo.Change.Key_6, &m_KeyInfo.Keep.Key_6 },
		{ "6", GLFW_KEY_KP_6, &m_KeyInfo.Change.Key_6, &m_KeyInfo.Keep.Key_6 },
		{ "7", GLFW_KEY_7, &m_KeyInfo.Change.Key_7, &m_KeyInfo.Keep.Key_7 },
		{ "7", GLFW_KEY_KP_7, &m_KeyInfo.Change.Key_7, &m_KeyInfo.Keep.Key_7 },
		{ "8", GLFW_KEY_8, &m_KeyInfo.Change.Key_8, &m_KeyInfo.Keep.Key_8 },
		{ "8", GLFW_KEY_KP_8, &m_KeyInfo.Change.Key_8, &m_KeyInfo.Keep.Key_8 },
		{ "9", GLFW_KEY_9, &m_KeyInfo.Change.Key_9, &m_KeyInfo.Keep.Key_9 },
		{ "9", GLFW_KEY_KP_9, &m_KeyInfo.Change.Key_9, &m_KeyInfo.Keep.Key_9 },

		//�L���Ȃ�(16�j
		{ "/", GLFW_KEY_KP_DIVIDE , &m_KeyInfo.Change.Key_DIVIDE, &m_KeyInfo.Keep.Key_DIVIDE },
		{ "*", GLFW_KEY_KP_MULTIPLY, &m_KeyInfo.Change.Key_MULTIPLY, &m_KeyInfo.Keep.Key_MULTIPLY },
		{ "-", GLFW_KEY_KP_SUBTRACT , &m_KeyInfo.Change.Key_SUBTRACT, &m_KeyInfo.Keep.Key_SUBTRACT },
		{ "+", GLFW_KEY_KP_ADD, &m_KeyInfo.Change.Key_ADD, &m_KeyInfo.Keep.Key_ADD },
		{ "Shift", GLFW_KEY_LEFT_SHIFT , &m_KeyInfo.Change.Key_SHIFT, &m_KeyInfo.Keep.Key_SHIFT },
		{ "Shift", GLFW_KEY_RIGHT_SHIFT, &m_KeyInfo.Change.Key_SHIFT, &m_KeyInfo.Keep.Key_SHIFT },
		{ "Ctrl", GLFW_KEY_LEFT_CONTROL, &m_KeyInfo.Change.Key_CONTROL, &m_KeyInfo.Keep.Key_CONTROL },
		{ "Ctrl", GLFW_KEY_RIGHT_CONTROL, &m_KeyInfo.Change.Key_CONTROL, &m_KeyInfo.Keep.Key_CONTROL },
		{ "Alt", GLFW_KEY_LEFT_ALT, &m_KeyInfo.Change.Key_ALT, &m_KeyInfo.Keep.Key_ALT },
		{ "Alt", GLFW_KEY_RIGHT_ALT, &m_KeyInfo.Change.Key_ALT, &m_KeyInfo.Keep.Key_ALT },
		{ " (�X�y�[�X)", GLFW_KEY_SPACE , &m_KeyInfo.Change.Key_SPACE, &m_KeyInfo.Keep.Key_SPACE },
		{ "��", GLFW_KEY_RIGHT, &m_KeyInfo.Change.Key_RIGHT, &m_KeyInfo.Keep.Key_RIGHT },
		{ "��", GLFW_KEY_LEFT, &m_KeyInfo.Change.Key_LEFT, &m_KeyInfo.Keep.Key_LEFT },
		{ "��", GLFW_KEY_DOWN , &m_KeyInfo.Change.Key_DOWN, &m_KeyInfo.Keep.Key_DOWN },
		{ "��", GLFW_KEY_UP, &m_KeyInfo.Change.Key_UP, &m_KeyInfo.Keep.Key_UP },
	};
	
	//�����ꂽ or ������Ώꍇ�̂ݏ��X�V�i���������̎��̓X���[����j
	if (GLFW_PRESS == p_action || GLFW_RELEASE == p_action)
	{
		//�e�L�[�i�L�[�{�[�h�j�̏�񕪃��[�v����
		for (int index = 0; KEY_SUMMARY_MAX > index; index++)
		{
			//�Y������L�[�������
			if (KeySummary[index].KeyDef == p_key)
			{
				//Change�ɂ� �����ꂽ�uGLFW_PRESS�v or �����ꂽ�uGLFW_RELEASE�v �����̂܂܊i�[
				*KeySummary[index].Change = p_action;

				//�����ꂽ�ꍇ
				if (GLFW_PRESS == p_action)
				{
					//Keep�ɂ� �������тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ���
					*KeySummary[index].Keep = !*KeySummary[index].Keep;

					printf("[%s]�L�[��������܂���\n", KeySummary[index].KeyChar);
				}
				break;
			}
		}
	}
}
