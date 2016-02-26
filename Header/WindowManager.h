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
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void CreateNewWindow();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�쐬�����E�B���h�E�n���h�����擾����
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	inline GLFWwindow* const GetWindow()
	{
		return m_window;
	}

private:

	GLFWwindow* m_window;		//���������E�B���h�E�n���h��
};
#endif