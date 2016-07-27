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
	bool StateChange;		//�}�E�X���N���b�N����Ă���Ɓutrue�v�A����Ă��Ȃ��Ɓufalse�v�i�N���b�N��ԂŃ`�F���W����j							
	bool StateKeep;			//�}�E�X���N���b�N���邽�тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ��i�N���b�N��Ԃ��L�[�v����j
	int PushCount;			//�}�E�X���������i�N���b�N�����j���v��
							//�@������Ԃ�[0]�ŁA�������i�N���b�N�����j�񐔕��A�l�����Z����Ă���
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
	bool Key_A; bool Key_B; bool Key_C; bool Key_D; bool Key_E; bool Key_F; bool Key_G;
	bool Key_H; bool Key_I; bool Key_J; bool Key_K; bool Key_L; bool Key_M; bool Key_N;
	bool Key_O; bool Key_P; bool Key_Q; bool Key_R; bool Key_S; bool Key_T; bool Key_U;
	bool Key_V; bool Key_W; bool Key_X; bool Key_Y; bool Key_Z;
	bool Key_0; bool Key_1; bool Key_2; bool Key_3; bool Key_4; bool Key_5; bool Key_6;
	bool Key_7; bool Key_8; bool Key_9;
	bool Key_DIVIDE; bool Key_MULTIPLY; bool Key_SUBTRACT; bool Key_ADD;
	bool Key_SHIFT; bool Key_CONTROL; bool Key_ALT; bool Key_SPACE;
	bool Key_RIGHT; bool Key_LEFT; bool Key_DOWN; bool Key_UP;
}KeyState;

//�L�[�i�L�[�{�[�h�j�̏��
typedef struct
{
	KeyState StateChange;		//�L�[��������Ă���Ɓutrue�v�A������Ă���Ɓufalse�v�i�L�[��ԂŃ`�F���W����j
	KeyState StateKeep;			//�L�[���������тɁutrue�v�Ɓufalse�v�����݂ɐ؂�ւ��i�L�[��Ԃ��L�[�v����j
	KeyState PushCount;			//�L�[�����������v��
								//�@������Ԃ�[0]�ŁA�������񐔕��A�l�����Z����Ă���
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
	*	�@p_window	�F[I/ ]�@�E�B���h�E�n���h��
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
		char *KeyChar;			//�L�[�̕�����
		int KeyDefine;			//�L�[�̒�`�l
		bool *StateChange;		//�uKeyInfo�v�́uStateChange�v�����o�Ɠ����i�ڍׂ͍��L�����o�Q�Ƃ̂��Ɓj
		bool *StateKeep;		//�uKeyInfo�v�́uStateKeep�v�����o�Ɠ����i�ڍׂ͍��L�����o�Q�Ƃ̂��Ɓj
		bool *PushCount;		//�uKeyInfo�v�́uPushCount�v�����o�Ɠ����i�ڍׂ͍��L�����o�Q�Ƃ̂��Ɓj
	}KeyInfoSummary;

	GLFWwindow* m_window;			//�E�B���h�E�n���h��
	static MouseInfo m_MouseInfo;	//�}�E�X�̏��
	static KeyInfo m_KeyInfo;		//�L�[�i�L�[�{�[�h�j�̏��
	static Vec2 m_RightClickPos;	//�}�E�X���E�N���b�N���ꂽ���̃J�[�\�����W
	static Vec2 m_LeftClickPos;		//�}�E�X�����N���b�N���ꂽ���̃J�[�\�����W
	static Vec2 m_MiddleClickPos;	//�}�E�X�������N���b�N���ꂽ���̃J�[�\�����W

};

#endif