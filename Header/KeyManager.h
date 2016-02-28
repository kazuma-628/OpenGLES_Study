#ifndef KEYMANAGER_H
#define KEYMANAGER_H

//include��`
#include "Common.h"

/////////////////////////////////////////////
//	�\���̂��`

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

class KeyManager
{

public:
	//�R���X�g���N�^
	KeyManager();

	//�f�X�g���N�^
	~KeyManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Key�Ǘ��}�l�[�W���[������������
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
	*	�@p_button	�F[I/ ]�@�����ꂽ�iGLFW_PRESS�j or �����ꂽ�iGLFW_RELEASE�j
	*	�@p_button	�F[I/ ]�@�悭�킩��Ȃ�
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

private:

	static MouseInfo m_MouseInfo;		//�}�E�X�̏��
	static CursorPos m_OldCursorPos;	//���O�i1�C�x���g�O�j�̃J�[�\�����W
	GLFWwindow* m_window;		//�E�B���h�E�n���h��
};

#endif