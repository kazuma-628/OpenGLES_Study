#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

//include��`
#include "Common.h"

class WindowManager
{

public:
	//�R���X�g���N�^
	WindowManager();

	//�f�X�g���N�^
	~WindowManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�E�B���h�E���쐬����
	*	����
	*	�@p_Width	�F[I/ ]�@�E�B���h�E�̕�
	*	�@p_Height	�F[I/ ]�@�E�B���h�E�̍���
	*	�@p_Title	�F[I/ ]�@�E�B���h�E�̖��O�i�E�B���h�E�����^�X�N�o�[�ɕ\�������j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void CreateNewWindow(const int p_Width, const int p_Height, const char* p_Title);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�쐬�����E�B���h�E�n���h�����擾����
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�E�B���h�E�n���h��
	*-------------------------------------------------------------------------------*/
	inline GLFWwindow* const GetWindow()
	{
		return m_window;
	}

private:

	GLFWwindow* m_window;		//���������E�B���h�E�n���h��
	int m_Width;		//���������E�B���h�E�̕�
	int m_Height;		//���������E�B���h�E�̍���
};
#endif