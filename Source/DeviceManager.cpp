#include "DeviceManager.h"

/////////////////////////////////////////////
//static�ϐ��̎��̂��`

MouseInfo DeviceManager::m_MouseInfo;		//�}�E�X�{�^���̏��	
KeyInfo DeviceManager::m_KeyInfo;			//�L�[�i�L�[�{�[�h�j�̏��
Vec2 DeviceManager::m_RightClickPos;		//�}�E�X���E�N���b�N���ꂽ���̃J�[�\�����W
Vec2 DeviceManager::m_LeftClickPos;			//�}�E�X�����N���b�N���ꂽ���̃J�[�\�����W
Vec2 DeviceManager::m_MiddleClickPos;		//�}�E�X�������N���b�N���ꂽ���̃J�[�\�����W

//�R���X�g���N�^
DeviceManager::DeviceManager()
{
	//������
	m_window = NULL;
	memset(&m_RightClickPos, 0, sizeof(m_RightClickPos));
	memset(&m_LeftClickPos, 0, sizeof(m_LeftClickPos));
	memset(&m_MiddleClickPos, 0, sizeof(m_MiddleClickPos));

	memset(&m_MouseInfo, 0, sizeof(m_MouseInfo));
	memset(&m_KeyInfo, 0, sizeof(m_KeyInfo));
}

//�f�X�g���N�^
DeviceManager::~DeviceManager()
{

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@Key�Ǘ��}�l�[�W���[������������
*	�@/�� �E�B���h�E�𕡐��������āA���ꂼ��Key�Ǘ����邱�Ƃ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::Initialize(GLFWwindow* const p_window)
{
	//�E�B���h�E����ۑ�
	m_window = p_window;

	//�}�E�X�{�^�����ω��������p�̃R�[���o�b�N��o�^
	glfwSetMouseButtonCallback(m_window, DeviceManager::MouseButtonCallback);

	//�}�E�X���W���ω��������p�̃R�[���o�b�N��o�^
	glfwSetCursorPosCallback(p_window, DeviceManager::CursorPosCallback);

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
*	�@�ڍׂ͉��L�Q�Ƃ̂���
*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWmousebuttonfun]�֐�
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
	Vec2 Pos;
	Pos.x = (GLfloat)PosX;
	Pos.y = (GLfloat)PosY;

	//�E�N���b�N�Ɋւ��鏈��
	if (GLFW_MOUSE_BUTTON_RIGHT == p_button)
	{
		//�����ꂽ�ꍇ
		if (GLFW_PRESS == p_action)
		{
			printf("�E�N���b�N��������܂���\n");

			//[StateChange]�ɂ́A�N���b�N����Ă���Ɓutrue�v��ݒ�
			m_MouseInfo.Right.StateChange = true;

			//[StateKeep]�ɂ́A�N���b�N���邽�тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ���
			m_MouseInfo.Right.StateKeep = !m_MouseInfo.Right.StateKeep;

			//[PushCount]�ɂ́A�N���b�N���邽�тɒl�����Z���Ă���
			m_MouseInfo.Right.PushCount++;

			//�����ꂽ���̍��W���L��
			m_RightClickPos.x = Pos.x;
			m_RightClickPos.y = Pos.y;
		}
		//�����ꂽ�ꍇ
		else if (GLFW_RELEASE == p_action)
		{
			//[StateChange]�ɂ́A�N���b�N����Ă��Ȃ��Ɓufalse�v��ݒ�
			m_MouseInfo.Right.StateChange = false;

			//�ێ����Ă������W��������
			memset(&m_MouseInfo.Right.ClickDiffPos, 0, sizeof(m_MouseInfo.Right.ClickDiffPos));
			memset(&m_RightClickPos, 0, sizeof(m_RightClickPos));
		}
	}

	//���N���b�N�Ɋւ��鏈��
	else if (GLFW_MOUSE_BUTTON_LEFT == p_button)
	{
		//�����ꂽ�ꍇ
		if (GLFW_PRESS == p_action)
		{
			printf("���N���b�N��������܂���\n");

			//[StateChange]�ɂ́A�N���b�N����Ă���Ɓutrue�v��ݒ�
			m_MouseInfo.Left.StateChange = true;

			//[StateKeep]�ɂ́A�N���b�N���邽�тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ���
			m_MouseInfo.Left.StateKeep = !m_MouseInfo.Left.StateKeep;

			//[PushCount]�ɂ́A�N���b�N���邽�тɒl�����Z���Ă���
			m_MouseInfo.Left.PushCount++;

			//�����ꂽ���̍��W���L��
			m_LeftClickPos.x = Pos.x;
			m_LeftClickPos.y = Pos.y;
		}
		//�����ꂽ�ꍇ
		else if (GLFW_RELEASE == p_action)
		{
			//[StateChange]�ɂ́A�N���b�N����Ă��Ȃ��Ɓufalse�v��ݒ�
			m_MouseInfo.Left.StateChange = false;

			//�ێ����Ă������W��������
			memset(&m_MouseInfo.Left.ClickDiffPos, 0, sizeof(m_MouseInfo.Left.ClickDiffPos));
			memset(&m_LeftClickPos, 0, sizeof(m_LeftClickPos));
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
*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWcursorposfun]�֐�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos)
{
	//���W�p�̕ϐ��錾
	//�@�R�[���o�b�N�pAPI�̈�����[double]�ׁ̈A���ʂ����d���Ȃ����̂悤�ȋ��n�������Ă���
	//�@�i���̂悤�ɂ��Ȃ��ƁA�R���p�C���Ń��[�j���O���o��̂Łj
	Vec2 Pos;
	Pos.x = (GLfloat)p_xpos;
	Pos.y = (GLfloat)p_ypos;

	//���W���R�s�[���ĕۑ�
	m_MouseInfo.Position = Pos;

	//�E�N���b�N��������Ă���ꍇ
	if (true == m_MouseInfo.Right.StateChange)
	{
		//�N���b�N���ꂽ������̍������X�V
		m_MouseInfo.Right.ClickDiffPos.x = Pos.x - m_RightClickPos.x;
		m_MouseInfo.Right.ClickDiffPos.y = Pos.y - m_RightClickPos.y;
	}

	//���N���b�N��������Ă���ꍇ
	if (true == m_MouseInfo.Left.StateChange)
	{
		//�N���b�N���ꂽ������̍������X�V
		m_MouseInfo.Left.ClickDiffPos.x = Pos.x - m_LeftClickPos.x;
		m_MouseInfo.Left.ClickDiffPos.y = Pos.y - m_LeftClickPos.y;
	}

	/////////////////////////////////////////////
	//	�f�o�b�O�p

	//	printf("Right.ClickDiffPos.x = %f, Right.ClickDiffPos.y = %f\n", m_MouseInfo.Right.ClickDiffPos.x, m_MouseInfo.Right.ClickDiffPos.y);
	//	printf("Left.ClickDiffPos.x = %f, Left.ClickDiffPos.y = %f\n", m_MouseInfo.Left.ClickDiffPos.x, m_MouseInfo.Left.ClickDiffPos.y);
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�}�E�X�z�C�[�����ω��������ɃR�[���o�b�N�����֐�
*	����
*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
*	�@p_xoffset	�F[I/ ]�@�X�N���[����X���I�t�Z�b�g
*	�@p_yoffset	�F[I/ ]�@�X�N���[����Y���I�t�Z�b�g
*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWscrollfun]�֐�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset)
{

	//�ЂƂ܂��X�N���[���㉺�����g��Ȃ��\��Ȃ̂Łup_yoffset�v�̂ݎ擾
	m_MouseInfo.ScrollAmount.y += (GLfloat)p_yoffset;

	/////////////////////////////////////////////
	//	�f�o�b�O�p

//	printf("p_yoffset = %f\n", m_MouseInfo.ScrollAmount.y);
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
*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWkeyfun]�֐�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void DeviceManager::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{

	//�L�[�̏��Ɗi�[����ϐ����܂Ƃ߂ĊǗ�����
	KeyInfoSummary KeySummary[] =
	{
		//�A���t�@�x�b�g�i26�j
		{ "A", GLFW_KEY_A, &m_KeyInfo.StateChange.Key_A, &m_KeyInfo.StateKeep.Key_A, &m_KeyInfo.PushCount.Key_A },
		{ "B", GLFW_KEY_B, &m_KeyInfo.StateChange.Key_B, &m_KeyInfo.StateKeep.Key_B, &m_KeyInfo.PushCount.Key_B },
		{ "C", GLFW_KEY_C, &m_KeyInfo.StateChange.Key_C, &m_KeyInfo.StateKeep.Key_C, &m_KeyInfo.PushCount.Key_C },
		{ "D", GLFW_KEY_D, &m_KeyInfo.StateChange.Key_D, &m_KeyInfo.StateKeep.Key_D, &m_KeyInfo.PushCount.Key_D },
		{ "E", GLFW_KEY_E, &m_KeyInfo.StateChange.Key_E, &m_KeyInfo.StateKeep.Key_E, &m_KeyInfo.PushCount.Key_E },
		{ "F", GLFW_KEY_F, &m_KeyInfo.StateChange.Key_F, &m_KeyInfo.StateKeep.Key_F, &m_KeyInfo.PushCount.Key_F },
		{ "G", GLFW_KEY_G, &m_KeyInfo.StateChange.Key_G, &m_KeyInfo.StateKeep.Key_G, &m_KeyInfo.PushCount.Key_G },
		{ "H", GLFW_KEY_H, &m_KeyInfo.StateChange.Key_H, &m_KeyInfo.StateKeep.Key_H, &m_KeyInfo.PushCount.Key_H },
		{ "I", GLFW_KEY_I, &m_KeyInfo.StateChange.Key_I, &m_KeyInfo.StateKeep.Key_I, &m_KeyInfo.PushCount.Key_I },
		{ "J", GLFW_KEY_J, &m_KeyInfo.StateChange.Key_J, &m_KeyInfo.StateKeep.Key_J, &m_KeyInfo.PushCount.Key_J },
		{ "K", GLFW_KEY_K, &m_KeyInfo.StateChange.Key_K, &m_KeyInfo.StateKeep.Key_K, &m_KeyInfo.PushCount.Key_K },
		{ "L", GLFW_KEY_L, &m_KeyInfo.StateChange.Key_L, &m_KeyInfo.StateKeep.Key_L, &m_KeyInfo.PushCount.Key_L },
		{ "M", GLFW_KEY_M, &m_KeyInfo.StateChange.Key_M, &m_KeyInfo.StateKeep.Key_M, &m_KeyInfo.PushCount.Key_M },
		{ "N", GLFW_KEY_N, &m_KeyInfo.StateChange.Key_N, &m_KeyInfo.StateKeep.Key_N, &m_KeyInfo.PushCount.Key_N },
		{ "O", GLFW_KEY_O, &m_KeyInfo.StateChange.Key_O, &m_KeyInfo.StateKeep.Key_O, &m_KeyInfo.PushCount.Key_O },
		{ "P", GLFW_KEY_P, &m_KeyInfo.StateChange.Key_P, &m_KeyInfo.StateKeep.Key_P, &m_KeyInfo.PushCount.Key_P },
		{ "Q", GLFW_KEY_Q, &m_KeyInfo.StateChange.Key_Q, &m_KeyInfo.StateKeep.Key_Q, &m_KeyInfo.PushCount.Key_Q },
		{ "R", GLFW_KEY_R, &m_KeyInfo.StateChange.Key_R, &m_KeyInfo.StateKeep.Key_R, &m_KeyInfo.PushCount.Key_R },
		{ "S", GLFW_KEY_S, &m_KeyInfo.StateChange.Key_S, &m_KeyInfo.StateKeep.Key_S, &m_KeyInfo.PushCount.Key_S },
		{ "T", GLFW_KEY_T, &m_KeyInfo.StateChange.Key_T, &m_KeyInfo.StateKeep.Key_T, &m_KeyInfo.PushCount.Key_T },
		{ "U", GLFW_KEY_U, &m_KeyInfo.StateChange.Key_U, &m_KeyInfo.StateKeep.Key_U, &m_KeyInfo.PushCount.Key_U },
		{ "V", GLFW_KEY_V, &m_KeyInfo.StateChange.Key_V, &m_KeyInfo.StateKeep.Key_V, &m_KeyInfo.PushCount.Key_V },
		{ "W", GLFW_KEY_W, &m_KeyInfo.StateChange.Key_W, &m_KeyInfo.StateKeep.Key_W, &m_KeyInfo.PushCount.Key_W },
		{ "X", GLFW_KEY_X, &m_KeyInfo.StateChange.Key_X, &m_KeyInfo.StateKeep.Key_X, &m_KeyInfo.PushCount.Key_X },
		{ "Y", GLFW_KEY_Y, &m_KeyInfo.StateChange.Key_Y, &m_KeyInfo.StateKeep.Key_Y, &m_KeyInfo.PushCount.Key_Y },
		{ "Z", GLFW_KEY_Z, &m_KeyInfo.StateChange.Key_Z, &m_KeyInfo.StateKeep.Key_Z, &m_KeyInfo.PushCount.Key_Z },

		//�����A�e���L�[�����i20�j
		{ "0", GLFW_KEY_0,    &m_KeyInfo.StateChange.Key_0, &m_KeyInfo.StateKeep.Key_0, &m_KeyInfo.PushCount.Key_0 },
		{ "0", GLFW_KEY_KP_0, &m_KeyInfo.StateChange.Key_0, &m_KeyInfo.StateKeep.Key_0, &m_KeyInfo.PushCount.Key_0 },
		{ "1", GLFW_KEY_1,    &m_KeyInfo.StateChange.Key_1, &m_KeyInfo.StateKeep.Key_1, &m_KeyInfo.PushCount.Key_1 },
		{ "1", GLFW_KEY_KP_1, &m_KeyInfo.StateChange.Key_1, &m_KeyInfo.StateKeep.Key_1, &m_KeyInfo.PushCount.Key_1 },
		{ "2", GLFW_KEY_2,    &m_KeyInfo.StateChange.Key_2, &m_KeyInfo.StateKeep.Key_2, &m_KeyInfo.PushCount.Key_2 },
		{ "2", GLFW_KEY_KP_2, &m_KeyInfo.StateChange.Key_2, &m_KeyInfo.StateKeep.Key_2, &m_KeyInfo.PushCount.Key_2 },
		{ "3", GLFW_KEY_3,    &m_KeyInfo.StateChange.Key_3, &m_KeyInfo.StateKeep.Key_3, &m_KeyInfo.PushCount.Key_3 },
		{ "3", GLFW_KEY_KP_3, &m_KeyInfo.StateChange.Key_3, &m_KeyInfo.StateKeep.Key_3, &m_KeyInfo.PushCount.Key_3 },
		{ "4", GLFW_KEY_4,    &m_KeyInfo.StateChange.Key_4, &m_KeyInfo.StateKeep.Key_4, &m_KeyInfo.PushCount.Key_4 },
		{ "4", GLFW_KEY_KP_4, &m_KeyInfo.StateChange.Key_4, &m_KeyInfo.StateKeep.Key_4, &m_KeyInfo.PushCount.Key_4 },
		{ "5", GLFW_KEY_5,    &m_KeyInfo.StateChange.Key_5, &m_KeyInfo.StateKeep.Key_5, &m_KeyInfo.PushCount.Key_5 },
		{ "5", GLFW_KEY_KP_5, &m_KeyInfo.StateChange.Key_5, &m_KeyInfo.StateKeep.Key_5, &m_KeyInfo.PushCount.Key_5 },
		{ "6", GLFW_KEY_6,    &m_KeyInfo.StateChange.Key_6, &m_KeyInfo.StateKeep.Key_6, &m_KeyInfo.PushCount.Key_6 },
		{ "6", GLFW_KEY_KP_6, &m_KeyInfo.StateChange.Key_6, &m_KeyInfo.StateKeep.Key_6, &m_KeyInfo.PushCount.Key_6 },
		{ "7", GLFW_KEY_7,    &m_KeyInfo.StateChange.Key_7, &m_KeyInfo.StateKeep.Key_7, &m_KeyInfo.PushCount.Key_7 },
		{ "7", GLFW_KEY_KP_7, &m_KeyInfo.StateChange.Key_7, &m_KeyInfo.StateKeep.Key_7, &m_KeyInfo.PushCount.Key_7 },
		{ "8", GLFW_KEY_8,    &m_KeyInfo.StateChange.Key_8, &m_KeyInfo.StateKeep.Key_8, &m_KeyInfo.PushCount.Key_8 },
		{ "8", GLFW_KEY_KP_8, &m_KeyInfo.StateChange.Key_8, &m_KeyInfo.StateKeep.Key_8, &m_KeyInfo.PushCount.Key_8 },
		{ "9", GLFW_KEY_9,    &m_KeyInfo.StateChange.Key_9, &m_KeyInfo.StateKeep.Key_9, &m_KeyInfo.PushCount.Key_9 },
		{ "9", GLFW_KEY_KP_9, &m_KeyInfo.StateChange.Key_9, &m_KeyInfo.StateKeep.Key_9, &m_KeyInfo.PushCount.Key_9 },

		//�L���Ȃ�(16�j
		{ "/", GLFW_KEY_KP_DIVIDE,        &m_KeyInfo.StateChange.Key_DIVIDE,   &m_KeyInfo.StateKeep.Key_DIVIDE,   &m_KeyInfo.PushCount.Key_DIVIDE   },
		{ "*", GLFW_KEY_KP_MULTIPLY,      &m_KeyInfo.StateChange.Key_MULTIPLY, &m_KeyInfo.StateKeep.Key_MULTIPLY, &m_KeyInfo.PushCount.Key_MULTIPLY },
		{ "-", GLFW_KEY_KP_SUBTRACT,      &m_KeyInfo.StateChange.Key_SUBTRACT, &m_KeyInfo.StateKeep.Key_SUBTRACT, &m_KeyInfo.PushCount.Key_SUBTRACT },
		{ "+", GLFW_KEY_KP_ADD,           &m_KeyInfo.StateChange.Key_ADD,      &m_KeyInfo.StateKeep.Key_ADD,      &m_KeyInfo.PushCount.Key_ADD      },
		{ "Shift", GLFW_KEY_LEFT_SHIFT,   &m_KeyInfo.StateChange.Key_SHIFT,    &m_KeyInfo.StateKeep.Key_SHIFT,    &m_KeyInfo.PushCount.Key_SHIFT    },
		{ "Shift", GLFW_KEY_RIGHT_SHIFT,  &m_KeyInfo.StateChange.Key_SHIFT,    &m_KeyInfo.StateKeep.Key_SHIFT,    &m_KeyInfo.PushCount.Key_SHIFT    },
		{ "Ctrl", GLFW_KEY_LEFT_CONTROL,  &m_KeyInfo.StateChange.Key_CONTROL,  &m_KeyInfo.StateKeep.Key_CONTROL,  &m_KeyInfo.PushCount.Key_CONTROL  },
		{ "Ctrl", GLFW_KEY_RIGHT_CONTROL, &m_KeyInfo.StateChange.Key_CONTROL,  &m_KeyInfo.StateKeep.Key_CONTROL,  &m_KeyInfo.PushCount.Key_CONTROL  },
		{ "Alt", GLFW_KEY_LEFT_ALT,       &m_KeyInfo.StateChange.Key_ALT,      &m_KeyInfo.StateKeep.Key_ALT,      &m_KeyInfo.PushCount.Key_ALT      },
		{ "Alt", GLFW_KEY_RIGHT_ALT,      &m_KeyInfo.StateChange.Key_ALT,      &m_KeyInfo.StateKeep.Key_ALT,      &m_KeyInfo.PushCount.Key_ALT      },
		{ " (�X�y�[�X)", GLFW_KEY_SPACE,  &m_KeyInfo.StateChange.Key_SPACE,    &m_KeyInfo.StateKeep.Key_SPACE,    &m_KeyInfo.PushCount.Key_SPACE    },
		{ "��", GLFW_KEY_RIGHT,           &m_KeyInfo.StateChange.Key_RIGHT,    &m_KeyInfo.StateKeep.Key_RIGHT,    &m_KeyInfo.PushCount.Key_RIGHT    },
		{ "��", GLFW_KEY_LEFT,            &m_KeyInfo.StateChange.Key_LEFT,     &m_KeyInfo.StateKeep.Key_LEFT,     &m_KeyInfo.PushCount.Key_LEFT     },
		{ "��", GLFW_KEY_DOWN,            &m_KeyInfo.StateChange.Key_DOWN,     &m_KeyInfo.StateKeep.Key_DOWN,     &m_KeyInfo.PushCount.Key_DOWN     },
		{ "��", GLFW_KEY_UP,              &m_KeyInfo.StateChange.Key_UP,       &m_KeyInfo.StateKeep.Key_UP,       &m_KeyInfo.PushCount.Key_UP       },
	};
	
	//�����ꂽ or ������Ώꍇ�̂ݏ��X�V�i���������̎��̓X���[����j
	if (GLFW_PRESS == p_action || GLFW_RELEASE == p_action)
	{
		//�e�L�[�i�L�[�{�[�h�j�̏�񕪃��[�v����
		for (int index = 0; (sizeof(KeySummary) / sizeof(KeySummary[0])) > index; index++)
		{
			//�Y������L�[�������
			if (KeySummary[index].KeyDefine == p_key)
			{
				//[StateChange]�ɂ́A������Ă���Ɓutrue�v or ������Ă��Ȃ��Ɓufalse�v��ݒ�
				*KeySummary[index].StateChange = p_action == GLFW_PRESS ? true : false;

				//�����ꂽ�ꍇ
				if (GLFW_PRESS == p_action)
				{
					printf("[%s]�L�[��������܂���\n", KeySummary[index].KeyChar);

					//[StateKeep]�ɂ́A�������тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ���
					*KeySummary[index].StateKeep = !*KeySummary[index].StateKeep;

					//[PushCount]�ɂ́A�������тɒl�����Z���Ă���
					*KeySummary[index].PushCount++;
				}
				break;
			}
		}
	}
}
