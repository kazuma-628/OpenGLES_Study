#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

//include��`
#include "Common.h"

//Define��`
#define KEY_SUMMARY_MAX	62		//�L�[�̏��Ɗi�[����ϐ����܂Ƃ߂ĊǗ�����ő�T�C�Y


/////////////////////////////////////////////
//	�}�E�X�֘A�̍\���̒�`

//�J�[�\���̍��W�n
typedef struct
{
	float x;		//X���W
	float y;		//Y���W
}CursorPos;

//�}�E�X�̏ڍ׏��
typedef struct
{
	int State;				//�}�E�X�̃N���b�N��ԁi������Ă���iGLFW_PRESS�j or ������Ă���iGLFW_RELEASE�j�j
	CursorPos Pos;			//�}�E�X�̃J�[�\�����W�i�}�E�X���N���b�N����Ă��鎞�����X�V����A
							//�@�N���b�N����Ă��Ȃ����͍Ō�̏�񂪕ێ������j
	CursorPos DiffPos;		//���O�i1�C�x���g�O�j�̃J�[�\���ʒu����̍������W�i�}�E�X���N���b�N����Ă��鎞�����X�V�����A����ȊO�� [0]�j
							//�@���O�̃J�[�\���ʒu����ǂꂾ���ړ��������ŁA�}�E�X�𓮂����Ȃ���� [0] ������
	CursorPos ClickPos;		//�}�E�X���N���b�N���ꂽ���̃J�[�\�����W�i�N���b�N����Ă��Ȃ����͍Ō�̏�񂪕ێ������j
	CursorPos ClickDiffPos;	//�}�E�X���N���b�N���ꂽ������̍������W�i�N���b�N����Ă��Ȃ����� [0] �j
}MouseDetailInfo;

//�}�E�X�̏��
typedef struct
{
	MouseDetailInfo Right;		//�}�E�X�̉E�N���b�N�̏��
	MouseDetailInfo Left;		//�}�E�X�̍��N���b�N�̏��
	float Scroll;
}MouseInfo;

/////////////////////////////////////////////
//	�L�[�i�L�[�{�[�h�j�֘A�̍\���̒�`

//�e�L�[�i�L�[�{�[�h�j�̏��
//�e�ϐ��ɕۑ������l�₻�̈Ӗ��́uKeyInfo�v�\���̂̃����o���Q�Ƃ��邱��
typedef struct
{
	int Key_A; int Key_B; int Key_C; int Key_D; int Key_E; int Key_F; int Key_G;
	int Key_H; int Key_I; int Key_J; int Key_K; int Key_L; int Key_M; int Key_N;
	int Key_O; int Key_P; int Key_Q; int Key_R; int Key_S; int Key_T; int Key_U;
	int Key_V; int Key_W; int Key_X; int Key_Y; int Key_Z;
	int Key_0; int Key_1; int Key_2; int Key_3; int Key_4; int Key_5; int Key_6;
	int Key_7; int Key_8; int Key_9;
	int Key_DIVIDE; int Key_MULTIPLY; int Key_SUBTRACT; int Key_ADD;
	int Key_SHIFT; int Key_CONTROL; int Key_ALT; int Key_SPACE;
	int Key_RIGHT; int Key_LEFT; int Key_DOWN; int Key_UP;
}KeyState;

//�L�[�i�L�[�{�[�h�j�̏��
typedef struct
{
	KeyState Change;		//�L�[��������Ă���ƁuGLFW_PRESS�v�A������Ă���ƁuGLFW_RELEASE�v�i�L�[��ԂŃ`�F���W����j
	KeyState Keep;			//�L�[���������тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ��i�L�[��Ԃ��L�[�v����j
}KeyInfo;


/////////////////////////////////////////////
//	�N���X��`

class DeviceManager
{

public:
	//�R���X�g���N�^
	DeviceManager();

	//�f�X�g���N�^
	~DeviceManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Key�Ǘ��}�l�[�W���[������������
	*	�@/�� �E�B���h�E�𕡐��������āA���ꂼ��Key�Ǘ����邱�Ƃ͂܂��Ή����Ă��Ȃ��̂Œ��� ��
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Initialize(GLFWwindow* const p_window);

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
	static void MouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods);

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
	static void CursorPosCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);

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
	static void ScrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�L�[�i�L�[�{�[�h�j���ω��������ɃR�[���o�b�N�����֐�
	*	����
	*	�@p_window		�F[I/ ]�@�E�B���h�E�n���h��
	*	�@p_key			�F[I/ ]�@�L�[�{�[�h�̃L�[
	*	�@p_scancode	�F[I/ ]�@�悭�킩��Ȃ��i�V�X�e���ŗL�̂ǂ����炱������j
	*	�@p_action		�F[I/ ]�@�����ꂽ�iGLFW_PRESS�j or �����ꂽ�iGLFW_RELEASE�j
	*	�@p_mods		�F[I/ ]�@Shift��Ctrl�Ȃǂ�������Ă��邩�̔��f�i��`����URL�Q�Ɓj
	*	�@�ڍׂ͉��LURL�Q�Ƃ̂���
	*	�@http://www.glfw.org/docs/latest/group__input.html#ga592dd1919f8a1dc7576b13cdd8b7b695
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	static void KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�}�E�X�̏����擾
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�E�N���b�N�̏��
	*-------------------------------------------------------------------------------*/
	inline MouseInfo GetMouseInfo(void)
	{
		//�ԋp���邽�߂ɏ����R�s�[����
		//���^�[�������l�̈ꕔ���������������̂�
		MouseInfo tmp_MouseButton = m_MouseInfo;

		//����ԋp�����̂Łu���O�̃J�[�\���ʒu����̍����v��������
		m_MouseInfo.Left.DiffPos.x = 0.0;
		m_MouseInfo.Left.DiffPos.y = 0.0;
		m_MouseInfo.Right.DiffPos.x = 0.0;
		m_MouseInfo.Right.DiffPos.y = 0.0;
		m_MouseInfo.Scroll = 0.0;

		/////////////////////////////////////////////
		//	�f�o�b�O�p
//		printf("tmp_Right.DiffPos.x = %f, tmp_Right.DiffPos.y = %f\n", tmp_MouseButton.Right.DiffPos.x, tmp_MouseButton.Right.DiffPos.y);
//		printf("tmp_Left.DiffPos.x = %f, tmp_Left.DiffPos.y = %f\n", tmp_MouseButton.Left.DiffPos.x, tmp_MouseButton.Left.DiffPos.y);

		return tmp_MouseButton;
	}

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�L�[�i�L�[�{�[�h�j�̏����擾
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�E�N���b�N�̏��
	*-------------------------------------------------------------------------------*/
	inline KeyInfo GetKeyInfo(void)
	{
		return m_KeyInfo;
	}

private:

	//�L�[�����ꌳ�Ǘ����邽�߂̍\����
	typedef struct
	{
		char* KeyChar;		//�L�[�̕�����
		int KeyDef;			//�L�[�̒�`�l
		int *Change;		//�uKeyInfo�v�́uChange�v�����o�Ɠ����i�ڍׂ͍��L�����o�Q�Ƃ̂��Ɓj
		int *Keep;			//�uKeyInfo�v�́uKeep�v�����o�Ɠ����i�ڍׂ͍��L�����o�Q�Ƃ̂��Ɓj
	}KeyInfoSummary;


	static MouseInfo m_MouseInfo;		//�}�E�X�̏��
	static CursorPos m_OldCursorPos;	//���O�i1�C�x���g�O�j�̃J�[�\�����W
	static KeyInfo m_KeyInfo;			//�L�[�i�L�[�{�[�h�j�̏��
	GLFWwindow* m_window;		//�E�B���h�E�n���h��

};

#endif