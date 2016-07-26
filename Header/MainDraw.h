#ifndef MAIN_DRAW_H
#define MAIN_DRAW_H

//include��`
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
#include "Texture.h"

class MainDraw
{

public:
	//�R���X�g���N�^
	MainDraw();

	//�f�X�g���N�^
	~MainDraw();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���C���`��̏���������
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Prepare();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���C���`����J�n����
	*	����
	*	�@p_Global				�F[I/O]�@�O���[�o���f�[�^
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Drawing(GlobalData *p_Global);

private:

	ShaderManager *m_MainShader;		//���C���V�F�[�_�[�I�u�W�F�N�g
	GLint m_attr_pos;					//���_�f�[�^
	GLint m_attr_color;					//�J���[�f�[�^
	GLint m_ProjModel_matrix;			//���W�ϊ��}�g���N�X�i�v���W�F�N�V�����}�g���N�X �~ ���f���r���[�}�g���b�N�X�j
};
#endif