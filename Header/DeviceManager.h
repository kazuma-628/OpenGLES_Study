#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

//include��`
#include "Common.h"

//Define��`


/////////////////////////////////////////////
//	�}�E�X�֘A�̍\���̒�`

//�}�E�X�̏ڍ׏��
typedef struct
{
	int State;				//�}�E�X�̃N���b�N��ԁi������Ă���iGLFW_PRESS�j or ������Ă���iGLFW_RELEASE�j�j
	Vec2 ClickDiffPos;		//�}�E�X���N���b�N���ꂽ���W����̍������W�i�N���b�N����Ă��Ȃ����� [0] �j
							//�@��F[x:50][y:50]�ŃN���b�N���āA�h���b�O��Ԃ�[x:40][y:60]�Ɉړ��������ꍇ�A
							//�@�@�@�i�[�����l��[x:-10][y:10]�ƂȂ�
}MouseDetail;

//�}�E�X�̏��
typedef struct
{
	MouseDetail Right;			//�}�E�X�̉E�N���b�N�̏��
	MouseDetail Left;			//�}�E�X�̍��N���b�N�̏��
//	MouseDetail Middle;			//�}�E�X�̒����N���b�N�̏��
	Vec2 Position;				//�}�E�X�̃J�[�\�����W
	Vec2 ScrollAmount;			//�X�N���[���̍��v�ʁA������Ԃ�[x:0�i��[���E]�X�N���[���j][y:0�i�c[�㉺]�X�N���[���j]�ŁA
								//�@�X�N���[�������������l���~�ρi���Z/���Z�j����Ă���
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
	*	�@�ڍׂ͉��L�Q�Ƃ̂���
	*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWmousebuttonfun]�֐�
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
	*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWcursorposfun]�֐�
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
	*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWscrollfun]�֐�
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
	*	�@[http://www.glfw.org/docs/latest/group__input.html]��[GLFWkeyfun]�֐�
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
	*	�@�}�E�X�̏��
	*-------------------------------------------------------------------------------*/
	inline MouseInfo GetMouseInfo(void)
	{
		return m_MouseInfo;
	}

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�L�[�i�L�[�{�[�h�j�̏����擾
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�L�[�i�L�[�{�[�h�j�̏��
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

	GLFWwindow* m_window;			//�E�B���h�E�n���h��
	static MouseInfo m_MouseInfo;	//�}�E�X�̏��
	static KeyInfo m_KeyInfo;		//�L�[�i�L�[�{�[�h�j�̏��
	static Vec2 m_RightClickPos;	//�}�E�X���E�N���b�N���ꂽ���̃J�[�\�����W
	static Vec2 m_LeftClickPos;	//�}�E�X�����N���b�N���ꂽ���̃J�[�\�����W
	static Vec2 m_MiddleClickPos;	//�}�E�X�������N���b�N���ꂽ���̃J�[�\�����W


};

#endif